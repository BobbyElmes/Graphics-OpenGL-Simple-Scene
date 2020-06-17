#include "CWK2Widget.h"
#include <GL/glu.h>
#include <QGLWidget>
#include <QSlider>
#include <cmath>
#include <iostream>

#include <QImage>
#include "Image.h"

//global variables
double thighLength = 3.0;
double shinLength = 3.0;
double globalPLayerX = -6.;
double globalPLayerY = 1.;
double globalPLayerZ= -1.;
double rightThighAngle = 0.;
double rightShinAngle = 0.;
double rightFootAngle = 0.;
double footballPos[3] = {0.,0.,0.};
//power multiplier for kick
double power = 0.005;
//value saved until button is pressed to change kick power
double tempPower = 10.0;
double circleAngle = 0.0;
double saveXZ[2] = {0.0,0.0};
double globeRotate = 0.;
//initial player shirt colour is red
char shirtColour = 'r';
GLuint textures[3];



int currentBond = 0;

// used to define material layout
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


static materialStruct redMaterial = {
  { 0.0, 0.0, 0.0, 1.0},
  { 0.5, 0.0, 0.0, 1.0},
  { 0.7, 0.6, 0.6, 1.0},
  32.0
};

static materialStruct blueMaterial = {
  { 0.0, 0.1, 0.6, 1.0},
  { 0.0, 0.5, 0.5, 1.0},
  { 0.5, 0.5, 0.5, 1.0},
  32.0
};

static materialStruct yellowMaterial = {
  { 0.0, 0.0, 0.0, 1.0},
  { 0.5, 0.5, 0.0, 1.0},
  { 0.6, 0.6, 0.0, 1.0},
  10.0
};

static materialStruct blackMaterial = {
  { 0.02, 0.02, 0.02, 1.0},
  { 0.01, 0.01, 0.01, 1.0},
  { 0.04, 0.04, 0.04, 1.0},
  2.0
};

static materialStruct greenMaterial = {
  { 0.02, 0.17, 0.02, 0.5},
  { 0.01, 0.6, 0.07, 0.5},
  { 0.6, 0.7, 0.6, 0.5},
  76.0
};

static materialStruct skinMaterial = {
  { 0.25, 0.2, 0.2, 0.9},
  { 1.0, 0.8, 0.8, 0.9},
  { 0.3, 0.3, 0.3, 0.9},
  11.0
};

static materialStruct whiteMaterial = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0
};

// constructor
CWK2Widget::CWK2Widget(QWidget *parent)
  : QGLWidget(parent),
    armangle(0),
    _image("./2.ppm"),
    _image2("Moi.ppm"),
    _image3("earth.ppm")
	{
    //each element of the football player is stored in an array of gluQuadratics
    for(int i = 0; i < 11; i++){
      player[i]=gluNewQuadric();
    }


	}


void CWK2Widget::initializeGL()
	{
	glClearColor(0.3, 0.3, 0.3, 0.0);
  glEnable(GL_TEXTURE_2D);
  glGenTextures(3, textures);

  //setting up different textures so they can easily be switched between in the textures array
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image.Width(), _image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image.imageField());
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image2.Width(), _image2.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image2.imageField());
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, textures[2]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image3.Width(), _image3.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image3.imageField());
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


 	}

CWK2Widget::~CWK2Widget()
{
  for(int i = 0; i < 11 ; i++)
    gluDeleteQuadric(player[i]);
}

//updates regularly over time, used to move the player around the ball
//whilst keeping him facing the ball, using some trig
void CWK2Widget::updateAngle(){
  double newx, newz, radius;

  radius = (double)sqrt(37);
  newz = (double)cos(((circleAngle* M_PI ) / 180.)) * radius;
  newx = (double)sin(((circleAngle* M_PI ) / 180.)) * radius;
  circleAngle += 1;
  globalPLayerX = newx;
  globalPLayerZ = newz;
  this->repaint();
}

//Changes values for the kick slider animation
void CWK2Widget::kick(int i){
  // value of 'i' detarmines the stage the animation is at
  if(i < 90){
    armangle = i*1.4;
    rightThighAngle = -i;
    rightShinAngle = -i*1.5;
    rightFootAngle = -i;
  }
  else{
    if(i < 250){
      armangle = 252 - i*1.4;
      rightThighAngle = -180 +i;

      if(i < 180){
        rightFootAngle = -180 +i;
        rightShinAngle = -270 + i*1.5;
      }
      else
        rightShinAngle = -180 +i;
    }
  }
  //saving position player is in where ball is kicked to determine
  //direction of travel
  if(i < 230){
    saveXZ[0] = globalPLayerX;
    saveXZ[1] = globalPLayerZ;
  }
  if(i > 230){
    footballPos[0] = (double)(i-230)*power*(-saveXZ[0] * fabs(saveXZ[0]+saveXZ[1]/saveXZ[1]));
    footballPos[2] = (i-230) * power*(-saveXZ[1] * fabs((saveXZ[1]+saveXZ[0])/saveXZ[0]));
    footballPos[1] = (double)(i-230) * power*10;

  }

  this->repaint();
}

//called when button is pressed to change the power of the player kick
void CWK2Widget::changePower(){
  power = tempPower;
}

//called every time the power value gets changed to stay up to date
void CWK2Widget::inputPower(double p){
  tempPower = 0.0005*p;
}

//called when the user changes the shirt colour drop down value
void CWK2Widget::changeShirtColour(int x){
  if(x == 0){
    shirtColour = 'r';
  }
  if(x == 1){
    shirtColour = 'l';
  }
  if(x == 2){
    shirtColour = 'y';
  }
}

// called every time the widget is resized
void CWK2Widget::resizeGL(int w, int h)
	{
	glViewport(0, 0, w, h);
	GLfloat light_pos[] = {1., 0.5, 1., 0.};

	glEnable(GL_LIGHTING); // enable lighting
        glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	materialStruct* p_front = &whiteMaterial;

       	glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
	glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
       	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,150.);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);

	}

//Creates the cube player head, with the inner facing side being the stunning 'de Kamps' face
void CWK2Widget::head(GLUquadricObj* head){
  GLfloat normals[][3] = { {1., 0. ,0.}, {-1., 0., 0.}, {0., 0., 1.}, {0., 0., -1.}, {0, 1, 0}, {0, -1, 0} };


  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f( 1.0,  1.0,  1.0);
  glEnd();



  glNormal3fv(normals[3]);
  glBegin(GL_POLYGON);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
  glEnd();


  glNormal3fv(normals[2]);
  glBegin(GL_POLYGON);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f( 1.0, -1.0, 1.0);
    glVertex3f( 1.0,  1.0, 1.0);
    glVertex3f(-1.0,  1.0, 1.0);
  glEnd();


  glNormal3fv(normals[1]);
  glBegin(GL_POLYGON);
    glVertex3f( -1.0, -1.0,  1.0);
    glVertex3f( -1.0, -1.0, -1.0);
    glVertex3f( -1.0,  1.0, -1.0);
    glVertex3f( -1.0,  1.0,  1.0);
  glEnd();


  glNormal3fv(normals[4]);
  glBegin(GL_POLYGON);
    glVertex3f(  1.0,  1.0,  1.0);
    glVertex3f(  1.0,  1.0, -1.0);
    glVertex3f( -1.0,  1.0, -1.0);
    glVertex3f( -1.0,  1.0,  1.0);
  glEnd();


  glNormal3fv(normals[5]);
  glBegin(GL_POLYGON);
    glVertex3f(  1.0,  -1.0,  1.0);
    glVertex3f(  1.0,  -1.0, -1.0);
    glVertex3f( -1.0,  -1.0, -1.0);
    glVertex3f( -1.0,  -1.0,  1.0);
  glEnd();

}

//creates player body
void CWK2Widget::torso(GLUquadricObj* torso){
  gluCylinder(torso,1.2,0.9,4,20,5);
}

//creates a thigh
void CWK2Widget::Thigh(GLUquadricObj* thigh){
  gluCylinder(thigh,0.5,0.5,thighLength,20,4);
}

//creates a shin
void CWK2Widget::Shin(GLUquadricObj* shin){
  gluCylinder(shin,0.5,0.3,shinLength,20,4);
}

//creates a pointy foot
void CWK2Widget::Foot(GLUquadricObj* foot){
  gluCylinder(foot,0.3,0.1,1,4,4);
}

//creates the shoulders
void CWK2Widget::shoulders(GLUquadricObj* shoulders){
  gluCylinder(shoulders,0.5,0.5,3,20,4);
}



//Creates a sphere made of triangles, phi and theta define the smoothness
//of the sphere and 'size' defines how big it is
void CWK2Widget::createPolySphere(int phi, int theta, double size){

  for(int lon = 0; lon < phi; lon++)
    for(int lat = 0; lat < theta; lat++){
      float phi2   = 2*M_PI/phi;
      float theta2 = M_PI/theta;
      glBegin(GL_TRIANGLES);
      double x, y, z, tempLat, tempLon;
      for(int i = 0; i < 6 ; i++){

        tempLat = lat;
        tempLon = lon;

        if(i == 1)
          tempLon += 1;
        if(i == 2 || i == 4){
          tempLat += 1;
          tempLon += 1;
        }
        if(i == 5)
          tempLat += 1;

        x = cos(tempLon*phi2)*sin(tempLat*theta2)*size;
        y = sin(tempLon*phi2)*sin(tempLat*theta2)*size;
        z = cos(tempLat*theta2)*size;

        glNormal3f(x,y,z);
        glTexCoord2f((float)(tempLon)/phi, (float)(tempLat)/theta);
        glVertex3f(x,y,z);
      }

      glEnd();
    }
}

//creates an arm
void CWK2Widget::Arm(GLUquadricObj* arm){
  gluCylinder(arm,0.35,0.35,3,20,4);
}

//defines the floor of the scene
void CWK2Widget::floor(){
  GLfloat normals[3] =  {0, 1, 0};

  glNormal3fv(normals);
  glBegin(GL_POLYGON);
    glVertex3f(  50.0,  -9.0,  50.0);
    glVertex3f(  50.0,  -9.0, -50.0);
    glVertex3f( -50.0,  -9.0, -50.0);
    glVertex3f( -50.0,  -9.0,  50.0);
  glEnd();


}

//used to change the current material for any newly rendered objects
void CWK2Widget::changeMaterial(char s){
  materialStruct* p_front = &whiteMaterial;
  if(s == 'r'){
    	p_front = &redMaterial;
  }
  if(s == 's'){
      p_front = &skinMaterial;
  }
  if(s == 'b'){
      p_front = &blackMaterial;
  }
  if(s == 'g'){
      p_front = &greenMaterial;
  }
  if(s == 'l'){
      p_front = &blueMaterial;
  }
  if(s == 'y'){
      p_front = &yellowMaterial;
  }
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
}


// paints the widget
void CWK2Widget::paintGL()
	{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      	glShadeModel(GL_SMOOTH);


      	glMatrixMode(GL_MODELVIEW);
       	glEnable(GL_DEPTH_TEST);


        //creating football
        glPushMatrix(); // save rotation and transformations
        glTranslatef(0., -6., 0.);
        glTranslatef(footballPos[0],footballPos[1], footballPos[2]);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        this->createPolySphere(30,30,1.);
        glPopMatrix();  // restore original state



  changeMaterial(shirtColour);
	// creating body
	glPushMatrix();
        glTranslatef(globalPLayerX,globalPLayerY,globalPLayerZ);
        glRotatef(circleAngle+90,0.,1.,0.);
      	glRotatef(90.,1.,0.,0.);
	this->torso(player[2]);
	glPopMatrix();


	changeMaterial(shirtColour);

	// shoulder
	glPushMatrix();
  glTranslatef(globalPLayerX,globalPLayerY,globalPLayerZ);
  glRotatef(circleAngle+90,0.,1.,0.);
      	glTranslatef(0.,0.,-3./2.);
	this->shoulders(player[1]);
	glPopMatrix();

  changeMaterial('s');

	// head
	glPushMatrix();
  glTranslatef(globalPLayerX,globalPLayerY,globalPLayerZ);
  glRotatef(circleAngle+90,0.,1.,0.);
	glTranslatef(0., 1.5, 0.);
	this->head(player[0]);
	glPopMatrix();

  changeMaterial(shirtColour);
	// arms
	glPushMatrix();
  glTranslatef(globalPLayerX,globalPLayerY,globalPLayerZ);
  glRotatef(circleAngle+90,0.,1.,0.);

	glRotatef(-(double)armangle,0.,0.,1.);
	glTranslatef(0.,0., 3/2.);
  glRotatef(90,1.,0.,0.);
	this->Arm(player[3]);
  glRotatef(-90,1.,0.,0.);
  glRotatef(2*(double)armangle,0.,0.,1.);
  glTranslatef(0.,0., -3);
  glRotatef(90,1.,0.,0.);


	this->Arm(player[4]);

	glPopMatrix();


  // thighs, shins and feet - more complicated as it deals with the animation of
  //the right leg which involves some trig
	glPushMatrix();
  glTranslatef(globalPLayerX,globalPLayerY,globalPLayerZ);
  glRotatef(circleAngle+90,0.,1.,0.);
	glTranslatef(0.,-4., 1);
       	glRotatef(90,1.,0.,0.);
        glRotatef(rightThighAngle,0.,1.,0.);
  changeMaterial('b');
	this->Thigh(player[5]);
  glRotatef(-rightThighAngle,0.,1.,0.);
  glTranslatef(thighLength*sin((rightThighAngle* M_PI ) / 180 ),0.,thighLength*cos((rightThighAngle* M_PI ) / 180 ));
  glRotatef(rightShinAngle,0.,1.,0.);
  changeMaterial('s');
  this->Shin(player[7]);
  glRotatef(-rightShinAngle,0.,1.,0.);
  glTranslatef(shinLength*sin((rightShinAngle* M_PI ) / 180 ),0.,shinLength*cos((rightShinAngle* M_PI ) / 180 ));
  glRotatef(90,0.,1.,0.);
  glRotatef(rightFootAngle,0.,1.,0.);
  changeMaterial('r');
  this->Foot(player[9]);
    glRotatef(-rightFootAngle,0.,1.,0.);
    glRotatef(-90,0.,1.,0.);
    glTranslatef(-shinLength*sin((rightShinAngle* M_PI ) / 180 ),0.,-shinLength*cos((rightShinAngle* M_PI ) / 180 ));
    glTranslatef(-thighLength*sin((rightThighAngle* M_PI ) / 180 ),0.,-thighLength*cos((rightThighAngle* M_PI ) / 180 ));

	glTranslatef(0.,-2.,0.);
  changeMaterial('b');
	this->Thigh(player[6]);
  glTranslatef(0.,0.,thighLength);
  changeMaterial('s');
  this->Shin(player[8]);
  glTranslatef(0.,0.,shinLength);
  glRotatef(90,0.,1.,0.);
  changeMaterial('r');
  this->Foot(player[10]);
	glPopMatrix();





  changeMaterial('g');
  //creates floor
  floor();
  //creates the spinning globe
  changeMaterial('w');
  glPushMatrix();
  glTranslatef(0., 20., 0.);
  glRotatef(globeRotate,0.,1.,0.);
  globeRotate++;
  glRotatef(90.,0.,0.,1.);
  glRotatef(90.,1.,0.,0.);
  glBindTexture(GL_TEXTURE_2D, textures[2]);
  this->createPolySphere(20,20,3.);
  glPopMatrix();

	glLoadIdentity();
        //set camera
       	gluLookAt(1.,1.,1., 0.0,0.0,0.0, 0.0,1.0,0.0);


	glFlush();

	}
