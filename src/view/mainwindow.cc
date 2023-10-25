#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, s21::Controller *c)
    : QMainWindow(parent), ui_(new Ui::MainWindow), controll_(c) {
  ui_->setupUi(this);
  bank_ = new BankWindow(nullptr, controll_);
  SetButtons();
  ui_->graph_switch->setCheckable(true);
}

MainWindow::~MainWindow() {
  delete ui_;
  delete bank_;
}

void MainWindow::SetButtons() {
  for (QAbstractButton *button : ui_->buttonGroup->buttons())
      connect(button, &QPushButton::clicked, this, &MainWindow::NumbersOperands);

  for (QAbstractButton *button : ui_->buttonGroup_2->buttons())
      connect(button, &QPushButton::clicked, this, &MainWindow::Maths);

  connect(ui_->pushButton_ac, &QPushButton::clicked, this, &MainWindow::ACClicked);
  connect(ui_->pushButton_c, &QPushButton::clicked, this, &MainWindow::CClicked);

  connect(ui_->pushButton_res, &QPushButton::clicked, this, &MainWindow::Result);
}

void MainWindow::NumbersOperands() {
  QPushButton *button_numb_oper = (QPushButton *)sender();
  ui_->string->setText(ui_->string->text() + button_numb_oper->text());
}

void MainWindow::Maths() {
  QPushButton *button_math = (QPushButton *)sender();

  QString new_string = button_math->text();
  new_string.chop(2);

  ui_->string->setText((ui_->string->text() + new_string));
}

void MainWindow::ACClicked() {
  ui_->string->setText("");
  x_.clear();
  y_.clear();
  ui_->grafic->clearGraphs();
}

void MainWindow::CClicked() {
  QString new_str = (QString)ui_->string->text();
  new_str.chop(1);
  ui_->string->setText(new_str);
}

void MainWindow::Result() {
  str_ = ui_->string->text().toStdString();

  x_res_ = ui_->string_X->text() == "" ? 0 : ui_->string_X->text().toDouble();

  if (ui_->graph_switch->isChecked()) {
    SetPoints();
    PaintGraf();
  } else {
    controll_->StartWork(str_, x_res_);
    QString result = QString::fromStdString(controll_->Result());
    ui_->string->setText(result);
  }
}

void MainWindow::PaintGraf() {

  ui_->grafic->clearGraphs();

  ui_->grafic->xAxis->setRange(x_start_, x_end_);
  ui_->grafic->yAxis->setRange(y_start_, y_end_);

  while (x_start_ <= x_end_) {
    controll_->StartWork(str_, x_start_);
    y_res_ = controll_->ResultNum();

    if (controll_->Status() && y_res_ >= y_start_ && y_res_ <= y_end_) {
      y_.push_back(y_res_);
      x_.push_back(x_start_);
    } else if (!controll_->Status()) {
      ui_->string->setText("Error");
    }
    x_start_ += step_;
  }

  ui_->grafic->addGraph();
  ui_->grafic->graph(0)->addData(x_, y_);
  ui_->grafic->replot();
  x_.clear();
  y_.clear();
}

void MainWindow::SetPoints() {
  x_start_ = ui_->string_Xrange_start->text() == ""
                 ? -2
                 : ui_->string_Xrange_start->text().toDouble();
  x_end_ = ui_->string_Xrange_end->text() == ""
               ? 2
               : ui_->string_Xrange_end->text().toDouble();
  y_start_ = ui_->string_Yrange_start->text() == ""
                 ? -2
                 : ui_->string_Yrange_start->text().toDouble();
  y_end_ = ui_->string_Yrange_end->text() == ""
               ? 2
               : ui_->string_Yrange_end->text().toDouble();
  step_ =
      (fabs(x_start_ - x_end_)) / 10000 ? (fabs(x_start_ - x_end_)) / 10000 : 1;
}

void MainWindow::on_CreditCalc_clicked() {
  this->close();
  bank_->show();
}
