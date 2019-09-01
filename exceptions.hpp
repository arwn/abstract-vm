#pragma once

#include <stdexcept>
#include <string>

#define EXCEPTION(name, inherits, ...) \
  class name : public inherits {       \
   public:                             \
    name(__VA_ARGS__);                 \
  };

// it has been done

EXCEPTION(overflow_int8, std::overflow_error);
EXCEPTION(overflow_int16, std::overflow_error);
EXCEPTION(overflow_int32, std::overflow_error);
EXCEPTION(overflow_float, std::overflow_error);
EXCEPTION(overflow_double, std::overflow_error);
EXCEPTION(underflow_int8, std::underflow_error);
EXCEPTION(underflow_int16, std::underflow_error);
EXCEPTION(underflow_int32, std::underflow_error);
EXCEPTION(underflow_float, std::underflow_error);
EXCEPTION(underflow_double, std::underflow_error);
EXCEPTION(division_by_zero, std::domain_error);
EXCEPTION(lexical_error, std::invalid_argument, std::string str);
EXCEPTION(unknown_instruction, std::invalid_argument, std::string str);
EXCEPTION(pop_empty_stack, std::logic_error);
EXCEPTION(assert_fail, std::logic_error);
EXCEPTION(not_enough_stack_element, std::logic_error);
EXCEPTION(cannot_manage, std::domain_error);
