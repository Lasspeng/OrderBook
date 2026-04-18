#include "Order.hpp"
#include "Orderbook.hpp"
#include <iostream>
#include <ostream>
#include <print>

int main() {
  Orderbook orderbook{ };
  const OrderId orderId{ 1 };
  orderbook.addOrder(std::make_unique<Order>(orderId, Side::Ask, 100, 10, nullptr, nullptr));
  std::cout << orderbook.getSize() << std::endl;

  OrderUpdate newOrder{ };
  newOrder.price = 75;
  orderbook.modifyOrder(orderId, newOrder);
  std::cout << orderbook.getSize() << std::endl;

  auto order{ orderbook.cancelOrder(orderId) };
  std::string side{ order->getSide() == Side::Bid ? "Bid" : "Ask" };
  std::println("Side: {} Price: {} Initial Volume: {}", side, order->getPrice(), order->getInitialVolume());
  std::cout << orderbook.getSize() << std::endl;
}
