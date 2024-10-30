#include "plotview.h"

#include "maincalc_ctrl.h"

PlotView::PlotView(QWidget *parent) : QWidget(parent) { CreateElements(); }

void PlotView::CreateElements() {
  spn_max_x = new QDoubleSpinBox(this);
  spn_min_x = new QDoubleSpinBox(this);

  spn_min_x->setMinimum(-1e10);
  spn_min_x->setMaximum(1e10);
  spn_min_x->setSingleStep(1);
  spn_min_x->setValue(-10);

  spn_max_x->setMinimum(-1e10);
  spn_max_x->setMaximum(1e10);
  spn_max_x->setSingleStep(1);
  spn_max_x->setValue(10);

  chart_widget = new ChartView();
  // chart_widget = new QChartView(this);
  // chart_widget->setRubberBand(QChartView::HorizontalRubberBand);
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->addWidget(chart_widget);

  QHBoxLayout *down_layout = new QHBoxLayout(this);
  down_layout->addWidget(new QLabel("X min: ", this));
  down_layout->addWidget(spn_min_x);
  down_layout->addWidget(new QLabel("X max: ", this));
  down_layout->addWidget(spn_max_x);

  main_layout->addLayout(down_layout);
  setLayout(main_layout);
}

void PlotView::DeleteGraphs() {
  QChart *chartD = chart_widget->chart();
  while (chartD && !chartD->series().isEmpty()) {
    QLineSeries *series = qobject_cast<QLineSeries *>(chartD->series().at(0));
    chartD->removeSeries(series);
    delete series;
  }
}

void PlotView::Drow(QString expression,
                    std::vector<std::pair<double, double>> pairs) {
    if(pairs.empty())
        return;
  DeleteGraphs();
  QChart *chart = new QChart;
  QValueAxis *axis_x = new QValueAxis(chart);
  axis_x->setRange(spn_min_x->value(), spn_max_x->value());
  chart->addAxis(axis_x, Qt::AlignBottom);

  QValueAxis *axis_y = new QValueAxis(chart);
  chart->addAxis(axis_y, Qt::AlignLeft);
  QLineSeries *series = new QLineSeries(chart);
  series->setColor(Qt::red);
  series->setName(expression);
  chart->addSeries(series);
  QVector<QPointF> values;
  double min = INFINITY, max = -INFINITY;
  for (const auto &point : pairs) {
    values.append(QPointF(point.first, point.second));
    if (min > point.second) min = point.second;
    if (max < point.second) max = point.second;
  }
  for (const auto &point : values) {
    if (std::isnan(point.y())) {
      series->attachAxis(axis_x);
      series->attachAxis(axis_y);
      series = new QLineSeries(chart);
      series->setColor(Qt::red);
      chart->addSeries(series);
      chart->legend()->markers(series).first()->setVisible(false);
    } else {
      series->append(point);
    }
  }
  if (min == max) {
    --min;
    ++max;
  }
  axis_y->setRange(min, max);
  series->attachAxis(axis_x);
  series->attachAxis(axis_y);
  chart_widget->setChart(chart);
  chart_widget->xmin = spn_min_x->value();
  chart_widget->xmax = spn_max_x->value();
}
