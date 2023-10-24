#ifndef BANKWINDOW_H
#define BANKWINDOW_H

#include <QMainWindow>

#include "../controller/calc_controller.h"
#include "../model/bank_model.h"

namespace Ui {
class BankWindow;
}

class BankWindow : public QMainWindow {
  Q_OBJECT

 public:
  BankWindow(QWidget *parent = nullptr, s21::Controller *c = nullptr);
  ~BankWindow();

 private:
  Ui::BankWindow *ui;
  s21::Controller *controll_;

 private slots:
  void on_pushButton_clicked();
  void on_Result_clicked();
};

#endif  // BANKWINDOW_H
