#pragma once
#include "Types.hpp"
#include <vector>

struct TradeSideInfo {
  OrderId orderId;
  Price price;
  Volume volume;
};

class Trade {
private:
  TradeSideInfo bidInfo;
  TradeSideInfo askInfo;

public:
  Trade(TradeSideInfo bidInfo, TradeSideInfo askInfo);
  TradeSideInfo getBidInfo() const;
  TradeSideInfo getAskInfo() const;
};

using Trades = std::vector<Trade>;
