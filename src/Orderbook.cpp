#include "Orderbook.hpp"

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

      Volume volumeFilled{ std::min(bid->getRemainingVolume(), ask->getRemainingVolume()) };
      bid->fillOrder(volumeFilled);
      ask->fillOrder(volumeFilled);


      if (bidPriceLevel.isEmpty())
        bids.erase(bidPrice);
      if (askPriceLevel.isEmpty())
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

Trades Orderbook::addOrder(OrderOwner order) {
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

OrderOwner Orderbook::cancelOrder(OrderId orderId) {
  auto orderIter{ orders.find(orderId) };
  if (orderIter == orders.end())
    throw std::logic_error("Tried to cancel an order that does not exist.");

  Order* order{ orderIter->second.get() };
  Price orderPrice{ order->getPrice() };

  if (order->getSide() == Side::Bid) {
    PriceLevel& priceLevel{ bids.at(orderPrice) };
    priceLevel.removeActiveOrder(order);
    if (priceLevel.isEmpty())
      bids.erase(priceLevel.getPrice());

  } else {
    PriceLevel& priceLevel{ asks.at(orderPrice) };
    priceLevel.removeActiveOrder(order);
    if (priceLevel.isEmpty()) 
      asks.erase(priceLevel.getPrice());
  }

  OrderOwner owner{ std::move(orderIter->second) };
  orders.erase(orderId);
  return owner;
}

Trades Orderbook::modifyOrder(OrderId orderId, OrderUpdate& orderUpdate) {
  OrderOwner existingOrder{ cancelOrder(orderId) };
  orderUpdate.updateOrder(existingOrder.get());
  return addOrder(std::move(existingOrder));
}

std::size_t Orderbook::getSize() const { return orders.size(); }
