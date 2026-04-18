#include "OrderUpdate.hpp"

void OrderUpdate::updateOrder(Order* existingOrder) {
  if (price.has_value())
    existingOrder->setPrice(price.value());
  if (remainingVolume.has_value())
    existingOrder->setRemainingVolume(remainingVolume.value());
}
