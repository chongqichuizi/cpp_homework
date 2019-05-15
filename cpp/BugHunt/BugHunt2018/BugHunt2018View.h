
// BugHunt2018View.h: CBugHunt2018View 类的接口
//

#pragma once
#include <atlimage.h>

class CBugHunt2018View : public CView
{
protected: // 仅从序列化创建
	CBugHunt2018View() noexcept;
	DECLARE_DYNCREATE(CBugHunt2018View)

// 特性
public:
	CBugHunt2018Doc* GetDocument() const;

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
	virtual ~CBugHunt2018View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImage m_bmpBackgroud;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // BugHunt2018View.cpp 中的调试版本
inline CBugHunt2018Doc* CBugHunt2018View::GetDocument() const
   { return reinterpret_cast<CBugHunt2018Doc*>(m_pDocument); }
#endif

