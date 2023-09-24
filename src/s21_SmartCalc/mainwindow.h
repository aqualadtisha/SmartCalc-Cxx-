#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "bankwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  BankWindow *bank;

  double x_start = 0, x_end = 0, step = 0, y_start = 0, y_end = 0;
  QVector<double> x, y;

 private slots:
  void numbers_operands();
  void maths();
  void ac_clicked();
  void c_clicked();

  void result();
  void on_pushButton_clicked();
};
#endif  // MAINWINDOW_H
