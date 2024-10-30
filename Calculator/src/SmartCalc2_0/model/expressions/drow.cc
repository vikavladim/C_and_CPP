#include "drow.h"

std::vector<std::pair<double, double>> Drow::Values(PolishNotation RPN,
                                                    const double& min_x,
                                                    const double& max_x) {
  double y = 0;
  double prev = 0;
  double delta_y = INFINITY;
  std::vector<std::pair<double, double>> vector;
  for (double x = min_x; x <= max_x; x += (max_x - min_x) / pow(2, 11)) {
    y = Calculate(RPN, x).get_result();
    if (std::isnan(y) || std::isinf(y) ||
        fabs(delta_y) < fabs(y - prev) &&
            (delta_y >= 0 && y - prev <= 0 || delta_y <= 0 && y - prev >= 0)) {
      delta_y = y - prev;
      prev = y;
      y = std::numeric_limits<double>::quiet_NaN();
    } else {
      delta_y = y - prev;
      prev = y;
    }
    vector.push_back({x, y});
  }
  return vector;
}

std::vector<std::pair<double, double>> Drow::Values(const std::string_view& str,
                                                    const double& min_x,
                                                    const double& max_x) {
  return Values(PolishNotation(str), min_x, max_x);
}
