#pragma once
#include "types.hpp"
#include "order.hpp"
#include <map>
#include <memory>
#include <unordered_map>
#include "trade.hpp"
#include "price_level.hpp"

class Orderbook {
private:
  std::map<Price, PriceLevel, std::greater<Price>> bids{ };
  std::map<Price, PriceLevel, std::less<Price>> asks{ };
  std::unordered_map<OrderId, std::unique_ptr<Order>> orders{ };

public:
  Orderbook() = default;
  
  bool canMatch(Side side, Price price) const;
  Trades matchOrders();
  Trades addOrder(OrderOwner order);
};
