#ifndef SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_DROW_H
#define SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_DROW_H

// #include <QPointF>
#include <algorithm>
#include <vector>

#include "calculate.h"

namespace vv {
class Drow;
}  // namespace vv

/**
 * @brief class for getting all needed pairs for drow plot
 *
 */
class Drow {
 public:
  /**
   * @brief return all pairs x and y
   *
   * @param RPN reverse polish notation of expression
   * @param min_x lowest x
   * @param max_x highest x
   * @return std::vector<std::pair<double, double>>
   */
  static std::vector<std::pair<double, double>> Values(PolishNotation RPN,
                                                       const double& min_x,
                                                       const double& max_x);
  /**
   * @brief return all pairs x and y
   *
   * @param str expression
   * @param min_x lowest x
   * @param max_x highest x
   * @return std::vector<std::pair<double, double>>
   */
  static std::vector<std::pair<double, double>> Values(
      const std::string_view& str, const double& min_x, const double& max_x);

  //  private:
  //   PolishNotation RPN;
};

#endif  // SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_DROW_H
