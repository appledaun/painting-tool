#include "stdafx.h"
#include "Figure.h"
#include "View.h"

Figure::Figure(int x, int y, int x2, int y2, COLORREF c, COLORREF bg_c)
	:m_x1(x), m_y1(y), m_x2(x2), m_y2(y2), fig_pen_color(c), fig_fill_color(bg_c)
{

}


Figure::~Figure()
{
}

bool Figure::inside(int x, int y) {
	return ((m_x1 <= x) && (x <= m_x2) && (m_y1 <= y) && (y <= m_y2));
}

void Figure::setView(View *v) {
	m_view = v;
}

void Figure::setColor(COLORREF c) {
	fig_pen_color = c;
}

void Figure::setBGColor(COLORREF c) {
	fig_fill_color = c;
}

void Figure::draw() {

	//
	m_view->setPenColor(fig_pen_color);
	m_view->setFillColor(fig_fill_color); 
	
	
}

int Figure::getType() {
	return 3;
}


