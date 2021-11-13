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
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
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
	//m_InstanceHandle = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
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
	//debugOutput("Click\n");  // IDE�� '���' â�� ���´�.
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

	if (btnFile->is_open()) {	//���ϸ޴��� �����ִ�
		MenuItem * filei = (MenuItem *)m_FileMenu->findComponent(e);
		if (is_clicked(e.x, e.y) && filei) {	//���Ͼ������� Ŭ���Ǿ���
			debugOutput("filesave\n");
			filei->action();	//� ���ϸ޴����� ����
			//return;
		}
	}
	if (btnFig->is_open()) {		//�����޴��� �����ִ�
		MenuItem * figi = (MenuItem *)m_FigMenu->findComponent(e);
		if (is_clicked(e.x, e.y) && figi) {		//������������ Ŭ���Ǿ���
			debugOutput("figsave\n");
			figi->action();	//� �������� ����
			//return;
		}
	}
	if (btnColor->is_open()) {		//����޴��� �����ִ�
		MenuItem * colori = (MenuItem *)m_ColorMenu->findComponent(e);
		if (is_clicked(e.x, e.y) && colori) {		//����������� Ŭ���Ǿ���
			debugOutput("colorsave\n");
			colori->action();	//� �������� ����
			//return;
		}
	}

	if (!(btnFile->is_open()) && !(btnFig->is_open()) && !(btnColor->is_open())) {
		TButton * b = (TButton *)m_Toolbar->findComponent(e);
		if (is_clicked(e.x, e.y) && b) {	//���ٰ� Ŭ���Ǿ���
			debugOutput("toolbar\n");
			b->action(); //select //� ��ư�� Ŭ�� �Ǿ��°� ����
			//return;
		}
	}

	if (is_clicked(e.x, e.y)) {	//Ŭ���Ǿ���
		//�޴��� Ŭ���Ǿ���
		if (m) {
			//m->action();	//�ش� �޴��� ���ų�, ���� �����־��ٸ� �ش� �޴��� �ݴ´�
			m->open_menu(m_Menubar);
		}
		//�޴� �� �ٸ� ���� Ŭ���Ǿ���
		else {
			m_Menubar->close_menu();	//��� �޴��� �ݴ´� 
			
		}
	}

	

	

}

void View::OnRButtonDown(MyEvent e)
{
	//�׷�ȭ, �̵�, ���簡 �����ؾ��Ѵ�.
	// ���α׷� ���� ����� �����ϱ� ���� ���� ��ư Ŭ���� �Ʒ� ���� ȣ���ϰ� ��������ϴ�.
	//eraseRect(e.x, e.y, 100, 100);
	//::PostMessage(m_WindowHandle, WM_CLOSE, NULL, NULL);
	
}

void View::OnRButtonUp(MyEvent e)
{
	//Figure * f = findFigure(e);
	Figure * f = findFigure(m_startX, m_startY);
	

	if (is_clicked(e.x, e.y)) {	//�׷� Ǯ��
		if (!m_selected.empty()) {
			debugOutput("RIGHTCLICK\n");
			for (auto i : m_selected) {
				i->is_group = 0;
			}
			m_selected.clear();
		}
		else if (f) { //������ ���� �ƴٸ� 
			m_figList.remove(f);
			m_figList.push_back(f);
		}
		return;
	}

	//��Ʈ�� + �巡�� => ���� 
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

	if (e.m_wParam & MK_SHIFT) {	//����Ʈ + �巡�� => �׷�ȭ ��Ű��
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
		for (auto i : m_selected) {	//Ȯ��
			//i->fig_fill_color = (RGB(0, 0, 0));
			m_figList.remove(i);
			m_figList.push_back(i);
			i->is_group = 1;
		}
		
		return;
	}

	

	if (f) {	//���� �̵���Ű��
		debugOutput("RIGHTMOVE");
		for (auto i : m_selected) {	//�׷�ȭ �� �� �̵���Ű��
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
	// Ű���� �Է��� �Ǹ� �� �Լ��� �ڵ� ȣ��˴ϴ�.  cin�̳� getchar, scanf ����
	// ǥ�� �Է��Լ��� �۵����� ������ onchar �� �� �̿��ؾ� �մϴ�.


}

// ������ ���� �����ϱ�
void View::setPenColor(COLORREF color)
{
	thePen = CreatePen(PS_SOLID, 1, color);
	SelectObject(m_DCHandle, thePen);
}

// ���� ���� �β��� ���ÿ� �����ϱ�
void View::setPen(COLORREF color, int width)
{
	thePen = CreatePen(PS_SOLID, width, color);
	SelectObject(m_DCHandle, thePen);
}

// ä�� ���� �����ϴ� �Լ�.
void View::setFillColor(COLORREF color)
{
	theBrush = CreateSolidBrush(color);
	SelectObject(m_DCHandle, theBrush);
}

// ���� ���� �����ϴ� �Լ�.
void View::setTextColor(COLORREF color)
{
	SetTextColor(m_DCHandle, color);
}
// ���� ������ �����ϴ� �Լ�.
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

// ���  ���빰���� �ٽ� �׷��ִ� �Լ�.  ������ �ʿ��� ���̴�.
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

// ȭ���� ���� ����� �ȵǾ� �ִٰ� �˸��� �Լ��Դϴ�.
// �� �Լ��� ȣ���ϸ� ȭ���� �������� 
// Main.cpp �ʿ� case WM_PAINT: �κ��� ����˴ϴ�.
// �ᱹ�� View ��ü�� display�� ����ǰ���.
void View::invalidate()
{
	InvalidateRect(m_WindowHandle, NULL, true);
}

// ��� �������� onInitialize �Լ����� �ʱ�ȭ����.
void View::onInitialize()
{
	// *** ��� ������Ʈ���� ���⿡�� �ʱ�ȭ����.
	m_Toolbar = new Toolbar(this);
	m_Menubar = new MenuBar(this);
	m_FileMenu = new Menu(0, this);
	m_FigMenu = new Menu(1, this);
	m_ColorMenu = new Menu(2, this);
	/*
	����
	btnRect = new TButton("R", this);
	btnEllipse = new TButton("E", this);
	btnLine = new TButton("L", this);
	m_Toolbar->addButton(btnRect);
	m_Toolbar->addButton(btnEllipse);
	m_Toolbar->addButton(btnLine);
	*/
	invalidate();
}

// �簢�� ��ġ�� �����.
void View::eraseRect(int x, int y, int   sizeX, int  sizeY) // �»�� x y �׸��� x�� y�� ũ��
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	setPenColor(RGB(255, 255, 255));
	setFillColor(RGB(255, 255, 255));
	drawRectangle(x, y, sizeX, sizeY);
}

// ������ ��ġ�� �����ش�.
RECT View::getClientRect()   // RECT���� left, right, top, bottom ��� ������ �ִ�.
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	RECT r;
	GetClientRect(m_WindowHandle, &r);
	return r;
}


// ���� ��Ʈ���� text�� ������� ��, ȭ��� �����ϴ� ũ�⸦ �����ִ� �Լ�
SIZE View::textSize(const std::string text)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
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
	// TODO: ���⿡ ���� �ڵ� �߰�.

	Menu * m = (Menu *)m_Menubar->findComponent(e);
	TButton *b = (TButton *)m_Toolbar->findComponent(e);
	MenuItem * filei = (MenuItem *)m_FileMenu->findComponent(e);
	MenuItem * figi = (MenuItem *)m_FigMenu->findComponent(e);
	MenuItem * colori = (MenuItem *)m_ColorMenu->findComponent(e);

	//���� ��ư 
	if (!btnFile->is_open() && !btnFig->is_open() && !btnColor->is_open()) {	//�޴��� ���� �ִٸ�~
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

	if (btnFile->is_open())	{	//���� �޴��� ���ȴٸ� 
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
	if (btnFig->is_open()) {	//���� �޴��� ���ȴٸ� 
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
	if (btnColor->is_open()) {	//���� �޴��� ���ȴٸ� 
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

	//�޴�
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
	//up down��ǥ Ȯ���Ͽ� Ŭ������ �巡������ Ȯ��
	return (m_startX == x && m_startY == y);
}

bool View::on_toolbar(int x, int y) {
	//Ŭ�� Ȥ�� �巡�� �� ���� ���� ��ġ�ΰ�
	return (m_startY <= 64 || y <= 64);
}

void View::actionPerformed(Component * b) {
	
	if (b == nullptr) return;
	else if (b == btnSave) {
		{
			/*�ϳ��� ������ ������ �� ������ �ʿ��ұ��?
			������ Ÿ��, ��ġ, ������ �� �ƴұ��?
			�̰� �׳� �ؽ�Ʈ ���Ͽ� ���� ������ �Ǵ� �̴ϴ�.*/
			ofstream a_file("example.txt");
			a_file << m_figList.size() << "\n";
			for (auto i : m_figList) {
				a_file << i->getType() << " " 
					<< i->m_x1 << " " << i->m_y1 << " " << i->m_x2 << " " << i->m_y2 << " "
					<< i->fig_pen_color << " " << i->fig_fill_color << "\n";
			}
			//a_file.open("example.txt", ios::app);  // append
			//a_file << "�ι�° ���Դϴ�.\n";
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
