#include <iostream>

#include <units.h>

namespace units {
	//------------------------------
	// INVERTED UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_AUXILIARY_UNITS)
	UNIT_ADD(inverted, per_meter, per_meter, per_m, compound_unit<inverse<length::meter>>)
#   endif

	// per_second is dimensionally equivalent to hertz, so we alias it
	namespace inverted {
		using per_second = compound_unit<inverse<time::second>>;
		using per_second_t = unit_t<per_second>;
	}

	namespace literals {
		inline constexpr inverted::per_second_t operator""_per_s(long double val) {
			return inverted::per_second_t(static_cast<double>(val));
		}
		inline constexpr inverted::per_second_t operator""_per_s(unsigned long long val) {
			return inverted::per_second_t(static_cast<double>(val));
		}
	}

	//------------------------------
	// ANGULAR ACCELERATION UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_ANGULAR_ACCELERATION_UNITS)
	UNIT_ADD(angular_acceleration, radians_per_second_squared, radians_per_second_squared, rad_per_s_sq, compound_unit<angle::radians, inverse<squared<time::seconds>>>)
	UNIT_ADD(angular_acceleration, degrees_per_second_squared, degrees_per_second_squared, deg_per_s_sq, compound_unit<angle::degrees, inverse<squared<time::seconds>>>)
#   endif

	//------------------------------
	// TYPE TRAITS FOR ANGLE DETECTION
	//------------------------------
	
	namespace traits {
		template<typename T>
		struct has_angle_dimension_t : std::false_type {};

		template<typename T>
		requires is_unit_t<T>::value
		struct has_angle_dimension_t<T> 
		{
			using base = typename T::unit_type::base_unit_type;
			static constexpr bool value = !std::is_same_v<typename base::radian_ratio, std::ratio<0>>;
		};
	}

	namespace aux {

		template<typename T>
		requires traits::is_unit_t<T>::value
		struct strip_angle_t
		{
			using si_base = typename T::unit_type::base_unit_type;
			using si_unit = units::unit<std::ratio<1>, si_base>;
			using si_type = units::unit_t<si_unit, typename T::underlying_type>;

			using stripped_si_base = units::base_unit<
				typename si_base::meter_ratio,
				typename si_base::kilogram_ratio,
				typename si_base::second_ratio,
				std::ratio<0>, // Radian removed
				typename si_base::ampere_ratio,
				typename si_base::kelvin_ratio,
				typename si_base::mole_ratio,
				typename si_base::candela_ratio,
				typename si_base::byte_ratio
			>;
			
			using stripped_si_unit = unit<std::ratio<1>, stripped_si_base>;

			using type = unit_t<stripped_si_unit, typename T::underlying_type>;
		};

	}

	namespace math {

		template<typename LHS, typename RHS>
		requires (
			traits::is_unit_t<LHS>::value &&
			traits::is_unit_t<RHS>::value &&
			traits::has_angle_dimension_t<LHS>::value &&
			!traits::has_angle_dimension_t<RHS>::value
		)
		auto operator*(const LHS& lhs, const RHS& rhs) noexcept
		{
			std::cout << "Stripping angle from LHS" << std::endl;
			return units::aux::strip_angle_t<LHS>::type(lhs()) * rhs;
		}

		template<typename LHS, typename RHS>
		requires (
			traits::is_unit_t<LHS>::value &&
			traits::is_unit_t<RHS>::value &&
			!traits::has_angle_dimension_t<LHS>::value &&
			traits::has_angle_dimension_t<RHS>::value
		)
		auto operator*(const LHS& lhs, const RHS& rhs) noexcept
		{
			return lhs * units::aux::strip_angle_t<RHS>::type(rhs());
		}
	}
}

using namespace units::literals;
using namespace units::math;

int main(int argc, char* argv[])
{
    std::cout << "Hello Units!" << std::endl;

    units::length::meter_t length1 = 5.0_m;
    units::time::second_t time1 = 10.0_s;
    units::velocity::meters_per_second_t velocity1 = length1 / time1;

    std::cout << "Length: " << length1 << std::endl;
    std::cout << "Time: " << time1 << std::endl;
    std::cout << "Velocity: " << velocity1 << std::endl;

    units::inverted::per_meter_t inv_length = 1.0 / length1;
    std::cout << "Inverted Length: " << inv_length << std::endl;

    units::inverted::per_second_t inv_time = 1.0_per_s;
    std::cout << "Inverted Time: " << inv_time << std::endl;

	units::length::meter_t radius = 2.0_m;

	units::angle::radian_t angle_rad = 1.0_rad;
	units::angle::degree_t angle_deg = 90.0_deg;
	units::length::meter_t arc_length_rad = radius * angle_rad;
	units::length::meter_t arc_length_deg = radius * angle_deg;
	std::cout << "Arc Length (rad): " << arc_length_rad << std::endl;
	std::cout << "Arc Length (deg): " << arc_length_deg << std::endl;

	units::angular_velocity::radians_per_second_t ang_vel_rad_per_s = 3.1415_rad / 1.0_s;
	units::angular_velocity::degrees_per_second_t ang_vel_deg_per_s = 180.0_deg / 1.0_s;
	units::velocity::meters_per_second_t tangential_vel_rad_per_s = ang_vel_rad_per_s * radius;
	auto tangential_vel_rad_per_s = ang_vel_rad_per_s * radius;
	units::velocity::meters_per_second_t tangential_vel_deg_per_s = ang_vel_deg_per_s * radius;
	std::cout << "Tangential Velocity (rad/s): " << tangential_vel_rad_per_s << std::endl;
	std::cout << "Tangential Velocity (deg/s): " << tangential_vel_deg_per_s << std::endl;

	units::angular_acceleration::radians_per_second_squared_t ang_acc_rad_per_s_sq = 3.1415_rad / (1.0_s * 1.0_s);
	units::angular_acceleration::degrees_per_second_squared_t ang_acc_deg_per_s_sq = 180.0_deg / (1.0_s * 1.0_s);
	units::acceleration::meters_per_second_squared_t tangential_acc_rad_per_s_sq = ang_acc_rad_per_s_sq * radius;
	units::acceleration::meters_per_second_squared_t tangential_acc_deg_per_s_sq = ang_acc_deg_per_s_sq * radius;
	std::cout << "Tangential Acceleration (rad/s^2): " << tangential_acc_rad_per_s_sq << std::endl;
	std::cout << "Tangential Acceleration (deg/s^2): " << tangential_acc_deg_per_s_sq << std::endl;

    return 0;
}