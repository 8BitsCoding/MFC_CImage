
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_my_image.Load(L"test.png");

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// 투명도 확인을 위한 사각형 출력
		dc.FillSolidRect(100, 100, 200, 200, RGB(0, 0, 255));

		int w = m_my_image.GetWidth();
		int h = m_my_image.GetHeight();
		// m_my_image.Draw(dc, 0, 0, w/2, h/2);		// 원본 그림이 w/2, h/2만큼 작게 출력된다.
		// m_my_image.Draw(dc, 0, 0, w*2, h*2);		//원본 그림이 w*2, h*2만큼 크게 출력된다.
		m_my_image.Draw(dc, 0, 0, 200, 200, 50, 50, 200, 200);		// 그림의 일부만 그린다.
		// m_my_image.Draw(dc, 0, 0, 200*2, 200*2, 50, 50, 200, 200);	// 위 그림을 2배 확대한다.
		// 0, 0,은 출력좌표
		// CDialogEx::OnPaint();

		m_my_image.AlphaBlend(dc, 0, 0, 100);		// 투명도를 설정한다.
		m_my_image.Draw(dc, m_pos.x - 50, m_pos.y - 50, 100, 100, m_pos.x - 50, m_pos.y - 50, 100, 100);
		// 클릭한 지점을 다시 그린다.

		m_my_image.Draw(dc, w, 0, 100*2, 100*2, m_pos.x - 50, m_pos.y - 50, 100, 100);
		// 클릭한 지점을 확대해서 그린다.
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pos = point;
	Invalidate();

	CDialogEx::OnLButtonDown(nFlags, point);
}
