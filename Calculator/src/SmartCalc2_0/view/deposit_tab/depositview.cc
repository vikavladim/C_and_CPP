#include "depositview.h"

#include "deposit_ctrl.h"

DepositView::DepositView(QWidget* parent) : QWidget(parent) {
  setObjectName("Вклады");
  CreateElements();
  foreach (QLabel* label, findChildren<QLabel*>()) {
    label->setTextInteractionFlags(Qt::TextSelectableByMouse);
  }
  SetElements();
  DepositCtrl* controller = new DepositCtrl(this);
}

void DepositView::CreateElements() {
  spn_sum = new QDoubleSpinBox(this);
  spn_sum->setMinimum(1e4);
  spn_sum->setMaximum(1e10);
  spn_sum->setSingleStep(1e4);
  spn_sum->setValue(1e6);

  combo_duration = new QComboBox(this);
  combo_duration->addItem("в днях");
  combo_duration->addItem("в месяцах");
  combo_duration->addItem("в годах");
  combo_duration->setCurrentIndex(1);

  spn_duration = new QSpinBox(this);
  spn_duration->setMinimum(1);
  spn_duration->setMaximum(365 * 15);
  spn_duration->setValue(6);

  ed_date = new QDateEdit(this);
  ed_date->setDate(QDate::currentDate());
  ed_date->setCalendarPopup(true);
  ed_date->setMinimumDate(QDate(2000, 1, 1));
  ed_date->setMaximumDate(QDate(2030, 1, 1));

  spn_percent = new QDoubleSpinBox(this);
  spn_percent->setMinimum(0.01);
  spn_percent->setMaximum(30);
  spn_percent->setSingleStep(0.1);
  spn_percent->setValue(4.5);

  combo_period = new QComboBox(this);
  combo_period->addItem("каждый день");
  combo_period->addItem("каждую неделю");
  combo_period->addItem("раз в месяц");
  combo_period->addItem("раз в квартал");
  combo_period->addItem("раз в полгода");
  combo_period->addItem("раз в год");
  combo_period->addItem("в конце срока");
  combo_period->setCurrentIndex(2);

  spn_tax = new QDoubleSpinBox(this);
  spn_tax->setMinimum(0.1);
  spn_tax->setMaximum(10);
  spn_tax->setSingleStep(0.1);
  spn_tax->setValue(3.5);

  check_capitalized = new QCheckBox("Капитализация процентов", this);
  scroll_area = new QScrollArea(this);
  scroll = new QWidget(this);
  scroll_layout = new QVBoxLayout(scroll);

  btn_add = new QPushButton(this);
  btn_add->setIcon(QIcon(":/view/images/plus.png"));

  btn_show_hide = new QPushButton("Показать таблицу всех результатов", this);
  btn_result = new QPushButton("Рассчитать", this);
  lbl_total = new QLabel(this);
  lbl_profit = new QLabel(this);
  lbl_tax = new QLabel(this);
  table_result = new QTableView(this);
  table_result->setVisible(false);
}

void DepositView::SetElements() {
  int i = 0;
  QHBoxLayout* main_layout = new QHBoxLayout(this);
  QVBoxLayout* main_left_layout = new QVBoxLayout(this);
  QGridLayout* form_layout = new QGridLayout(this);
  SetWidgetGridPosition(form_layout, new QLabel("Сумма вклада:", this), i);
  SetWidgetGridPosition(form_layout, spn_sum, i);
  SetWidgetGridPosition(form_layout, new QLabel("Срок размещения:", this), i);
  QHBoxLayout* period_layout = new QHBoxLayout(this);
  period_layout->addWidget(combo_duration);
  period_layout->addWidget(spn_duration);
  form_layout->addLayout(period_layout, 1, 1);
  ++i;
  SetWidgetGridPosition(form_layout, new QLabel("Начало срока:", this), i);
  SetWidgetGridPosition(form_layout, ed_date, i);
  SetWidgetGridPosition(form_layout, new QLabel("Процентная ставка:", this), i);
  SetWidgetGridPosition(form_layout, spn_percent, i);
  SetWidgetGridPosition(form_layout, new QLabel("Периодичность выплат:", this),
                        i);
  SetWidgetGridPosition(form_layout, combo_period, i);
  SetWidgetGridPosition(form_layout, new QLabel("Налоговая ставка:", this), i);
  SetWidgetGridPosition(form_layout, spn_tax, i);

  main_left_layout->addLayout(form_layout);
  main_left_layout->addWidget(check_capitalized);
  main_left_layout->addWidget(new QLabel("Списания и пополнения:", this));

  scroll->setLayout(scroll_layout);
  scroll_area->setWidget(scroll);
  scroll_area->setWidgetResizable(true);
  main_left_layout->addWidget(scroll_area);

  main_left_layout->addWidget(btn_add);
  main_left_layout->addWidget(btn_show_hide);
  main_left_layout->addWidget(btn_result);

  i = 0;
  QGridLayout* result_layout = new QGridLayout(this);
  SetWidgetGridPosition(result_layout, new QLabel("Общая сумма:", this), i);
  SetWidgetGridPosition(result_layout, lbl_total, i);
  SetWidgetGridPosition(result_layout, new QLabel("Из них прибыль:", this), i);
  SetWidgetGridPosition(result_layout, lbl_profit, i);
  SetWidgetGridPosition(result_layout, new QLabel("Налог:", this), i);
  SetWidgetGridPosition(result_layout, lbl_tax, i);
  main_left_layout->addLayout(result_layout);

  main_layout->addLayout(main_left_layout);
  main_layout->addWidget(table_result);
  setLayout(main_layout);
}

void DepositView::SetWidgetGridPosition(QGridLayout* grid_layout,
                                        QWidget* widget, int& i) {
  grid_layout->addWidget(widget, floor(static_cast<double>(i) / kCountColumns),
                         i % kCountColumns);
  ++i;
}

QWidget* DepositView::AddWidget() {
  QWidget* widget = new QWidget(scroll);
  QHBoxLayout* layout = new QHBoxLayout(widget);

  QDoubleSpinBox* spn_add_summ = new QDoubleSpinBox(widget);
  spn_add_summ->setMinimum(-1000000);
  spn_add_summ->setMaximum(1000000);
  spn_add_summ->setDecimals(0);
  spn_add_summ->setSingleStep(10000);
  layout->addWidget(spn_add_summ);

  QDateEdit* date = new QDateEdit(widget);
  date->setDate(ed_date->date());
  date->setCalendarPopup(true);
  date->setMinimumDate(ed_date->date().addDays(1));
  date->setMaximumDate(QDate(2030, 1, 1));
  layout->addWidget(date);

  QPushButton* btn_cross = new QPushButton(widget);
  btn_cross->setIcon(QIcon(":/view/images/cross.jpeg"));
  layout->addWidget(btn_cross);

  scroll_layout->addWidget(widget);

  return widget;
}

void DepositView::ShowResult(
    const QVector<std::tuple<QDate, double, double>>& result,
    const double& total, const double& profit, const double tax) {
  lbl_total->setText(QString::number(total, 'f', 2));
  lbl_profit->setText(QString::number(profit, 'f', 2));
  lbl_tax->setText(QString::number(tax, 'f', 2));

  QStandardItemModel* model = new QStandardItemModel(table_result);
  for (auto& [date, percent, sum_deposit] : result) {
    QList<QStandardItem*> itemList;
    itemList.append(new QStandardItem(date.toString("dd.MM.yy")));
    itemList.append(new QStandardItem(QString::number(percent, 'f', 2)));
    itemList.append(new QStandardItem(QString::number(sum_deposit, 'f', 2)));
    model->appendRow(itemList);
  }
  model->setHorizontalHeaderItem(0, new QStandardItem("Дата"));
  model->setHorizontalHeaderItem(1, new QStandardItem("Процент"));
  model->setHorizontalHeaderItem(2, new QStandardItem("Сумма"));
  table_result->setModel(model);
  table_result->resizeColumnsToContents();
}
