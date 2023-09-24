#include "bankwindow.h"

#include "mainwindow.h"
#include "ui_bankwindow.h"

BankWindow::BankWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::BankWindow) {
  ui->setupUi(this);
  ui->annuity->setCheckable(true);
  ui->differ->setCheckable(true);
}

BankWindow::~BankWindow() { delete ui; }

void BankWindow::on_pushButton_clicked() {
  MainWindow* main = new MainWindow;
  this->close();
  main->show();
}

void BankWindow::on_Result_clicked() {
  double sum = ui->SUM->text().toDouble();
  double percent = ui->percents->text().toDouble();
  int months = ui->Month->text().toInt();
  int type = 2;
  double table[months][5];
  RES_credit result;

  if (ui->annuity->isChecked()) type = 0;
  if (ui->differ->isChecked()) type = 1;
  result = s21_credit_calc(sum, months, percent, type, table);

  ui->MonthlyPayment->setText(QString::number(result.monthly_payment));
  ui->Overprice->setText(QString::number(result.overprice));
  ui->TotalPayment->setText(QString::number(result.total_payment));

  ui->tableWidget->setColumnCount(5);
  ui->tableWidget->setShowGrid(true);
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  QStringList headers;
  headers.append("Месяц");
  headers.append("Сумма платежа");
  headers.append("Основной долг");
  headers.append("Проценты");
  headers.append("Остаток долга");
  ui->tableWidget->setHorizontalHeaderLabels(headers);
  ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

  for (int i{0}; i < months; i++) {
    ui->tableWidget->insertRow(i);
    ui->tableWidget->setItem(
        i, 0, new QTableWidgetItem(QString::number(table[i][0])));
    ui->tableWidget->setItem(
        i, 1, new QTableWidgetItem(QString::number(table[i][1])));
    ui->tableWidget->setItem(
        i, 2, new QTableWidgetItem(QString::number(table[i][2])));
    ui->tableWidget->setItem(
        i, 3, new QTableWidgetItem(QString::number(table[i][3])));
    ui->tableWidget->setItem(
        i, 4, new QTableWidgetItem(QString::number(table[i][4])));
  }
}
