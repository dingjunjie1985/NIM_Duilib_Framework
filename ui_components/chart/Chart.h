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
			virtual Coordinate* CreateCoordinate();		//�̳�����Ҫ��������ӿ� ��ʵ���Զ���GridBody
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






