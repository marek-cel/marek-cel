# Rust Hello World

A template Rust project demonstrating best practices, project structure, and common patterns.

## Prerequisites

### Install Rust

```bash
# Linux/macOS
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# Windows: Download and run rustup-init.exe from https://rustup.rs
```

After installation, ensure these components are installed:

```bash
rustup component add clippy      # Linter
rustup component add rustfmt     # Formatter
```

### VSCode Extensions

Open this project in VSCode and accept the recommended extensions prompt, or install manually:

1. **rust-analyzer** (essential) - Language server, autocomplete, go-to-definition
2. **CodeLLDB** - Debugging support (Linux/macOS) or **C/C++** for Windows
3. **Even Better TOML** - Cargo.toml syntax highlighting
4. **crates** - Manage dependencies in Cargo.toml
5. **Error Lens** - Inline error display

## Project Structure

```
rust_hello_world/
├── Cargo.toml          # Project manifest (like CMakeLists.txt + conanfile.txt)
├── Cargo.lock          # Locked dependency versions (committed for binaries)
├── rustfmt.toml        # Code formatter config
├── clippy.toml         # Linter config
├── src/
│   ├── main.rs         # Binary entry point
│   └── lib.rs          # Library code (optional)
├── tests/
│   └── integration_tests.rs  # Integration tests
├── examples/
│   └── basic_usage.rs  # Example programs
├── benches/            # Benchmarks (empty for now)
└── .vscode/
    ├── settings.json   # Editor settings
    ├── launch.json     # Debug configurations
    ├── tasks.json      # Build tasks
    └── extensions.json # Recommended extensions
```

## Common Commands

| Command | Description | C++/CMake Equivalent |
|---------|-------------|---------------------|
| `cargo build` | Debug build | `cmake --build . --config Debug` |
| `cargo build --release` | Release build | `cmake --build . --config Release` |
| `cargo run` | Build and run | Build + execute |
| `cargo test` | Run all tests | `ctest` |
| `cargo clippy` | Run linter | clang-tidy |
| `cargo fmt` | Format code | clang-format |
| `cargo doc --open` | Generate docs | Doxygen |
| `cargo clean` | Remove build artifacts | `rm -rf build/` |
| `cargo add <crate>` | Add dependency | Add to conanfile |
| `cargo update` | Update dependencies | `conan install --update` |

## Quick Start

```bash
# Build and run
cargo run

# Run tests
cargo test

# Run with release optimizations
cargo run --release

# Run example
cargo run --example basic_usage

# Check code without building (faster)
cargo check

# Run linter
cargo clippy

# Format code
cargo fmt
```

## Key Differences from C++

| Concept | C++ | Rust |
|---------|-----|------|
| Null safety | `nullptr` / `std::optional` | `Option<T>` (enforced) |
| Error handling | Exceptions / error codes | `Result<T, E>` |
| Memory management | RAII / smart pointers | Ownership + Borrow checker |
| Immutability | `const` keyword | Immutable by default |
| Build system | CMake / Make | Cargo (built-in) |
| Package manager | Conan / vcpkg | Cargo (built-in) |
| Namespaces | `namespace` | `mod` (modules) |
| Header files | `.h` / `.hpp` | None needed |
| Generics | Templates | Generics with traits |
| Inheritance | Classes | Traits (composition) |

## Learning Resources

- [The Rust Book](https://doc.rust-lang.org/book/) - Start here
- [Rust by Example](https://doc.rust-lang.org/rust-by-example/) - Learn by doing
- [Rustlings](https://github.com/rust-lang/rustlings) - Small exercises
- [Rust for C++ Developers](https://google.github.io/comprehensive-rust/) - Google's course

## License

MIT
