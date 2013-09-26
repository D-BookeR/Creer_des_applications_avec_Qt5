#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QLineF>

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit		Widget(QWidget *parent = 0);
					~Widget();

protected:
	void			paintEvent(QPaintEvent *event);

private:
	void			calculateBoundingRect();

public slots:
	void			SlotUpdateLines(const QList<QLineF> &lines);

private:
	QList<QLineF>	m_linesToDrawList;
	QRectF			m_boundingRect;
};

#endif // WIDGET_H
