#ifndef SMARTCALC_SMARTCALC2_0_VIEW_MAINWINDOWVIEW_H
#define SMARTCALC_SMARTCALC2_0_VIEW_MAINWINDOWVIEW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QTabWidget>

#include "./ui_mainwindowview.h"
#include "creditview.h"
#include "depositview.h"
#include "maincalcview.h"

QT_BEGIN_NAMESPACE
namespace vv {
class MainWindowView;
}
QT_END_NAMESPACE

/**
 * @brief main window
 *
 */
class MainWindowView : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Construct a new Main Window View object
   *
   * @param parent parent
   */
  MainWindowView(QWidget *parent = nullptr);
  /**
   * @brief Destroy the Main Window View object
   *
   */
  ~MainWindowView();

 private:
  Ui::MainWindowView *ui;
  void AddTab(QWidget *widget);
  QTabWidget *tab_widget;
  QString ReadFileToString(const QString &fileName);
  //  Controller *controller;
};
#endif  // SMARTCALC_SMARTCALC2_0_VIEW_MAINWINDOWVIEW_H
