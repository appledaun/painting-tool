#pragma once
/*메뉴바는 전체이고 
메뉴바는 여러개의 메뉴를 포함합니다. 따라서 Container에서 상속 받습니다.
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