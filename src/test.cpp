#include <gtest/gtest.h>

#include "Model/parser.h"

TEST(test, S21_parser) {
  std::string input =
      "acos(sin(cos(3))) + (tan(-5) ^ log(1000)) - sqrt(x) * asin(+0.6) / "
      "atan(ln(69 mod 6))";
  double x = 2;
  s21::Calculator test = s21::Calculator(&x);
  ASSERT_DOUBLE_EQ(test.DoCalculation(input),
                   acos(sin(cos(3))) + pow(tan(-5), log10(1000)) -
                       sqrt(x) * asin(+0.6) / atan(log(69 % 6)));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
