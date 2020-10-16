#pragma once

namespace nim_comp
{
	namespace chart
	{
		enum CoordinateDimension				//����ϵά��
		{
			CoordinateDimension_2D = 2,
			CoordinateDimension_3D = 3
		};

		enum CoordinateStyle					//����ϵ���
		{
			CoordinateStyle_Quadrant1 = (1 << 0),	//��1����
			CoordinateStyle_Quadrant2 = (1 << 1),	//��2����
			CoordinateStyle_Quadrant3 = (1 << 2),	//��3����
			CoordinateStyle_Quadrant4 = (1 << 3),	//��4����
			CoordinateStyle_Zoom = (1 << 4),		//����
		};

		enum DataGeometryType					//���ݼ�������
		{
			DataGeometryType_PolygonalLine = 0,	//����
			DataGeometryType_CurveLine,			//����
			DataGeometryType_Bar,				//��״ͼ
			DataGeometryType_Pie				//��ͼ
		};

		enum DataStyle
		{
			DataStyle_Animation = (1 << 0),		//����Ч��
			DataStyle_MouseTip = (1 << 1),		//����Ч��
		};

		enum ChartFrameStyle
		{
			ChartFrameStyle_Grid = (1 << 0),	//����Ч��
		};

		//������
		class Axis{
		public:
			std::wstring title;
			ui::CSize range;
		public:
			Axis(){};
			virtual ~Axis(){};
		};

		//����ϵ
		class Coordinate
		{
			friend class Chart;
		public:
			Coordinate(){};
			virtual ~Coordinate(){};

		protected:
			CoordinateDimension m_dimension = CoordinateDimension_2D;
			int m_nStyle = CoordinateStyle_Quadrant1 | CoordinateStyle_Zoom;
			Axis m_hAxis;
			Axis m_vAxis;

			ui::CSize m_szOff = {5,5};		//ԭ�����Chart��ƫ������
		};

		//����������Ϣ
		class DataInfo
		{
		public:
			double  pos[3];
			double	value;
		public:
			DataInfo(){ memset(pos, 0, sizeof(pos)); value = 0.0; };
			~DataInfo();
		};


		//���ݼ�����
		class DataSet
		{
		public:
			std::vector<DataInfo*> data_set;
			DataGeometryType	geometry_type = DataGeometryType_PolygonalLine;
			int					data_style = (DataStyle_Animation | DataStyle_MouseTip);

			
		public:
			DataSet(){};
			virtual ~DataSet(){};

			bool IsAnimation(){ return (data_style & DataStyle_Animation); };
			bool IsMouseTip(){ return (data_style & DataStyle_MouseTip); };

		};

		class Chart : public ui::Control
		{
			
		public:
			Chart();
			virtual ~Chart();


			virtual void PaintChild(ui::IRenderContext* pRender, const ui::UiRect& rcPaint) override;
			virtual void Paint(ui::IRenderContext* pRender, const ui::UiRect& rcPaint) override;
			virtual void PaintBkColor(ui::IRenderContext*pRender) override;
			virtual void PaintBody(ui::IRenderContext* pRender);		//not override
			virtual void PaintBorder(ui::IRenderContext* pRender) override;

		protected:
			Coordinate *m_pCoord = nullptr;
			std::map<std::string, DataSet*> m_mapDataSet;
			int m_nChartStyle = ChartFrameStyle_Grid;

		};



	}
}






