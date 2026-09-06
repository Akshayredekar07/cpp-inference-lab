# **Compiler Setup**

**Scope:** Installing and verifying a base C++ compiler on Linux and Windows (no CUDA).

---

## **Linux (Ubuntu/Debian)**

```bash
sudo apt update
sudo apt install build-essential gdb cmake git
```

Verify:
```bash
g++ --version
gdb --version
cmake --version
```

**Compile/run a file:**
```bash
g++ program.cpp -o program -std=c++20
./program
```

---

## **Windows**

### **Option A — MSVC (recommended, matches most industry codebases)**
- Install **Visual Studio 2026** (Community edition) with the **"Desktop development with C++"** workload.
- Includes MSVC compiler, Windows SDK, and the "Developer Command Prompt."

Verify (inside Developer Command Prompt):
```powershell
cl
```

**Compile/run a file:**
```powershell
cl /std:c++20 program.cpp
.\program.exe
```

### **Option B — MinGW-w64 (GCC on Windows, lighter weight)**
- Install via [MSYS2](https://www.msys2.org/):
```powershell
pacman -S mingw-w64-ucrt-x86_64-gcc
```
- Add `C:\msys64\ucrt64\bin` to your PATH.

Verify:
```powershell
g++ --version
```

**Compile/run a file:**
```powershell
g++ program.cpp -o program.exe -std=c++20
.\program.exe
```

---

## **VS Code integration (either OS)**

- Install the **C/C++** extension (Microsoft) and **CMake Tools** extension.
- Point VS Code at your compiler via `.vscode/c_cpp_properties.json` (auto-generated on first build) or a `CMakeLists.txt`.

---

## **Which to pick**

| Situation | Use |
|---|---|
| Following this roadmap generally | GCC (Linux) or MinGW-w64 (Windows) |
| Targeting CUDA/GPU work | See `compiler-cuda-compatibility.md` — compiler version matters here |
| Windows-native production work | MSVC |