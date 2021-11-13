#include "stdafx.h"
#include "container.h"
#include "Misc.h"
#include "tbutton.h"
#include "Figure.h"
//#include "MyButton.h"
#include <string>

Container::Container() {

}
Container::Container(View * v) {

}
Container::Container(std::string s, View * v) : Component(s, v) {

}

void Container::addComponent(Component * t) {
	m_CompList.push_back(t);
	/*
	응용
	t->setLocation(tButtonNum);
	tButtonNum++;
	*/
}

Component * Container::findComponent(MyEvent e) {
	// TODO: 여기에 구현 코드 추가.
	for (auto b : m_CompList) {
		if (b->inside(e.x, e.y)) return b;
	}
	return nullptr;

}

Figure * Container::findFigure(int x, int y) {
	
	list<Figure *>::reverse_iterator i;
	for (i = m_figList.rbegin(); i != m_figList.rend(); i++) {
		debugOutput("findFigure\n");
		if ((*i)->inside(x, y)) {
			debugOutput("Fig inside\n");
			return (*i);
		}
	}
	return nullptr;
	/*
	for (auto b : m_figList) {
		debugOutput("findingFigure\n");

		if (b->inside(e.x, e.y)) {
			debugOutput("Fig inside\n");
			return b;
		}
	}
	return nullptr;
	*/
}

void Container::openMenus() {
	for (auto b : m_CompList) {
		b->draw();
	}
}