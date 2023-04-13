#ifndef CALC_H
#define CALC_H

#include <QChartView>
#include <QMainWindow>
#include <QShortcut>
#include <QSplineSeries>
#include <QtCharts>

QT_BEGIN_NAMESPACE

namespace Ui {
class calc;
}
QT_END_NAMESPACE

class calc : public QMainWindow {
  Q_OBJECT

 public:
  calc(QWidget *parent = nullptr);
  ~calc();

 private:
  Ui::calc *ui;

 private slots:
  void NumPressed(int n);
  void MathButtonPressed();
  void ACButtonPressed();
  void PointButtonPressed();
  void EQButtonPressed();
  void OpenButtonPressed();
  void CloseButtonPressed();
  void AdvButtonPressed();
  void XButtonPressed();
  void SignButtonPressed();
  void SetButtonsNums(bool b);
  void SetButtonsBinar(bool b);
  void SetButtonsUnar(bool b);
};
#endif  // CALC_H
