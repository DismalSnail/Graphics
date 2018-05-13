
// Homework5View.cpp : CHomework5View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHomework5View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CHomework5View 构造/析构

CHomework5View::CHomework5View()
{
	// TODO: 在此处添加构造代码

}

CHomework5View::~CHomework5View()
{
}

BOOL CHomework5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CHomework5View 绘制

void CHomework5View::OnDraw(CDC* /*pDC*/)
{
	CHomework5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_gl.OnPaint();
	// TODO: 在此处为本机数据添加绘制代码
}


// CHomework5View 打印


void CHomework5View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHomework5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHomework5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHomework5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CHomework5View 诊断

#ifdef _DEBUG
void CHomework5View::AssertValid() const
{
	CView::AssertValid();
}

void CHomework5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHomework5Doc* CHomework5View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHomework5Doc)));
	return (CHomework5Doc*)m_pDocument;
}
#endif //_DEBUG


// CHomework5View 消息处理程序


void CHomework5View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_gl.OnSize(cx,cy);

	// TODO: 在此处添加消息处理程序代码
}


void CHomework5View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_gl.OnPaint();

	CView::OnTimer(nIDEvent);
}


BOOL CHomework5View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


BOOL CHomework5View::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
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
	// TODO: 在此添加专用代码和/或调用基类
}
