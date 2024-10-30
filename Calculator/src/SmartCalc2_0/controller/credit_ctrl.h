#ifndef SMARTCALC_SMARTCALC2_0_CONTROLLER_CREDIT_CTRL_H
#define SMARTCALC_SMARTCALC2_0_CONTROLLER_CREDIT_CTRL_H

#include <QPushButton>

#include "creditcalc.h"
#include "creditview.h"

QT_BEGIN_NAMESPACE
namespace vv {
class CreditCtrl;
}
QT_END_NAMESPACE
/**
 * @brief controller class for credit tab
 *
 */
class CreditCtrl : public QObject {
  Q_OBJECT
 public:
  /**
   * @brief Construct a new Credit Ctrl object
   *
   * @param parent credit widget
   */
  CreditCtrl(CreditView *parent = nullptr);
 public slots:
  /**
   * @brief slot for result button
   *
   */
  void OnResultButton();

 private:
  CreditView *view;
};

#endif  // SMARTCALC_SMARTCALC2_0_CONTROLLER_CREDIT_CTRL_H
