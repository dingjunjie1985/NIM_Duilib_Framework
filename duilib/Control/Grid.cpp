#include "StdAfx.h"
#include "GridHeader.h"
#include "GridBody.h"

namespace ui
{
	Grid::Grid() 
		: ScrollableBox(new VLayout()){
		m_pHeader = new GridHeader;
		m_pBody = new GridBody;
		Add(m_pHeader);
		Add(m_pBody);

		m_pHeader->m_pGrid = this;
		m_pHeader->m_pBody = m_pBody;
		m_pBody->m_pGrid = this;
		m_pBody->m_pHeader = m_pHeader;

		SetBkColor(L"white");
	}

	Grid::~Grid(){
		m_pHeader->DetachControl();
		m_pBody->DetachControl();
	}

	void Grid::Init()
	{
		SetHeaderHeight(32);
		SetHeaderBkColor(L"splitline_level2");
		SetBorderColor(L"splitline_level2");
		SetBorderSize({ 1, 1, 1, 1 });
	}

	inline int Grid::GetColCount(){ return m_pHeader->m_hlayout.size(); };
	inline int Grid::GetRowCount(){ return m_pBody->m_vlayout.size(); }

	void Grid::SetHeaderHeight(int height){
		m_pHeader->SetFixedHeight(height);
	}

	void Grid::SetHeaderBkColor(std::wstring bkcolor){
		m_pHeader->SetBkColor(bkcolor);
	}

	bool Grid::AddHeaderEle(std::wstring text, int width)
	{
		return m_pHeader->AddHeaderEle(text, width);
	}

	bool Grid::AddRow()
	{
		return m_pBody->AddRow();
	}

	CSize Grid::CalcRequiredSize(const UiRect& rc)
	{
		assert(m_pHeader && m_pBody && m_pHeader->GetFixedWidth() == m_pBody->GetFixedWidth());
		CSize requiredSize;
		
		UiRect childSize = rc;
		if (!m_bScrollBarFloat && m_pVerticalScrollBar && m_pVerticalScrollBar->IsValid()) {
			childSize.right -= m_pVerticalScrollBar->GetFixedWidth();
		}
		if (!m_bScrollBarFloat && m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsValid()) {
			childSize.bottom -= m_pHorizontalScrollBar->GetFixedHeight();
		}
		/*requiredSize = */m_pLayout->ArrangeChild(m_items, childSize);

		requiredSize.cx = m_pHeader->GetFixedWidth() > 0 ? m_pHeader->GetFixedWidth() : 0;
		requiredSize.cy = m_pBody->GetFixedHeight() > 0 ? m_pBody->GetFixedHeight() : 0;

		return requiredSize;
	}

	void Grid::PaintChild(IRenderContext* pRender, const UiRect& rcPaint)
	{
		UiRect rcTemp;
		if (!::IntersectRect(&rcTemp, &rcPaint, &m_rcItem)) return;

		CSize scrollPos = GetScrollPos();
		UiRect rcNewPaint = GetPaddingPos();
		AutoClip alphaClip(pRender, rcNewPaint, m_bClip);
		rcNewPaint.Offset(scrollPos.cx, 0);
		rcNewPaint.Offset(GetRenderOffset().x, GetRenderOffset().y);

		CPoint ptOffset(scrollPos.cx, 0);
		CPoint ptOldOrg = pRender->OffsetWindowOrg(ptOffset);
		m_pHeader->AlphaPaint(pRender, rcNewPaint);
		pRender->SetWindowOrg(ptOldOrg);

		rcNewPaint.Offset(0, scrollPos.cy);
		ptOffset.y = scrollPos.cy;
		ptOldOrg = pRender->OffsetWindowOrg(ptOffset);
		m_pBody->AlphaPaint(pRender, rcNewPaint);
		pRender->SetWindowOrg(ptOldOrg);

		if (m_pHorizontalScrollBar && m_pHorizontalScrollBar->IsVisible()) {
			m_pHorizontalScrollBar->AlphaPaint(pRender, rcPaint);
		}

		if (m_pVerticalScrollBar && m_pVerticalScrollBar->IsVisible()) {
			m_pVerticalScrollBar->AlphaPaint(pRender, rcPaint);
		}

		static bool bFirstPaint = true;
		if (bFirstPaint) {
			bFirstPaint = false;
			LoadImageCache(true);
		}
	}
}