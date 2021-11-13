#pragma once
class View;
class Figure
{
public:
	static const int RECT = 1, ELLIPSE = 2, LINE = 3;
	Figure(int x, int y, int x2, int y2, COLORREF, COLORREF);
	~Figure();
	bool inside(int x, int y);
	void setView(View *);
	void setColor(COLORREF);
	void setBGColor(COLORREF);
	virtual void draw();
	virtual int getType();
	int m_x1, m_y1, m_x2, m_y2;
	bool is_group = 0;
	View *m_view = 0;
	COLORREF fig_pen_color;
	COLORREF fig_fill_color;
};


