#include "mainwindowview.h"

MainWindowView::MainWindowView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowView) {
  ui->setupUi(this);

  setStyleSheet(ReadFileToString(":/view/style.css"));
  ui->menubar->hide();
  tab_widget = new QTabWidget(this);
  QMainWindow::setCentralWidget(tab_widget);
  AddTab(new MainCalcView(this));
  AddTab(new CreditView(this));
  AddTab(new DepositView(this));

  tab_widget->setCurrentIndex(0);
  setWindowTitle("SmartCalc v. 2.0");
}

MainWindowView::~MainWindowView() { delete ui; }

void MainWindowView::AddTab(QWidget *widget) {
  ;
  tab_widget->addTab(widget, widget->objectName());
}

QString MainWindowView::ReadFileToString(const QString &fileName) {
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Не удалось открыть файл:" << file.errorString();
    return QString();
  }

  QTextStream in(&file);
  QString content = in.readAll();

  file.close();
  return content;
}
