
// Homework5View.cpp : CHomework5View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Homework5.h"
#endif

#include "Homework5Doc.h"
#include "Homework5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHomework5View

IMPLEMENT_DYNCREATE(CHomework5View, CView)

BEGIN_MESSAGE_MAP(CHomework5View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHomework5View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CHomework5View ����/����

CHomework5View::CHomework5View()
{
	// TODO: �ڴ˴���ӹ������

}

CHomework5View::~CHomework5View()
{
}

BOOL CHomework5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CHomework5View ����

void CHomework5View::OnDraw(CDC* /*pDC*/)
{
	CHomework5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_gl.OnPaint();
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CHomework5View ��ӡ


void CHomework5View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHomework5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CHomework5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CHomework5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CHomework5View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHomework5View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHomework5View ���

#ifdef _DEBUG
void CHomework5View::AssertValid() const
{
	CView::AssertValid();
}

void CHomework5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHomework5Doc* CHomework5View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHomework5Doc)));
	return (CHomework5Doc*)m_pDocument;
}
#endif //_DEBUG


// CHomework5View ��Ϣ�������


void CHomework5View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_gl.OnSize(cx,cy);

	// TODO: �ڴ˴������Ϣ����������
}


void CHomework5View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_gl.OnPaint();

	CView::OnTimer(nIDEvent);
}


BOOL CHomework5View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


BOOL CHomework5View::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_gl.PreTranslateMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
	return CView::PreTranslateMessage(pMsg);
}


void CHomework5View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	if (!m_gl.Init(GetSafeHwnd()))
	{
		AfxMessageBox("error");
	}
	SetTimer(1,30,NULL);
	// TODO: �ڴ����ר�ô����/����û���
}
