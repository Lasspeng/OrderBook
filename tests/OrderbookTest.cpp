#include <gtest/gtest.h>
#include "Orderbook.hpp"

class OrderbookTest : public ::testing::Test {
protected:
  Orderbook orderbook;

  OrderOwner createOrder(OrderId orderId, Side side,
                         Price price, Volume volume)
  {
    return std::make_unique<Order>(
      orderId,
      side,
      price,
      volume,
      nullptr,
      nullptr);
  }

  Trades addBid(OrderId orderId, Price price, Volume volume) {
    return orderbook.addOrder(createOrder(orderId, Side::Bid, price, volume));
  }

  Trades addAsk(OrderId orderId, Price price, Volume volume) {
    return orderbook.addOrder(createOrder(orderId, Side::Ask, price, volume));
  }
};

TEST_F(OrderbookTest, AddBidAndAskOrders) {
  addBid(1, 100, 10);
  EXPECT_EQ(orderbook.getSize(), 1);
  EXPECT_EQ(orderbook.bestBid()->getPrice(), 100);

  addAsk(2, 110, 10);
  EXPECT_EQ(orderbook.getSize(), 2);
  EXPECT_EQ(orderbook.bestAsk()->getPrice(), 110);
}

TEST_F(OrderbookTest, FullyMatchOrders) {
  addBid(1, 100, 10);
  Trades matchedOrders{ addAsk(2,100, 10) };

  EXPECT_EQ(orderbook.getSize(), 0);
  EXPECT_EQ(matchedOrders.size(), 1);

}

TEST_F(OrderbookTest, PartiallyMatchOrders) {
  addBid(1, 100, 5);
  Trades matchedOrders{ addAsk(2, 100, 10) };

  EXPECT_EQ(orderbook.getSize(), 1);
  EXPECT_EQ(matchedOrders.size(), 1);
}

TEST_F(OrderbookTest, CancelOrders) {
  addBid(1, 100, 10);

  OrderUpdate orderUpdate{ };
  orderUpdate.price = 70;
  orderUpdate.remainingVolume = 5;

  orderbook.modifyOrder(1, orderUpdate);

  EXPECT_EQ(orderbook.bestBid()->getPrice(), 70);
  EXPECT_EQ(orderbook.bestBid()->getRemainingVolume(), 5);

  addAsk(2, 110, 10);

  OrderUpdate orderUpdate2{ };
  orderUpdate2.price = 85;
  orderUpdate2.remainingVolume = 3;

  orderbook.modifyOrder(2, orderUpdate2);

  EXPECT_EQ(orderbook.bestAsk()->getPrice(), 85);
  EXPECT_EQ(orderbook.bestAsk()->getRemainingVolume(), 3);
}
