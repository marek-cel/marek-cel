CXX = g++

LIBS = 

LNKFLAGS = 
CXXFLAGS = -Wall -g -O2 -std=c++17

# C++11: c++11 (c++0x)
# C++14: c++14 (c++1y) 
# C++17: c++17 (c++1z)
# C++20: c++20 (c++2a)

SOURCES = \
	src/00_test.cpp \
	src/02_range_for.cpp \
	src/02_switch.cpp \
	src/03_auto.cpp \
	src/03_decltype.cpp \
	src/03_enum_class.cpp \
	src/03_raw_strings.cpp \
	src/03_register.cpp \
	src/03_text_types.cpp \
	src/03_using_typedef.cpp \
	src/04_assign_if.cpp \
	src/04_bit_operators.cpp \
	src/04_comma.cpp \
	src/04_const_cast.cpp \
	src/04_dynamic_cast.cpp \
	src/04_logic_operators.cpp \
	src/04_reinterpret_cast.cpp \
	src/04_static_assert.cpp \
	src/04_static_cast.cpp \
	src/05_std_string.cpp \
	src/06_function_cpp_11.cpp \
	src/06_function_default_arguments.cpp \
	src/06_rvalue_ref.cpp \
	src/07_preprocessor.cpp \
	src/08_arrays.cpp \
	src/11_pointers.cpp \
	src/12_new.cpp \
	src/14_function_pointers.cpp \
	src/16_mutable.cpp \
	src/17_std_string.cpp \
	src/19_noexcept.cpp \
	src/20_local_class.cpp \
	src/20_nested_class.cpp \
	src/21_constexpr_constructor.cpp \
	src/21_default_constructor.cpp \
	src/21_delegating_constructors.cpp \
	src/21_explicit.cpp \
	src/21_initialization_list.cpp \
	src/21_initializer_list.cpp \
	src/21_initializer_list_2.cpp \
	src/22_copy_constructor.cpp \
	src/22_move_constructor.cpp \
	src/23_initialization.cpp \
	src/24_pointer_to_member.cpp \
	src/25_converting_constructor.cpp \
	src/25_convertion_operator.cpp \
	src/26_user_defined_literals.cpp \
	src/27_functor.cpp \
	src/27_move_assign_operator.cpp \
	src/29_bit_fields.cpp \
	src/30_lambda_expression.cpp \
	src/31_final_class.cpp \
	src/31_inheritance.cpp \
	src/32_final_virtual_function.cpp \
	src/32_override.cpp

################################################################################

.SUFFIXES: .cpp

all: bin/06_static_function cppfiles

bin/06_static_function: 
	$(CXX) -c $(INCLUDES) $(CXXFLAGS) src/06_static_function.cpp -o src/06_static_function.o
	$(CXX) -c $(INCLUDES) $(CXXFLAGS) src/06_static_function_ext.cpp -o src/06_static_function_ext.o
	$(CXX) -o bin/06_static_function $(LNKFLAGS) src/06_static_function.o src/06_static_function_ext.o $(LIBS)

cppfiles: $(SOURCES:.cpp=)

.cpp:
	$(CXX) $(INCLUDES) $(CXXFLAGS) $*.cpp -o bin/$(notdir $*) $(LNKFLAGS)

################################################################################

clean:
	@rm -f src/*.o
	@rm -f bin/*
