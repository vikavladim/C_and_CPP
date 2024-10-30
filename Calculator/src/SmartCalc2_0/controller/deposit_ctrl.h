#ifndef SMARTCALC_SMARTCALC2_0_CONTROLLER_DEPOSIT_CTRL_H
#define SMARTCALC_SMARTCALC2_0_CONTROLLER_DEPOSIT_CTRL_H

#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QStandardItem>
#include <QStatusBar>

#include "depositcalc.h"
#include "depositview.h"

QT_BEGIN_NAMESPACE
namespace vv {
class DepositCtrl;
}
QT_END_NAMESPACE
/**
 * @brief controller class for deposit tab
 *
 */
class DepositCtrl : public QObject {
  Q_OBJECT
 public:
  /**
   * @brief Construct a new Deposit Ctrl object
   *
   * @param parent deposit widget for controlling
   */
  DepositCtrl(DepositView *parent = nullptr);
 public slots:
  /**
   * @brief for result button
   *
   */
  void OnResultButton();
  /**
   * @brief for button show/hide, show and hide window
   *
   */
  void OnShowHideButton();
  /**
   * @brief add new row with withdraws
   *
   */
  void OnAddButton();
  /**
   * @brief delete row with withdrow
   *
   */
  void OnDeleteButton();

 private:
  DepositView *view;
  QMainWindow *main_window;
};

#endif  // SMARTCALC_SMARTCALC2_0_CONTROLLER_DEPOSIT_CTRL_H
