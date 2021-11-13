#include "stdafx.h"
#include "toolbar.h"
#include "Misc.h"

Toolbar::Toolbar() {

}

Toolbar::Toolbar(View * v) {
	m_view = v;
}

//버튼 추가 하기
void Toolbar::addButton(TButton * t) {
	Container::addComponent(t); //m_CompList.push_back(t);
	t->setLocation(tButtonNum);
	tButtonNum++;
}


/*
상위 클래스에서 
//클릭된 곳이 버튼인가?
MyButton * Toolbar::findButton(MyEvent e)
{
	// TODO: 여기에 구현 코드 추가.
	for (auto b : m_CompList) {
		if (b->inside(e.x, e.y)) return (TButton *)b;
	}
	return nullptr;
}
*/

//툴바 그리기
void Toolbar::draw() {
	m_view->setPenColor(RGB(230, 230, 230));
	m_view->setFillColor(RGB(230, 230, 230));
	m_view->drawRectangle(0, 32, m_view->getWindowWidth(), 64);
	for (auto b : m_CompList) {
		b->draw();
	}
}