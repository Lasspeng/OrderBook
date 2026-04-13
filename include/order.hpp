#pragma once
#include "types.hpp"
#include <memory>

class Order {
private:
  OrderId orderId;
  Side side;
  Price price;
  Volume volume;
  SequenceNum sequenceNum;
  Order* next{ nullptr };
  Order* prev{ nullptr };

public:
  Order() = default;
  Order(OrderId orderId, Side side, Price price, Volume volume, Order* next, Order* prev);

  OrderId getOrderId() const;
  Side getSide() const;
  Price getPrice() const;
  Volume getVolume() const;
  SequenceNum getSequenceNum() const;
  Order* getNextOrder() const;
  Order* getPrevOrder() const;

  void setNextOrder(Order* nextOrder);
  void setPrevOrder(Order* prevOrder);

  void fillOrder(Volume fillVolume);
  bool isFilled() const;
};

using OrderOwner = std::unique_ptr<Order>;
