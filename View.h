#pragma once
#include "iostream"
#include "string"
#include "Proj2018.h"
#include "list"
#include "Misc.h"
#include "container.h"
#include "component.h"
#include "ButtonListener.h"
#define MAX_LOADSTRING 100

class Figure;
class MyButton;
class Component;
class Toolbar;
class TButton;
class MenuBar;
class Menu;
class MenuItem;
class View :public Container, public ButtonListener
{
public:
	View(HINSTANCE);
	~View();
protected:
	HWND m_WindowHandle;    //  ���� ���� handle
	HDC m_DCHandle;	// DC handle
	HBRUSH brushWhite, brushBlack;
	HPEN penWhite, penBlack;
	// �ӽ� ����
	int count = 0;
	HPEN thePen;
	HBRUSH theBrush;
	HINSTANCE m_InstanceHandle;
	WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

public:
	// �ʱ�ȭ �Լ���
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL initInstance(/*HINSTANCE hInstance, */int nCmdShow);

	// �̺�Ʈ ó�� �Լ���
	virtual void OnLButtonDown(MyEvent e);
	virtual void OnLButtonUp(MyEvent e);
	virtual void OnRButtonDown(MyEvent e);
	virtual void OnRButtonUp(MyEvent e);
	virtual void OnChar(long ch);

	void setPenColor(COLORREF color);         // �� ���� ����. �β��� 1�� �ڵ�.
	void setPen(COLORREF color, int width);   // �� ����� �β����� ����.
	void setFillColor(COLORREF color);
	void setTextColor(COLORREF color);
	void setTextBkColor(COLORREF color);
	void drawRectangle(int x, int y, int sizeX, int sizeY);
	void drawEllipse(int x, int y, int sizeX, int sizeY);
	void drawLine(int x, int y, int sizeX, int sizeY);
	void drawText(std::string str, int x, int y);
	void drawIcon(int x, int y, HICON i);
	void redrawAll();
	//void eraseAll();
	void invalidate();
	virtual void onInitialize();

protected:
	int m_startX, m_startY;  // 1�ܰ迡�� �ʿ��� ����
	bool is_drawing;  //  
	TButton * lastBtn = 0;
	Menu * lastMn = 0;
	MenuItem * lastFigM = 0, *lastFileM = 0, *lastColorM = 0;
	int currentFig = 0;	//� �����ΰ� 
	int currentBtn = 0;	//� �޴��ΰ� 

	Toolbar * m_Toolbar = 0;
	MenuBar * m_Menubar = 0;
	Menu * m_FileMenu = 0;
	Menu * m_FigMenu = 0;
	Menu * m_ColorMenu = 0;
	COLORREF m_color = RGB(0, 0, 0);
	COLORREF m_bg_color = RGB(255, 255, 255);
	list<Figure *> m_selected;
public:
	void eraseRect(int x, int y, int sizeX, int sizeY);
	RECT getClientRect();
	SIZE textSize(std::string text);

	void addFigure(Figure *);
	TButton * btnRect, *btnEllipse, *btnLine, 
		*btnRed, *btnGreen, *btnBlue, *btnBlack, 
		*btnBGRed, *btnBGGreen, *btnBGBlue, *btnBGWhite;
	Menu *btnFig, *btnFile, *btnColor;
	MenuItem *btnSave, *btnOpen, 
		*btnR, *btnE, *btnL, 
		*btnMRed, *btnMGreen, *btnMBlue, *btnMBlack, 
		*btnBGR, *btnBGG, *btnBGB, *btnBGW;

	void OnMouseMove(MyEvent e);
	void menuActions(Component * b);
	//void buttonActions(Component *b);
	int getWindowWidth();
	bool is_clicked(int x, int y);
	bool on_toolbar(int x, int y);
	void actionPerformed(Component *);
	void setCurrentFig(int);
	void setColor(COLORREF);
	void setBGColor(COLORREF);
};

