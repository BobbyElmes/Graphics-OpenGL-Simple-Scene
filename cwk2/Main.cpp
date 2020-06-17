#include <QApplication>
#include <QVBoxLayout>
#include "CWK2Window.h"

int main(int argc, char *argv[])
	{
	
	QApplication app(argc, argv);



       	CWK2Window *window = new CWK2Window(NULL);



	window->resize(512, 612);


	window->show();


	app.exec();


	delete window;


	return 0;
	}
