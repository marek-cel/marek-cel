//! Integration tests for the rust_hello_world library.
//!
//! Files in the `tests/` directory are compiled as separate crates
//! and can only access public APIs - perfect for integration testing.

use rust_hello_world::utils;
use rust_hello_world::Point;

#[test]
fn test_utils_integration() {
    // Test the public API as an external user would
    let result = utils::add(10, 20);
    assert_eq!(result, 30);
}

#[test]
fn test_safe_divide_integration() {
    match utils::safe_divide(100.0, 4.0) {
        Some(result) => assert_eq!(result, 25.0),
        None => panic!("Expected Some, got None"),
    }
}

#[test]
fn test_error_handling_pattern() {
    // Demonstrating idiomatic Rust error handling
    let input = "42";

    // Using match
    match utils::parse_number(input) {
        Ok(num) => assert_eq!(num, 42),
        Err(e) => panic!("Parse failed: {e}"),
    }

    // Using if let
    if let Ok(num) = utils::parse_number(input) {
        assert_eq!(num, 42);
    }

    // Using unwrap_or for defaults
    let num = utils::parse_number("invalid").unwrap_or(0);
    assert_eq!(num, 0);
}

#[test]
fn test_point_api() {
    let origin = Point::origin();
    assert_eq!(origin.x, 0.0);
    assert_eq!(origin.y, 0.0);

    let point = Point::new(5.0, 12.0);
    assert_eq!(point.distance_from_origin(), 13.0);
}
