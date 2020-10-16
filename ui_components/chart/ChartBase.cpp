#include "stdafx.h"
#include "ChartBase.h"

using namespace ui;

namespace nim_comp
{
	namespace chart
	{
		Chart::Chart()
		{
			m_pCoord = new Coordinate;
		}
		Chart::~Chart()
		{
			for each (auto it in m_mapDataSet)
			{
				delete it.second;
			}
			m_mapDataSet.clear();

			if (m_pCoord)
			{
				delete m_pCoord;
			}
		}

		void Chart::PaintChild(IRenderContext* pRender, const UiRect& rcPaint)
		{
			return __super::PaintChild(pRender, rcPaint);
		}

		void Chart::Paint(IRenderContext* pRender, const UiRect& rcPaint)
		{
			if (!::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem)) return;

			PaintBkColor(pRender);
			PaintBkImage(pRender);
			PaintStatusColor(pRender);
			PaintStatusImage(pRender);
			//PaintText(pRender);
			PaintBody(pRender);
			PaintBorder(pRender);

		}

		void Chart::PaintBkColor(ui::IRenderContext*pRender)
		{
			__super::PaintBkColor(pRender);
			if (m_nChartStyle & ChartFrameStyle_Grid)
			{
				int offx = m_pCoord->m_szOff.cx;
				int offy = m_pCoord->m_szOff.cy;
				int index = 0;
				for (int left = m_rcItem.left + offx; left < m_rcItem.right; left += 60)
				{
					UiRect rc(left, m_rcItem.top, left + 60, m_rcItem.bottom - offy);
					DWORD dwColor = 0xffeacd07;
					if ((index % 2) == 1)
					{
						dwColor = 0xffcdae07;
					}
					pRender->DrawColor(rc, dwColor);
					index++;
				}

				for (int top = m_rcItem.bottom - offy; top > m_rcItem.top; top -= 60)
				{
					UiRect rc(m_rcItem.left, top, m_rcItem.right, top);
					pRender->DrawLine(rc, 1, 0xfffadd07);
				}
			}
		}

		void Chart::PaintBorder(IRenderContext* pRender)
		{
			__super::PaintBorder(pRender);
		}

		void Chart::PaintBody(IRenderContext* pRender)
		{

		}







	}
}






