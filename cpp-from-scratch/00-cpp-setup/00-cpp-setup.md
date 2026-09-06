# **C++ Setup**

## **Topics**

- Installing a C++ compiler (GCC on Linux, MSVC/MinGW on Windows) — full steps in `docs/compiler-setup.md`
- Understanding the compile → link → run pipeline
- Compiling a single file: `g++ program.cpp -o program`
- Running the compiled binary: `./program`
- Choosing an editor: VS Code + C/C++ extension, or a full IDE (CLion, Visual Studio)
- Basic CMake project structure (`CMakeLists.txt`, `cmake -B build`, `cmake --build build`)

---

## **Verify setup**

```bash
g++ --version
cmake --version
```

```cpp
// hello.cpp
#include <iostream>

int main() {
    std::cout << "Setup working" << std::endl;
    return 0;
}
```

```bash
g++ hello.cpp -o hello
./hello
```

---

## **Practice**

- Compile and run the hello-world program above
- Modify it to print your name and today's date (hardcoded)
- Create a two-file project (`main.cpp` + `helper.cpp`/`helper.h`) and compile them together:
  `g++ main.cpp helper.cpp -o app`
- Set up a minimal `CMakeLists.txt` for the same two-file project and build it via CMake instead of a direct `g++` call