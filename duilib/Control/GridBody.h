#pragma once
#include "GridBase.h"

namespace ui
{
	class Grid;
	class GridBody : public Box
	{
		friend class Grid;
		friend class GridSelRange;
	protected:
		GridBody(Grid *pGrid);
		virtual ~GridBody(){};

		void SetDefaultRowHeight(int height){ m_defaultRowHeight = height; };
		void SetDefaultColWidth(int width){ m_defaultColWidth = width; };
		int GetTotalRowHeight(){}

	protected:	//pass by grid
		/**
		* @brief 总列数
		*/
		int GetColCount() const;
		void SetColCount(int count);

		/**
		* @brief 总行数
		*/
		int GetRowCount() const;
		void SetRowCount(int count);

		/**
		* @brief 固定列数
		*/
		int GetFixedColCount() const;
		void SetFixedColCount(int fixed);

		/**
		* @brief 固定行数
		*/
		int GetFixedRowCount() const;
		void SetFixedRowCount(int fixed);

		/**
		* @brief 列宽;
		* @param[in] col_index: 第几列,base on 0;
		*/
		int GetColumnWidth(int col_index) const;
		void SetColumnWidth(int col_index, int width);

		/**
		* @brief 表头高度
		*/
		int GetHeaderHeight() const;
		void SetHeaderHeight(int height);

		/**
		* @brief 固定行列的背景色
		*/
		std::wstring GetFixedBkColor() const;
		void SetFixedBkColor(std::wstring color);

		/**
		* @brief 选中单元格的前景色
		*/
		std::wstring GetSelForeColor() const;
		void SetSelForeColor(std::wstring color);

		/**
		* @brief 网格线颜色
		*/
		std::wstring GetGridLineColor() const;
		void SetGridLineColor(std::wstring color);
	
		int GetFixedColWidth() const;
		int GetFixedRowHeight() const;

		/**
		* @brief 设置/获取单元格文本内容;
		* @param[in] row_index: 第几行,base on 0;
		* @param[in] col_index: 第几列,base on 0;
		*/
		std::wstring GetGridItemText(int row_index, int col_index);
		bool SetGridItemText(std::wstring text, int row_index, int col_index);

		/**
		* @brief 判断单元格是否fixed;
		* @param[in] row_index: 第几行,base on 0;
		* @param[in] col_index: 第几列,base on 0;
		*/
		bool IsGridItemFixed(int row_index, int col_index);

		/**
		* @brief 插入列在表格最后;
		* @param[in] text: 表头文本;
		* @param[in] width: 列宽度;
		* @return 返回新加的表头单元格对象指针,null表示未成功;
		*/
		GridItem* AddCol(std::wstring text, int width = 80);

		/**
		* @brief 插入行在表格最后
		* @return 返回 true为成功，false 为失败
		*/
		bool AddRow();

		/**
		* @brief 获取单元格对象
		* @param[in] row_index: 第几行,base on 0;
		* @param[in] col_index: 第几列,base on 0;
		* @return 返回单元格对象指针,null表示未找到;
		*/
		GridItem *GetGridItem(int row_index, int col_index);

		/**
		* @brief 移除一行
		* @param[in] row_index: 第几行,base on 0;
		* @return 返回 true为成功，false 为失败
		*/
		bool RemoveRow(int row_index);

		/**
		* @brief 移除一列
		* @param[in] col_index: 第几列,base on 0;
		* @return 返回 true为成功，false 为失败
		*/
		bool RemoveCol(int col_index);

		/**
		* @brief 清除整表
		* @param[in] include_header: true表示清除header, false表示保留header;
		*/
		void Clear(bool include_header);

		/**
		* @brief 表格内容变更后的回调注册
		* @param[in] callback
		*/
		void AttachTextChange(const EventCallback& callback)	{ this->OnEvent[kEventTextChange] += callback; }

		/**
		* @brief 导入excel
		* @param[in] file:	excel路劲;
		* @param[in] sheet_num:	导入的excel的第几页, base on 0;
		* @param[in] touch_header: true表示excel的第一行做为Grid的Header内容
		* @return 返回 true为成功，false 为失败
		*/
		bool LoadExcel(std::wstring file, int sheet_num, bool touch_header);

		/**
		* @brief 列根据内容自动调整宽度
		* @param[in] col_index:	要调整的列序号, base on 0;
		* @param[in] min_width:	最小宽度;
		* @param[in] max_width: 最大宽度, -1代表没有限制;
		* @return 返回 true为成功，false 为失败;
		*/
		bool AutoFixColWidth(int col_index, int min_width = 30, int max_width = -1);

	protected:
		virtual void HandleMessage(EventArgs& event) override;
		virtual bool ButtonDown(EventArgs& msg) override;
		virtual bool ButtonUp(EventArgs& msg) override;
		virtual bool OnMouseDoubleClick(EventArgs& msg);		//no override
		virtual bool OnMouseMove(EventArgs& msg);				//no override

		virtual void PaintChild(IRenderContext* pRender, const UiRect& rcPaint) override;
		virtual void PaintStatusColor(IRenderContext* pRender) override;
		virtual void PaintText(IRenderContext* pRender) override;
		virtual void PaintBorder(IRenderContext* pRender) override;
	protected:
		/**
		* @brief 编辑的单元格为Combo类型时, 选中了ComboItem调用;
		* @return 不关键;
		*/
		bool OnComboEditSelected(EventArgs *args);

	protected:
		/*
		* @brief 计算vector<int>之和;
		* @return 和;
		*/
		int _SumIntList(const std::vector<int> &vec);

		/*
		* @brief 获取表头行信息;
		* @return 表头行信息;
		*/
		GridRow* _GetHeader() const;

		virtual void _BeginEditGridItem(GridItem *item);
		virtual void _EndEdit();
		bool _GetGridItemByMouse(CPoint pt, CPoint& position, bool fixed = false);
		int _GetGridItemTop(int row_index);
		int _GetGridItemLeft(int col_index);

		/*
		* @brief 清除编辑及选中状态;
		*/
		UiRect _GetGridItemPos(int row_index, int col_index);

		/*
		* @brief 清除编辑及选中状态;
		*/
		void _ClearModifyAndSel();
	protected:
		Grid *m_pGrid = nullptr;

		/* 保存列宽 */
		GridLayout m_hLayout;

		/* 保存行高 */
		GridLayout m_vLayout;

		/* 所有行信息, 第一行为Header */
		std::vector<GridRow*> m_vecRow;

		/* 固定行/列数 */
		unsigned int m_nFixedCol = 0;
		unsigned int m_nFixedRow = 0;

		/* 保存选中信息 */
		GridSelRange m_selRange;

		/* 拖动表头相关 */
		//bool m_bDragColumn = false;
		int m_nDragColmun = -1;
		CPoint m_ptDragColumnStart;
		int m_nDrawDragColumnMovingOffX = 0;			// = m_nDragColmun的右边界 -  m_ptDragColumnMoving.x; 为了保证拖动线的位置准确性
		CPoint m_ptDragColumnMoving;

		/* 一些属性 */
		int m_defaultRowHeight = 24;
		int m_defaultColWidth = 80;
		std::wstring m_strFixedBkColor = L"splitline_level2";
		std::wstring m_strSelForeColor = L"grid_sel_fore";
		std::wstring m_strGridLineColor = L"grid_line";
		std::wstring m_strGridFont = L"system_12";
		UINT	m_uTextStyle = DT_CENTER | DT_CENTER | DT_VCENTER | DT_SINGLELINE;
		
		/* 编辑时候的RichEdit/Combo控件 */
		RichEdit *m_pReEdit = nullptr;
		Combo *m_pComboEdit = nullptr;

		GridItem *m_pReEditGridItem = nullptr;
		GridItem *m_pComboEditGridItem = nullptr;
	};
}