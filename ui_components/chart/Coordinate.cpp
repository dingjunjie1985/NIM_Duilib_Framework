#include "stdafx.h"
#include "Coordinate.h"
#include "Chart.h"

using namespace ui;

namespace nim_comp
{
	namespace chart
	{
		//-------------------------------------Coordinate---------------------------------------
		//-------------------------------------Coordinate---------------------------------------

		Coordinate::Coordinate(Chart *pChart) :m_pChart(pChart){
		}

		Coordinate::~Coordinate(){
			for each (auto it in m_mapDataSet)
			{
				delete it.second;
			}
			m_mapDataSet.clear();
			m_pChart = nullptr;
		}

		bool Coordinate::AddDataSet(std::string name, DataSet* pDataSet)
		{
			m_mapDataSet[name] = pDataSet;
			return true;
		}

		void Coordinate::Paint(IRenderContext* pRender, const UiRect& rcPaint)
		{
			if (!::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem)) return;

			PaintBkColor(pRender);
			PaintBkImage(pRender);
			PaintStatusColor(pRender);
			PaintStatusImage(pRender);
			PaintBody(pRender);
			PaintBorder(pRender);

		}

		void Coordinate::PaintBkColor(ui::IRenderContext*pRender)
		{
			__super::PaintBkColor(pRender);
			if (m_nStyle & CoordinateStyle_BK_Grid)
			{
				UiRect rcCoord = m_pChart->GetPos();
				rcCoord.Deflate(m_rcInset);
				int index = 0;
				DWORD dwColorDark = GetTextColor(L"bk_dark");
				DWORD dwColorLight = GetTextColor(L"bk_light");
				DWORD dwLine = GetTextColor(L"color_sep_line");
				for (int left = rcCoord.left; left < rcCoord.right; left += m_nGridCellSize)
				{
					int right = left + m_nGridCellSize;
					if (right > rcCoord.right)
						right = rcCoord.right;
					UiRect rc(left, rcCoord.top, right, rcCoord.bottom);
					DWORD dwColor = dwColorDark;
					if ((index % 2) == 1)
					{
						dwColor = dwColorLight;
					}
					pRender->DrawColor(rc, dwColor);
					index++;
				}

				for (int top = rcCoord.bottom - m_nGridCellSize; top > rcCoord.top; top -= m_nGridCellSize)
				{
					UiRect rc(rcCoord.left, top, rcCoord.right - 1, top);
					pRender->DrawLine(rc, 1, dwLine);
				}
				for (int left = rcCoord.left + m_nGridCellSize; left < rcCoord.right; left += m_nGridCellSize)
				{
					UiRect rc(left, rcCoord.top, left, rcCoord.bottom - 1);
					pRender->DrawLine(rc, 1, dwLine);
				}
			}
		}

		void Coordinate::PaintBorder(IRenderContext* pRender)
		{
			__super::PaintBorder(pRender);
		}

		void Coordinate::PaintBody(IRenderContext* pRender)
		{
			UiRect rcCoord = m_pChart->GetPos();
			rcCoord.Deflate(m_rcInset);
			for (auto it = m_mapDataSet.cbegin(); it != m_mapDataSet.cend(); it++)
			{
				DataSet *pDataSet = it->second;
				pDataSet->Paint(pRender, rcCoord, this);
			}
		}

	


	}
}






