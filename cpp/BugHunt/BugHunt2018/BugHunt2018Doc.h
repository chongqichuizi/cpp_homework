
// BugHunt2018Doc.h: CBugHunt2018Doc 类的接口
//


#pragma once
#include "Bug.h"
#include <vector>

class CBugHunt2018Doc : public CDocument
{
protected: // 仅从序列化创建
	CBugHunt2018Doc() noexcept;
	DECLARE_DYNCREATE(CBugHunt2018Doc)

// 特性
public:

// 操作
public:
	const std::vector<Bug*> &GetBuglist()const { return m_listBug; }
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CBugHunt2018Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	std::vector<Bug*> m_listBug;
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
