#include <optional>
#include "Types.hpp"
#include "Order.hpp"

struct OrderUpdate {
  std::optional<Price> price{ };
  std::optional<Volume> remainingVolume{ };

  void updateOrder(Order* existingOrder);
};
