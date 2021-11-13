#pragma once

/*메뉴는 여러개의 메뉴 항목(Menu Item)을 포함합니다. Container에서 상속 받습니다.
*/
#include "container.h"
#include "menuItem.h"
#include <list>
#include <string>

using namespace std;

class View;
class MenuBar;
class Menu :public Container {
public:
	Menu();
	Menu(int, View * v);
	Menu(string, View *);
	void addMenu(MenuItem *);
	//MyButton * findButton(MyEvent e);
	//void draw();
	virtual void draw();
	virtual void tempDraw();
	void setLocation(int n);
	void open_menu(MenuBar *);
	void close_menu();
	bool is_open();
	void openMenus();
	static const int MFILE = 4, MFIG = 5;
private:
	//View * m_view;
	//list<TButton *> m_CompList;
	int menuNum;
	int menuItemNum = 1;
	list<MenuItem *> m_menuitemList;
	bool open = 0;
	//string name;
};