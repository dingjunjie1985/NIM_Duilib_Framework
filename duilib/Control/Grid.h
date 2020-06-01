#pragma once
#include "GridBase.h"

namespace ui
{
	class GridBody;
	class UILIB_API Grid : public ScrollableBox
	{
		friend class GridBody;
	public:
		Grid();
		virtual ~Grid();
		virtual void Init() override;

	public:
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
		

	protected:
		virtual void PaintChild(IRenderContext* pRender, const UiRect& rcPaint) override;
	protected:
		GridBody *m_pBody = nullptr;

		bool m_bPaintGridLine = true;
		bool m_bEditable = true;
	};

	
}