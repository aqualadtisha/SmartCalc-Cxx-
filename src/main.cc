#include "view/mainwindow.h"
#include "controller/calc_controller.h"
#include "model/calc_model.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  s21::SimpleCalcModel model;
  s21::CreditModel b_model;
  s21::Controller controller(&model, &b_model);
  QApplication a(argc, argv);
  MainWindow v(nullptr, &controller);
  QLocale::setDefault(QLocale::C);
  v.show();
  return a.exec();
}
