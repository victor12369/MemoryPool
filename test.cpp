#include <chrono>
#include <list>
#include <memory>
#include <random>

#include "memory_pool.h"
using namespace rrlib;
template <class TFunc>
uint64_t get_exec_time(TFunc&& func) {
  using namespace std::chrono;
  auto t = high_resolution_clock::now();
  func();
  return duration_cast<nanoseconds>(high_resolution_clock::now() - t).count();
}

uint64_t random() {
  static std::mt19937_64 mt;
  return mt();
}

#define N 10000
#define M 1000
#define X 32
void* ptr[N];
size_t pos[N];

void test_memorypool() {
  MemoryPool mp(X, 1048576);
  for (int x = 0; x < M; x++) {
    for (int i = 0; i < N; i++) {
      ptr[i] = mp.Allocate();
      // memset(ptr[i], 0xFF, 128);
    }
    for (int i = 0; i < N; i++) {
      mp.Free(ptr[pos[i]]);
    }
  }
}
void test_malloc() {
  for (int x = 0; x < M; x++) {
    for (int i = 0; i < N; i++) {
      ptr[i] = malloc(X);
      // memset(ptr[i], 0xFF, 128);
    }
    for (int i = 0; i < N; i++) {
      free(ptr[pos[i]]);
    }
  }
}
void test_zone() {
  for (int x = 0; x < M; x++) {
    MemoryZone mz;
    for (int i = 0; i < N; i++) {
      ptr[i] = mz.Allocate(X);
      // memset(ptr[i], 0xFF, 128);
    }
  }
}
int main() {
  for (size_t i = 0; i < N; i++) pos[i] = i;
  std::shuffle(pos, pos + N, std::mt19937_64{});
  test_memorypool();
  printf("pool  :%gns.\n", get_exec_time(test_memorypool) * 1.0 / N / M);
  test_zone();
  printf("zone  :%gns.\n", get_exec_time(test_zone) * 1.0 / N / M);
  test_malloc();
  printf("malloc:%gns.\n", get_exec_time(test_malloc) * 1.0 / N / M);
  return 0;
}
