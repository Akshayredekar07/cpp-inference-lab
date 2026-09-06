# **Compiler ↔ CUDA Compatibility**

**Scope:** Making sure your host compiler (GCC/MSVC) is a version `nvcc` actually accepts. This breaks silently if skipped — `nvcc` rejects unsupported compiler versions with a build error, not a warning.

---

## **The problem**

Each CUDA Toolkit release supports only a specific range of host compiler versions. Your system's default GCC (installed via `apt`) or Visual Studio toolset is often newer than what your CUDA version supports.

**Always check the official table before installing:**
[docs.nvidia.com/cuda/cuda-installation-guide-linux](https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html#system-requirements) (Linux)
[docs.nvidia.com/cuda/cuda-installation-guide-microsoft-windows](https://docs.nvidia.com/cuda/cuda-installation-guide-microsoft-windows/index.html) (Windows)

---

## **Linux — pinning a compatible GCC**

Install a second, older GCC alongside your default:
```bash
sudo apt install gcc-12 g++-12
```

Point `nvcc` at it explicitly (don't rely on the system default):
```bash
nvcc --compiler-bindir=/usr/bin/g++-12 -o out file.cu
```

Or set it project-wide via CMake:
```cmake
set(CMAKE_CUDA_HOST_COMPILER /usr/bin/g++-12)
```

**Manage multiple versions with `update-alternatives` if switching often:**
```bash
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100
sudo update-alternatives --config gcc
```

---

## **Windows — pinning a compatible MSVC toolset**

Visual Studio can hold multiple toolset versions side by side.

1. Open **Visual Studio Installer** → your VS install → **Modify**.
2. Go to **Individual Components** tab.
3. Under "Compilers, build tools, and runtimes," check the specific **MSVC v14.3x build tools** version your CUDA release supports (not just the newest one).

Verify which toolset is active:
```powershell
cl
```
(version string in the output corresponds to a specific MSVC toolset)

Point CUDA at a specific toolset via environment or CMake if multiple are installed:
```cmake
set(CMAKE_GENERATOR_TOOLSET "v143,version=14.38")
```

---

## **Quick sanity check (either OS)**

```bash
nvcc -o test test.cu
```
If this fails with an "unsupported compiler" error, the fix is always the same: install an older compiler version alongside the current one, and point `nvcc`/CMake at it — don't downgrade your system's default compiler.

---

## **Rule of thumb**

Don't assume the latest compiler works with the latest CUDA. Check the compatibility table for your **exact** CUDA point release before installing anything — this is the single most common CUDA setup failure.