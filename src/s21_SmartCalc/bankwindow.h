#ifndef BANKWINDOW_H
#define BANKWINDOW_H

#include <QMainWindow>

extern "C" {
#include "../s21_BankCalc.h"
}

namespace Ui {
class BankWindow;
}

class BankWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit BankWindow(QWidget *parent = nullptr);
  ~BankWindow();

 private:
  Ui::BankWindow *ui;

 private slots:
  void on_pushButton_clicked();
  void on_Result_clicked();
};

#endif  // BANKWINDOW_H
