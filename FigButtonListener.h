#pragma once
#include "ButtonListener.h"
class View;
class FigButtonListener :
	public ButtonListener
{
public:
	FigButtonListener(View *);
	~FigButtonListener();
	void actionPerformed(Component *);

protected:
	View * m_view;

};

