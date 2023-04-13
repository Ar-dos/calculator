#include "controller.h"

double Controller::Calculate(std::string input) {
  double res = calc->DoCalculation(input);
  return res;
}
