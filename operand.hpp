#pragma once

#include <string>
#include "exceptions.hpp"

// septype does not need an explanation. come on dude.
enum class septype {
  Error = -1,
  None = 0,
  Space = 1,
  Newline = 2,
  Comment = 3
};

// optype represents an operator class
enum class optype {
  Error = -1,
  None = 0,
  Int8 = 4,
  Int16 = 5,
  Int32 = 6,
  Float = 7,
  Double = 8
};

// commandtype is an asvm command
enum class commandtype {
  Error = -1,
  None = 0,
  Exit = 16,
  Push = 17,
  Pop = 18,
  Dump = 19,
  Assert = 20,
  Add = 21,
  Sub = 22,
  Mul = 23,
  Div = 24,
  Mod = 25,
  Print = 26,
  Emit = 27,
  EndStream = 28
};

class ioperand {
 public:
  virtual int get_precision(void) const = 0;
  virtual optype get_type(void) const = 0;
  virtual ioperand const* operator+(ioperand const& rhs) const = 0;
  virtual ioperand const* operator-(ioperand const& rhs) const = 0;
  virtual ioperand const* operator*(ioperand const& rhs) const = 0;
  virtual ioperand const* operator/(ioperand const& rhs) const = 0;
  virtual ioperand const* operator%(ioperand const& rhs) const = 0;
  virtual std::string const& to_string(void) const = 0;
  virtual ~ioperand(void) {}
};

class operand : public ioperand {
 public:
  virtual int get_precision(void) const;
  virtual optype get_type(void) const;
  virtual std::string const& to_string(void) const;
  union datatypes get_data(void) const;

  virtual ioperand const* operator+(ioperand const& rhs) const;
  virtual ioperand const* operator-(ioperand const& rhs) const;
  virtual ioperand const* operator*(ioperand const& rhs) const;
  virtual ioperand const* operator/(ioperand const& rhs) const;
  virtual ioperand const* operator%(ioperand const& rhs) const;
  void operator=(const operand& rhs);

  operand() = delete;
  operand(std::string string, optype type);
  operand(operand& o) = default;
  operand& operator=(operand& o) = default;
  virtual ~operand() = default;

 protected:
  // this is the only shit that matters
  std::string _string;
  optype _type = optype::None;
};

class operand_factory {
 public:
  ioperand const* create_operand(std::string const& value, optype type) const;
  ioperand const* create_int8(std::string const& value) const;
  ioperand const* create_int16(std::string const& value) const;
  ioperand const* create_int32(std::string const& value) const;
  ioperand const* create_float(std::string const& value) const;
  ioperand const* create_double(std::string const& value) const;
};
