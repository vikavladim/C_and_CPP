#ifndef SMARTCALC_SMARTCALC2_0_CONTROLLER_MAINCALC_CTRL_H
#define SMARTCALC_SMARTCALC2_0_CONTROLLER_MAINCALC_CTRL_H

#include <QDebug>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QRectF>
#include <QString>
#include <QtCharts>

#include "maincalcview.h"
#include "vv_calculator.h"

QT_BEGIN_NAMESPACE namespace vv { class MainCalcCtrl; }
QT_END_NAMESPACE

/**
 * @brief controller class for main expression tab
 *
 */
class MainCalcCtrl : public QObject {
  Q_OBJECT
 public:
  /**
   * @brief Construct a new Main Calc Ctrl object
   *
   * @param parent tab of expression widget
   */
  MainCalcCtrl(MainCalcView *parent = nullptr);
 public slots:
  /**
   * @brief duble digit or function from button on the board
   *
   */
  void OnWriteButton();
  /**
   * @brief perform operations, drow plot, calculate with x
   *
   */
  void Calculation();
  /**
   * @brief show and hide widget with plot
   *
   */
  void OnShowHidePressed();
  /**
   * @brief react to mouse wheel, scale plot
   *
   * @param event information about mouse
   */
  void WheelEvent(QWheelEvent *event);
  /**
   * @brief react to mouse move in plot
   *
   * @param event information about mouse
   */
  void MoveEvent(QMouseEvent *event);
  /**
   * @brief plot redrow if you change min and max x
   *
   */
  void Redrow();

 private:
  // MainCalcView *widget;
  CalcView *calc_view;
  PlotView *plot_view;
  void AddConnections();
  // void DeleteGraphs();
  QMainWindow *main_window;
};

#endif  // SMARTCALC_SMARTCALC2_0_CONTROLLER_MAINCALC_CTRL_H
