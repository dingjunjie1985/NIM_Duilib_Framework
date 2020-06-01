#pragma once
#include "GridBase.h"

namespace ui
{
	typedef std::vector<GridItem*> GridRow; 
	typedef std::vector<int> GridLayout;

	class Grid;
	class GridBody : public Box
	{
		friend class Grid;
	protected:
		GridBody(Grid *pGrid);
		virtual ~GridBody(){};

		void DetachControl(){ m_pGrid = nullptr; };
		void SetDefaultRowHeight(int height){ m_defaultRowHeight = height; };
		int GetTotalRowHeight(){}

	protected:	//pass by grid
		int GetColCount() const;
		int GetRowCount() const;
		int GetFixedColCount() const;
		int GetFixedRowCount() const;
		int GetFixedColWidth() const;
		int GetFixedRowHeight() const;
		int GetHeaderHeight() const;
		std::wstring GetFixedBkColor() const;
		std::wstring GetGridLineColor() const;

		void SetColCount(int count);
		void SetRowCount(int count);
		void SetFixedColCount(int fixed);
		void SetFixedRowCount(int fixed);
		void SetHeaderHeight(int height);
		void SetFixedBkColor(std::wstring bkcolor);
		void SetGridLineColor(std::wstring bkcolor);

		GridItem* AddHeaderItem(std::wstring text, int width = 80);
		bool AddRow();

		GridItem *GetGridItem(int row, int col);
	protected:
		virtual void HandleMessage(EventArgs& event) override;
		virtual bool ButtonDown(EventArgs& msg) override;
		virtual bool OnMouseDoubleClick(EventArgs& msg);		//no override

		
		virtual void PaintStatusColor(IRenderContext* pRender) override;
		virtual void PaintText(IRenderContext* pRender) override;
		virtual void PaintBorder(IRenderContext* pRender) override;
	protected:
		bool OnComboEditSelected(EventArgs *args);

	private:
		int _SumIntList(const std::vector<int> &vec);
		GridRow* _GetHeader() const;
		void _EndEdit();
	protected:
		Grid *m_pGrid = nullptr;

		GridLayout m_hLayout;
		GridLayout m_vLayout;
		std::vector<GridRow*> m_vecRow;
		unsigned int m_nFixedCol = 0;
		unsigned int m_nFixedRow = 0;

		int m_defaultRowHeight = 24;
		std::wstring m_strFixedBkColor;
		std::wstring m_strGridLineColor;

		UINT	m_uTextStyle = DT_CENTER | DT_CENTER | DT_VCENTER | DT_SINGLELINE;

		RichEdit *m_pReEdit = nullptr;
		Combo *m_pComboEdit = nullptr;

		GridItem *m_pReEditGridItem = nullptr;
		GridItem *m_pComboEditGridItem = nullptr;
	};
}