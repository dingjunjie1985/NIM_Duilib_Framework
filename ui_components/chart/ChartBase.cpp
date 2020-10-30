#include "stdafx.h"
#include "ChartBase.h"
#include "Coordinate.h"

using namespace ui;

namespace nim_comp
{
	namespace chart
	{
		void DataSet::Paint(ui::IRenderContext* pRender, const ui::UiRect& rcPaint, Coordinate *pCoord)
		{
			float fHAxisDistance = pCoord->m_hAxis.range[1] - pCoord->m_hAxis.range[0];
			float fVAxisDistance = pCoord->m_vAxis.range[1] - pCoord->m_vAxis.range[0];
			int nHAxisLen = rcPaint.GetWidth();
			int nVAxisLen = rcPaint.GetHeight();

			if (geometry_type == DataGeometryType_PolygonalLine)
			{
				CPoint ptPrev = { -1, -1 };
				for each (DataInfo *pDataInfo in data_set)
				{
					if (pDataInfo->pos[0] > pCoord->m_hAxis.range[1] || pDataInfo->pos[0] < pCoord->m_hAxis.range[0]
						|| pDataInfo->value > pCoord->m_vAxis.range[1] || pDataInfo->value < pCoord->m_vAxis.range[0])
						continue;
					int x = (pDataInfo->pos[0] - pCoord->m_hAxis.range[0]) * nHAxisLen / fHAxisDistance + rcPaint.left;
					int y = (pCoord->m_vAxis.range[1] - pDataInfo->value) * nVAxisLen / fVAxisDistance + rcPaint.top;
					pRender->FillEllipse({ x - 3, y - 3, x + 3, y + 3 }, base_color);
					if (ptPrev.x != -1)
					{
						pRender->DrawLine({ ptPrev.x, ptPrev.y, x, y }, 1, base_color);
					}

					ptPrev = { x, y };
				}
			}
			else if (geometry_type == DataGeometryType_Bar)
			{
				for each (DataInfo *pDataInfo in data_set)
				{
					if (pDataInfo->pos[0] > pCoord->m_hAxis.range[1] || pDataInfo->pos[0] < pCoord->m_hAxis.range[0]
						|| pDataInfo->value > pCoord->m_vAxis.range[1] || pDataInfo->value < pCoord->m_vAxis.range[0])
						continue;
					int x = (pDataInfo->pos[0] - pCoord->m_hAxis.range[0]) * nHAxisLen / fHAxisDistance + rcPaint.left;
					int y = (pCoord->m_vAxis.range[1] - pDataInfo->value) * nVAxisLen / fVAxisDistance + rcPaint.top;
					UiRect rc = { x - 6, y, x + 6, rcPaint.bottom };
					pRender->DrawRect(rc, 1, base_color);
				}
			}
		}

		



	}
}






