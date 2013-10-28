#include <QApplication>
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QMainWindow w;
  QLabel hello ( "Bonjour, je suis une application Qt !", &w );
  w.show();

  hello.setAlignment(Qt::AlignCenter);
  hello.resize(w.size());

  return a.exec();
}
