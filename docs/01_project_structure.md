# Project Structure and Build System

## Directory Organization

We have adopted a standard C++ project layout to ensure scalability and separation of concerns.

```
/
├── src/          # Implementation files (.cpp) - The actual logic
├── include/      # Header files (.h) - Interfaces and declarations
├── tests/        # Unit tests - Verification code
├── data/         # Input datasets - Roots and schemes
├── docs/         # Documentation - Rationale and guides
├── build/        # Build artifacts - Compiled binaries (ignored by git)
└── CMakeLists.txt # Build configuration
```

### Rationale

1. **Separation of Interface and Implementation**: Putting headers in `include/` and logic in `src/` keeps the codebase clean. Users (or other modules) only need to look at headers to understand how to use a component.
2. **Out-of-Source Builds**: The `build/` directory ensures that compilation artifacts (object files, Makefiles, executables) do not pollute the source directories. This makes "cleaning" the project as simple as `rm -rf build`.
3. **Data Separation**: Keeping `data/` separate prevents hardcoding strings in source files and allows for easy swapping of datasets (e.g., testing vs. production).

## Build System: Makefile

We chose **Make** (Makefile) because CMake was not available in the target environment.

1. **Simplicity**: A simple Makefile is sufficient for this project size.
2. **Standard**: Works on almost all Unix-like systems with g++.

### Configuration

Our `Makefile` enforces C++17 standards:

```makefile
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra
```
