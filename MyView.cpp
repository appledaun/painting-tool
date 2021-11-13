#include "stdafx.h"
/*어떤 버튼을 만들지, 어떤 도형을 그릴지 이것은 응용에 국한한 이야기이므로 상속받은 View클래스 (MyView라고 부르자) 에서 해주어야 한다.
반면에 툴바를 만들어주고 툴바 버튼을 눌렀을 때 해당 버튼의 액션이 실행되게 하는 것은 라이브러리의 공통적인 부분이다.

그림그리는 함수는 가상메소드가 아닌 일반 메소드로 둔다. 왜냐하면 override할 필요가 없이 사용만 하기 때문이다.
마우스 다루는 함수등은 응용마다 달라지는 부분이 있고 고정된 부분이 있으므로 무조건 상위 클래스에
있는 동일 함수를 먼저 실행하고 나서 응용 코드를 실행하도록 만들어 줘야한다.
*/
#include "MyView.h" 

#include "Figure.h"
#include "CLine.h"
#include "Ellipse.h"
#include "Rect.h"
#include "tbutton.h"
#include "Misc.h"
#include "toolbar.h"
#include "menu.h"
#include "menubar.h"
#include "menuItem.h"
#include "FigButtonListener.h"
#include "ColorButtonListener.h"

MyView::MyView(HINSTANCE hInstance):View(hInstance) {

}

void MyView::OnLButtonDown(MyEvent e) {
	View::OnLButtonDown(e);
	m_startX = e.x; m_startY = e.y;

}
void MyView::OnLButtonUp(MyEvent e) {

	View::OnLButtonUp(e);
	// no button is clicked.
	if (!is_clicked(e.x, e.y) &&/*!is_drawing && */on_toolbar(e.x, e.y)) {
		// 이 경우는 버튼을 누른 뒤 이동하여 캔버스에서 뗀 경우이다. 
		return;
	}

	if (!is_clicked(e.x, e.y)) {
		if (currentFig == Figure::LINE) { // 선분
			//figType = Figure::LINE;
			addFigure(new CLine(m_startX, m_startY, e.x, e.y, m_color, m_bg_color));
		}
		else if (currentFig == Figure::ELLIPSE) {  // 타원
			addFigure(new CEllipse(m_startX, m_startY, e.x, e.y, m_color, m_bg_color));
		}
		else if (currentFig == Figure::RECT) {  // 사각형
			addFigure(new Rect(m_startX, m_startY, e.x, e.y, m_color, m_bg_color));
		}
	}
	
	invalidate();
}
void MyView::OnRButtonDown(MyEvent e) {
	View::OnRButtonDown(e);
	m_startX = e.x; m_startY = e.y;
}
void MyView::OnRButtonUp(MyEvent e) {
	View::OnRButtonUp(e);
	invalidate();
}
void MyView::OnChar(long ch) {
	View::OnChar(ch);
}

void MyView::onInitialize() {
	View::onInitialize();
	
	//-----------툴바 메뉴---------------------
	btnRect = new TButton("R", this);
	HICON rectIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	rectIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnRect->setIcon(rectIcon);
	btnRect->addButtonListener(new FigButtonListener(this));	//리스너 연결 

	btnEllipse = new TButton("E", this);
	HICON ellipseIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	ellipseIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON2),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnEllipse->setIcon(ellipseIcon);
	btnEllipse->addButtonListener(new FigButtonListener(this));	//리스너 연결 

	btnLine = new TButton("L", this);
	HICON lineIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	lineIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON3),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnLine->setIcon(lineIcon);
	btnLine->addButtonListener(new FigButtonListener(this)); //리스너 연결 

	btnRed = new TButton("RED", this);
	HICON redIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	redIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON8),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnRed->setIcon(redIcon);
	btnRed->addButtonListener(new ColorButtonListener(this)); //리스너 연결 

	btnGreen = new TButton("GRREN", this);
	HICON greenIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	greenIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON9),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnGreen->setIcon(greenIcon);
	btnGreen->addButtonListener(new ColorButtonListener(this)); //리스너 연결 

	btnBlue = new TButton("BLUE", this);
	HICON blueIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	blueIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON10),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBlue->setIcon(blueIcon);
	btnBlue->addButtonListener(new ColorButtonListener(this)); //리스너 연결 

	btnBlack = new TButton("BLACK", this);
	HICON blackIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	blackIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON11),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBlack->setIcon(blackIcon);
	btnBlack->addButtonListener(new ColorButtonListener(this)); //리스너 연결

	btnBGRed = new TButton("BGRED", this);
	HICON bgredIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	bgredIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON4),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBGRed->setIcon(bgredIcon);
	btnBGRed->addButtonListener(new ColorButtonListener(this)); //리스너 연결

	btnBGGreen = new TButton("BGGreen", this);
	HICON bggreenIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	bggreenIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON5),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBGGreen->setIcon(bggreenIcon);
	btnBGGreen->addButtonListener(new ColorButtonListener(this)); //리스너 연결

	btnBGBlue = new TButton("BGBLUE", this);
	HICON bgblueIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	bgblueIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON6),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBGBlue->setIcon(bgblueIcon);
	btnBGBlue->addButtonListener(new ColorButtonListener(this)); //리스너 연결
	
	btnBGWhite = new TButton("BGWHITE", this);
	HICON bgwhiteIcon;  // 다른 아이콘 변수도 설정 아이콘 ID 가 IDI_ICON3 라고 가정하고,
	bgwhiteIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON7),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBGWhite->setIcon(bgwhiteIcon);
	btnBGWhite->addButtonListener(new ColorButtonListener(this)); //리스너 연결

	m_Toolbar->addButton(btnRect);
	m_Toolbar->addButton(btnEllipse);
	m_Toolbar->addButton(btnLine);
	m_Toolbar->addButton(btnRed);
	m_Toolbar->addButton(btnGreen);
	m_Toolbar->addButton(btnBlue);
	m_Toolbar->addButton(btnBlack);
	m_Toolbar->addButton(btnBGRed);
	m_Toolbar->addButton(btnBGGreen);
	m_Toolbar->addButton(btnBGBlue);
	m_Toolbar->addButton(btnBGWhite);
	//----------------------------------------------

	//---------------메뉴바 메뉴--------------------
	btnFile = new Menu("파일", this);
	btnFile->addButtonListener(this);
	btnFig = new Menu("도형", this);
	btnFig->addButtonListener(this);
	btnColor = new Menu("색깔", this);

	m_Menubar->addMenu(btnFile);
	m_Menubar->addMenu(btnFig);
	m_Menubar->addMenu(btnColor);
	//------------------------------------------------

	//--------------메뉴바 하위메뉴--------------------
	btnSave = new MenuItem("저장", this);
	btnSave->addButtonListener(this);
	btnOpen = new MenuItem("열기", this); 
	btnOpen->addButtonListener(this);

	btnR = new MenuItem("사각형", this);
	btnR->addButtonListener(new FigButtonListener(this));
	btnE = new MenuItem("타원", this);
	btnE->addButtonListener(new FigButtonListener(this));
	btnL = new MenuItem("선분", this);
	btnL->addButtonListener(new FigButtonListener(this));

	btnMRed = new MenuItem("빨강", this);
	btnMRed->addButtonListener(new ColorButtonListener(this));
	btnMGreen = new MenuItem("초록", this);
	btnMGreen->addButtonListener(new ColorButtonListener(this));
	btnMBlue = new MenuItem("파랑", this);
	btnMBlue->addButtonListener(new ColorButtonListener(this));
	btnMBlack = new MenuItem("검정", this);
	btnMBlack->addButtonListener(new ColorButtonListener(this));
	btnBGR = new MenuItem("B빨강", this);
	btnBGR->addButtonListener(new ColorButtonListener(this));
	btnBGG = new MenuItem("B초록", this);
	btnBGG->addButtonListener(new ColorButtonListener(this));
	btnBGB = new MenuItem("B파랑", this);
	btnBGB->addButtonListener(new ColorButtonListener(this));
	btnBGW = new MenuItem("B하양", this);
	btnBGW->addButtonListener(new ColorButtonListener(this));

	m_FileMenu->addMenu(btnSave);
	m_FileMenu->addMenu(btnOpen);

	m_FigMenu->addMenu(btnR);
	m_FigMenu->addMenu(btnE);
	m_FigMenu->addMenu(btnL);

	m_ColorMenu->addMenu(btnMRed);
	m_ColorMenu->addMenu(btnMGreen);
	m_ColorMenu->addMenu(btnMBlue);
	m_ColorMenu->addMenu(btnMBlack);
	m_ColorMenu->addMenu(btnBGR);
	m_ColorMenu->addMenu(btnBGG);
	m_ColorMenu->addMenu(btnBGB);
	m_ColorMenu->addMenu(btnBGW);
	//----------------------------------------------
}

