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
		SetScrollBarPadding({ 0, 32, 0, 0 });
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

	int Grid::GetFixedColWidth()
	{
		return 30;
	}
	int Grid::GetFixedRowHeight()
	{
		return m_pHeader->GetFixedHeight();
	}

	void Grid::ProcessVScrollBar(UiRect rc, int cyRequired)
	{
		UiRect rcScrollBarPos = rc;
		rcScrollBarPos.left += m_rcScrollBarPadding.left;
		rcScrollBarPos.top += m_rcScrollBarPadding.top;
		rcScrollBarPos.right -= m_rcScrollBarPadding.right;
		rcScrollBarPos.bottom -= m_rcScrollBarPadding.bottom;

		if (m_pVerticalScrollBar == NULL) return;

		rc.left += m_pLayout->GetPadding().left;
		rc.top += m_pLayout->GetPadding().top;
		rc.right -= m_pLayout->GetPadding().right;
		rc.bottom -= m_pLayout->GetPadding().bottom;
		int nHeight = rc.bottom - rc.top - GetFixedRowHeight();
		if (cyRequired > nHeight && !m_pVerticalScrollBar->IsValid()) {
			m_pVerticalScrollBar->SetScrollRange(cyRequired - nHeight);
			m_pVerticalScrollBar->SetScrollPos(0);
			m_bScrollProcess = true;
			SetPos(m_rcItem);
			m_bScrollProcess = false;

			return;
		}
		// No scrollbar required
		if (!m_pVerticalScrollBar->IsValid()) return;

		// Scroll not needed anymore?
		int cyScroll = cyRequired - nHeight;
		if (cyScroll <= 0 && !m_bScrollProcess) {
			m_pVerticalScrollBar->SetScrollPos(0);
			m_pVerticalScrollBar->SetScrollRange(0);
			SetPos(m_rcItem);
		}
		else {
			UiRect rcVerScrollBarPos(rcScrollBarPos.right - m_pVerticalScrollBar->GetFixedWidth(), rcScrollBarPos.top, rcScrollBarPos.right, rcScrollBarPos.bottom);
			m_pVerticalScrollBar->SetPos(rcVerScrollBarPos);

			if (m_pVerticalScrollBar->GetScrollRange() != cyScroll) {
				int iScrollPos = m_pVerticalScrollBar->GetScrollPos();
				m_pVerticalScrollBar->SetScrollRange(::abs(cyScroll));
				if (!m_pVerticalScrollBar->IsValid()) {
					m_pVerticalScrollBar->SetScrollPos(0);
				}

				if (iScrollPos > m_pVerticalScrollBar->GetScrollPos()) {
					SetPos(m_rcItem);
				}
			}
		}
	}

	void Grid::ProcessHScrollBar(UiRect rc, int cxRequired)
	{
		UiRect rcScrollBarPos = rc;
		rcScrollBarPos.left += m_rcScrollBarPadding.left;
		rcScrollBarPos.top += m_rcScrollBarPadding.top;
		rcScrollBarPos.right -= m_rcScrollBarPadding.right;
		rcScrollBarPos.bottom -= m_rcScrollBarPadding.bottom;

		if (m_pHorizontalScrollBar == NULL) return;

		rc.left += m_pLayout->GetPadding().left;
		rc.top += m_pLayout->GetPadding().top;
		rc.right -= m_pLayout->GetPadding().right;
		rc.bottom -= m_pLayout->GetPadding().bottom;
		int nWidth = rc.right - rc.left/* - GetFixedColWidth()*/;
		if (cxRequired > nWidth && !m_pHorizontalScrollBar->IsValid()) {
			m_pHorizontalScrollBar->SetScrollRange(cxRequired - nWidth);
			m_pHorizontalScrollBar->SetScrollPos(0);
			m_bScrollProcess = true;
			SetPos(m_rcItem);
			m_bScrollProcess = false;

			return;
		}
		// No scrollbar required
		if (!m_pHorizontalScrollBar->IsValid()) return;

		// Scroll not needed anymore?
		int cxScroll = cxRequired - nWidth;
		if (cxScroll <= 0 && !m_bScrollProcess) {
			m_pHorizontalScrollBar->SetScrollPos(0);
			m_pHorizontalScrollBar->SetScrollRange(0);
			SetPos(m_rcItem);
		}
		else {
			UiRect rcVerScrollBarPos(rcScrollBarPos.left, rcScrollBarPos.bottom - m_pHorizontalScrollBar->GetFixedHeight(), rcScrollBarPos.right, rcScrollBarPos.bottom);
			m_pHorizontalScrollBar->SetPos(rcVerScrollBarPos);

			if (m_pHorizontalScrollBar->GetScrollRange() != cxScroll) {
				int iScrollPos = m_pHorizontalScrollBar->GetScrollPos();
				m_pHorizontalScrollBar->SetScrollRange(::abs(cxScroll));
				if (!m_pHorizontalScrollBar->IsValid()) {
					m_pHorizontalScrollBar->SetScrollPos(0);
				}

				if (iScrollPos > m_pHorizontalScrollBar->GetScrollPos()) {
					SetPos(m_rcItem);
				}
			}
		}
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