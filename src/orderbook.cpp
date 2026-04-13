#pragma once
#include "../include/orderbook.hpp"

bool Orderbook::canMatch(Side side, Price price) const {
  if (side == Side::Bid) {
    if (asks.empty()) return false;
    const Price bestAsk{ asks.begin()->first };
    return price >= bestAsk;
  } else {
    if (bids.empty()) return false;
    const Price bestBid{ bids.begin()->first };
    return price >= bestBid;
  }
}

Trades Orderbook::matchOrders() {
  Trades trades;
  trades.reserve(orders.size());

  while (true) {
    if (bids.empty() || asks.empty()) break;
    auto& [bidPrice, bidPriceLevel] = *bids.begin();
    auto& [askPrice, askPriceLevel] = *asks.begin();

    if (bidPrice < askPrice) break;

    while (bids.size() && asks.size()) {
      Order* bid{ bidPriceLevel.getHead() };
      Order* ask{ askPriceLevel.getHead() };

      Volume volumeFilled{ std::min(bid->getVolume(), ask->getVolume()) };
      bid->fillOrder(volumeFilled);
      ask->fillOrder(volumeFilled);


      if (bidPriceLevel.getHead() == nullptr)
        bids.erase(bidPrice);
      if (askPriceLevel.getHead() == nullptr)
        asks.erase(askPrice);

      trades.emplace_back(
        TradeSideInfo{ bid->getOrderId(), bid->getPrice(), volumeFilled },
        TradeSideInfo{ ask->getOrderId(), ask->getPrice(), volumeFilled }
      );

      if (bid->isFilled()) {
        bidPriceLevel.removeActiveOrder(bid);
        orders.erase(bid->getOrderId());
      }
      if (ask->isFilled()) {
        askPriceLevel.removeActiveOrder(ask);
        orders.erase(ask->getOrderId());
      }
    }
  }
  return trades;
}

Trades Orderbook::addOrder(OrderOwner order)
{
  OrderId orderId{ order->getOrderId() };
  Price orderPrice{ order->getPrice() };

  if (orders.contains(orderId))
    return { };

  if (order->getSide() == Side::Bid) {
    if (!bids.contains(orderPrice))
      bids.insert({ orderPrice, PriceLevel{ orderPrice } });
    bids[orderPrice].addOrder(order.get());

  } else {
    if (!asks.contains(orderPrice))
      asks.insert({ orderPrice, PriceLevel{ orderPrice } });
    asks[orderPrice].addOrder(order.get());
  }

  orders.insert({ orderId, std::move(order) });

  return matchOrders();
}
