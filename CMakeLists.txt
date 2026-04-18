cmake_minimum_required(VERSION 3.23)

project(Orderbook)

set(CMAKE_CXX_STANDARD 23)

add_executable(Orderbook
  src/main.cpp
  src/Order.cpp
  src/Orderbook.cpp
  src/OrderUpdate.cpp
  src/PriceLevel.cpp
  src/Trade.cpp
)

target_include_directories(Orderbook PRIVATE include)
