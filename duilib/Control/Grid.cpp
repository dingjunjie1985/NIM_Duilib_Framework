#include "StdAfx.h"
#include "GridBody.h"

namespace ui
{
	Grid::Grid() : ScrollableBox(new VLayout()){
		m_pBody = new GridBody(this);
		Add(m_pBody);

		SetBkColor(L"white");
	}

	Grid::~Grid(){
		m_pBody->DetachControl();
	}

	void Grid::Init()
	{
		SetHeaderHeight(32);
		SetFixedBkColor(L"splitline_level2");
		SetBorderColor(L"splitline_level1");
		SetGridLineColor(L"grid_line");
		SetBorderSize({ 1, 1, 1, 1 });
		if (m_pVerticalScrollBar)
			m_pVerticalScrollBar->SetAutoHideScroll(false);
		if (m_pHorizontalScrollBar)
			m_pHorizontalScrollBar->SetAutoHideScroll(false);
	}

	int Grid::GetColCount() const{ return m_pBody->GetColCount(); }
	int Grid::GetRowCount() const{ return m_pBody->GetRowCount(); }
	int Grid::GetFixedColCount() const{ return m_pBody->GetFixedColCount(); }
	int Grid::GetFixedRowCount() const{ return m_pBody->GetFixedRowCount(); }
	int Grid::GetFixedColWidth() const{ return m_pBody->GetFixedColWidth(); }
	int Grid::GetFixedRowHeight() const{ return m_pBody->GetFixedRowHeight(); }
	int Grid::GetHeaderHeight() const{ return m_pBody->GetHeaderHeight(); }
	std::wstring Grid::GetFixedBkColor() const{ return m_pBody->GetFixedBkColor(); }
	std::wstring Grid::GetGridLineColor() const{ return m_pBody->GetGridLineColor(); }

	void Grid::SetColCount(int count){ return m_pBody->SetColCount(count); }
	void Grid::SetRowCount(int count){ return m_pBody->SetRowCount(count); }
	void Grid::SetFixedColCount(int fixed){ return m_pBody->SetFixedColCount(fixed); }
	void Grid::SetFixedRowCount(int fixed){ return m_pBody->SetFixedRowCount(fixed); }
	void Grid::SetHeaderHeight(int height){ 
		m_pBody->SetHeaderHeight(height); 
		SetScrollBarPadding({ 0, height, 0, 0 });
	}
	void Grid::SetFixedBkColor(std::wstring bkcolor){ m_pBody->SetFixedBkColor(bkcolor); }
	void Grid::SetGridLineColor(std::wstring bkcolor){ m_pBody->SetGridLineColor(bkcolor); }

	GridItem* Grid::AddHeaderItem(std::wstring text, int width){ return m_pBody->AddHeaderItem(text, width); }
	bool Grid::AddRow(){ return m_pBody->AddRow(); }

	GridItem *Grid::GetGridItem(int row, int col){ return m_pBody->GetGridItem(row, col); }

	void Grid::PaintChild(IRenderContext* pRender, const UiRect& rcPaint)
	{
		UiRect rcTemp;
		if (!::IntersectRect(&rcTemp, &rcPaint, &m_rcItem)) return;

		for (auto it = m_items.begin(); it != m_items.end(); it++) {
			Control* pControl = *it;
			if (!pControl->IsVisible()) continue;
			pControl->AlphaPaint(pRender, rcPaint);
		}

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