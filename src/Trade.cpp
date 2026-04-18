#pragma once
#include "Trade.hpp"

Trade::Trade(TradeSideInfo bidInfo, TradeSideInfo askInfo)
        : bidInfo{ bidInfo }
        , askInfo{ askInfo }
{ }

TradeSideInfo Trade::getBidInfo() const { return bidInfo; }
TradeSideInfo Trade::getAskInfo() const { return askInfo; }
