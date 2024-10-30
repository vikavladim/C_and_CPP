#ifndef SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_CALCVIEW_H
#define SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_CALCVIEW_H

// #include <QtCore/qmath.h>

#include <QDebug>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <cmath>
#include <memory>

QT_BEGIN_NAMESPACE
namespace vv {
class CalcView;
}
QT_END_NAMESPACE

class MainCalcCtrl;

/**
 * @brief left panel of main expression window, include buttons with functions,
 * digits and field
 *
 */

class CalcView : public QWidget {
  Q_OBJECT
  friend class MainCalcCtrl;

 public:
  /**
   * @brief Construct a new Calc View object
   *
   * @param parent parent
   */
  CalcView(QWidget *parent = nullptr);
  ~CalcView();

 private:
  QLineEdit *line_edit;

  QPushButton *btn_C;
  QPushButton *btn_CE;

  QPushButton *btn_1;
  QPushButton *btn_2;
  QPushButton *btn_3;
  QPushButton *btn_4;
  QPushButton *btn_5;
  QPushButton *btn_6;
  QPushButton *btn_7;
  QPushButton *btn_8;
  QPushButton *btn_9;
  QPushButton *btn_0;

  QPushButton *btn_open_parethesis;
  QPushButton *btn_close_parethesis;

  QPushButton *btn_sin;
  QPushButton *btn_cos;
  QPushButton *btn_tg;

  QPushButton *btn_asin;
  QPushButton *btn_acos;
  QPushButton *btn_atg;

  QPushButton *btn_log;
  QPushButton *btn_ln;

  QPushButton *btn_sqrt;

  QPushButton *btn_pow;
  QPushButton *btn_sum;
  QPushButton *btn_sub;
  QPushButton *btn_mul;
  QPushButton *btn_div;
  QPushButton *btn_mod;

  QPushButton *btn_dot;
  QPushButton *btn_x;

  QPushButton *btn_show_hide;
  QPushButton *btn_result;

  QDoubleSpinBox *spn_x;

  QVBoxLayout *main_calc_layout;
  QHBoxLayout *layout_cce;
  QGridLayout *grid_layout;
  QHBoxLayout *layout_for_x;
  QHBoxLayout *layout_down;
  QHBoxLayout *main_layout;

  void CreateButtons();
  void CreateLayouts();
  void CreateSpn();
  void CreateLineEdit();
  void AddObjectToGridLayout();
  void SetWidgetGridPosition(QWidget *widget, int &i);
  void SetObjectNames();
  const int kCountColumns = 5;
  QString ReadFileToString(const QString &fileName);
};

#endif  // SMARTCALC_SMARTCALC2_0_VIEW_EXPRESSIONS_TAB_CALCVIEW_H
