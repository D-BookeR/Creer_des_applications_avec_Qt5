#ifndef PROCESSEUR_H
#define PROCESSEUR_H

#include <QObject>
#include <QList>
#include <QLineF>
#include <QTimer>

class Processeur : public QObject
{
	Q_OBJECT
public:
	explicit		Processeur(int iInitWidth, int iInitIter, QObject *parent = 0);

signals:
	void			SignalDataChanged(const QList<QLineF> &lines);

private:
	void			initGenZero();
	QPointF			calculatePeak(QPointF pointA, QPointF pointB);

public slots:
	void			SlotGenerateNext();
	void			SlotSetMaxValue(int iGenMax);
	void			SlotSetWidth(int iWidth);
	void			SlotStartAnim();
	void			SlotStopAnim();

private:
	int				m_iGenerationCount;
	int				m_iGenerationMax;
	int				m_iWidth;
	QList<QLineF>	m_lineList;
	QTimer			m_timer;
};

#endif // PROCESSEUR_H
