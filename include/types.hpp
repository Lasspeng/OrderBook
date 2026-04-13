#pragma once
#include <cstdint>

enum class Side {
  Bid,
  Ask
};

using Price = std::uint64_t;
using OrderId = std::uint64_t;
using Volume = std::uint32_t;
using SequenceNum = std::uint64_t;
