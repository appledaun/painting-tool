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
	HWND m_WindowHandle;    //  바탕 윈도 handle
	HDC m_DCHandle;	// DC handle
	HBRUSH brushWhite, brushBlack;
	HPEN penWhite, penBlack;
	// 임시 변수
	int count = 0;
	HPEN thePen;
	HBRUSH theBrush;
	HINSTANCE m_InstanceHandle;
	WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

public:
	// 초기화 함수들
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL initInstance(/*HINSTANCE hInstance, */int nCmdShow);

	// 이벤트 처리 함수들
	virtual void OnLButtonDown(MyEvent e);
	virtual void OnLButtonUp(MyEvent e);
	virtual void OnRButtonDown(MyEvent e);
	virtual void OnRButtonUp(MyEvent e);
	virtual void OnChar(long ch);

	void setPenColor(COLORREF color);         // 펜 색깔 설정. 두께는 1로 자동.
	void setPen(COLORREF color, int width);   // 펜 색깔과 두께까지 설정.
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
	int m_startX, m_startY;  // 1단계에서 필요한 변수
	bool is_drawing;  //  
	TButton * lastBtn = 0;
	Menu * lastMn = 0;
	MenuItem * lastFigM = 0, *lastFileM = 0, *lastColorM = 0;
	int currentFig = 0;	//어떤 도형인가 
	int currentBtn = 0;	//어떤 메뉴인가 

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

