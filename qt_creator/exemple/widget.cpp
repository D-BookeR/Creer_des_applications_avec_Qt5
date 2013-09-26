#include "widget.h"
#include <QPainter>
#include <QDebug>

Widget::Widget(QWidget *parent)
	:
	QWidget(parent)
{
	this->setStyleSheet("background-color: white;");
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.save();
	painter.setRenderHint(QPainter::Antialiasing);

	painter.translate(this->width()/2.0 - m_boundingRect.center().x(),
					  this->height()/2.0 - m_boundingRect.center().y());

	painter.setPen(QPen(Qt::black, 0.0));

	for (int i=0; i<m_linesToDrawList.size(); ++i) {
		painter.drawLine(m_linesToDrawList.at(i));
	}

	painter.restore();
}


void Widget::calculateBoundingRect()
{
	qreal xMin = INT_MAX, xMax = INT_MIN, yMin = INT_MAX, yMax = INT_MIN;

	for (int i=0; i<m_linesToDrawList.size(); ++i) {
		xMin = qMin(xMin, m_linesToDrawList.at(i).x1());
		xMin = qMin(xMin, m_linesToDrawList.at(i).x2());

		xMax = qMax(xMax,  m_linesToDrawList.at(i).x1());
		xMax = qMax(xMax,  m_linesToDrawList.at(i).x2());

		yMin = qMin(yMin, m_linesToDrawList.at(i).y1());
		yMin = qMin(yMin, m_linesToDrawList.at(i).y2());

		yMax = qMax(yMax,  m_linesToDrawList.at(i).y1());
		yMax = qMax(yMax,  m_linesToDrawList.at(i).y2());
	}

	m_boundingRect.setLeft(xMin);
	m_boundingRect.setTop(yMin);
	m_boundingRect.setRight(xMax);
	m_boundingRect.setBottom(yMax);
}

void Widget::SlotUpdateLines(const QList<QLineF> &lines)
{
	m_linesToDrawList = lines;
	calculateBoundingRect();
	update();
}
