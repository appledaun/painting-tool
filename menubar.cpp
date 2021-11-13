#include "stdafx.h"
#include "menubar.h"
#include "Misc.h"
#include "container.h"

MenuBar::MenuBar() {

}
MenuBar::MenuBar(View * v) {
	m_view = v;
}

//버튼 추가하기
void MenuBar::addMenu(Menu * m) {
	Container::addComponent(m); //m_CompList.push_back(t);
	//m_menuList.push_back(m);
	m->setLocation(menuNum);
	menuNum++;
}

//메뉴바 그리기
void MenuBar::draw() {
	m_view->setPenColor(RGB(230, 230, 230));
	m_view->setFillColor(RGB(230, 230, 230));
	m_view->drawRectangle(0, 0, m_view->getWindowWidth(), 32);
	/*
	for (auto b : m_menuList) {
		b->draw();
	}
	*/
	for (auto b : m_CompList) {
		b->draw();
	}
}

void MenuBar::close_menu() {
	for (auto b : m_CompList) {
		Menu * m = (Menu *)b;
		m->close_menu();
	}
}