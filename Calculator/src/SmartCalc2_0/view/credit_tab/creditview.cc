#include "creditview.h"

#include "credit_ctrl.h"

CreditView::CreditView(QWidget* parent) : QWidget(parent) {
  setObjectName("Кредиты");
  CreateElements();
  foreach (QLabel* label, findChildren<QLabel*>()) {
    label->setTextInteractionFlags(Qt::TextSelectableByMouse);
  }
  SetElements();
  CreditCtrl* controller = new CreditCtrl(this);
}

void CreditView::CreateElements() {
  spn_sum = new QDoubleSpinBox(this);
  spn_sum->setMinimum(10000);
  spn_sum->setMaximum(INFINITY);
  spn_sum->setSingleStep(10000);
  spn_sum->setValue(1e6);

  combo_period = new QComboBox(this);
  combo_period->addItem("в годах");
  combo_period->addItem("в месяцах");

  spn_duration = new QSpinBox(this);
  spn_duration->setMinimum(1);
  spn_duration->setMaximum(12 * 30);
  spn_duration->setSingleStep(1);
  spn_duration->setValue(6);

  spn_percent = new QDoubleSpinBox(this);
  spn_percent->setMinimum(0.01);
  spn_percent->setMaximum(50);
  spn_percent->setSingleStep(0.1);
  spn_percent->setValue(4.5);

  check_annual = new QRadioButton("Аннуитентные", this);
  check_annual->setChecked(true);
  check_differential = new QRadioButton("Дифференцированные", this);

  btn_result = new QPushButton("Рассчитать");

  table = new QTableView(this);

  lbl_result_total = new QLabel(this);
  lbl_result_overpayment = new QLabel(this);
}

void CreditView::SetElements() {
  int i = 0;
  QVBoxLayout* main_layout = new QVBoxLayout(this);
  QGridLayout* form_layout = new QGridLayout(this);

  SetWidgetGridPosition(form_layout, new QLabel("Общая сумма кредита:", this),
                        i);
  SetWidgetGridPosition(form_layout, spn_sum, i);

  QHBoxLayout* period_layout = new QHBoxLayout(this);
  period_layout->addWidget(new QLabel("Срок:", this));
  period_layout->addWidget(combo_period);
  ++i;
  form_layout->addLayout(period_layout, 1, 0);

  SetWidgetGridPosition(form_layout, spn_duration, i);
  SetWidgetGridPosition(form_layout, new QLabel("Процентная ставка:", this), i);
  SetWidgetGridPosition(form_layout, spn_percent, i);

  main_layout->addLayout(form_layout);

  main_layout->addWidget(new QLabel("Тип платежей:", this));
  //  QButtonGroup* gb_type = new QButtonGroup(this);
  main_layout->addWidget(check_annual);
  main_layout->addWidget(check_differential);
  main_layout->addWidget(btn_result);
  main_layout->addWidget(table);

  QGridLayout* result_layout = new QGridLayout(this);
  i = 0;
  SetWidgetGridPosition(result_layout, new QLabel("Общая сумма долга:", this),
                        i);
  SetWidgetGridPosition(result_layout, lbl_result_total, i);
  SetWidgetGridPosition(result_layout, new QLabel("Из них переплата:", this),
                        i);
  SetWidgetGridPosition(result_layout, lbl_result_overpayment, i);
  main_layout->addLayout(result_layout);
  setLayout(main_layout);
}

void CreditView::SetWidgetGridPosition(QGridLayout* grid_layout,
                                       QWidget* widget, int& i) {
  grid_layout->addWidget(widget, floor(static_cast<double>(i) / kCountColumns),
                         i % kCountColumns);
  ++i;
}

void CreditView::ShowResult(const std::vector<double>& result,
                            const double& total, const double& overpayment) {
  QDate date = QDate::currentDate();
  QStandardItemModel* model = new QStandardItemModel(table);
  for (const double& value : result) {
    QList<QStandardItem*> itemList;
    date = date.addMonths(1);
    itemList.append(new QStandardItem(date.toString("MMMM yyyy")));
    itemList.append(new QStandardItem(QString::number(value)));
    model->appendRow(itemList);
  }
  model->setHorizontalHeaderItem(0, new QStandardItem("Дата"));
  model->setHorizontalHeaderItem(1, new QStandardItem("Сумма"));
  table->setModel(model);
  table->resizeColumnsToContents();
  lbl_result_total->setText(QString::number(total, 'f', 2));
  lbl_result_overpayment->setText(QString::number(overpayment, 'f', 2));
}
