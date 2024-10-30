#ifndef SMARTCALC_SMARTCALC2_0_VIEW_CREDITVIEW_H
#define SMARTCALC_SMARTCALC2_0_VIEW_CREDITVIEW_H

#include <QButtonGroup>
#include <QComboBox>
#include <QDate>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QStandardItem>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace vv {
class CreditView;
}
QT_END_NAMESPACE

class CreditCtrl;
/**
 * @brief panel with credit tab
 *
 */
class CreditView : public QWidget {
  Q_OBJECT
  friend class CreditCtrl;

 public:
  /**
   * @brief Construct a new Credit View object
   *
   * @param parent parent
   */
  CreditView(QWidget* parent = nullptr);

 private:
  QDoubleSpinBox* spn_sum;
  QComboBox* combo_period;
  QSpinBox* spn_duration;
  QDoubleSpinBox* spn_percent;
  QRadioButton* check_annual;
  QRadioButton* check_differential;
  QPushButton* btn_result;
  QTableView* table;
  QLabel* lbl_result_total;
  QLabel* lbl_result_overpayment;
  void CreateElements();
  void SetElements();
  void SetWidgetGridPosition(QGridLayout* grid_layout, QWidget* widget, int& i);
  const int kCountColumns = 2;
  void ShowResult(const std::vector<double>& result, const double& total,
                  const double& overpayment);
};

#endif  // SMARTCALC_SMARTCALC2_0_VIEW_CREDITVIEW_H
