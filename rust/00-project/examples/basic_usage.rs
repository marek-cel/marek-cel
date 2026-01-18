//! Example: Using the library
//!
//! Run with: `cargo run --example basic_usage`

use rust_hello_world::utils;
use rust_hello_world::Point;

fn main() {
    println!("=== Rust Hello World Library Examples ===\n");

    // Using the add function
    let sum = utils::add(5, 7);
    println!("5 + 7 = {sum}");

    // Using Option with pattern matching
    println!("\n--- Safe Division (Option type) ---");
    let numbers = [(10.0, 2.0), (10.0, 0.0)];

    for (a, b) in numbers {
        match utils::safe_divide(a, b) {
            Some(result) => println!("{a} / {b} = {result}"),
            None => println!("{a} / {b} = Cannot divide by zero!"),
        }
    }

    // Using Result with the ? operator pattern
    println!("\n--- Parsing Numbers (Result type) ---");
    let inputs = ["42", "   123  ", "not a number"];

    for input in inputs {
        match utils::parse_number(input) {
            Ok(num) => println!("Parsed '{input}' -> {num}"),
            Err(e) => println!("Failed to parse '{input}': {e}"),
        }
    }

    // Using the Point struct
    println!("\n--- Point struct ---");
    let p1 = Point::origin();
    let p2 = Point::new(3.0, 4.0);

    println!("Origin: ({}, {})", p1.x, p1.y);
    println!("Point: ({}, {})", p2.x, p2.y);
    println!("Distance from origin: {}", p2.distance_from_origin());
}
