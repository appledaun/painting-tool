#include "ColorButtonListener.h"
#include "View.h"
#include "tbutton.h"
#include "menuItem.h"
#include "component.h"
#include "Figure.h"


ColorButtonListener::ColorButtonListener(View * v)
{
	m_view = v;
}


ColorButtonListener::~ColorButtonListener()
{
}


void ColorButtonListener::actionPerformed(Component * b) {
	debugOutput("colorlistener\n");
	if (b == nullptr)
		return;
	if (b == m_view->btnRed || b == m_view->btnMRed) {
		m_view->setColor(RGB(255, 0, 0));
	}
	else if (b == m_view->btnGreen || b == m_view->btnMGreen) {
		m_view->setColor(RGB(0, 255, 0));
	}
	else if (b == m_view->btnBlue || b == m_view->btnMBlue) {
		m_view->setColor(RGB(0, 0, 255));
	}
	else if (b == m_view->btnBlack || b == m_view->btnMBlack) {
		m_view->setColor(RGB(0, 0, 0));
	}
	else if (b == m_view->btnBGRed || b == m_view->btnBGR) {
		m_view->setBGColor(RGB(255, 0, 0));
	}
	else if (b == m_view->btnBGGreen || b == m_view->btnBGG) {
		m_view->setBGColor(RGB(0, 255, 0));
	}
	else if (b == m_view->btnBGBlue || b == m_view->btnBGB) {
		m_view->setBGColor(RGB(0, 0, 255));
	}
	else if (b == m_view->btnBGWhite || b == m_view->btnBGW) {
		m_view->setBGColor(RGB(255, 255, 255));
	}
}