#ifndef SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_PLOTVIEW_H
#define SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_PLOTVIEW_H

// #include <QChartView>
#include <QObject>
#include <QWidget>
#include <QtCharts>
#include <algorithm>

#include "chartview.h"

QT_BEGIN_NAMESPACE
namespace vv {
class PlotView;
}
QT_END_NAMESPACE

class MainCalcCtrl;
/**
 * @brief right panel widget with plot
 *
 */
class PlotView : public QWidget {
  Q_OBJECT
  friend class MainCalcCtrl;

 public:
  /**
   * @brief Construct a new Plot View object
   *
   * @param parent parent
   */
  PlotView(QWidget *parent = nullptr);

 private:
  ChartView *chart_widget;
  // QChartView *chart_widget;
  QDoubleSpinBox *spn_min_x;
  QDoubleSpinBox *spn_max_x;
  void CreateElements();
  void DeleteGraphs();
  void Drow(QString expression, std::vector<std::pair<double, double>> values);
};

#endif  // SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_PLOTVIEW_H
