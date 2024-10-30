#include "calcview.h"

#include "maincalc_ctrl.h"

CalcView::CalcView(QWidget *parent) : QWidget(parent) {
  CreateLineEdit();
  CreateButtons();
  CreateLayouts();
  CreateSpn();
  SetObjectNames();
  AddObjectToGridLayout();
}

CalcView::~CalcView() {
  // delete layout_cce;
  // delete layout_for_x;
  // delete grid_layout;
  // delete layout_down;

  // delete main_layout;
}

void CalcView::CreateButtons() {
  btn_C = new QPushButton("C", this);
  btn_CE = new QPushButton("CE", this);

  btn_1 = new QPushButton("1", this);
  btn_2 = new QPushButton("2", this);
  btn_3 = new QPushButton("3", this);
  btn_4 = new QPushButton("4", this);
  btn_5 = new QPushButton("5", this);
  btn_6 = new QPushButton("6", this);
  btn_7 = new QPushButton("7", this);
  btn_8 = new QPushButton("8", this);
  btn_9 = new QPushButton("9", this);
  btn_0 = new QPushButton("0", this);
  btn_open_parethesis = new QPushButton("(", this);
  btn_close_parethesis = new QPushButton(")", this);
  btn_sin = new QPushButton("sin(x)", this);
  btn_cos = new QPushButton("cos(x)", this);
  btn_tg = new QPushButton("tan(x)", this);
  btn_asin = new QPushButton("asin(x)", this);
  btn_acos = new QPushButton("acos(x)", this);
  btn_atg = new QPushButton("atan(x)", this);
  btn_log = new QPushButton("log(x)", this);
  btn_ln = new QPushButton("ln(x)", this);
  btn_sqrt = new QPushButton("sqrt(x)", this);
  btn_pow = new QPushButton("^x", this);
  btn_sum = new QPushButton("+", this);
  btn_sub = new QPushButton("-", this);
  btn_mul = new QPushButton("*", this);
  btn_div = new QPushButton("/", this);
  btn_mod = new QPushButton("mod", this);
  btn_dot = new QPushButton(".", this);
  btn_x = new QPushButton("x", this);
  btn_show_hide = new QPushButton("Показать график", this);
  btn_result = new QPushButton("Вычислить(=)", this);
}

void CalcView::AddObjectToGridLayout() {
  // QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_calc_layout->addWidget(line_edit);

  // QHBoxLayout *layout_cce = new QHBoxLayout(this);
  layout_cce->addWidget(btn_C);
  layout_cce->addWidget(btn_CE);
  main_calc_layout->addLayout(layout_cce);

  // QGridLayout *grid_layout = new QGridLayout(this);
  int i = 0;
  SetWidgetGridPosition(btn_open_parethesis, i);
  SetWidgetGridPosition(btn_pow, i);
  SetWidgetGridPosition(btn_sin, i);
  SetWidgetGridPosition(btn_cos, i);
  SetWidgetGridPosition(btn_tg, i);
  SetWidgetGridPosition(btn_close_parethesis, i);
  SetWidgetGridPosition(btn_sqrt, i);
  SetWidgetGridPosition(btn_asin, i);
  SetWidgetGridPosition(btn_acos, i);
  SetWidgetGridPosition(btn_atg, i);
  SetWidgetGridPosition(btn_log, i);
  SetWidgetGridPosition(btn_ln, i);
  SetWidgetGridPosition(btn_7, i);
  SetWidgetGridPosition(btn_8, i);
  SetWidgetGridPosition(btn_9, i);
  SetWidgetGridPosition(btn_sum, i);
  SetWidgetGridPosition(btn_sub, i);
  SetWidgetGridPosition(btn_4, i);
  SetWidgetGridPosition(btn_5, i);
  SetWidgetGridPosition(btn_6, i);
  SetWidgetGridPosition(btn_mul, i);
  SetWidgetGridPosition(btn_div, i);
  SetWidgetGridPosition(btn_1, i);
  SetWidgetGridPosition(btn_2, i);
  SetWidgetGridPosition(btn_3, i);
  ++i;
  SetWidgetGridPosition(btn_mod, i);
  SetWidgetGridPosition(btn_dot, i);
  SetWidgetGridPosition(btn_0, i);
  SetWidgetGridPosition(btn_x, i);

  // QHBoxLayout *layout_for_x = new QHBoxLayout(this);
  layout_for_x->addWidget(new QLabel("x=", this));
  layout_for_x->addWidget(spn_x);
  grid_layout->addLayout(layout_for_x, kCountColumns, 0);

  main_calc_layout->addLayout(grid_layout);

  // QHBoxLayout *layout_down = new QHBoxLayout(this);
  layout_down->addWidget(btn_show_hide);
  layout_down->addWidget(btn_result);
  main_calc_layout->addLayout(layout_down);

  main_layout->addLayout(main_calc_layout);

  setLayout(main_layout);
}

void CalcView::CreateLineEdit() {
  line_edit = new QLineEdit(this);
  line_edit->setAlignment(Qt::AlignRight);
  //  connect(line_edit, SIGNAL(returnPressed()), this,
  //          SLOT(CalculationAndDrawing()));
}

void CalcView::SetWidgetGridPosition(QWidget *widget, int &i) {
  grid_layout->addWidget(widget, floor(static_cast<double>(i) / kCountColumns),
                         i % kCountColumns);
  ++i;
}

void CalcView::CreateSpn() {
  spn_x = new QDoubleSpinBox(this);
  spn_x->setMinimum(-1e10);
  spn_x->setMaximum(1e10);
  spn_x->setSingleStep(0.1);
}

void CalcView::SetObjectNames() {
  btn_C->setObjectName("C");
  btn_CE->setObjectName("CE");
  btn_result->setObjectName("result");
  btn_show_hide->setObjectName("graph");
}

void CalcView::CreateLayouts() {
  main_layout = new QHBoxLayout(this);
  main_calc_layout = new QVBoxLayout(this);
  layout_cce = new QHBoxLayout(this);
  grid_layout = new QGridLayout(this);
  layout_for_x = new QHBoxLayout(this);
  layout_down = new QHBoxLayout(this);
  // layout_down = std::make_shared<QHBoxLayout>();
}

QString CalcView::ReadFileToString(const QString &fileName) {
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return QString();
  }

  QTextStream in(&file);
  QString content = in.readAll();

  file.close();
  return content;
}
