#include "StdAfx.h"

namespace ui
{
	Grid::Grid() : ScrollableBox(new VLayout()){
		
	}

	Grid::~Grid(){
	}

	GridBody* Grid::ConstructGridBody()
	{
		return new GridBody(this);
	}

	void Grid::Init()
	{
		if (m_bIsInit)
			return;

		m_pBody = ConstructGridBody();
		if (!m_pBody)
			m_pBody = new GridBody(this);
		Add(m_pBody);

		SetBkColor(L"white");
		SetBorderColor(L"splitline_level1");
		SetBorderSize({ 1, 1, 1, 1 });

		SetHeaderHeight(32);
		SetFixedBkColor(L"splitline_level2");
		SetGridLineColor(L"grid_line");
		
		if (m_pVerticalScrollBar)
			m_pVerticalScrollBar->SetAutoHideScroll(false);
		if (m_pHorizontalScrollBar)
			m_pHorizontalScrollBar->SetAutoHideScroll(false);

		m_bIsInit = true;
	}

	int Grid::GetColCount() const{ return m_pBody->GetColCount(); }
	void Grid::SetColCount(int count){ return m_pBody->SetColCount(count); }

	int Grid::GetRowCount() const{ return m_pBody->GetRowCount(); }
	void Grid::SetRowCount(int count){ return m_pBody->SetRowCount(count); }

	int Grid::GetFixedColCount() const{ return m_pBody->GetFixedColCount(); }
	void Grid::SetFixedColCount(int fixed){ return m_pBody->SetFixedColCount(fixed); }

	int Grid::GetFixedRowCount() const{ return m_pBody->GetFixedRowCount(); }
	void Grid::SetFixedRowCount(int fixed){ return m_pBody->SetFixedRowCount(fixed); }

	int Grid::GetHeaderHeight() const{ return m_pBody->GetHeaderHeight(); }
	void Grid::SetHeaderHeight(int height){
		m_pBody->SetHeaderHeight(height);
		SetScrollBarPadding({ 0, height, 0, 0 });
	}

	std::wstring Grid::GetFixedBkColor() const{ return m_pBody->GetFixedBkColor(); }
	void Grid::SetFixedBkColor(std::wstring bkcolor){ m_pBody->SetFixedBkColor(bkcolor); }

	std::wstring Grid::GetGridLineColor() const{ return m_pBody->GetGridLineColor(); }
	void Grid::SetGridLineColor(std::wstring bkcolor){ m_pBody->SetGridLineColor(bkcolor); }

	std::wstring Grid::GetGridItemText(int row, int col){ return m_pBody->GetGridItemText(row, col); }
	bool Grid::SetGridItemText(std::wstring text, int row, int col){ return m_pBody->SetGridItemText(text, row, col); }

	bool Grid::IsGridItemFixed(int row, int col){ return m_pBody->IsGridItemFixed(row, col); }

	int Grid::GetFixedColWidth() const{ return m_pBody->GetFixedColWidth(); }
	int Grid::GetFixedRowHeight() const{ return m_pBody->GetFixedRowHeight(); }
	
	GridItem* Grid::AddHeaderItem(std::wstring text, int width){ return m_pBody->AddHeaderItem(text, width); }
	bool Grid::AddRow(){ return m_pBody->AddRow(); }

	GridItem *Grid::GetGridItem(int row, int col){ return m_pBody->GetGridItem(row, col); }

	void Grid::Clear(bool include_header){ return m_pBody->Clear(include_header); }
	bool Grid::RemoveRow(int row){ return m_pBody->RemoveRow(row); }
	bool Grid::RemoveCol(int col){ return m_pBody->RemoveCol(col); }

	void Grid::AttachTextChange(const EventCallback& callback){ return m_pBody->AttachTextChange(callback); }

	bool Grid::ButtonDown(EventArgs& msg)
	{
		m_pBody->_EndEdit();
		return true;
	}
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