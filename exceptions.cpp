#include "exceptions.hpp"

overflow_int8::overflow_int8() : std::overflow_error("Int8 overflow") {}
overflow_int16::overflow_int16() : std::overflow_error("Int16 overflow") {}
overflow_int32::overflow_int32() : std::overflow_error("Int32 overflow") {}
overflow_float::overflow_float() : std::overflow_error("Float overflow") {}
overflow_double::overflow_double() : std::overflow_error("Double overflow") {}
underflow_int8::underflow_int8() : std::underflow_error("Int8 underflow") {}
underflow_int16::underflow_int16() : std::underflow_error("Int16 underflow") {}
underflow_int32::underflow_int32() : std::underflow_error("Int32 underflow") {}
underflow_float::underflow_float() : std::underflow_error("Float underflow") {}
underflow_double::underflow_double()
    : std::underflow_error("Double underflow") {}
division_by_zero::division_by_zero() : std::domain_error("Division by zero") {}
lexical_error::lexical_error(std::string str)
    : std::invalid_argument("Invalid line: " + str) {}
unknown_instruction::unknown_instruction(std::string str)
    : std::invalid_argument("Unknown Instruction: " + str) {}
pop_empty_stack::pop_empty_stack() : std::logic_error("Poping empty stack") {}
assert_fail::assert_fail() : std::logic_error("Assert Failed") {}
not_enough_stack_element::not_enough_stack_element()
    : std::logic_error("Less than two stack element") {}
cannot_manage::cannot_manage() : std::domain_error("cannot manage number") {}
