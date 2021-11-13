#include "stdafx.h"
/*� ��ư�� ������, � ������ �׸��� �̰��� ���뿡 ������ �̾߱��̹Ƿ� ��ӹ��� ViewŬ���� (MyView��� �θ���) ���� ���־�� �Ѵ�.
�ݸ鿡 ���ٸ� ������ְ� ���� ��ư�� ������ �� �ش� ��ư�� �׼��� ����ǰ� �ϴ� ���� ���̺귯���� �������� �κ��̴�.

�׸��׸��� �Լ��� ����޼ҵ尡 �ƴ� �Ϲ� �޼ҵ�� �д�. �ֳ��ϸ� override�� �ʿ䰡 ���� ��븸 �ϱ� �����̴�.
���콺 �ٷ�� �Լ����� ���븶�� �޶����� �κ��� �ְ� ������ �κ��� �����Ƿ� ������ ���� Ŭ������
�ִ� ���� �Լ��� ���� �����ϰ� ���� ���� �ڵ带 �����ϵ��� ����� ����Ѵ�.
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
		// �� ���� ��ư�� ���� �� �̵��Ͽ� ĵ�������� �� ����̴�. 
		return;
	}

	if (!is_clicked(e.x, e.y)) {
		if (currentFig == Figure::LINE) { // ����
			//figType = Figure::LINE;
			addFigure(new CLine(m_startX, m_startY, e.x, e.y, m_color, m_bg_color));
		}
		else if (currentFig == Figure::ELLIPSE) {  // Ÿ��
			addFigure(new CEllipse(m_startX, m_startY, e.x, e.y, m_color, m_bg_color));
		}
		else if (currentFig == Figure::RECT) {  // �簢��
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
	
	//-----------���� �޴�---------------------
	btnRect = new TButton("R", this);
	HICON rectIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	rectIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnRect->setIcon(rectIcon);
	btnRect->addButtonListener(new FigButtonListener(this));	//������ ���� 

	btnEllipse = new TButton("E", this);
	HICON ellipseIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	ellipseIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON2),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnEllipse->setIcon(ellipseIcon);
	btnEllipse->addButtonListener(new FigButtonListener(this));	//������ ���� 

	btnLine = new TButton("L", this);
	HICON lineIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	lineIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON3),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnLine->setIcon(lineIcon);
	btnLine->addButtonListener(new FigButtonListener(this)); //������ ���� 

	btnRed = new TButton("RED", this);
	HICON redIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	redIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON8),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnRed->setIcon(redIcon);
	btnRed->addButtonListener(new ColorButtonListener(this)); //������ ���� 

	btnGreen = new TButton("GRREN", this);
	HICON greenIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	greenIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON9),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnGreen->setIcon(greenIcon);
	btnGreen->addButtonListener(new ColorButtonListener(this)); //������ ���� 

	btnBlue = new TButton("BLUE", this);
	HICON blueIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	blueIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON10),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBlue->setIcon(blueIcon);
	btnBlue->addButtonListener(new ColorButtonListener(this)); //������ ���� 

	btnBlack = new TButton("BLACK", this);
	HICON blackIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	blackIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON11),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBlack->setIcon(blackIcon);
	btnBlack->addButtonListener(new ColorButtonListener(this)); //������ ����

	btnBGRed = new TButton("BGRED", this);
	HICON bgredIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	bgredIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON4),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBGRed->setIcon(bgredIcon);
	btnBGRed->addButtonListener(new ColorButtonListener(this)); //������ ����

	btnBGGreen = new TButton("BGGreen", this);
	HICON bggreenIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	bggreenIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON5),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBGGreen->setIcon(bggreenIcon);
	btnBGGreen->addButtonListener(new ColorButtonListener(this)); //������ ����

	btnBGBlue = new TButton("BGBLUE", this);
	HICON bgblueIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	bgblueIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON6),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBGBlue->setIcon(bgblueIcon);
	btnBGBlue->addButtonListener(new ColorButtonListener(this)); //������ ����
	
	btnBGWhite = new TButton("BGWHITE", this);
	HICON bgwhiteIcon;  // �ٸ� ������ ������ ���� ������ ID �� IDI_ICON3 ��� �����ϰ�,
	bgwhiteIcon = (HICON)LoadImage(this->m_InstanceHandle, MAKEINTRESOURCE(IDI_ICON7),
		IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	btnBGWhite->setIcon(bgwhiteIcon);
	btnBGWhite->addButtonListener(new ColorButtonListener(this)); //������ ����

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

	//---------------�޴��� �޴�--------------------
	btnFile = new Menu("����", this);
	btnFile->addButtonListener(this);
	btnFig = new Menu("����", this);
	btnFig->addButtonListener(this);
	btnColor = new Menu("����", this);

	m_Menubar->addMenu(btnFile);
	m_Menubar->addMenu(btnFig);
	m_Menubar->addMenu(btnColor);
	//------------------------------------------------

	//--------------�޴��� �����޴�--------------------
	btnSave = new MenuItem("����", this);
	btnSave->addButtonListener(this);
	btnOpen = new MenuItem("����", this); 
	btnOpen->addButtonListener(this);

	btnR = new MenuItem("�簢��", this);
	btnR->addButtonListener(new FigButtonListener(this));
	btnE = new MenuItem("Ÿ��", this);
	btnE->addButtonListener(new FigButtonListener(this));
	btnL = new MenuItem("����", this);
	btnL->addButtonListener(new FigButtonListener(this));

	btnMRed = new MenuItem("����", this);
	btnMRed->addButtonListener(new ColorButtonListener(this));
	btnMGreen = new MenuItem("�ʷ�", this);
	btnMGreen->addButtonListener(new ColorButtonListener(this));
	btnMBlue = new MenuItem("�Ķ�", this);
	btnMBlue->addButtonListener(new ColorButtonListener(this));
	btnMBlack = new MenuItem("����", this);
	btnMBlack->addButtonListener(new ColorButtonListener(this));
	btnBGR = new MenuItem("B����", this);
	btnBGR->addButtonListener(new ColorButtonListener(this));
	btnBGG = new MenuItem("B�ʷ�", this);
	btnBGG->addButtonListener(new ColorButtonListener(this));
	btnBGB = new MenuItem("B�Ķ�", this);
	btnBGB->addButtonListener(new ColorButtonListener(this));
	btnBGW = new MenuItem("B�Ͼ�", this);
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

