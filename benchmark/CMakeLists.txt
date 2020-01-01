find_package(benchmark REQUIRED)

add_executable(pl0-benchmark benchmark.cpp)
target_link_libraries(pl0-benchmark PRIVATE pl0 benchmark::benchmark)
