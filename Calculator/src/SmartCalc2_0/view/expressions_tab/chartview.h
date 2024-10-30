#ifndef SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_CHARTVIEW_H
#define SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_CHARTVIEW_H

#include <QChartView>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace vv {
class ChartView;
}
QT_END_NAMESPACE

/**
 * @brief plot widget with my signals for wheel and move events
 *
 */

class ChartView : public QChartView {
  Q_OBJECT
  qreal mFactor = 1.0;

 public:
  /**
   * @brief minimal x, that you can see on the plot
   *
   */
  double xmin = -10;
  /**
   * @brief maximal x, that you can see on the plot
   *
   */
  double xmax = 10;

 protected:
  void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
 signals:
  void wheel_event(QWheelEvent *event);
  void move_event(QMouseEvent *event);
};

#endif  // SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_CHARTVIEW_H
