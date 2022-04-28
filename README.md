# MemoryPool
A C++ memory pool implementation, header-only.
Contain two main classes, `MemoryPool` and `MemoryZone`.

### MemoryPool: 
- A pool that used to allocate fixed memory block.
- It's efficient when do plenty allocation and deallocation with a stable memory usage (6-10 times faster than malloc/free), and it's always more efficient than malloc/free.

### MemoryZone: 
- A pool that simulates stack memory allocation used to allocate plenty *temporary* memory.
- Very time efficient (tens to hundreds of times faster than malloc/free), but not support for deallocation, so may waste memory.
