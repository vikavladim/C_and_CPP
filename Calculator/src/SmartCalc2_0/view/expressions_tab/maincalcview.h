#ifndef SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_MAINCALCVIEW_H
#define SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_MAINCALCVIEW_H

#include <QHBoxLayout>
#include <QObject>
#include <QWidget>

#include "calcview.h"
#include "plotview.h"

QT_BEGIN_NAMESPACE
namespace vv {
class MainCalcView;
}
QT_END_NAMESPACE
class MainCalcCtrl;

/**
 * @brief main expression tab with left panel with buttons and right panel with
 * plot
 *
 */
class MainCalcView : public QWidget {
  Q_OBJECT
  friend class MainCalcCtrl;

 public:
  /**
   * @brief Construct a new Main Calc View object
   *
   * @param parent parent
   */
  MainCalcView(QWidget* parent = nullptr);
  // ~MainCalcView();

 private:
  // MainCalcCtrl* controller;
  CalcView* calc_view;
  PlotView* plot_view;
};

#endif  // SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_MAINCALCVIEW_H
