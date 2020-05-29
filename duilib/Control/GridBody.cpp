#include "StdAfx.h"
#include "GridBody.h"
#include "GridHeader.h"

namespace ui
{
	bool GridBody::AddRow()
	{
		m_vlayout.push_back(m_defaultRowHeight);
		if (GetFixedHeight() == DUI_LENGTH_STRETCH)
		{
			SetFixedHeight(m_defaultRowHeight);
		}
		else
		{
			SetFixedHeight(GetFixedHeight() + m_defaultRowHeight);
		}
		Invalidate();
		return true;
	}

	void GridBody::PaintBorder(IRenderContext* pRender)
	{
		__super::PaintBorder(pRender);
		if (m_bPaintGridLine && m_vlayout.size() > 0)
		{
			pRender->SetWindowOrg({ -m_rcItem.left, -m_rcItem.top });
			CSize offsz = m_pGrid->GetScrollPos();
			int posx = 0, posy = 0;
			UiRect rcLineH, rcLineV;
			//draw rcLineH
			rcLineH.left = 0;
			rcLineH.right = m_pHeader->GetFixedWidth();
			for (auto it = m_vlayout.cbegin(); it != m_vlayout.cend(); it++)
			{
				posy += *it;
				if (posy - offsz.cy > 0)
				{
					rcLineH.top = rcLineH.bottom = posy - offsz.cy - 1;
					pRender->DrawLine(rcLineH, 1, 0xffcccccc);
				}
			}

			//draw rcLineV
			rcLineV.top = 0;
			rcLineV.bottom = posy > GetHeight() ? GetHeight() : posy;
			for (auto it = m_pHeader->m_hlayout.cbegin(); it != m_pHeader->m_hlayout.cend(); it++)
			{
				posx += *it;
				if (posx - offsz.cx > 0)
				{
					rcLineV.left = rcLineV.right = posx - offsz.cx - 1;
					pRender->DrawLine(rcLineV, 1, 0xffcccccc);
				}
			}
			pRender->SetWindowOrg({ 0, 0 });
		}
	}

	void GridBody::PaintText(IRenderContext* pRender)
	{
		int posx = 30;
		int posy = 0;
		for (size_t i = 0; i < m_vlayout.size(); i++)
		{
			DWORD dwClrColor = GlobalManager::GetTextColor(L"textdefaultcolor");
			wchar_t wbuf[16] = {};
			_itow(i + 1, wbuf, 10);
			UiRect rc = { 0, posy, 30, posy + m_vlayout[i] };
			rc.Offset({ m_rcItem.left, m_rcItem.top });
			pRender->DrawText(rc, wbuf, dwClrColor, L"system_12", m_uTextStyle, 255, false);
			posy += m_vlayout[i];
		}

		for (size_t i = 0; i < 10; i++)
		{
			DWORD dwClrColor = GlobalManager::GetTextColor(L"textdefaultcolor");
			wchar_t wbuf[16] = {};
			_itow(i + 1, wbuf, 10);
			UiRect rc = { posx, 0, posx + 80, 24 };
			rc.Offset({ m_rcItem.left, m_rcItem.top });
			pRender->DrawText(rc, wbuf, dwClrColor, L"system_12", m_uTextStyle, 255, false);
			posx += 80;
		}
	}
}