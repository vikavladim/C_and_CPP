#ifndef SMARTCALC_SMARTCALC2_0_VIEW_DEPOSITVIEW_H
#define SMARTCALC_SMARTCALC2_0_VIEW_DEPOSITVIEW_H

#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>
#include <cmath>

// #include "depositcalc.h"

QT_BEGIN_NAMESPACE
namespace vv {
class DepositView;
}
QT_END_NAMESPACE

class DepositCtrl;
/**
 * @brief panel with deposit tab
 *
 */
class DepositView : public QWidget {
  Q_OBJECT
  friend class DepositCtrl;

 public:
  /**
   * @brief Construct a new Deposit View object
   *
   * @param parent parent
   */
  DepositView(QWidget* parent = nullptr);

 private:
  QDoubleSpinBox* spn_sum;
  QComboBox* combo_duration;
  QSpinBox* spn_duration;
  QDateEdit* ed_date;
  QDoubleSpinBox* spn_percent;
  QComboBox* combo_period;
  QDoubleSpinBox* spn_tax;
  QCheckBox* check_capitalized;
  // QScrollArea* scroll;
  QWidget* scroll;
  QVBoxLayout* scroll_layout;
  QPushButton* btn_add;
  QPushButton* btn_show_hide;
  QPushButton* btn_result;
  QLabel* lbl_total;
  QLabel* lbl_profit;
  QLabel* lbl_tax;
  QScrollArea* scroll_area;
  QTableView* table_result;
  void CreateElements();
  void SetElements();
  void SetWidgetGridPosition(QGridLayout* grid_layout, QWidget* widget, int& i);
  const int kCountColumns = 2;
  QWidget* AddWidget();
  void ShowResult(const QVector<std::tuple<QDate, double, double>>& result,
                  const double& total, const double& profit, const double tax);
};

#endif  // SMARTCALC_SMARTCALC2_0_VIEW_DEPOSITVIEW_H
