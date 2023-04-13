#include <array>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>

namespace s21 {
class Calculator {
 private:
  enum Type : int { kEmpty = 0, kNumber, kSymbol, kPointer };

  struct Command {
    char symbol;
    std::string input;
    int value;
    size_t length;

    Command(char symbol, std::string input, int value, size_t length)
        : symbol(symbol), input(input), value(value), length(length) {}
  };

  std::array<Command, 15> commands = {
      Command('+', " + ", 2, 3),   Command('-', " - ", 2, 3),
      Command('*', " * ", 3, 3),   Command('/', " / ", 3, 3),
      Command('^', " ^ ", 3, 3),   Command('%', " mod ", 3, 5),
      Command('!', "sin(", 4, 3),  Command('@', "cos(", 4, 3),
      Command('#', "tan(", 4, 3),  Command('c', "acos(", 4, 4),
      Command('s', "asin(", 4, 4), Command('t', "atan(", 4, 4),
      Command('&', "ln(", 4, 2),   Command('?', "log(", 4, 3),
      Command('$', "sqrt(", 4, 4)};

  struct Object {
    double data;
    char symbol;
    double *ptr;
    int type;

    Object() : data(0), symbol('0'), ptr(nullptr), type(kEmpty) {}
    Object(double d) : data(d), symbol('0'), ptr(nullptr), type(kNumber) {}
    Object(char s) : data(0), symbol(s), ptr(nullptr), type(kSymbol) {}
    Object(double *ptr) : data(0), symbol('0'), ptr(ptr), type(kPointer) {}
  };

  struct Character {
    char symbol;
    int value;

    Character(char symbol, int value) : symbol(symbol), value(value){};
  };

  std::stack<Object> main;
  std::stack<Character> characters;

  double *x;

  void MoveFromCharactersToMain();
  void Push(char c, int value);
  void Parse(std::string arr);
  void Reverse();

  size_t FindCommand(std::string arr, size_t i);
  size_t FindUnar(std::string arr, size_t i);
  size_t FindValue(std::string arr, size_t i);
  size_t FindBrackets(std::string arr, size_t i);
  size_t FindBinarAndFunc(std::string arr, size_t i);

  Object GetObjectFromStack(std::stack<Object> *st);
  char CheckZTop();
  int CheckTypeTop();
  void DoOperation(char c, std::stack<Object> *st);
  double Math();

 public:
  Calculator(double *ptr) : x(ptr) {}
  Calculator() = default;
  double DoCalculation(std::string input);
};
}  // namespace s21
