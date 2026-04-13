#pragma once
#include "../include/order.hpp"
#include <format>
#include <stdexcept>


Order::Order(OrderId orderId, Side side, Price price,
             Volume volume, Order* next, Order* prev)
  : orderId{orderId}
  , side{side}
  , price{price}
  , volume{volume}
  , next{next}
  , prev{prev}
{ }

OrderId Order::getOrderId() const { return orderId; }
Side Order::getSide() const { return side; }
Price Order::getPrice() const { return price; }
Volume Order::getVolume() const { return volume; }
SequenceNum Order::getSequenceNum() const { return sequenceNum; }
Order* Order::getNextOrder() const { return next; }
Order* Order::getPrevOrder() const { return prev; }

void Order::setNextOrder(Order* nextOrder) { next = nextOrder; }
void Order::setPrevOrder(Order* prevOrder) { prev = prevOrder; }

void Order::fillOrder(Volume fillVolume) {
  if (getVolume() < fillVolume) {
    throw std::invalid_argument(std::format("Order number {} cannot be filled for more than its current volume", orderId));
  }
  volume -= fillVolume;
}

bool Order::isFilled() const { return volume == 0; }
