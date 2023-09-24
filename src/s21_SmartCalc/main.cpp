#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  QLocale::setDefault(QLocale::C);
  w.show();
  return a.exec();
}
