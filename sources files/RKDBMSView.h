
// RKDBMSView.h : interface of the CRKDBMSView class
//
 
#pragma once
#include "RKDBMSDoc.h"

class CRKDBMSView : public CView
{
	DECLARE_DYNCREATE(CRKDBMSView)
protected: // create from serialization only
	CRKDBMSView();
	virtual ~CRKDBMSView();
	
// Attributes
public:
	CRKDBMSDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:

// Implementation
public:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in RKDBMSView.cpp
inline CRKDBMSDoc* CRKDBMSView::GetDocument() const
   { return reinterpret_cast<CRKDBMSDoc*>(m_pDocument); }
#endif

