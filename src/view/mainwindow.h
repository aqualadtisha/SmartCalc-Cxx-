#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <string>

#include "../controller//calc_controller.h"
#include "bankwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr, s21::Controller *c = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui_;
  BankWindow *bank_;

  double x_start_ = 0, x_end_ = 0, step_ = 0, y_start_ = 0, y_end_ = 0,
         x_res_ = 0, y_res_ = 0;
  QVector<double> x_, y_;
  bool error_ = false;
  std::string str_;

 private slots:
  void NumbersOperands();
  void Maths();
  void ACClicked();
  void CClicked();
  void SetButtons();

  void Result();
  void on_CreditCalc_clicked();
  void PaintGraf();
  void SetPoints();

 private:
  s21::Controller *controll_;
};
#endif  // MAINWINDOW_H
