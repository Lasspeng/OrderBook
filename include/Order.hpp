#pragma once
#include "Types.hpp"
#include <memory>

class Order {
private:
  OrderId orderId;
  Side side;
  Price price;
  Volume initialVolume;
  Volume remainingVolume;
  SequenceNum sequenceNum;
  Order* next{ nullptr };
  Order* prev{ nullptr };

public:
  Order() = default;
  Order(OrderId orderId, Side side, Price price, Volume volume, Order* next, Order* prev);

  OrderId getOrderId() const;
  Side getSide() const;
  Price getPrice() const;
  Volume getInitialVolume() const;
  Volume getRemainingVolume() const;
  SequenceNum getSequenceNum() const;
  Order* getNextOrder() const;
  Order* getPrevOrder() const;

  void setOrderId(OrderId newOrderId);
  void setSide(Side newSide);
  void setPrice(Price newPrice);
  void setInitialVolume(Volume newInitialVolume);
  void setRemainingVolume(Volume newRemainingVolume);
  void setNextOrder(Order* nextOrder);
  void setPrevOrder(Order* prevOrder);

  void fillOrder(Volume fillVolume);
  bool isFilled() const;
};

using OrderOwner = std::unique_ptr<Order>;
