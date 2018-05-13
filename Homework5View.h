
// Homework5View.h : CHomework5View 类的接口
//

#pragma once

#include "MyOpenGL.h"
class CHomework5View : public CView
{
protected: // 仅从序列化创建
	CHomework5View();
	DECLARE_DYNCREATE(CHomework5View)

// 特性
public:
	CHomework5Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CHomework5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	CMyOpenGL m_gl;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // Homework5View.cpp 中的调试版本
inline CHomework5Doc* CHomework5View::GetDocument() const
   { return reinterpret_cast<CHomework5Doc*>(m_pDocument); }
#endif

