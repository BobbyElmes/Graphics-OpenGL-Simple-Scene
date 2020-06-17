#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <GL/glut.h>
#include <QImage>
#include "Image.h"

class CWK2Widget: public QGLWidget
	{ //

	Q_OBJECT

	public:

	CWK2Widget(QWidget *parent);
	~CWK2Widget();

	public slots:
	void updateAngle();

	public slots:
        void kick(int i);
				void changePower();
				void inputPower(double p);
				void changeShirtColour(int x);


	protected:

	void initializeGL();

	void resizeGL(int w, int h);
	
	void paintGL();

	private:

	void head(GLUquadricObj* arm);
	void torso(GLUquadricObj* arm);
	void shoulders(GLUquadricObj* arm);
	void upper_arm_left();
	void lower_arm_left();
	void createPolySphere(int phi, int theta, double size);
	void bonds(int i);
	void Thigh(GLUquadricObj* thigh);
	void Shin(GLUquadricObj* shin);
	void Foot(GLUquadricObj* foot);
	void Arm(GLUquadricObj* arm);
	void loadTexture(GLuint texture, Image image);
	void changeMaterial(char s);
	void floor();

	GLUquadricObj* phead;
	GLUquadricObj* ptorso;
	GLUquadricObj* pshoulders;
	GLUquadricObj* pupperleft;
	GLUquadricObj* plowerleft;
	GLUquadricObj* thighRight;
	GLUquadricObj* thighLeft;
	GLUquadricObj* shinRight;
	GLUquadricObj* shinLeft;
	GLUquadricObj* footRight;
	GLUquadricObj* footLeft;
	GLUquadricObj* armLeft;
	GLUquadricObj* armRight;



	GLUquadricObj* football;
	GLUquadricObj*  player[11];
	Image   _image;
	Image   _image2;
	Image   _image3;

	int armangle;


	};

#endif
