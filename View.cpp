#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "string"
#include "View.h"

#include "Misc.h"
#include "Rect.h"	
#include "Ellipse.h"
#include "CLine.h"

#include "MyButton.h"
#include "toolbar.h"
#include "tbutton.h"

#include "component.h"
#include "menubar.h"
#include "menu.h"
#include "menuItem.h"

#include <fstream>


using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);  // Prototype to external fun

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM View::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJ2018));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL; //  MAKEINTRESOURCEW(IDC_PROJ2018);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

View::View(HINSTANCE hInstance):m_InstanceHandle(hInstance) {
	m_InstanceHandle = hInstance;
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PROJ2018, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
}

View::~View()
{

}

BOOL View::initInstance( int nCmdShow )
{
	//m_InstanceHandle = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
	m_WindowHandle = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 1000,  600, nullptr, nullptr, m_InstanceHandle, nullptr);

	if (!m_WindowHandle)
	{
		return FALSE;
	}

	ShowWindow(m_WindowHandle, nCmdShow);
	UpdateWindow(m_WindowHandle);
	m_DCHandle = ::GetDC(m_WindowHandle);
	onInitialize();
	//mainView = new View(hWnd);

	return TRUE;
}

void View::OnLButtonDown(MyEvent e)
{
	//debugOutput("Click\n");  // IDE의 '출력' 창에 나온다.
	//m_startX = e.x; m_startY = e.y;
	/*
	Menu * m = 0;
	TButton * b = 0;
	m = (Menu *)m_Menubar->findComponent(e);
	b = (TButton *)m_Toolbar->findComponent(e);

	//is_drawing = (b && m) == false ? true : false;
	*/
}

void View::OnLButtonUp(MyEvent e)
{
	
	Menu * m = (Menu *)m_Menubar->findComponent(e);
	//Figure * f = (Figure *)m_fig

	if (btnFile->is_open()) {	//파일메뉴가 열려있다
		MenuItem * filei = (MenuItem *)m_FileMenu->findComponent(e);
		if (is_clicked(e.x, e.y) && filei) {	//파일아이템이 클릭되었다
			debugOutput("filesave\n");
			filei->action();	//어떤 파일메뉴인지 저장
			//return;
		}
	}
	if (btnFig->is_open()) {		//도형메뉴가 열려있다
		MenuItem * figi = (MenuItem *)m_FigMenu->findComponent(e);
		if (is_clicked(e.x, e.y) && figi) {		//도형아이템이 클릭되었다
			debugOutput("figsave\n");
			figi->action();	//어떤 도형인지 저장
			//return;
		}
	}
	if (btnColor->is_open()) {		//색깔메뉴가 열려있다
		MenuItem * colori = (MenuItem *)m_ColorMenu->findComponent(e);
		if (is_clicked(e.x, e.y) && colori) {		//색깔아이템이 클릭되었다
			debugOutput("colorsave\n");
			colori->action();	//어떤 색깔인지 저장
			//return;
		}
	}

	if (!(btnFile->is_open()) && !(btnFig->is_open()) && !(btnColor->is_open())) {
		TButton * b = (TButton *)m_Toolbar->findComponent(e);
		if (is_clicked(e.x, e.y) && b) {	//툴바가 클릭되었다
			debugOutput("toolbar\n");
			b->action(); //select //어떤 버튼이 클릭 되었는가 저장
			//return;
		}
	}

	if (is_clicked(e.x, e.y)) {	//클릭되었다
		//메뉴가 클릭되었다
		if (m) {
			//m->action();	//해당 메뉴를 열거나, 원래 열려있었다면 해당 메뉴를 닫는다
			m->open_menu(m_Menubar);
		}
		//메뉴 외 다른 곳이 클릭되었다
		else {
			m_Menubar->close_menu();	//모든 메뉴를 닫는다 
			
		}
	}

	

	

}

void View::OnRButtonDown(MyEvent e)
{
	//그룹화, 이동, 복사가 가능해야한다.
	// 프로그램 종료 방법을 데모하기 위해 우측 버튼 클릭시 아래 줄을 호출하게 만들었습니다.
	//eraseRect(e.x, e.y, 100, 100);
	//::PostMessage(m_WindowHandle, WM_CLOSE, NULL, NULL);
	
}

void View::OnRButtonUp(MyEvent e)
{
	//Figure * f = findFigure(e);
	Figure * f = findFigure(m_startX, m_startY);
	

	if (is_clicked(e.x, e.y)) {	//그룹 풀기
		if (!m_selected.empty()) {
			debugOutput("RIGHTCLICK\n");
			for (auto i : m_selected) {
				i->is_group = 0;
			}
			m_selected.clear();
		}
		else if (f) { //도형이 선택 됐다면 
			m_figList.remove(f);
			m_figList.push_back(f);
		}
		return;
	}

	//컨트롤 + 드래그 => 복사 
	if (e.m_wParam & MK_CONTROL) {
		debugOutput("control\n");
		if (!m_selected.empty()) {
			debugOutput("EMPTY\n");
			m_selected.clear();
		}
		Figure f(m_startX, m_startY, e.x, e.y, m_color, m_bg_color);
		for (auto i : m_figList) {
			if (f.inside(i->m_x1, i->m_y1) && f.inside(i->m_x2, i->m_y2)) {
				m_selected.push_back(i);
			}
			
		}
		for (auto j : m_selected) {
			debugOutput("MOVE\n");

			m_color = j->fig_pen_color;
			m_bg_color = j->fig_fill_color;
			switch (j->getType()) {
			case Figure::RECT:
				addFigure(new Rect(j->m_x1 - 30, j->m_y1 - 30, j->m_x2 - 30, j->m_y2 - 30, 
					j->fig_pen_color, j->fig_fill_color));
				break;
			case Figure::ELLIPSE:
				addFigure(new CEllipse(j->m_x1 - 30, j->m_y1 - 30, j->m_x2 - 30, j->m_y2 - 30, 
					j->fig_pen_color, j->fig_fill_color));
				break;
			case Figure::LINE:
				addFigure(new CLine(j->m_x1 - 30, j->m_y1 - 30, j->m_x2 - 30, j->m_y2 - 30, 
					j->fig_pen_color, j->fig_fill_color));
				break;
			}
			//m_figList.push_back(j);
		}

		return;
	}

	if (e.m_wParam & MK_SHIFT) {	//쉬프트 + 드래그 => 그룹화 시키기
		debugOutput("shift\n");

		if (!m_selected.empty()) {
			debugOutput("EMPTY\n");
			for (auto i : m_selected) {
				i->is_group = 0;
			}
			m_selected.clear();
		}

		Figure f(m_startX, m_startY, e.x, e.y, m_color, m_bg_color);
		for (auto i : m_figList) {
			if (f.inside(i->m_x1, i->m_y1) && f.inside(i->m_x2, i->m_y2)) {
				m_selected.push_back(i);
			}
		}
		for (auto i : m_selected) {	//확인
			//i->fig_fill_color = (RGB(0, 0, 0));
			m_figList.remove(i);
			m_figList.push_back(i);
			i->is_group = 1;
		}
		
		return;
	}

	

	if (f) {	//도형 이동시키기
		debugOutput("RIGHTMOVE");
		for (auto i : m_selected) {	//그룹화 된 것 이동시키기
			if (i == f) {
				for (auto j : m_selected) {
					debugOutput("MOVE\n");
					j->m_x1 += (e.x - m_startX);
					j->m_x2 += (e.x - m_startX);
					j->m_y1 += (e.y - m_startY);
					j->m_y2 += (e.y - m_startY);
				}
				return;
			}
		}

		m_figList.remove(f);
		m_figList.push_back(f);	
		f->m_x1 += (e.x - m_startX);
		f->m_x2 += (e.x - m_startX);
		f->m_y1 += (e.y - m_startY);
		f->m_y2 += (e.y - m_startY);
	}


	

}

void View::OnChar(long ch)
{
	// 키보드 입력이 되면 이 함수가 자동 호출됩니다.  cin이나 getchar, scanf 같은
	// 표준 입력함수는 작동하지 않으니 onchar 를 잘 이용해야 합니다.


}

// 라인의 색을 지정하기
void View::setPenColor(COLORREF color)
{
	thePen = CreatePen(PS_SOLID, 1, color);
	SelectObject(m_DCHandle, thePen);
}

// 선의 색과 두께를 동시에 지정하기
void View::setPen(COLORREF color, int width)
{
	thePen = CreatePen(PS_SOLID, width, color);
	SelectObject(m_DCHandle, thePen);
}

// 채움 색을 결정하는 함수.
void View::setFillColor(COLORREF color)
{
	theBrush = CreateSolidBrush(color);
	SelectObject(m_DCHandle, theBrush);
}

// 글자 색을 지정하는 함수.
void View::setTextColor(COLORREF color)
{
	SetTextColor(m_DCHandle, color);
}
// 글자 배경색을 지정하는 함수.
void View::setTextBkColor(COLORREF color)
{
	SetBkColor(m_DCHandle, color);
}

void View::drawRectangle(int x1, int y1, int x2, int y2)
{
	Rectangle(m_DCHandle, x1, y1, x2, y2);
}

void View::drawEllipse(int x1, int y1, int x2, int y2)
{
	Ellipse(m_DCHandle, x1, y1, x2, y2);
}

void View::drawLine(int x1, int y1, int x2, int y2)
{
	MoveToEx(m_DCHandle, x1, y1, NULL);
	LineTo(m_DCHandle, x2, y2);
}


void View::drawText(std::string str, int x, int y)
{
	TextOutA(m_DCHandle, x, y, str.c_str(), strlen(str.c_str()));
}

void View::drawIcon(int x, int y, HICON i) {
	DrawIcon(m_DCHandle, x, y, i);
}

// 모든  내용물들을 다시 그려주는 함수.  수정이 필요할 것이다.
void View::redrawAll()
{
	if (m_Toolbar) {
		m_Toolbar->draw();
	}
	
	for (auto r: m_figList) {
		r->draw();
	}
	if (m_Menubar) { 
		m_Menubar->draw();
	}

	if (m_FileMenu && btnFile->is_open()) {
		debugOutput("filemenu ");
		m_FileMenu->openMenus();
	}
	if (m_FigMenu && btnFig->is_open()) {
		debugOutput("figmenu ");
		m_FigMenu->openMenus();
	}
	if (m_ColorMenu && btnColor->is_open()) {
		debugOutput("colormenu ");
		m_ColorMenu->openMenus();
	}
}

// 화면이 현재 제대로 안되어 있다고 알리는 함수입니다.
// 이 함수를 호출하면 화면이 지워지고 
// Main.cpp 쪽에 case WM_PAINT: 부분이 실행됩니다.
// 결국은 View 객체의 display가 실행되겠죠.
void View::invalidate()
{
	InvalidateRect(m_WindowHandle, NULL, true);
}

// 모든 윈도들을 onInitialize 함수에서 초기화하자.
void View::onInitialize()
{
	// *** 모든 컴포넌트들을 여기에서 초기화하자.
	m_Toolbar = new Toolbar(this);
	m_Menubar = new MenuBar(this);
	m_FileMenu = new Menu(0, this);
	m_FigMenu = new Menu(1, this);
	m_ColorMenu = new Menu(2, this);
	/*
	응용
	btnRect = new TButton("R", this);
	btnEllipse = new TButton("E", this);
	btnLine = new TButton("L", this);
	m_Toolbar->addButton(btnRect);
	m_Toolbar->addButton(btnEllipse);
	m_Toolbar->addButton(btnLine);
	*/
	invalidate();
}

// 사각형 위치를 지운다.
void View::eraseRect(int x, int y, int   sizeX, int  sizeY) // 좌상귀 x y 그리고 x축 y축 크기
{
	// TODO: 여기에 구현 코드 추가.
	setPenColor(RGB(255, 255, 255));
	setFillColor(RGB(255, 255, 255));
	drawRectangle(x, y, sizeX, sizeY);
}

// 윈도의 위치를 돌려준다.
RECT View::getClientRect()   // RECT에는 left, right, top, bottom 멤버 변수가 있다.
{
	// TODO: 여기에 구현 코드 추가.
	RECT r;
	GetClientRect(m_WindowHandle, &r);
	return r;
}


// 현재 폰트에서 text를 출력했을 때, 화면상에 차지하는 크기를 돌려주는 함수
SIZE View::textSize(const std::string text)
{
	// TODO: 여기에 구현 코드 추가.
	SIZE size;
	const char *s = text.c_str();
	GetTextExtentPoint32A(m_DCHandle, s, strlen(s), &size);
	return size;
}

void View::addFigure(Figure *r) {
	m_figList.push_back(r);
	r->setView(this);
	//r->setColor(m_color);
	//r->setBGColor(m_bg_color);
}

void View::OnMouseMove(MyEvent e)
{
	// TODO: 여기에 구현 코드 추가.

	Menu * m = (Menu *)m_Menubar->findComponent(e);
	TButton *b = (TButton *)m_Toolbar->findComponent(e);
	MenuItem * filei = (MenuItem *)m_FileMenu->findComponent(e);
	MenuItem * figi = (MenuItem *)m_FigMenu->findComponent(e);
	MenuItem * colori = (MenuItem *)m_ColorMenu->findComponent(e);

	//툴바 버튼 
	if (!btnFile->is_open() && !btnFig->is_open() && !btnColor->is_open()) {	//메뉴가 닫혀 있다면~
		if (lastBtn == b) {//return;
			// hover in or out
		}
		else {
			if (lastBtn != nullptr) {
				lastBtn->draw();
			}
			if (b != nullptr) {
				b->tempDraw();
			}
			lastBtn = b;
		}
	}

	if (btnFile->is_open())	{	//파일 메뉴가 열렸다면 
		if (lastFileM == filei) {//return;
		// hover in or out
		}
		else {
			if (lastFileM != nullptr) {
				lastFileM->draw();
			}
			if (filei != nullptr) {
				filei->tempDraw();
			}
			lastFileM = filei;
		}
	}
	if (btnFig->is_open()) {	//도형 메뉴가 열렸다면 
		if (lastFigM == figi) {//return;
		// hover in or out
		}
		else {
			if (lastFigM != nullptr) {
				lastFigM->draw();
			}
			if (figi != nullptr) {
				figi->tempDraw();
			}
			lastFigM = figi;
		}
	}
	if (btnColor->is_open()) {	//색깔 메뉴가 열렸다면 
		if (lastColorM == colori) {//return;
		// hover in or out
		}
		else {
			if (lastColorM != nullptr) {
				lastColorM->draw();
			}
			if (colori != nullptr) {
				colori->tempDraw();
			}
			lastColorM = colori;
		}
	}

	//메뉴
	if (lastMn == m) {//return;
		// hover in or out
	}
	else {
		if (lastMn != nullptr) {
			lastMn->draw();
		}
		if (m != nullptr) {
			m->tempDraw();
		}
		lastMn = m;
	}

}

void View::menuActions(Component * b) {
	
}

int View::getWindowWidth() {
	RECT r;
	GetWindowRect(m_WindowHandle, &r);
	return r.right - r.left;
}

bool View::is_clicked(int x, int y) {
	//up down좌표 확인하여 클릭인지 드래그인지 확인
	return (m_startX == x && m_startY == y);
}

bool View::on_toolbar(int x, int y) {
	//클릭 혹은 드래그 된 곳이 툴바 위치인가
	return (m_startY <= 64 || y <= 64);
}

void View::actionPerformed(Component * b) {
	
	if (b == nullptr) return;
	else if (b == btnSave) {
		{
			/*하나의 도형을 저장할 때 무엇이 필요할까요?
			도형의 타입, 위치, 색정보 등 아닐까요?
			이걸 그냥 텍스트 파일에 적어 놓으면 되는 겁니다.*/
			ofstream a_file("example.txt");
			a_file << m_figList.size() << "\n";
			for (auto i : m_figList) {
				a_file << i->getType() << " " 
					<< i->m_x1 << " " << i->m_y1 << " " << i->m_x2 << " " << i->m_y2 << " "
					<< i->fig_pen_color << " " << i->fig_fill_color << "\n";
			}
			//a_file.open("example.txt", ios::app);  // append
			//a_file << "두번째 줄입니다.\n";
			a_file.close();

			
		}

	}
	else if (b == btnOpen) {			
		
		int n[7], num = 0;
		bool is_end = 0;
		ifstream b_file("example.txt");
		b_file >> num;
		for(int j = 0; j < num; j++) {
			//int n[7];
			for (int i = 0; i < 7; i++) {
				if (b_file.eof()) {
					is_end = 1;
				}
				b_file >> n[i];
			}
			if (is_end) break;
			
			m_color = n[5];
			m_bg_color = n[6];
			switch (n[0]) {

			case Figure::RECT:
				addFigure(new Rect(n[1], n[2], n[3], n[4], n[5], n[6]));
				break;
			case Figure::ELLIPSE:
				addFigure(new CEllipse(n[1], n[2], n[3], n[4], n[5], n[6]));
				break;
			case Figure::LINE :
				addFigure(new CLine(n[1], n[2], n[3], n[4], n[5], n[6]));
				break;
			}
		}
		b_file.close();
	}
}

void View::setCurrentFig(int c) {
	currentFig = c;
}
void View::setColor(COLORREF c) {
	m_color = c;
}
void View::setBGColor(COLORREF c) {
	m_bg_color = c;
}
