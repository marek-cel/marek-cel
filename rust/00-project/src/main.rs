//! # Rust Hello World
//!
//! A simple Hello World application demonstrating Rust basics.

/// The main entry point of the application.
///
/// # Examples
///
/// Run with: `cargo run`
fn main() {
    println!("Hello, World!");

    // Demonstrate some Rust basics for a C++ developer
    let greeting = greet("Rustacean");
    println!("{greeting}");

    // Variables are immutable by default (like const in C++)
    let immutable_value = 42;
    println!("Immutable: {immutable_value}");

    // Use `mut` for mutable variables
    let mut counter = 0;
    counter += 1;
    println!("Counter: {counter}");

    // Type inference works, but you can be explicit
    let explicit_type: i32 = 100;
    println!("Explicit i32: {explicit_type}");
}

/// Creates a personalized greeting.
///
/// # Arguments
///
/// * `name` - A string slice containing the name to greet
///
/// # Returns
///
/// A `String` containing the greeting message
///
/// # Examples
///
/// ```
/// let greeting = greet("World");
/// assert_eq!(greeting, "Hello, World! Welcome to Rust.");
/// ```
fn greet(name: &str) -> String {
    format!("Hello, {name}! Welcome to Rust.")
}

// Unit tests - run with `cargo test`
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_greet() {
        let result = greet("Test");
        assert_eq!(result, "Hello, Test! Welcome to Rust.");
    }

    #[test]
    fn test_greet_empty() {
        let result = greet("");
        assert_eq!(result, "Hello, ! Welcome to Rust.");
    }
}
