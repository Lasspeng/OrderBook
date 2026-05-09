#pragma once
#include "Types.hpp"
#include "Order.hpp"
#include <map>
#include <memory>
#include <unordered_map>
#include "Trade.hpp"
#include "PriceLevel.hpp"
#include "OrderUpdate.hpp"

class Orderbook {
private:
  std::map<Price, PriceLevel, std::greater<Price>> bids{ };
  std::map<Price, PriceLevel, std::less<Price>> asks{ };
  std::unordered_map<OrderId, std::unique_ptr<Order>> orders{ };

  bool canMatch(Side side, Price price) const;
  Trades matchOrders();

public:
  Orderbook() = default;
  
  Trades addOrder(OrderOwner order);
  Trades modifyOrder(OrderId orderId, OrderUpdate& orderUpdate);
  OrderOwner cancelOrder(OrderId orderId);
  std::size_t getSize() const;
};
