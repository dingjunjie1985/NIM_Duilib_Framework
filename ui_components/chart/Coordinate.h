#pragma once
#include "ChartBase.h"

namespace nim_comp
{
	namespace chart
	{
		//坐标系
		class Coordinate : public ui::Control
		{
			friend class Chart;
			friend class DataSet;
		public:
			Coordinate(Chart *pChart);
			virtual ~Coordinate();

		public:
			bool AddDataSet(std::string name, DataSet* pDataSet);

		public:
			virtual void Paint(ui::IRenderContext* pRender, const ui::UiRect& rcPaint) override;
			virtual void PaintBkColor(ui::IRenderContext*pRender) override;
			virtual void PaintBody(ui::IRenderContext* pRender);					//not override
			virtual void PaintBorder(ui::IRenderContext* pRender) override;

		protected:
			Chart *m_pChart = nullptr;
			CoordinateDimension m_dimension = CoordinateDimension_2D;
			int m_nStyle = CoordinateStyle_Quadrant1 | CoordinateStyle_Zoom | CoordinateStyle_BK_Grid;
			Axis m_hAxis;
			Axis m_vAxis;
			std::map<std::string, DataSet*> m_mapDataSet;

			ui::UiRect m_rcInset = { 35, 5, 5, 20  };		//原点对于Chart的偏移像素
			int m_nGridCellSize = 60;
		};


	}
}






