#include "stdafx.h"
#include "toolbar.h"
#include "Misc.h"

Toolbar::Toolbar() {

}

Toolbar::Toolbar(View * v) {
	m_view = v;
}

//��ư �߰� �ϱ�
void Toolbar::addButton(TButton * t) {
	Container::addComponent(t); //m_CompList.push_back(t);
	t->setLocation(tButtonNum);
	tButtonNum++;
}


/*
���� Ŭ�������� 
//Ŭ���� ���� ��ư�ΰ�?
MyButton * Toolbar::findButton(MyEvent e)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	for (auto b : m_CompList) {
		if (b->inside(e.x, e.y)) return (TButton *)b;
	}
	return nullptr;
}
*/

//���� �׸���
void Toolbar::draw() {
	m_view->setPenColor(RGB(230, 230, 230));
	m_view->setFillColor(RGB(230, 230, 230));
	m_view->drawRectangle(0, 32, m_view->getWindowWidth(), 64);
	for (auto b : m_CompList) {
		b->draw();
	}
}