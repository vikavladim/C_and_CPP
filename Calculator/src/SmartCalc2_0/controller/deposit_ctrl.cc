#include "deposit_ctrl.h"

DepositCtrl::DepositCtrl(DepositView* parent)
    : QObject(parent),
      view(parent),
      main_window(qobject_cast<QMainWindow*>(parent->parent())) {
  connect(view->btn_result, SIGNAL(clicked()), this, SLOT(OnResultButton()));
  connect(view->btn_add, SIGNAL(clicked()), this, SLOT(OnAddButton()));
  connect(view->btn_show_hide, SIGNAL(clicked()), this,
          SLOT(OnShowHideButton()));
  connect(view->ed_date, &QDateEdit::dateChanged, this,
          [this](const QDate& date) {
            auto vector = view->scroll->findChildren<QDateEdit*>();
            for (auto it : vector) {
              it->setMinimumDate(date.addDays(1));
            }
          });
}

void DepositCtrl::OnResultButton() {
  int duration = view->spn_duration->value();
  QStandardItem* item = nullptr;
  auto vector1 = view->scroll->findChildren<QDateEdit*>();
  auto vector2 = view->scroll->findChildren<QDoubleSpinBox*>();
  QVector<QPair<QDate, double>> pairs;

  while (!vector1.empty()) {
    pairs.push_back(
        QPair<QDate, double>(vector1.back()->date(), vector2.back()->value()));
    vector1.pop_back();
    vector2.pop_back();
  }

  QDate end = view->ed_date->date();
  int dur = view->spn_duration->value();
  switch (view->combo_duration->currentIndex()) {
    case 0:
      end = end.addDays(dur);
      break;
    case 1:
      end = end.addMonths(dur);
      break;
    case 2:
      end = end.addYears(dur);
      break;
  }
  try {
    DepositCalc deposit =
        DepositCalc(view->ed_date->date(), end, view->spn_sum->value(),
                    view->spn_percent->value(), view->spn_tax->value(),
                    static_cast<Period>(view->combo_period->currentIndex()),
                    view->check_capitalized->isChecked(), pairs);
    view->ShowResult(deposit.get_deposits(), deposit.get_total(),
                     deposit.get_profit(), deposit.get_tax_sum());
  } catch (std::invalid_argument& ex) {
    main_window->statusBar()->showMessage(ex.what(), 1000);
  }
}

void DepositCtrl::OnShowHideButton() {
  if (view->table_result->isHidden()) {
    view->table_result->setVisible(true);
    main_window->resize(main_window->width() * 2, main_window->height());
    view->btn_show_hide->setText("Скрыть таблицу всех результатов");
  } else {
    view->table_result->setVisible(false);
    main_window->resize(main_window->width() / 2, main_window->height());
    view->btn_show_hide->setText("Показать таблицу всех результатов");
  }
}

void DepositCtrl::OnAddButton() {
  connect(view->AddWidget()->findChild<QPushButton*>(), SIGNAL(clicked()), this,
          SLOT(OnDeleteButton()));
}

void DepositCtrl::OnDeleteButton() {
  QPushButton* btn = (QPushButton*)sender();
  btn->parent()->deleteLater();
}
