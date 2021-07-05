#include <QApplication>

#include "controller.h"
#include "model.h"
#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QPalette pal = a.palette();
  pal.setColor(QPalette::Window, QColor::fromRgb(245, 245, 245));
  a.setPalette(pal);

  QFile styleFile(":/style/style.qss");
  if (styleFile.open(QIODevice::ReadOnly)) {
    QTextStream textStream(&styleFile);
    QString styleSheet = textStream.readAll();
    styleFile.close();
    a.setStyleSheet(styleSheet);
  }

  model m;
  controller c;
  view w;

  c.set_model(&m);
  c.set_view(&w);
  w.set_controller(&c);
  w.show();

  w.setWindowIcon(QIcon(":/icon/icon.png"));

  return a.exec();
}
