# **C++ for Inference Engineering**

**Scope:** C++/CUDA depth for LLM inference engineering (vLLM/SGLang/TRT-LLM/FlashInfer level)

## **Phase 0 − Prerequisites (2-3 days)**

**Checklist before starting Phase 1:**
- Comfortable with pointers/references distinction in C
- Understand stack vs heap allocation
- Can read a Makefile or basic CMakeLists.txt
- Know what a GPU thread/block/grid is conceptually

**If shaky:** K&R C (relevant chapters) + "CUDA by Example" ch.1-2


## **Phase 1 − Modern C++ Core (Weeks 1-4)**

**Goal:** Read/write the C++ subset used in inference engine codebases.

### **Week 1 − Foundations**
- Compilation model: headers vs source, `#include` guards, linking, object files
- Classes: constructors/destructors, `explicit`, initialization lists
- RAII
- References vs pointers vs `const` correctness

**Project 1.1 − RAII resource wrapper**
- `GpuBuffer` class (CPU-only stub, no CUDA)
- Allocates `float*` buffer in constructor, frees in destructor
- Deleted copy constructor/assignment
- Move constructor/assignment
- `main.cpp`: create buffers in a vector, resize, verify no double-free

### **Week 2 − Templates & STL**
- Function templates, class templates
- `std::vector`, `std::unordered_map`, `std::array`
- `std::optional`, `std::variant`
- `auto`, structured bindings, range-based for

**Project 1.2 − Generic tensor shape struct**
- `Shape<N>` template class (compile-time rank), stores dimensions
- `numel()` method (product of dims)
- `operator==`
- Free function `reshape_is_valid(Shape<N> from, Shape<M> to)`

### **Week 3 − Move semantics & smart pointers**
- `std::move`, `std::forward`, rvalue references
- `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`
- Rule of 5 (destructor, copy ctor, copy assign, move ctor, move assign)
- Perfect forwarding in factory functions

**Project 1.3 − Tiny KV-cache allocator (CPU simulation)**
- `unique_ptr<float[]>` backed fixed-size "pages"
- Free-list of page indices
- `allocate_page()` / `free_page(int idx)` methods
- Track fragmentation stats

### **Week 4 − Templates deeper + CRTP**
- SFINAE (recognition level)
- C++20 concepts / `requires` clauses
- CRTP (Curiously Recurring Template Pattern)
- Read one real header from vLLM's `csrc/` − identify templates, RAII, CRTP usage

**Project 1.4 − Checkpoint: mini object pool**
- Generic `ObjectPool<T>` template class
- CRTP-based "poolable" interface
- RAII acquire/release via custom `PoolHandle<T>` wrapper

**Resources:** *Effective Modern C++* (Meyers) − Items 1-7, 8-18, 23-30


## **Phase 2 − CUDA C++ Fundamentals (Weeks 5-8)**

**Goal:** Write correct CUDA kernels; understand memory hierarchy well enough to diagnose slowness.

### **Week 5 − CUDA programming model**
- `__global__`, `__device__`, `__host__` qualifiers
- Grid/block/thread hierarchy, `threadIdx`, `blockIdx`, `blockDim`
- `cudaMalloc`, `cudaMemcpy`, `cudaFree`
- Kernel launch syntax `<<<grid, block>>>`
- Error-checking macros (`cudaGetLastError`)

**Project 2.1 − Vector add**
- Benchmark vs CPU loop at N = 1K, 1M, 100M
- Vary block size (32, 128, 256, 1024), plot effect
- Error-checking macros around every CUDA call

### **Week 6 − Memory hierarchy**
- Global, shared, registers, constant, texture memory
- `__shared__` memory and `__syncthreads()`
- Memory coalescing
- Bank conflicts in shared memory

**Project 2.2 − Naive matmul vs shared-memory tiled matmul**
- Naive CUDA matmul (one thread per output element, global memory reads)
- Shared-memory tiled version (`__shared__` tiles, sync, compute)
- Benchmark at 512x512, 2048x2048, 4096x4096 (expect 3-8x speedup from tiling)

### **Week 7 − Streams, events, async**
- CUDA streams (overlap compute and memory transfer)
- Events for timing/synchronization
- `cudaMemcpyAsync`, pinned host memory
- Multi-stream execution basics

**Project 2.3 − Overlap compute and transfer**
- Split Project 2.2 matmul input into chunks
- 2 streams: overlap `cudaMemcpyAsync` of chunk N+1 with compute of chunk N
- Measure wall-clock improvement vs single-stream version

### **Week 8 − Reductions and warp-level primitives**
- Warp shuffle instructions (`__shfl_down_sync`, etc.)
- Tree-based reduction in shared memory
- Atomic operations (`atomicAdd`) − when to avoid
- Occupancy (`nvcc --ptxas-options=-v`)

**Project 2.4 − Checkpoint: parallel sum reduction (10M floats)**
1. Naive with atomics
2. Shared-memory tree reduction
3. Warp-shuffle based (no `__syncthreads()` within a warp)
- Benchmark all 3

**Resources:** "Programming Massively Parallel Processors" (Kirk & Hwu) ch. 1-6; NVIDIA CUDA C++ Programming Guide (reference)


## **Phase 3 − Reading Production Inference Code (Weeks 9-11)**

**Goal:** Comprehension speed on real kernels, not authorship.

### **Week 9 − Attention kernel anatomy**
- Read FlashAttention paper (algorithm → code mapping)
- Read `vllm/csrc/attention/` (paged attention kernel)
- Identify: KV cache indexing, softmax, online-softmax trick (running max/sum)

**Project 3.1 − Reimplement online softmax**
- Plain CUDA, no attention − just the math
- Input: array of scores; compute running max + running sum in one pass
- Verify numerically against naive two-pass softmax

### **Week 10 − Read FlashInfer + one real PR**
- Read FlashInfer's paged-KV-cache attention kernel (C++/CUDA)
- Pick one closed vLLM PR that touched `csrc/`: read diff + discussion, identify perf problem solved
- Log every unfamiliar C++ idiom, look each up individually

**Project 3.2 − Annotate a real kernel**
- Take one real attention kernel file (vLLM or FlashInfer)
- Line-by-line annotated copy explaining each block
- Scope: one full kernel function, not the whole file

### **Week 11 − CUTLASS / CuTe exposure**
- Skim CUTLASS docs (recognition level)
- Understand "GEMM template" at a high level
- Compare a CuTe DSL (Python) example from FlashAttention 4 side-by-side with the C++ CUTLASS equivalent

**Project 3.3 − Checkpoint: technical summary**
- 1-page write-up: naive attention → FlashAttention (tiling + online softmax) → paged attention (KV cache blocks)


## **Phase 4 − Triton as the Practical Alternative (Weeks 12-14)**

**Goal:** Write the kernels shipped in practice − most inference kernel work is Triton, not raw CUDA C++.

### **Week 12 − Triton basics**
- `tl.program_id`, blocks, `tl.load`/`tl.store`
- Autotuning with `@triton.autotune`
- Direct comparison to CUDA C++ equivalent

**Project 4.1 − Reimplement Project 2.2's matmul in Triton**
- Benchmark against hand-written CUDA version and `torch.matmul`
- Reference point: Triton within 10-20% of hand-tuned CUDA

### **Week 13 − Fused ops**
- Fusion concept: memory bandwidth savings (e.g. RMSNorm+quant, bias+activation)
- Write a fused RMSNorm kernel in Triton

**Project 4.2 − Fused RoPE + RMSNorm kernel**
- Fuse two transformer forward-pass ops into one Triton kernel
- Validate numerical correctness against separate PyTorch ops
- Benchmark fused vs unfused

### **Week 14 − CuTe DSL exposure + decision framework**
- 2-3 official CuTe DSL tutorials
- Revisit decision framework: Triton vs CuTe DSL vs raw CUDA C++

**Project 4.3 − Checkpoint: decision memo**
- 3 hypothetical kernel tasks (e.g. fuse MoE gating, custom quantization kernel, irregular sparse attention)
- One paragraph each justifying tool choice



## **Phase 5 − Integration Project (Weeks 15-18)**

**Goal:** One project touching every layer − Python API, C++/CUDA extension, build system.

**Capstone − Custom PyTorch CUDA extension**
1. Custom fused op not in stock PyTorch (e.g. fused SwiGLU + quantization, custom paged-KV read op)
2. Build via `torch.utils.cpp_extension`
3. Python-callable function backed by CUDA kernel
4. Correctness tests against pure-PyTorch reference
5. Benchmark script vs naive PyTorch equivalent
6. README: memory access pattern + why it's faster (or isn't)

**Stretch goal:** small PR against vLLM or FlashInfer (doc fix or exposed kernel parameter counts)

## **Done criteria**

Without notes, you should be able to:
- Explain RAII and why vLLM's memory manager depends on it
- Read a vLLM/FlashInfer attention kernel file and explain each section
- Write a correct (not necessarily optimal) CUDA kernel for a reduction or elementwise op
- Write the same kernel in Triton and explain the tradeoff
- Justify, for a given kernel task, whether it needs C++/CUDA, Triton, or CuTe DSL

**Out of scope:** PTX, warp specialization, Hopper/Blackwell TMA, occupancy tuning at the SM level (separate roadmap)


## **Time budget**

| Phase | Weeks | Hours/week | Focus |
|---|---|---|---|
| 0 | 0.5 | − | Prereq check |
| 1 | 1-4 | 8-10 | Modern C++ core |
| 2 | 5-8 | 8-10 | CUDA fundamentals |
| 3 | 9-11 | 6-8 | Reading production code |
| 4 | 12-14 | 8-10 | Triton + CuTe DSL |
| 5 | 15-18 | 10-12 | Integration capstone |

**Total: ~18 weeks.**