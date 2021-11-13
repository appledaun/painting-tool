#pragma once
#include "ButtonListener.h"
class View;
class ColorButtonListener :
	public ButtonListener
{
public:
	ColorButtonListener(View *);
	~ColorButtonListener();
	void actionPerformed(Component *);

protected:
	View * m_view;
};



