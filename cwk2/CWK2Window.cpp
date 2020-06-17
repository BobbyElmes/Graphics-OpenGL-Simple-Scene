#include "CWK2Window.h"
#include <iostream>
#include <QInputDialog>
#include <QString>


CWK2Window::CWK2Window(QWidget *parent)
	: QWidget(parent)
	{



	// window
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// main widget
	cubeWidget = new CWK2Widget(this);
	windowLayout->addWidget(cubeWidget);

	// animation slider
	nSlider = new QSlider(Qt::Horizontal);
        connect(nSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(kick(int)));
        windowLayout->addWidget(nSlider);
				nSlider->setMinimum(0);
				nSlider->setMaximum(500);
				nSlider->setValue(0);
	//power header
		powerHeader = new QLabel();
			powerHeader ->setText("POWER");
			powerHeader -> setFixedHeight(12);
			powerHeader -> setAlignment(Qt::AlignCenter);
			windowLayout->addWidget(powerHeader);
	//power input box
		power = new QDoubleSpinBox();
			connect(power, SIGNAL(valueChanged(double)), cubeWidget, SLOT(inputPower(double)));
			power->setValue(10.0);
			windowLayout->addWidget(power);
	//power button
		powerButton = new QPushButton();
			powerButton ->setText("CHANGE KICK POWER");
			connect(powerButton, SIGNAL(pressed()), cubeWidget, SLOT(changePower()));
			windowLayout->addWidget(powerButton);
	//colour header
		colourHeader = new QLabel();
			colourHeader ->setText("SET PLAYER'S SHIRT COLOUR");
			colourHeader -> setFixedHeight(30);
			colourHeader -> setAlignment(Qt::AlignCenter);
			windowLayout->addWidget(colourHeader);
	//colour dropdown
		colourChoice = new QComboBox();
			colourChoice->addItem(1 + " RED");
			colourChoice->addItem(2 + "  BLUE");
			colourChoice->addItem(3 + "   YELLOW");
			windowLayout->addWidget(colourChoice);
			connect(colourChoice, SIGNAL(currentIndexChanged(int)),  cubeWidget, SLOT(changeShirtColour(int)));
	//timer to update the scene
	timerr = new QTimer(this);
        connect(timerr, SIGNAL(timeout()),  cubeWidget, SLOT(updateAngle()));
        timerr->start(0);

	}

// destructor
CWK2Window::~CWK2Window()
	{
	  delete timerr;
	delete nSlider;
	delete cubeWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	}

// resets everything
void CWK2Window::ResetInterface()
	{
	nSlider->setMinimum(0);
	nSlider->setMaximum(500);
	nSlider->setValue(0);

	//CWK2Widget->update();
	update();
	}
