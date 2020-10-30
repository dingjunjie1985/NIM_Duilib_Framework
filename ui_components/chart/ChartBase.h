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
			CoordinateStyle_Zoom =		(1 << 4),	//����
			CoordinateStyle_BK_Grid =	(1 << 5),	//����Ч��
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
			ChartFrameStyle_Zoom = (1 << 0),	//����
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
		class Coordinate;
		class DataSet
		{
		public:
			std::vector<DataInfo*> data_set;
			DataGeometryType	geometry_type = DataGeometryType_PolygonalLine;
			int					data_style = (DataStyle_Animation | DataStyle_MouseTip);

			DWORD				base_color = 0xffffffff;
		public:
			DataSet(){};
			virtual ~DataSet(){};

			bool IsAnimation(){ return (data_style & DataStyle_Animation); };
			bool IsMouseTip(){ return (data_style & DataStyle_MouseTip); };

			virtual void Paint(ui::IRenderContext* pRender, const ui::UiRect& rcPaint, Coordinate *pCoord);

		};

		//������
		class Axis{
		public:
			std::wstring title;
			double range[2];
		public:
			Axis(){ range[0] = 0.f;  range[1] = 1.f; };
			virtual ~Axis(){};

			void SetRange(const double& from, const double& to){ range[0] = from; range[1] = to; };
		};


	}
}






