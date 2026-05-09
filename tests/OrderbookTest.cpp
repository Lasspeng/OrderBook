#include <gtest/gtest.h>
#include "Orderbook.hpp"

TEST(OrderbookTest, AddBidAndAskOrders) {
  Orderbook orderbook{ };
  orderbook.addOrder(std::make_unique<Order>(1, Side::Bid, 100, 10, nullptr, nullptr));

  EXPECT_EQ(orderbook.getSize(), 1);
}
