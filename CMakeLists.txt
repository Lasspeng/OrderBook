cmake_minimum_required(VERSION 3.23)
project(Orderbook)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_library(OrderbookLib
  src/Order.cpp
  src/Orderbook.cpp
  src/OrderUpdate.cpp
  src/PriceLevel.cpp
  src/Trade.cpp
)
target_include_directories(OrderbookLib PUBLIC include)

add_executable(Orderbook
  src/main.cpp
)
target_link_libraries(Orderbook PRIVATE OrderbookLib)

enable_testing()
add_executable(OrderbookTest tests/OrderbookTest.cpp)

target_link_libraries(OrderbookTest
  PRIVATE
  OrderbookLib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(OrderbookTest)
