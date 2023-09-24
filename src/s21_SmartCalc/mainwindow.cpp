#include "mainwindow.h"

#include <stdlib.h>

#include <iostream>
#include <string>

#include "ui_mainwindow.h"

extern "C" {
#include "../s21_SmartCalc.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  bank = new BankWindow;

  connect(ui->pushButton_00, SIGNAL(clicked()), this, SLOT(numbers_operands()));
  connect(ui->pushButton_01, SIGNAL(clicked()), this, SLOT(numbers_operands()));
  connect(ui->pushButton_02, SIGNAL(clicked()), this, SLOT(numbers_operands()));
  connect(ui->pushButton_03, SIGNAL(clicked()), this, SLOT(numbers_operands()));
  connect(ui->pushButton_04, SIGNAL(clicked()), this, SLOT(numbers_operands()));
  connect(ui->pushButton_05, SIGNAL(clicked()), this, SLOT(numbers_operands()));
  connect(ui->pushButton_06, SIGNAL(clicked()), this, SLOT(numbers_operands()));
  connect(ui->pushButton_07, SIGNAL(clicked()), this, SLOT(numbers_operands()));
  connect(ui->pushButton_08, SIGNAL(clicked()), this, SLOT(numbers_operands()));
  connect(ui->pushButton_09, SIGNAL(clicked()), this, SLOT(numbers_operands()));
  connect(ui->pushButton_c_dot, SIGNAL(clicked()), this,
          SLOT(numbers_operands()));

  connect(ui->pushButton_sum, SIGNAL(clicked()), this,
          SLOT(numbers_operands()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this,
          SLOT(numbers_operands()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this,
          SLOT(numbers_operands()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(numbers_operands()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(numbers_operands()));
  connect(ui->pushButton_Lbrac, SIGNAL(clicked()), this,
          SLOT(numbers_operands()));
  connect(ui->pushButton_Rbrac, SIGNAL(clicked()), this,
          SLOT(numbers_operands()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(numbers_operands()));

  connect(ui->pushButton_ac, SIGNAL(clicked()), this, SLOT(ac_clicked()));
  connect(ui->pushButton_c, SIGNAL(clicked()), this, SLOT(c_clicked()));

  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(maths()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(maths()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(maths()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(maths()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(maths()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(maths()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(maths()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(maths()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(maths()));

  connect(ui->pushButton_res, SIGNAL(clicked()), this, SLOT(result()));
  connect(ui->string, SIGNAL(returnPressed()), this, SLOT(result()));

  ui->graph_switch->setCheckable(true);
}

MainWindow::~MainWindow() {
  delete ui;
  delete bank;
}

void MainWindow::numbers_operands() {
  QPushButton *button_numb_oper = (QPushButton *)sender();
  ui->string->setText(ui->string->text() + button_numb_oper->text());
}

void MainWindow::maths() {
  QPushButton *button_math = (QPushButton *)sender();

  QString new_string = button_math->text();
  new_string.chop(2);

  ui->string->setText((ui->string->text() + new_string));
}

void MainWindow::ac_clicked() {
  ui->string->setText("");
  x.clear();
  y.clear();
  ui->grafic->clearGraphs();
}

void MainWindow::c_clicked() {
  QString new_str = (QString)ui->string->text();
  new_str.chop(1);
  ui->string->setText(new_str);
}

void MainWindow::result() {
  double x_res = 0, y_res = 0;
  int Error = 0;

  std::string str = ui->string->text().toStdString();
  const char *expression = str.c_str();

  x_res = ui->string_X->text() == "" ? 0 : ui->string_X->text().toDouble();
  x_start = ui->string_Xrange_start->text() == ""
                ? -2
                : ui->string_Xrange_start->text().toDouble();
  x_end = ui->string_Xrange_end->text() == ""
              ? 2
              : ui->string_Xrange_end->text().toDouble();
  y_start = ui->string_Yrange_start->text() == ""
                ? -2
                : ui->string_Yrange_start->text().toDouble();
  y_end = ui->string_Yrange_end->text() == ""
              ? 2
              : ui->string_Yrange_end->text().toDouble();
  step = (fabs(x_start - x_end)) / 10000 ? (fabs(x_start - x_end)) / 10000 : 1;

  if (ui->graph_switch->isChecked()) {
    ui->grafic->clearGraphs();
    ui->grafic->xAxis->setRange(x_start, x_end);
    ui->grafic->yAxis->setRange(y_start, y_end);

    while (x_start <= x_end && Error != -1) {
      y_res = s21_SmartCalc(expression, x_start, &Error);

      if (Error == 0 && y_res >= y_start && y_res <= y_end) {
        y.push_back(y_res);
        x.push_back(x_start);
      } else if (Error == -1) {
        ui->string->setText("Error");
      }
      x_start += step;
    }

    ui->grafic->addGraph();
    ui->grafic->graph(0)->addData(x, y);
    ui->grafic->replot();
    x.clear();
    y.clear();

  } else {
    double res = s21_SmartCalc(expression, x_res, &Error);
    QString result = Error == 0 ? QString::number(res) : "Error";
    ui->string->setText(result);
  }
}

void MainWindow::on_pushButton_clicked() {
  this->close();
  bank->show();
}
