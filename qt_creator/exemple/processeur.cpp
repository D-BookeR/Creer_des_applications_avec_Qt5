#include "processeur.h"
#include <QDebug>
#include <QtMath>

Processeur::Processeur(int iInitWidth, int iInitIter, QObject *parent)
	:
	QObject(parent),
	m_iGenerationCount(0),
	m_iGenerationMax(iInitIter),
	m_iWidth(iInitWidth)
{
	connect(&m_timer, &QTimer::timeout, this, &Processeur::SlotGenerateNext);
}

QPointF Processeur::calculatePeak(QPointF pointA, QPointF pointB)
{
	return QPointF(
					(pointA.x()+pointB.x())*qCos(M_PI/3) - (pointB.y()-pointA.y())*-qSin(M_PI/3),
					(pointA.y()+pointB.y())*qCos(M_PI/3) + (pointB.x()-pointA.x())*-qSin(M_PI/3)
				);
}

void Processeur::initGenZero()
{
	m_lineList.clear();
	QPointF p1(0.0, 0.0);
	QPointF p2(m_iWidth, 0.0);
	QPointF peak = calculatePeak(p1, p2);

	m_lineList.append( QLineF(p2, p1) ); //sens des aiguilles d'une montre
	m_lineList.append( QLineF(p1, peak) );
	m_lineList.append( QLineF(peak, p2) );
}

void Processeur::SlotGenerateNext()
{
	Q_ASSERT(m_iGenerationMax > 0);

	if (m_iGenerationCount == 0) {
		initGenZero();
	} else {
		QList<QLineF>	newLineList;

		for (int i=0; i<m_lineList.size(); ++i) {
			QPointF p1 = m_lineList.at(i).p1();
			QPointF p2 = m_lineList.at(i).p2();

			QPointF p3(p1.x()+(p2.x()-p1.x())/3.0,		p1.y()+(p2.y()-p1.y())/3.0);
			QPointF p4(p1.x()+2*(p2.x()-p1.x())/3.0,	p1.y()+2*(p2.y()-p1.y())/3.0);

			QPointF peak = calculatePeak(p3, p4);

			/*

					 sommet
					   /\
					  /  \
			p1-----p3/    \p4-----p2

			*/

			//1er tiers
			newLineList.append(QLineF(p1, p3));
			//1er coté du sommet
			newLineList.append(QLineF(p3, peak));
			//2nd coté du sommet
			newLineList.append(QLineF(peak, p4));
			//dernier tiers
			newLineList.append(QLineF(p4, p2));
		}

		m_lineList = newLineList;
	}

	emit SignalDataChanged(m_lineList);

	m_iGenerationCount = (m_iGenerationCount+1)%m_iGenerationMax;
}

void Processeur::SlotSetMaxValue(int iGenMax)
{
	m_iGenerationMax = iGenMax;
}

void Processeur::SlotSetWidth(int iWidth)
{
	m_iWidth = iWidth;
    m_iGenerationCount = 0;
}

void Processeur::SlotStartAnim()
{
	SlotGenerateNext();
	m_timer.start(1000);
}

void Processeur::SlotStopAnim()
{
	m_timer.stop();
}
