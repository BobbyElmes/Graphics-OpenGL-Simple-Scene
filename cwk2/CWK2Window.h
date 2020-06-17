#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QBoxLayout>
#include <QTimer>
#include <QInputDialog>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include "CWK2Widget.h"

class CWK2Window: public QWidget
	{
	public:



	CWK2Window(QWidget *parent);
	~CWK2Window();



	QMenuBar *menuBar;

		QMenu *fileMenu;

			QAction *actionQuit;


	QBoxLayout *windowLayout;


	CWK2Widget *cubeWidget;
	//slider for animation
	QSlider *nSlider;

	//for changing the power the ball is kicked with
	QDoubleSpinBox * power;
	QPushButton * powerButton;
	//for choosing shirt colour
	QComboBox * colourChoice;
	QLabel * powerHeader;
	QLabel *colourHeader;


	// timer for movement and globe rotation
	QTimer* timerr;


	void ResetInterface();
	};

#endif
