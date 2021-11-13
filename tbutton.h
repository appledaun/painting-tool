#pragma once
#include "MyButton.h"
#include "View.h"
#include <string>	

using namespace std;

class TButton : public MyButton {
public:
	TButton();
	TButton(string, View *);
	virtual void draw();
	virtual void tempDraw();
	void setLocation(int n);
	void setIcon(HICON h);
private:

};


