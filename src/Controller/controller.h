#include "../Model/parser.h"

class Controller {
 private:
  s21::Calculator *calc;

 public:
  Controller(s21::Calculator *c) : calc(c){};
  double Calculate(std::string input);
};
