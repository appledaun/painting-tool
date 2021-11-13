#pragma once
/*�޴��ٴ� ��ü�̰� 
�޴��ٴ� �������� �޴��� �����մϴ�. ���� Container���� ��� �޽��ϴ�.
*/
#include "container.h"
#include "menu.h"
#include <list>
#include <string>

using namespace std;

class View;

class MenuBar :public Container {
public:
	MenuBar();
	MenuBar(View * v);
	void addMenu(Menu *);
	//MyButton * findButton(MyEvent e);
	void draw();
	void close_menu();
private:
	//list<Menu *> m_menuList;
	int menuNum = 0;
	//View * m_view;
};