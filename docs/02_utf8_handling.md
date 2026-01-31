# UTF-8 Handling Strategy

## The Challenge

Arabic text processing presents specific challenges in C++:

1. **Multi-byte Characters**: Arabic characters in UTF-8 are typically 2 bytes. Standard `std::string` indexing (`str[i]`) accesses bytes, not characters.
2. **Encoding consistency**: Input files, source code literals, and terminal output must all agree on encoding.

## Solution

### 1. Storage: UTF-8 (`std::string`)

We store text in standard `std::string` encoded as UTF-8.

- **Pros**: Compatible with standard input/output, file systems, and most libraries. Memory efficient for ASCII metadata.
- **Cons**: Indicies do not correspond to character positions.

### 2. Processing: UTF-32 (`std::u32string`)

When we need to manipulate characters (e.g., getting the 3rd radical, matching templates), we convert to `std::u32string`.

- **Type**: `char32_t` holds a single Unicode code point.
- **Pros**: Fixed width (4 bytes). `str[i]` is exactly the i-th character.
- **Cons**: higher memory usage.

### 3. Conversion Mechanism

We implemented `UnicodeHelper` to bridge these worlds.

```cpp
// Convert to code points for processing
std::u32string u32 = utf8_to_utf32(input_utf8);

// Process... (e.g. u32[2])

// Convert back for display/storage
std::string output = utf32_to_utf8(u32);
```

We use C++ standard `<codecvt>` (specifically `std::codecvt_utf8<char32_t>`) for these conversions. While deprecated in C++17, it remains the most standard "built-in" way to handle this without external dependencies like ICU, which simplifies the build process for this project.

### Compiler Flags

We ensure the compiler treats source files as UTF-8. For MSVC, we added `/utf-8`. On Linux (GCC/Clang), UTF-8 is generally the default, but we ensure our source files are saved as UTF-8.
