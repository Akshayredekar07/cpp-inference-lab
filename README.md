# **cpp-inference-lab**

<p align="center">
  Structured C++ learning journey — Language Foundations → Systems Programming → CUDA / Inference Engineering
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white"/>
  <img src="https://img.shields.io/badge/Status-In%20Progress-FFB300?style=flat-square"/>
  <img src="https://img.shields.io/badge/Focus-CUDA%20%2F%20Inference-6A1B9A?style=flat-square"/>
</p>

A personal, structured C++ learning repo, built topic by topic with small real projects instead of tutorials. Language foundations first, systems-level projects next, CUDA/inference-engineering depth last — no skipping ahead to kernels before ownership of pointers, RAII, and templates is solid.

C++ here is a means to an end: **inference engineering**. The path runs from core language mechanics through small systems projects (HTTP server, shell, key-value store) into the CUDA/Triton layer used in frameworks like vLLM and FlashInfer.

---

## **Setup**

Full setup instructions live in `docs/`:

| File | Covers |
|---|---|
| `docs/compiler-setup.md` | Installing a base C++ compiler (GCC / MSVC / MinGW) on Linux and Windows |
| `docs/compiler-cuda-compatibility.md` | Matching compiler versions to your CUDA Toolkit version |
| `docs/instructions.md` | How to use this repo, conventions, where things live |
| `docs/style-guide.md` | Formatting rules followed by every notes file |

Quick check after setup:
```bash
g++ --version
cmake --version
nvcc --version   # only if doing CUDA/inference work
```

---

## **Roadmap Overview**

Full topic breakdown lives inside each numbered folder's notes file — not duplicated here.

| Phase | Folder | Focus |
|---|---|---|
| 0 | `00-cpp-setup/` | Toolchain and environment setup |
| 1 | `01-cpp-basics/` | Syntax, types, I/O, preprocessor |
| 2 | `02-control-flow/` | Conditionals, loops, patterns |
| 3 | `03-cpp-functions/` | Functions, overloading, lambdas |
| 4 | `04-arrays-strings/` | Arrays, `std::string`, string algorithms |
| 5 | `05-pointers-refs/` | Pointers, references, smart pointers |
| 6 | `06-oop-basics/` | Classes, inheritance, polymorphism |
| 7 | `07-oper-overload/` | Operator overloading |
| 8 | `08-dynamic-memory/` | `new`/`delete`, RAII, smart pointers |
| 9 | `09-stl-library/` | Containers, iterators, algorithms |
| 10 | `10-cpp-exceptions/` | Exception handling |
| 11 | `11-file-handling/` | File streams, serialization |
| 12 | `12-cpp-templates/` | Generic programming, SFINAE |
| 13 | `13-modern-cpp/` | C++11 through C++20 features |
| 14 | `14-advanced-cpp/` | Multithreading, move semantics, design patterns |
| — | `cpp_inference_roadmap.md` | CUDA / Triton / inference-engineering track (separate phased roadmap) |

**Projects:** `15-projects/` — `mini-http-server`, `mini-shell`, `key-value-store`, `json-parser`, `chat-server`, `grep-clone`, `ls-clone`

---

## **Repo Structure**

```
cpp-roadmap/
├── README.md
├── .gitignore
├── docs/                  # setup guides, conventions
├── resources/             # cheatsheets, diagrams, reference links
├── 00-cpp-setup/ ... 14-advanced-cpp/
└── 15-projects/
```


<p align="center">
  Built by <a href="https://github.com/akshayredekar07">@akshayredekar07</a> — AI Engineer learning C++ for CUDA / inference-engineering infrastructure
</p>