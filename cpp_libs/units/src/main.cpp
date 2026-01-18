#include <iostream>

#include <units.h>

namespace units
{
	namespace traits
	{

		/**
		 * \brief trait to detect if a unit_t has an angle dimension.
		 */
		template<typename T>
		struct has_angle_dimension_t : std::false_type {};

		/**
		 * \brief specialization for unit_t types to detect if they have an angle dimension.
		 */
		template<typename T>
		requires is_unit_t<T>::value
		struct has_angle_dimension_t<T> 
		{
			using base = typename T::unit_type::base_unit_type;
			static constexpr bool value = !std::is_same_v<typename base::radian_ratio, std::ratio<0>>;
		};
	} // namespace traits

	namespace detail {
		
		/**
		 * \brief Metafunction to strip the angle dimension from a unit_t type.
		 */
		template<typename T>
		requires traits::is_unit_t<T>::value
		struct strip_angle_dimension
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

			/**
			 * \brief Function to strip the angle dimension from a unit_t instance.
			 * \param x The unit_t instance to strip.
			 * \return A new unit_t instance without the angle dimension.
			 */
			static constexpr type strip(const T& x) noexcept
			{
				si_type si_value = x;
				return type(si_value());
			}
		};

		template<typename LHS, typename RHS>
		struct need_angle_stripping : std::false_type {};

		template<typename LHS, typename RHS>
		requires (
			traits::is_unit_t<LHS>::value &&
			traits::is_unit_t<RHS>::value &&
			!std::is_same_v<LHS, RHS> &&
			(traits::has_angle_dimension_t<LHS>::value != traits::has_angle_dimension_t<RHS>::value)
		)
		struct need_angle_stripping<LHS, RHS> : std::true_type {};

	} // namespace detail

	template<typename LHS, typename RHS>
	requires (
		units::traits::is_unit_t<LHS>::value
		&&
		units::traits::is_unit_t<RHS>::value
		&&
		units::traits::is_convertible_unit_t<LHS, units::angle::radian_t>::value
	)
	auto operator*(const LHS& lhs, const RHS& rhs) noexcept
	{
		return detail::strip_angle_dimension<LHS>::strip(lhs) * rhs;
	}
}

using namespace units::literals;
using namespace units::math;

int main(int argc, char* argv[])
{
	units::detail::strip_angle_dimension<units::angle::radian_t>::type angle_in_meters = units::detail::strip_angle_dimension<units::angle::radian_t>::strip(3.14_rad);

	auto tangential_velocity = 1.0_rad_per_s * 2.0_m;
	std::cout << "Tangential Velocity: " << tangential_velocity << std::endl;

    return 0;
}