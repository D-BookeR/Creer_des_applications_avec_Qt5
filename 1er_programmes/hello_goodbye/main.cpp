#include <QApplication>
#include <QMainWindow>
#include <QPushButton>


void init(QMainWindow *w)
{
  QPushButton *bt = new QPushButton( "Bonjour, Qt !", w );

  QObject::connect(bt, &QPushButton::clicked, &QApplication::quit);
  QObject::connect(bt, &QPushButton::pressed, [=](){ bt->setText("Bye!"); } );

  w->show();
  bt->resize(w->size());
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QMainWindow w;
  init(&w);

  return a.exec();
}
