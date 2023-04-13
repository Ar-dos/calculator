#include <QApplication>

#include "calc.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  calc w;
  w.show();
  return a.exec();
}
