#include "stdafx.h"
#include "MyButton.h"
#include "View.h"

MyButton::MyButton() 
{
}

MyButton::MyButton(std::string s, View * v): Component(s, v) {

}

MyButton::~MyButton()
{
}

// ���� �׸��� �Լ� draw
void MyButton::draw()
{
	//Component::draw();
}

// ��ư ���� ���콺�� �ö���� �� �׸� �׸��� �Լ�.
void MyButton::tempDraw() {
	
	//Component::tempDraw();
}

/*
���� Ŭ�������� 
// ���콺�� ��ư ��ġ�� �ִ��� �Ǻ��ϴ� �Լ�
bool MyButton::inside(int x, int y) {
	return (m_x <= x && x <= m_x + m_sizex
		&& m_y <= y && y <= m_y + m_sizey);
}

void MyButton::action() {
	debugOutput(m_title);
	m_view->buttonActions(this);
}
*/
