#pragma once

/*�޴��׸��� ���� �׼��� �Ͼ�� �ϴ� �κ��Դϴ�. ��ư���� ��� �޽��ϴ�.*/
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