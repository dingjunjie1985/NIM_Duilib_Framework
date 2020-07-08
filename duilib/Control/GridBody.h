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
		int GetColCount() const;
		void SetColCount(int count);

		int GetRowCount() const;
		void SetRowCount(int count);

		int GetFixedColCount() const;
		void SetFixedColCount(int fixed);

		int GetFixedRowCount() const;
		void SetFixedRowCount(int fixed);

		int GetColumnWidth(int col_index) const;
		void SetColumnWidth(int col_index, int width);

		int GetHeaderHeight() const;
		void SetHeaderHeight(int height);

		std::wstring GetFixedBkColor() const;
		void SetFixedBkColor(std::wstring color);

		std::wstring GetSelForeColor() const;
		void SetSelForeColor(std::wstring color);

		std::wstring GetGridLineColor() const;
		void SetGridLineColor(std::wstring color);
	
		int GetFixedColWidth() const;
		int GetFixedRowHeight() const;

		std::wstring GetGridItemText(int row, int col);
		bool SetGridItemText(std::wstring text, int row, int col);

		bool IsGridItemFixed(int row, int col);

		GridItem* AddCol(std::wstring text, int width = 80);
		bool AddRow();

		GridItem *GetGridItem(int row, int col);

		bool RemoveRow(int row);
		bool RemoveCol(int col);
		void Clear(bool include_header);

		void AttachTextChange(const EventCallback& callback)	{ this->OnEvent[kEventTextChange] += callback; }

		bool LoadExcel(std::wstring file);

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
		bool OnComboEditSelected(EventArgs *args);

	protected:
		int _SumIntList(const std::vector<int> &vec);
		GridRow* _GetHeader() const;
		virtual void _BeginEditGridItem(GridItem *item);
		virtual void _EndEdit();
		bool _GetGridItemByMouse(CPoint pt, CPoint& position, bool fixed = false);
		int _GetGridItemTop(int row_index);
		int _GetGridItemLeft(int col_index);
		UiRect _GetGridItemPos(int row_index, int col_index);
	protected:
		Grid *m_pGrid = nullptr;

		GridLayout m_hLayout;
		GridLayout m_vLayout;
		std::vector<GridRow*> m_vecRow;
		unsigned int m_nFixedCol = 0;
		unsigned int m_nFixedRow = 0;

		GridSelRange m_selRange;

		//bool m_bDragColumn = false;
		int m_nDragColmun = -1;
		CPoint m_ptDragColumnStart;
		int m_nDrawDragColumnMovingOffX = 0;			// = m_nDragColmun的右边界 -  m_ptDragColumnMoving.x; 为了保证拖动线的位置准确性
		CPoint m_ptDragColumnMoving;


		int m_defaultRowHeight = 24;
		int m_defaultColWidth = 80;
		std::wstring m_strFixedBkColor = L"splitline_level2";
		std::wstring m_strSelForeColor = L"grid_sel_fore";
		std::wstring m_strGridLineColor = L"grid_line";

		UINT	m_uTextStyle = DT_CENTER | DT_CENTER | DT_VCENTER | DT_SINGLELINE;

		RichEdit *m_pReEdit = nullptr;
		Combo *m_pComboEdit = nullptr;

		GridItem *m_pReEditGridItem = nullptr;
		GridItem *m_pComboEditGridItem = nullptr;
	};
}