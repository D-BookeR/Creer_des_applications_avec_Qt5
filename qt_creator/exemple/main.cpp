#include "widget.h"
#include "controles.h"
#include "processeur.h"
#include <QApplication>
#include <QDesktopWidget>

#define DEFAULT_WIDTH		600
#define DEFAULT_ITER_MAX	4

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QDesktopWidget desktop;
	QRectF screenRect = desktop.availableGeometry();

	Controles controls(DEFAULT_WIDTH, DEFAULT_ITER_MAX);
	Processeur processor(DEFAULT_WIDTH, DEFAULT_ITER_MAX);
	Widget w;

	QObject::connect(&controls, &Controles::SignalWidthChanged, &processor, &Processeur::SlotSetWidth);
	QObject::connect(&controls, &Controles::SignalPlay, &processor, &Processeur::SlotStartAnim);
	QObject::connect(&controls, &Controles::SignalPause, &processor, &Processeur::SlotStopAnim);
	QObject::connect(&controls, &Controles::SignalIterationMaxChanged, &processor, &Processeur::SlotSetMaxValue);
	QObject::connect(&processor, &Processeur::SignalDataChanged, &w, &Widget::SlotUpdateLines);

	w.resize(800, 800);
	controls.show();
	w.show();

	controls.move(screenRect.width()/2 - (controls.frameSize().width()+w.frameSize().width())/2, 50);
	w.move(controls.x()+controls.frameSize().width(), 50);

	QObject::connect(&a, &QGuiApplication::lastWindowClosed, &QCoreApplication::quit);

	return a.exec();
}
