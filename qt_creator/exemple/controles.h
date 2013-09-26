#ifndef CONTROLES_H
#define CONTROLES_H

#include <QWidget>

namespace Ui {
	class Controles;
}

class Controles : public QWidget
{
	Q_OBJECT
	
public:
	explicit		Controles(int iInitWidth, int iInitIteration, QWidget *parent = 0);
					~Controles();

signals:
	void			SignalPlay();
	void			SignalPause();
	void			SignalIterationMaxChanged(int);
	void			SignalWidthChanged(int);

public slots:
    void			SlotUpdateButtonText(bool isActive);

private slots:
	void			on_button_clicked();
	void			on_iterationSlider_valueChanged(int value);
	void			on_widthSlider_valueChanged(int value);

private:
	Ui::Controles	*m_ui;
	bool			m_isRunning;
};

#endif // CONTROLES_H
