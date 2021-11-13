#pragma once

/*메뉴항목은 실제 액션이 일어나야 하는 부분입니다. 버튼에서 상속 받습니다.*/
#include "MyButton.h"
#include "View.h"
#include <string>	

using namespace std;

class MenuItem :public MyButton {
public:
	MenuItem();
	MenuItem(string, View *);
	virtual void draw();
	virtual void tempDraw();
	void setLocation(int, int);
protected:

private:
};