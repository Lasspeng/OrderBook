#include <cstddef>
#include "Types.hpp"
#include "Order.hpp"


class PriceLevel {
private:
  Price price;
  Volume totalVolume;
  std::size_t orderCount;
  Order* head{ nullptr };
  Order* tail{ nullptr };

public:
  PriceLevel() = default;
  PriceLevel(Price price);

  Price getPrice() const;
  Volume getTotalVolume() const;
  std::size_t getOrderCount() const;
  Order* getHead() const;
  Order* getTail() const;
  bool isEmpty() const;

  void removeActiveOrder(Order* order);
  void addOrder(Order* order);
};
