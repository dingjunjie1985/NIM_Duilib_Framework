#include "stdafx.h"
#include "Chart.h"
#include "Coordinate.h"

using namespace ui;

namespace nim_comp
{
	namespace chart
	{
		Chart::Chart()
		{
			
		}
		Chart::~Chart()
		{
			m_pCoord = nullptr;
		}

		Coordinate* Chart::CreateCoordinate()
		{
			return new Coordinate(this);
		}

		void Chart::Init()
		{
			if (m_bIsInit)
				return;

			m_pCoord = CreateCoordinate();
			if (!m_pCoord)
				m_pCoord = new Coordinate(this);
			Add(m_pCoord);

			m_bIsInit = true;
		}

		bool Chart::AddDataSet(std::string name, DataSet* pDataSet)
		{
			return	m_pCoord->AddDataSet(name, pDataSet);
		}

		void Chart::PaintChild(IRenderContext* pRender, const UiRect& rcPaint)
		{
			return __super::PaintChild(pRender, rcPaint);
		}



	}
}






