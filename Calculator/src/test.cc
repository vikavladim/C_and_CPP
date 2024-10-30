#include <cmath>

// #include "SmartCalc2_0/external/googletest/googlemock/include/gmock/gmock.h"
// #include "SmartCalc2_0/external/googletest/googletest/include/gtest/gtest.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "vv_calculator.h"

TEST(Caclculator, AllOperatoins) {
  // MyParser p("sin(1/7)+cos(1/7)*ln(3)-tan(90)*atan(90)");
  // PolishNotation RPN(p);
  // auto c = RPN.get_output();
  // while (!c.empty()) {
  //   std::cout << c.front() << std::endl;
  //   c.pop();
  // }

  // Calculate c(RPN, -5);
  ASSERT_EQ(Calculate("2+2*3+-++--4").get_result(), 2 + 2 * 3 + -(-(-4)));
  ASSERT_EQ(Calculate("2+x*3+-++--x", -5).get_result(), 2 + -5 * 3 + -(-(5)));
  ASSERT_EQ(Calculate("2^ x * 3 + -(x)", -5).get_result(),
            pow(2, -5) * 3 + -(-(5)));
  ASSERT_EQ(Calculate("2^ x * 3 + -(x)", -5).get_result(),
            pow(2, -5) * 3 + -(-(5)));
  ASSERT_EQ(Calculate("2^ 3^2").get_result(), pow(2, 9));
  ASSERT_EQ(Calculate("2^ 3^2^3").get_result(), pow(2, pow(3, 8)));
  ASSERT_EQ(Calculate("log(25)").get_result(), log10(25));
  ASSERT_EQ(Calculate("ln(25)").get_result(), log(25));
  ASSERT_EQ(Calculate("-7^2").get_result(), -49);
  ASSERT_EQ(Calculate("3-(1+2)*asin(x)", 1).get_result(),
            3 - (1 + 2) * asin(1));
  ASSERT_EQ(Calculate("sin(1/7)+cos(1/7)*ln(3)-tan(90)*atan(90)").get_result(),
            sin(1. / 7) + cos(1. / 7) * log(3) - tan(90) * atan(90));
  ASSERT_EQ(Calculate("acos(sqrt(1/9)*1.7)").get_result(),
            acos(sqrt(1. / 9) * 1.7));
  ASSERT_EQ(Calculate("8 mod 3").get_result(), 2);
  ASSERT_EQ(Calculate("-8 mod 3").get_result(), 1);

  ASSERT_TRUE(std::isinf(Calculate("8/0").get_result()));
  ASSERT_TRUE(std::isnan(Calculate("0/0").get_result()));
  ASSERT_ANY_THROW(Calculate("8(/0").get_result());
  ASSERT_ANY_THROW(Calculate("8)/0").get_result());
  ASSERT_ANY_THROW(Calculate("8/*9+").get_result());
  ASSERT_ANY_THROW(Calculate("abracadabrashvabra").get_result());
  ASSERT_ANY_THROW(Calculate("2       2").get_result());
  ASSERT_ANY_THROW(Calculate("").get_result());
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
