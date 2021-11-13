#pragma once

/*�޴��� �������� �޴� �׸�(Menu Item)�� �����մϴ�. Container���� ��� �޽��ϴ�.
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