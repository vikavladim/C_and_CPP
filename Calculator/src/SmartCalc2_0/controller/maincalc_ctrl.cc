#include "maincalc_ctrl.h"

MainCalcCtrl::MainCalcCtrl(MainCalcView* parent)
    : QObject(parent),
      calc_view(parent->calc_view),
      plot_view(parent->plot_view),
      main_window(qobject_cast<QMainWindow*>(parent->parent())) {
  AddConnections();
}

void MainCalcCtrl::OnWriteButton() {
  const QRegularExpression re = QRegularExpression("([.(]|[0-9]+)");
  QPushButton* btn = (QPushButton*)sender();
  QString strWithoutX = btn->text().left(btn->text().indexOf('x'));
  if (strWithoutX.isEmpty()) strWithoutX = btn->text();
  if (!strWithoutX.contains(re)) calc_view->line_edit->insert(" ");
  calc_view->line_edit->insert(strWithoutX);
  if (!strWithoutX.contains(re)) calc_view->line_edit->insert(" ");
}

void MainCalcCtrl::AddConnections() {
  auto list_buttons = calc_view->findChildren<QPushButton*>();
  for (QPushButton* button : list_buttons) {
    if (button->objectName() != "result" && button->objectName() != "C" &&
        button->objectName() != "CE" && button->objectName() != "graph") {
      connect(button, SIGNAL(clicked()), this, SLOT(OnWriteButton()));
    }
  }

  connect(calc_view->line_edit, SIGNAL(returnPressed()), this,
          SLOT(Calculation()));
  connect(calc_view->btn_result, SIGNAL(clicked()), this, SLOT(Calculation()));

  connect(calc_view->btn_show_hide, SIGNAL(clicked()), this,
          SLOT(OnShowHidePressed()));

  connect(calc_view->btn_C, &QPushButton::clicked, this,
          [this]() { calc_view->line_edit->backspace(); });
  connect(calc_view->btn_CE, &QPushButton::clicked, this,
          [this]() { calc_view->line_edit->clear(); });

  connect(plot_view->chart_widget, SIGNAL(wheel_event(QWheelEvent*)), this,
          SLOT(WheelEvent(QWheelEvent*)));
  connect(plot_view->chart_widget, SIGNAL(move_event(QMouseEvent*)), this,
          SLOT(MoveEvent(QMouseEvent*)));

  connect(plot_view->spn_min_x, SIGNAL(valueChanged(double)), this,
          SLOT(Redrow()));
  connect(plot_view->spn_max_x, SIGNAL(valueChanged(double)), this,
          SLOT(Redrow()));
}

void MainCalcCtrl::Calculation() {
  try {
    QString str = calc_view->line_edit->text();
    PolishNotation RPN(str.toStdString());
    Calculate calc(RPN, calc_view->spn_x->value());
    calc_view->line_edit->setText(
        QString::fromStdString(std::to_string(calc.get_result())));

    plot_view->Drow(str, Drow::Values(RPN, plot_view->spn_min_x->value(),
                                      plot_view->spn_max_x->value()));
  } catch (std::invalid_argument& ex) {
    main_window->statusBar()->showMessage(ex.what(), 1000);
  }
}

void MainCalcCtrl::OnShowHidePressed() {
  if (plot_view->isHidden()) {
    plot_view->setVisible(true);
    main_window->resize(main_window->width() * 2, main_window->height());
    calc_view->btn_show_hide->setText("Скрыть график");
  } else {
    plot_view->setVisible(false);
    main_window->resize(main_window->width() / 2, main_window->height());
    calc_view->btn_show_hide->setText("Показать график");
  }
}

void MainCalcCtrl::WheelEvent(QWheelEvent* event) {
  double xmin = plot_view->chart_widget->xmin;
  double xmax = plot_view->chart_widget->xmax;
  double koeff = 0, scale = 1.5;
  if (event->angleDelta().y() > 0) {
    koeff = -(xmax - xmin) * (scale - 1) / 2 / scale;
  } else {
    koeff = (xmax - xmin) * (scale - 1) / 2;
  }
  plot_view->spn_min_x->setValue(xmin - koeff);
  plot_view->spn_max_x->setValue(xmax + koeff);
  Redrow();
}

void MainCalcCtrl::MoveEvent(QMouseEvent* event) {
  //    static QPoint startPos; // Статическая переменная для хранения начальных
  //   //  координат

  // //    qDebug()<<event->type();
  //    if (event->buttons() & Qt::LeftButton) {
  //        if (event->type() == QMouseEvent::MouseMove) {
  //            QPoint currentPos = event->pos(); // Текущие координаты
  //            int deltaX = currentPos.x() - startPos.x(); // Разница по оси X
  //            int deltaY = currentPos.y() - startPos.y(); // Разница по оси Y
  //            qDebug() << "Перемещение на пикселей: " << deltaX << ", " <<
  //            deltaY;
  //        }
  //        else// (event->type() == QMouseEvent::MouseButtonPress) {
  //        {
  //            startPos = event->pos(); // Сохраняем начальные координаты
  //            qDebug()<<"btn!";
  //        }
  //    }
}

void MainCalcCtrl::Redrow() {
  QChart* chart = plot_view->chart_widget->chart();
  if (chart->series().empty()) {
    plot_view->chart_widget->xmin = plot_view->spn_min_x->value();
    plot_view->chart_widget->xmax = plot_view->spn_max_x->value();
    return;
  }
  if (plot_view->spn_min_x->value() == plot_view->spn_max_x->value()) return;
  QAbstractSeries* series = chart->series().first();
  plot_view->Drow(series->name(), Drow::Values(series->name().toStdString(),
                                               plot_view->spn_min_x->value(),
                                               plot_view->spn_max_x->value()));
}
