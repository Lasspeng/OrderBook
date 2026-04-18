#include "Order.hpp"
#include <format>

Order::Order(OrderId orderId, Side side, Price price,
             Volume initialVolume, Order* next, Order* prev)
  : orderId{ orderId }
  , side{ side }
  , price{ price }
  , initialVolume{ initialVolume }
  , remainingVolume{ initialVolume }
  , next{ next }
  , prev{ prev }
{ }

OrderId Order::getOrderId() const { return orderId; }
Side Order::getSide() const { return side; }
Price Order::getPrice() const { return price; }
Volume Order::getInitialVolume() const { return initialVolume; }
Volume Order::getRemainingVolume() const { return remainingVolume; }
SequenceNum Order::getSequenceNum() const { return sequenceNum; }
Order* Order::getNextOrder() const { return next; }
Order* Order::getPrevOrder() const { return prev; }

void Order::setOrderId(OrderId newOrderId) { orderId = newOrderId; }
void Order::setSide(Side newSide) { side = newSide; }
void Order::setPrice(Price newPrice) { price = newPrice; }
void Order::setInitialVolume(Volume newInitalVolume) { initialVolume = newInitalVolume; }
void Order::setRemainingVolume(Volume newRemainingVolume) { remainingVolume = newRemainingVolume; }
void Order::setNextOrder(Order* nextOrder) { next = nextOrder; }
void Order::setPrevOrder(Order* prevOrder) { prev = prevOrder; }

void Order::fillOrder(Volume fillVolume) {
  if (getRemainingVolume() < fillVolume) {
    throw std::invalid_argument(std::format("Order number {} cannot be filled for more than its current remaining volume", orderId));
  }
  remainingVolume -= fillVolume;
}

bool Order::isFilled() const { return remainingVolume == 0; }
