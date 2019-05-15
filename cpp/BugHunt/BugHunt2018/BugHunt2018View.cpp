
// BugHunt2018View.cpp: CBugHunt2018View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "BugHunt2018.h"
#endif

#include "BugHunt2018Doc.h"
#include "BugHunt2018View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_TIMER_BUGMOVE 100
// CBugHunt2018View

IMPLEMENT_DYNCREATE(CBugHunt2018View, CView)

BEGIN_MESSAGE_MAP(CBugHunt2018View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CBugHunt2018View 构造/析构

CBugHunt2018View::CBugHunt2018View() noexcept
{
	// TODO: 在此处添加构造代码
	if (m_bmpBackgroud.Load(_T(".\\Bitmap\\Frog.jpg")) != S_OK)//.\\表示当前的工作路径
		AfxMessageBox(_T("Load the backgroud bitmap failed"));//_T作用是把非unicode字符集转换为unicode字符集
	Sprite::SetParentWnd(this);
}

CBugHunt2018View::~CBugHunt2018View()
{
}

BOOL CBugHunt2018View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CBugHunt2018View 绘图

void CBugHunt2018View::OnDraw(CDC* pDC)
{
	CBugHunt2018Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rectClient;
	GetClientRect(rectClient);

	int w = m_bmpBackgroud.GetWidth();
	int h = m_bmpBackgroud.GetHeight();
	int x = (rectClient.Width() - w) / 2;
	int y = (rectClient.Height() - h) / 2;
	m_bmpBackgroud.Draw(pDC->GetSafeHdc(), x, y);//(0,0)为起点
	for (auto p : pDoc->GetBuglist()) {
		if (p)
			p->Draw(pDC);
	}
}


// CBugHunt2018View 打印

BOOL CBugHunt2018View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CBugHunt2018View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CBugHunt2018View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CBugHunt2018View 诊断

#ifdef _DEBUG
void CBugHunt2018View::AssertValid() const
{
	CView::AssertValid();
}

void CBugHunt2018View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBugHunt2018Doc* CBugHunt2018View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBugHunt2018Doc)));
	return (CBugHunt2018Doc*)m_pDocument;
}
#endif //_DEBUG


// CBugHunt2018View 消息处理程序


void CBugHunt2018View::OnTimer(UINT_PTR nIDEvent)//时钟时间的ID
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CBugHunt2018Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	switch (nIDEvent) {
	case ID_TIMER_BUGMOVE:
		for (auto p : pDoc->GetBuglist()) {
			if (p)
				p->Move();
		}
		break;
	default:
		break;
	}
	Invalidate();
	CView::OnTimer(nIDEvent);
}


int CBugHunt2018View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(ID_TIMER_BUGMOVE, 30, NULL);
	return 0;
}


BOOL CBugHunt2018View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE; // CView::OnEraseBkgnd(pDC);
}
