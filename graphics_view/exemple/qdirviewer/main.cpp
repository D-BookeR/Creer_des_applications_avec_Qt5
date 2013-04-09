#include <QApplication>
#include <QFileDialog>

//@extract-start Qt-commun-QGraphicsView-ex-main
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString selectedDir = QFileDialog::getExistingDirectory();
    if (selectedDir.isEmpty()) {
        return 0;
    }

    MainWindow w(selectedDir);
    QObject::connect(&a, &QCoreApplication::aboutToQuit, &w, &MainWindow::slotOnQuit);
    w.showMaximized();
    
    return a.exec();
}
//@extract-end
