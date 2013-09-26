#include "controles.h"
#include "ui_controles.h"

//------------------------------- Constructeur ---------------------------------

Controles::Controles(int iInitWidth, int iInitIteration, QWidget *parent)
	:
	QWidget(parent, Qt::Tool),
	m_ui(new Ui::Controles),
	m_isRunning(false)
{
	m_ui->setupUi(this);

	m_ui->widthSlider->setValue(iInitWidth);
	m_ui->iterationSlider->setValue(iInitIteration);
	SlotUpdateButtonText(false);
}

//------------------------------- Destructeur ----------------------------------

Controles::~Controles()
{
	delete m_ui;
}

//--------------------------------- Méthodes -----------------------------------

void Controles::SlotUpdateButtonText(bool isActive)
{
    if (isActive)
		m_ui->button->setText("Pause");
	else
		m_ui->button->setText("Démarrer");
}

//---------------------------------- Slots -------------------------------------

void Controles::on_button_clicked()
{
	m_isRunning = !m_isRunning;
	SlotUpdateButtonText(m_isRunning);
	m_ui->widthSlider->setEnabled(!m_isRunning);

	if (m_isRunning) {
		emit SignalPlay();
	} else {
		emit SignalPause();
	}
}

void Controles::on_iterationSlider_valueChanged(int value)
{
	emit SignalIterationMaxChanged(value);
}

void Controles::on_widthSlider_valueChanged(int value)
{
	emit SignalWidthChanged(value);
}
