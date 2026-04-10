#include <cstdint>
#include <cstddef>
#include <map>
#include <unordered_map>

enum class Side
{
  Buy,
  Sell
};

using Price = std::int64_t;
using Volume = std::uint32_t;
using OrderId = std::uint32_t;

struct Order
{
  OrderId orderId;
  Side side;
  Price price;
  Volume volume;

  Order* prev;
  Order* next;
};

struct PriceLevel
{
  Price price;
  Volume totalVolume;
  std::size_t orderCount;

  Order* head;
  Order* tail;
};

std::map<Price, PriceLevel*> bids;
std::map<Price, PriceLevel*> asks;
std::unordered_map<OrderId, Order*> orders;
