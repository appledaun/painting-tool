#pragma once
#include "View.h"
#include "ButtonListener.h"

class MyView : public View//, public ButtonListener {
{
public:
	MyView(HINSTANCE);
	void OnLButtonDown(MyEvent e);
	void OnLButtonUp(MyEvent e);
	void OnRButtonDown(MyEvent e);
	void OnRButtonUp(MyEvent e);
	void onInitialize();
	void OnChar(long ch);
};
