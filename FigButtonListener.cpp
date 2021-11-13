#include "FigButtonListener.h"
#include "View.h"
#include "tbutton.h"
#include "menuItem.h"
#include "component.h"
#include "Figure.h"



FigButtonListener::FigButtonListener(View * v)
{
	m_view = v;
}


FigButtonListener::~FigButtonListener()
{
}

void FigButtonListener::actionPerformed(Component * b) {
	debugOutput("figlistener\n");
	//b = (TButton *)b;
	if (b == nullptr)
		return;
	if (b == m_view->btnRect || b == m_view->btnR) {
		m_view->setCurrentFig(Figure::RECT);
	}
	else if (b == m_view->btnEllipse || b == m_view->btnE) {
		m_view->setCurrentFig(Figure::ELLIPSE);
	}
	else if (b == m_view->btnLine || b == m_view->btnL) {
		m_view->setCurrentFig(Figure::LINE);
	}
}

