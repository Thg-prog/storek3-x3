#include "stack.cpp"
#include <vector>
#include <stack>
#include <time.h>
#include <benchmark/benchmark.h>

static void STD_STACK(benchmark::State& state) {
  std::stack<int> a;
  for (auto _ : state) {
    a.push( 4 );
    a.pop();
  }  
}
// Register the function as a benchmark
BENCHMARK(STD_STACK);

// Define another benchmark
static void MY_STACK(benchmark::State& state) {
  Stack<int> a;
  for (auto _ : state) {
    a.push( 4 );
    a.pop();
  }
}
BENCHMARK(MY_STACK);

BENCHMARK_MAIN();