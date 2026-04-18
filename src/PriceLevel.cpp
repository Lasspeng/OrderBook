#include "../include/PriceLevel.hpp"

PriceLevel::PriceLevel(Price price)
    : price{ price }
    , totalVolume{ 0 }
    , orderCount{ 0 }
    , head{ nullptr }
    , tail{ nullptr }
    { }

Price PriceLevel::getPrice() const { return price; }
Volume PriceLevel::getTotalVolume() const { return totalVolume; }
std::size_t PriceLevel::getOrderCount() const { return orderCount; }
Order* PriceLevel::getHead() const { return head; }
Order* PriceLevel::getTail() const { return tail; }
bool PriceLevel::isEmpty() const { return head == nullptr; }

void PriceLevel::removeActiveOrder(Order* order) {
  Order* prev{ order->getPrevOrder() };
  Order* next{ order->getNextOrder() };

  if (order == head)
    head = order->getNextOrder();
  else
    prev->setNextOrder(next);

  if (order == tail)
    tail->setNextOrder(nullptr);
  else
    next->setPrevOrder(prev);

  order->setNextOrder(nullptr);
  order->setPrevOrder(nullptr);

  totalVolume -= order->getInitialVolume();
  --orderCount;
}

void PriceLevel::addOrder(Order* order) {
  totalVolume += order->getInitialVolume();
  ++orderCount;

  if (head == nullptr)
    head = order;

  if (tail == nullptr)
    tail = order;
  else {
    tail->setNextOrder(order);
    order->setPrevOrder(tail);
    tail = order;
  }
}
