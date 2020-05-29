#include "StdAfx.h"
#include "GridHeader.h"
#include "GridBody.h"

namespace ui
{
	template<typename InheritType>
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

	template<typename InheritType>
	void GridHeadEleTemplate<InheritType>::PaintText(IRenderContext* pRender)
	{
		if (m_sText.empty()) return;
		UiRect rc = this->m_rcItem;
		rc.left += m_rcTextPadding.left;
		rc.right -= m_rcTextPadding.right;
		rc.top += m_rcTextPadding.top;
		rc.bottom -= m_rcTextPadding.bottom;

		bool bLineLimit = false;
		std::wstring sFontId;
		pRender->DrawText(rc, m_sText, 0xff000000, sFontId, m_uTextStyle, 255, bLineLimit);
	}

	//------------------------------------GridHeader-----------------------------------------
	bool GridHeader::AddHeaderEle(std::wstring text, int width)
	{
		GridHeadEleControl *item = new GridHeadEleControl(text, width);
		item->SetBkColor(m_strHeaderBkColor);
		item->SetFixedHeight(GetFixedHeight());
		item->m_nIndex = GetCount();
		item->m_pHeader = this;
		bool ret = __super::Add(item);
		if (ret){
			if (GetFixedWidth() == DUI_LENGTH_STRETCH){
				SetFixedWidth(item->GetFixedWidth());
			}
			else{
				SetFixedWidth(GetFixedWidth() + item->GetFixedWidth());
			}
			m_pBody->SetFixedWidth(GetFixedWidth());
			m_hlayout.push_back(width);
		}
		else
			delete item;
		return ret;
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

	void GridHeader::PaintBorder(IRenderContext* pRender)
	{
		__super::PaintBorder(pRender);
		if (m_hlayout.size() > 0)
		{
			//CSize offsz = m_pGrid->GetScrollPos();
			int posx = 0;
			UiRect rcLineV;
			rcLineV.top = m_rcItem.top + 6;
			rcLineV.bottom = m_rcItem.top + GetHeight() - 6;
			for (auto it = m_hlayout.cbegin(); it != m_hlayout.cend(); it++)
			{
				posx += *it;
				rcLineV.left = rcLineV.right = m_rcItem.left + posx - 1;		//tip by djj 20200529 这里不需要offset HScrollPos, 貌似pRender里面已经offset了
				pRender->DrawLine(rcLineV, 1, 0xffcccccc);
			}
		}
	}
}