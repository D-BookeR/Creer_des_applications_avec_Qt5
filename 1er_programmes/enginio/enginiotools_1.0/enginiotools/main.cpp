#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QString locale = QLocale::system().name();

  QTranslator qtTranslator;
  qtTranslator.load("qt_" + locale,
          QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  app.installTranslator(&qtTranslator);

  QTranslator appTranslator;
  appTranslator.load("enginiotools_" + locale, QCoreApplication::applicationDirPath());
  app.installTranslator(&appTranslator);

  MainWindow w;
  w.show();

  return app.exec();
}
