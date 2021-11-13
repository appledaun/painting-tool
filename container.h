#pragma once
#include "component.h"
#include <list>

class MyEvent;
//class MyButton;
class Figure;
class View;

using namespace std;

class Container :public Component {
public:
	Container();
	Container(View *);
	Container(string, View *);
	virtual void addComponent(Component *);
	Component * findComponent(MyEvent e);
	Figure * findFigure(int x, int y);
	virtual void openMenus();

protected:
	list<Component *> m_CompList;
	std::list<Figure *> m_figList;

private:
};