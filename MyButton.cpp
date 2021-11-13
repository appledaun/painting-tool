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

// 평상시 그리는 함수 draw
void MyButton::draw()
{
	//Component::draw();
}

// 버튼 위로 마우스가 올라왔을 때 그림 그리는 함수.
void MyButton::tempDraw() {
	
	//Component::tempDraw();
}

/*
상위 클래스에서 
// 마우스가 버튼 위치에 있는지 판별하는 함수
bool MyButton::inside(int x, int y) {
	return (m_x <= x && x <= m_x + m_sizex
		&& m_y <= y && y <= m_y + m_sizey);
}

void MyButton::action() {
	debugOutput(m_title);
	m_view->buttonActions(this);
}
*/
