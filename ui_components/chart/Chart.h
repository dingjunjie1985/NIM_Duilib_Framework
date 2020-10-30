#pragma once
#include "ChartBase.h"

namespace nim_comp
{
	namespace chart
	{
		class Chart : public ui::Box
		{
			
		public:
			Chart();
			virtual ~Chart();
			virtual Coordinate* CreateCoordinate();		//继承类需要重载这个接口 并实现自定义GridBody
			virtual void Init() override;
		public:
			bool AddDataSet(std::string name, DataSet* pDataSet);

		public:
			virtual void PaintChild(ui::IRenderContext* pRender, const ui::UiRect& rcPaint) override;

		protected:
			Coordinate *m_pCoord = nullptr;
			
			int m_nChartStyle = ChartFrameStyle_Zoom;

			bool m_bIsInit = false;

		};



	}
}






