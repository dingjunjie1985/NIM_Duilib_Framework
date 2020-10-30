#pragma once

namespace nim_comp
{
	namespace chart
	{
		enum CoordinateDimension				//坐标系维度
		{
			CoordinateDimension_2D = 2,
			CoordinateDimension_3D = 3
		};

		enum CoordinateStyle					//坐标系风格
		{
			CoordinateStyle_Quadrant1 = (1 << 0),	//第1象限
			CoordinateStyle_Quadrant2 = (1 << 1),	//第2象限
			CoordinateStyle_Quadrant3 = (1 << 2),	//第3象限
			CoordinateStyle_Quadrant4 = (1 << 3),	//第4象限
			CoordinateStyle_Zoom =		(1 << 4),	//缩放
			CoordinateStyle_BK_Grid =	(1 << 5),	//网格效果
		};

		enum DataGeometryType					//数据几何类型
		{
			DataGeometryType_PolygonalLine = 0,	//折线
			DataGeometryType_CurveLine,			//曲线
			DataGeometryType_Bar,				//柱状图
			DataGeometryType_Pie				//饼图
		};

		enum DataStyle
		{
			DataStyle_Animation = (1 << 0),		//动画效果
			DataStyle_MouseTip = (1 << 1),		//浮窗效果
		};

		enum ChartFrameStyle
		{
			ChartFrameStyle_Zoom = (1 << 0),	//缩放
		};

		//单个数据信息
		class DataInfo
		{
		public:
			double  pos[3];
			double	value;
		public:
			DataInfo(){ memset(pos, 0, sizeof(pos)); value = 0.0; };
			~DataInfo();
		};


		//数据集对象
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

		//坐标轴
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






