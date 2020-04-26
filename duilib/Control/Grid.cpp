#include "StdAfx.h"

namespace ui
{
	template<typename InheritType = Control>
	void GridHeadEleTemplate<InheritType>::HandleMessage(EventArgs& msg)
	{
		if (!IsMouseEnabled() && msg.Type > kEventMouseBegin && msg.Type < kEventMouseEnd) {
			if (m_pParent != NULL) m_pParent->HandleMessageTemplate(msg);
			return;
		}
		//UiRect rc = m_rcItem;
		if (msg.Type == kEventMouseButtonDown)
		{
			RECT rect = { m_rcItem.right - 4, m_rcItem.top, m_rcItem.right, m_rcItem.bottom };
			if (PtInRect(&rect, msg.ptMouse)){
				::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
				m_pHeader->DoResizeMessage(msg);
			}
		}
		else if (msg.Type == kEventMouseMove)
		{
			RECT rect = { m_rcItem.right - 4, m_rcItem.top, m_rcItem.right, m_rcItem.bottom };
			if (PtInRect(&rect, msg.ptMouse)){
				::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
				m_pHeader->DoResizeMessage(msg);
			}
			else if (IsMouseFocused())
			{
				::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
				m_pHeader->DoResizeMessage(msg);
			}
		}
		else if (msg.Type == kEventMouseButtonUp)
		{
			if (IsMouseFocused())
				m_pHeader->DoResizeMessage(msg);
		}
		__super::HandleMessage(msg);
	}

	template<typename InheritType = Control>
	void GridHeadEleTemplate<InheritType>::PaintText(IRenderContext* pRender)
	{
		if (m_pEleInfo->strText.empty()) return;
		UiRect rc = this->m_rcItem;
		rc.left += m_pEleInfo->rcTextPadding.left;
		rc.right -= m_pEleInfo->rcTextPadding.right;
		rc.top += m_pEleInfo->rcTextPadding.top;
		rc.bottom -= m_pEleInfo->rcTextPadding.bottom;

		bool bLineLimit = false;
		std::wstring sFontId;
		pRender->DrawText(rc, m_pEleInfo->strText, 0xff000000, sFontId, m_pEleInfo->uTextStyle, 255, bLineLimit);
	}

	template<typename InheritType = Control>
	void GridHeadEleTemplate<InheritType>::PaintBorder(IRenderContext* pRender)
	{
		UiRect rcBorder;
		rcBorder.left = rcBorder.right = m_rcItem.right - 2;
		rcBorder.top = m_rcItem.top + 4;
		rcBorder.bottom = m_rcItem.bottom - 4;
		pRender->DrawLine(rcBorder, 1, 0xff000000);
	}

	bool GridHeader::Add(Control* pControl)
	{
		GridHeadEleControl *ele = dynamic_cast<GridHeadEleControl*>(pControl);
		assert(ele);
		if (!ele){
			delete ele;
			return false;
		}
		ele->SetBkColor(m_strHeaderBkColor);
		ele->SetFixedWidth(80);
		ele->SetFixedHeight(32);
		ele->m_nIndex = GetCount();
		ele->m_pHeader = this;
		return __super::Add(ele);
	}

	void GridHeader::SetHeaderBkColor(std::wstring bkcolor)
	{
		if (bkcolor == m_strHeaderBkColor)
			return;
		m_strHeaderBkColor = bkcolor;
		for each (auto it in m_items)
		{
			it->SetBkColor(m_strHeaderBkColor);
		}
	}

	void GridHeader::DoResizeMessage(EventArgs& msg)
	{
		if (msg.Type == kEventMouseButtonDown)
		{
			m_ptStartResize = msg.ptMouse;
		}
		else if (msg.Type == kEventMouseButtonUp)
		{
			//assert(m_ptStartResize.x != -1);
			if (m_ptStartResize.x != -1)
			{

			}
		}
	}

	Grid::Grid(){
		m_pHeader = new GridHeader;
		m_pBody = new GridBody;
		Add(m_pHeader);
		Add(m_pBody);

		m_pHeader->m_pOwner = this;
		m_pBody->m_pOwner = this;
		m_pBody->m_pHeader = m_pHeader;
	}

	Grid::~Grid(){

	}

	void Grid::Init()
	{
		SetHeaderHeight(32);
		SetHeaderBkColor(L"gray");
		SetBorderColor(L"gray");
		SetBorderSize({ 1, 1, 1, 1 });
	}


	void Grid::SetHeaderHeight(int height){
		m_pHeader->SetFixedHeight(height);
	}
	void Grid::SetHeaderBkColor(std::wstring bkcolor){
		m_pHeader->SetHeaderBkColor(bkcolor);
	}

	bool Grid::AddHeaderEle(std::wstring text)
	{
		GridHeadEleControl *item = new GridHeadEleControl;
		item->m_pEleInfo->strText = text;
		return m_pHeader->Add(item);
	}
}