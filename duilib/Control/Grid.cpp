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
}