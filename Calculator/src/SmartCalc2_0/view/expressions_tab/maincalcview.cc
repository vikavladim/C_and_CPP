#include "maincalcview.h"

#include "maincalc_ctrl.h"

MainCalcView::MainCalcView(QWidget *parent) : QWidget(parent) {
  QHBoxLayout *main_layout = new QHBoxLayout(this);
  setObjectName("Выражения");

  calc_view = new CalcView(this);
  plot_view = new PlotView(this);
  plot_view->setVisible(false);
  // calc_view = new CalcView(controller, this);
  // plot_view = new PlotView(controller, this);
  // controller =
  new MainCalcCtrl(this);

  main_layout->addWidget(calc_view);
  main_layout->addWidget(plot_view);
}
