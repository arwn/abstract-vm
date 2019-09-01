// Aren R. Windham 2019
// TODO:
//  fix -e flag breaking fucking everything
//  remove comments.

//#include "FlexLexer.h"
#include <FlexLexer.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include "exceptions.hpp"
#include "operand.hpp"

// ofsets are the location in the string where the number starts. for example in
// `double(13)' the number 13 starts 7 to the right of the first character.
#define INT8_OFFSET 5
#define INT16_OFFSET 6
#define INT32_OFFSET 6
#define FLOAT_OFFSET 6
#define DOUBLE_OFFSET 7

#ifdef DEBUG
void print_operators(std::deque<commandtype> const& operators) {
  std::cout << "printing operators deque" << std::endl;
  for (auto it = operators.cbegin(); it != operators.cend(); ++it) {
    std::cout << static_cast<int>(*it) << " ";
  }
}

void print_operands(std::deque<const ioperand*> const& operands) {
  std::cout << std::endl << "printing operands deque" << std::endl;
  for (auto it = operands.cbegin(); it != operands.cend(); ++it) {
    std::cout << (*it)->to_string() << " of type " << (int)(*it)->get_type()
              << std::endl;
  }
  std::cout << std::endl;
}

void print_operands(std::vector<const ioperand*> const& operands) {
  std::cout << std::endl << "printing operands in runtime" << std::endl;
  for (auto it = operands.cbegin(); it != operands.cend(); ++it) {
    std::cout << (*it)->to_string() << " of type " << (int)(*it)->get_type()
              << std::endl;
  }
  std::cout << std::endl;
}
#endif

const std::string usage = "usage: asvm [-he] [file]";

int main(int argc, char** argv) {
  try {
    FlexLexer* lexer = new yyFlexLexer();

    // read from file if is the file exist.
    if (argc > 1) {
      std::ifstream* ifstream = new std::ifstream(argv[argc - 1]);
      if (ifstream->good() == 0) {
        perror("Can't open file");
        exit(1);
      }
      lexer->switch_streams(ifstream);
    }

    std::deque<const ioperand*> operands;
    std::deque<commandtype> operators;
    operand_factory factory;
    bool uop = false;
    int linum = 1;
    int token;
    while ((token = lexer->yylex())) {
      std::string str = lexer->YYText();
      switch (token) {
        case -1:
          std::cerr << "Excuse me but what the fuck?" << std::endl;
          operators.push_front(commandtype::Error);
          break;
        case static_cast<int>(septype::None):
        case static_cast<int>(septype::Space):
          break;
        case static_cast<int>(septype::Newline):
          linum++;
        case static_cast<int>(septype::Comment):
          break;  // ignore whitespace sorta
        case static_cast<int>(optype::Int8):
          if (uop == false) {
            std::cerr << linum << ": orphaned operand" << std::endl;
          } else {
            try {
              operands.push_front(factory.create_operand(
                  str.substr(INT8_OFFSET, str.length() - 1 - INT8_OFFSET),
                  (optype)token));
            } catch (std::exception& e) {
              std::cerr << e.what() << std::endl;
              operands.push_front(factory.create_operand("0", (optype)token));
            }
          }
          uop = false;
          break;
        case static_cast<int>(optype::Int16):
          if (uop == false) {
            std::cerr << linum << ": orphaned operand" << std::endl;
          } else {
            try {
              operands.push_front(factory.create_operand(
                  str.substr(INT16_OFFSET, str.length() - 1 - INT16_OFFSET),
                  (optype)token));
            } catch (std::exception& e) {
              std::cerr << e.what() << std::endl;
              operands.push_front(factory.create_operand("0", (optype)token));
            }
          }
          uop = false;
          break;
        case static_cast<int>(optype::Int32):
          if (uop == false) {
            std::cerr << linum << ": orphaned operand" << std::endl;
          } else {
            try {
              operands.push_front(factory.create_operand(
                  str.substr(INT32_OFFSET, str.length() - 1 - INT32_OFFSET),
                  (optype)token));
            } catch (std::exception& e) {
              std::cerr << e.what() << std::endl;
              operands.push_front(factory.create_operand("0", (optype)token));
            }
          }
          uop = false;
          break;
        case static_cast<int>(optype::Float):
          if (uop == false) {
            std::cerr << linum << ": orphaned operand" << std::endl;
          } else {
            try {
              operands.push_front(factory.create_operand(
                  str.substr(FLOAT_OFFSET, str.length() - 1 - FLOAT_OFFSET),
                  (optype)token));
            } catch (std::exception& e) {
              std::cerr << e.what() << std::endl;
              operands.push_front(factory.create_operand("0", (optype)token));
            }
          }
          uop = false;
          break;
        case static_cast<int>(optype::Double):
          if (uop == false) {
            std::cerr << linum << ": orphaned operand" << std::endl;
          } else {
            try {
              operands.push_front(factory.create_operand(
                  str.substr(DOUBLE_OFFSET, str.length() - 1 - DOUBLE_OFFSET),
                  (optype)token));
            } catch (std::exception& e) {
              std::cerr << e.what() << std::endl;
              operands.push_front(factory.create_operand("0", (optype)token));
            }
          }
          uop = false;
          break;
        case static_cast<int>(commandtype::Exit):
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            operators.push_front(commandtype::Exit);
          }
          break;
        case static_cast<int>(commandtype::Push):
          if (uop) {
            std::cerr << linum << ": orphaned uop" << std::endl;
          } else {
            operators.push_front(commandtype::Push);
            uop = true;
          }
          break;
        case static_cast<int>(commandtype::Pop):
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            operators.push_front(commandtype::Pop);
          }
          break;
        case static_cast<int>(commandtype::Dump):
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            operators.push_front(commandtype::Dump);
          }
          break;
        case static_cast<int>(commandtype::Assert):
          if (uop) {
            std::cerr << linum << ": orphaned uop" << std::endl;
          } else {
            operators.push_front(commandtype::Assert);
            uop = true;
          }
          break;
        case static_cast<int>(commandtype::Add):
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            operators.push_front(commandtype::Add);
          }
          break;
        case static_cast<int>(commandtype::Sub):
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            operators.push_front(commandtype::Sub);
          }
          break;
        case static_cast<int>(commandtype::Mul):
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            operators.push_front(commandtype::Mul);
          }
          break;
        case static_cast<int>(commandtype::Div):
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            operators.push_front(commandtype::Div);
          }
          break;
        case static_cast<int>(commandtype::Mod):
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            operators.push_front(commandtype::Mod);
          }
          break;
        case static_cast<int>(commandtype::Print):
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            operators.push_front(commandtype::Print);
          }
          break;
        case static_cast<int>(commandtype::Emit):
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            operators.push_front(commandtype::Emit);
          }
          break;
        case static_cast<int>(commandtype::EndStream):
          if (argc == 2) break;  // if reading from a file, ignore
          if (uop) {
            operators.pop_front();
            std::cerr << linum << ": orphaned uop" << std::endl;
            uop = false;
          } else {
            goto evaluate;
          }
          break;
        default:
          std::cerr << linum << ": not implemented: " << lexer->YYText()
                    << std::endl;  // this should never be called;
      }
    }
    // finally check if last operator is a uop
    if (uop) {
      operators.pop_front();
      std::cerr << "orphaned uop" << std::endl;
    }
    // if last operator is not exit then it's a lexical error
    if (operators.front() != commandtype::Exit) {
      std::cerr << "exit not last instruction" << std::endl;
    }

  evaluate:
    // evaluate the code hehe...
    std::vector<const ioperand*> stack;
    while (operators.size() > 0) {
      switch (operators.back()) {
        case commandtype::Error:
          std::cerr << "error in vm stack??" << std::endl;
          break;
        case commandtype::Exit:
          std::cout << "bye.." << std::endl;
          exit(0);
          break;
        case commandtype::Push:
          if (operands.size() > 0) {
            stack.push_back(operands.back());
            operands.pop_back();
          } else {
            std::cerr << "Pushing on empty stack" << std::endl;
          }
          break;
        case commandtype::Pop:
          if (stack.size() > 0) {
            stack.pop_back();
          } else {
            std::cerr << "Pop on empty stack" << std::endl;
          }
          break;
        case commandtype::Dump:
          std::cout << "Dump:";
          for (auto const& val : stack) {
            std::cout << "\t";
            switch (val->get_type()) {
              case optype::Int8:
                std::cout << "int8: ";
                break;
              case optype::Int16:
                std::cout << "int16: ";
                break;
              case optype::Int32:
                std::cout << "int32: ";
                break;
              case optype::Float:
                std::cout << "Float: ";
                break;
              case optype::Double:
                std::cout << "Double: ";
                break;
              default:
                break;
            }
            std::cout << val->to_string() << std::endl;
          }
          std::cout << std::endl;
          break;
        case commandtype::Assert:
          if (operands.size() < 1) {
            // this should never run
            std::cerr << "assert somehow doesn't have a child" << std::endl;
          } else if (stack.size() < 1) {  // the actual assertion
            std::cerr << "assert on empty stack" << std::endl;
          } else {
            if (stack.back()->to_string() != operands.back()->to_string()) {
              std::cerr << linum << ": assertion failed" << std::endl
                        << "case:\t" << stack.back()->to_string()
                        << "!=" << operands.back()->to_string() << std::endl;
            }
          }
          operands.pop_back();
          break;
        // if add, sub, mul, mod, div overflow the top two stack elements are
        // eaten.
        case commandtype::Add:
          if (stack.size() > 1) {
            try {
              const ioperand* a = stack.back();
              stack.pop_back();
              const ioperand* b = stack.back();
              stack.pop_back();
              stack.push_back(*a + *b);
            } catch (std::exception& e) {
              std::cerr << e.what() << std::endl;
            }
          } else {
            std::cerr << "adding on stack with size of < 2" << std::endl;
          }
          break;
        case commandtype::Sub:
          if (stack.size() > 1) {
            try {
              const ioperand* a = stack.back();
              stack.pop_back();
              const ioperand* b = stack.back();
              stack.pop_back();
              stack.push_back(*b - *a);
            } catch (std::exception& e) {
              std::cerr << e.what() << std::endl;
            }
          } else {
            std::cerr << "subtracting on stack with size of < 2" << std::endl;
          }
          break;
        case commandtype::Mul:
          if (stack.size() > 1) {
            try {
              const ioperand* a = stack.back();
              stack.pop_back();
              const ioperand* b = stack.back();
              stack.pop_back();
              stack.push_back(*a * *b);
            } catch (std::exception& e) {
              std::cerr << e.what() << std::endl;
            }
          } else {
            std::cerr << "multiplying on stack with size of < 2" << std::endl;
          }
          break;
        case commandtype::Div:
          if (stack.size() > 1) {
            try {
              const ioperand* a = stack.back();
              stack.pop_back();
              const ioperand* b = stack.back();
              stack.pop_back();
              stack.push_back(*b / *a);
            } catch (std::exception& e) {
              std::cerr << e.what() << std::endl;
            }
          } else {
            std::cerr << "dividing on stack with size of < 2" << std::endl;
          }
          break;
        case commandtype::Mod:
          if (stack.size() > 1) {
            try {
              const ioperand* a = stack.back();
              stack.pop_back();
              const ioperand* b = stack.back();
              stack.pop_back();
              stack.push_back(*b % *a);
            } catch (std::exception& e) {
              std::cerr << e.what() << std::endl;
            }
          } else {
            std::cerr << "modeulose on stack with size of < 2" << std::endl;
          }
          break;
        case commandtype::Print:
          if (stack.size() < 1) {
            std::cerr << "print on empty stack" << std::endl;
          } else {
            std::cout << stack.back()->to_string() << std::endl;
          }
          break;
        case commandtype::Emit:
          if (stack.size() < 1) {
            std::cerr << "emit on empty stack" << std::endl;
          } else if (stack.back()->get_type() != optype::Int8) {
            std::cerr << "number too large to print" << std::endl;
          } else {
            std::cout << static_cast<char>(
                std::stoi(stack.back()->to_string()));
          }
          break;
        default:
          std::cerr << linum << ": not implemented" << std::endl;
      }
      operators.pop_back();
    }

#ifdef DEBUG
    // for debugging the stacks
    print_operands(operands);
    print_operators(operators);
    print_operands(stack);
#endif
  } catch (std::exception& e) {
    std::cout << "an error occured, send a bug report" << std::endl
              << &e << std::endl;
  }
  return (0);
}
