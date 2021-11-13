#include "stdafx.h"
#include "CLine.h"
#include "View.h"

CLine::CLine(int x1, int y1, int x2, int y2, COLORREF c, COLORREF bg_c)
	:Figure(x1, y1, x2, y2, c, bg_c)
{
}


CLine::~CLine()
{
}


void CLine::draw()
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	Figure::draw();
	/*
	���� Ŭ��������
	// xx�����Ƽ� �簢���� ä�� ���� �������� �ʾҴ�. ������ � ������ �׷ȴ��Ŀ� ���� ���� �޶����� �ȴ�.
	m_view->setPenColor(fig_pen_color);
	m_view->setFillColor(RGB(255, 255, 255));  //  ���� ��� �簢���� ä����� �� ������ �غ���.
	*/
	m_view->drawLine(m_x1, m_y1, m_x2, m_y2);
	if (is_group) {
		SIZE s = m_view->textSize("group");
		int xoff = ((m_x2 - m_x1) - s.cx) / 2;
		int yoff = ((m_y2 - m_y1) - s.cy) / 2;
		m_view->setTextBkColor(fig_fill_color);
		m_view->drawText("group", m_x1 + xoff, m_y1 + yoff);
	}
}

int CLine::getType() {
	return Figure::LINE;
}