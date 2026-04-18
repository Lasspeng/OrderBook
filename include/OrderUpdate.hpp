#include <optional>
#include "types.hpp"
#include "order.hpp"

struct OrderUpdate {
  std::optional<Price> price{ };
  std::optional<Volume> remainingVolume{ };

  void updateOrder(Order* existingOrder);
};
