#pragma once
#include "tbutton.h"
#include <list>
#include <string>
#include "container.h"

using namespace std;

class View;
class Toolbar :public Container {
public:
	Toolbar();
	Toolbar(View * v);
	void addButton(TButton *);
	//MyButton * findButton(MyEvent e);
	void draw();
private:
	View * m_view;
	//list<TButton *> m_CompList;
	int tButtonNum = 0;
	
 };