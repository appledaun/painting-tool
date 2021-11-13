#include "stdafx.h"
#include "Rect.h"
#include "View.h"

Rect::Rect(int x, int y, int x2, int y2, COLORREF c, COLORREF bg_c)
	:Figure(x,y,x2,y2, c, bg_c)
{
	if (m_x1 > m_x2) {  // ��-�츦 �ٲ۴�.
		int t = m_x1; m_x1 = m_x2; m_x2 = t;
	}
	if (m_y1 > m_y2) {  // ��-�ϸ� �ٲ۴�.
		int t = m_y1; m_y1 = m_y2; m_y2 = t;
	}
}


Rect::~Rect()
{
}


void Rect::draw()
{	
	Figure::draw();
	/*
	���� Ŭ�������� 
	// xx�����Ƽ� �簢���� ä�� ���� �������� �ʾҴ�. ������ � ������ �׷ȴ��Ŀ� ���� ���� �޶����� �ȴ�.
	m_view->setPenColor(fig_pen_color);
	m_view->setFillColor(RGB(255, 255, 255));  //  ���� ��� �簢���� ä����� �� ������ �غ���.
	*/
	m_view-> drawRectangle(m_x1, m_y1, m_x2, m_y2);
	if (is_group) {
		SIZE s = m_view->textSize("group");
		int xoff = ((m_x2 - m_x1) - s.cx) / 2;
		int yoff = ((m_y2 - m_y1) - s.cy) / 2;
		m_view->setTextBkColor(fig_fill_color);
		m_view->drawText("group", m_x1 + xoff, m_y1 + yoff);
	}
}

int Rect::getType() {
	return Figure::RECT;
}
