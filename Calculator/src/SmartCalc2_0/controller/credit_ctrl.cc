#include "credit_ctrl.h"

CreditCtrl::CreditCtrl(CreditView* parent) : QObject(parent), view(parent) {
  connect(view->btn_result, SIGNAL(clicked()), this, SLOT(OnResultButton()));
}

void CreditCtrl::OnResultButton() {
  int duration = view->spn_duration->value();
  if (view->combo_period->currentIndex() == 0) duration *= 12;
  CreditCalc credit(view->spn_sum->value(), duration,
                    view->spn_percent->value(),
                    view->check_annual->isChecked());
  view->ShowResult(credit.get_monthly_payment(), credit.get_total(),
                   credit.get_overpayment());
}