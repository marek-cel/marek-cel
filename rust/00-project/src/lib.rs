//! # Rust Hello World Library
//!
//! This module provides reusable functionality that can be used
//! by the binary or as a library by other projects.

/// A module demonstrating Rust's module system.
///
/// Similar to namespaces in C++, but with explicit visibility control.
pub mod utils {
    /// Adds two numbers together.
    ///
    /// # Arguments
    ///
    /// * `a` - First number
    /// * `b` - Second number
    ///
    /// # Examples
    ///
    /// ```
    /// use rust_hello_world::utils::add;
    /// assert_eq!(add(2, 3), 5);
    /// ```
    pub fn add(a: i32, b: i32) -> i32 {
        a + b
    }

    /// Demonstrates Option type (Rust's null-safe alternative).
    ///
    /// Similar to std::optional in C++17, but enforced at compile time.
    pub fn safe_divide(numerator: f64, denominator: f64) -> Option<f64> {
        if denominator == 0.0 {
            None
        } else {
            Some(numerator / denominator)
        }
    }

    /// Demonstrates Result type for error handling.
    ///
    /// Rust doesn't have exceptions - errors are values!
    pub fn parse_number(input: &str) -> Result<i32, std::num::ParseIntError> {
        input.trim().parse()
    }
}

/// Demonstrates struct definition (similar to C++ struct/class).
#[derive(Debug, Clone, PartialEq)]
pub struct Point {
    pub x: f64,
    pub y: f64,
}

impl Point {
    /// Creates a new Point (constructor pattern).
    pub fn new(x: f64, y: f64) -> Self {
        Self { x, y }
    }

    /// Creates a point at the origin.
    pub fn origin() -> Self {
        Self { x: 0.0, y: 0.0 }
    }

    /// Calculates distance from origin.
    pub fn distance_from_origin(&self) -> f64 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_add() {
        assert_eq!(utils::add(2, 3), 5);
        assert_eq!(utils::add(-1, 1), 0);
    }

    #[test]
    fn test_safe_divide() {
        assert_eq!(utils::safe_divide(10.0, 2.0), Some(5.0));
        assert_eq!(utils::safe_divide(10.0, 0.0), None);
    }

    #[test]
    fn test_parse_number() {
        assert_eq!(utils::parse_number("42"), Ok(42));
        assert!(utils::parse_number("not a number").is_err());
    }

    #[test]
    fn test_point() {
        let p = Point::new(3.0, 4.0);
        assert_eq!(p.distance_from_origin(), 5.0);
    }
}
