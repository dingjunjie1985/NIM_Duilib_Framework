#pragma once
#include "GridBase.h"
//#include "GridBody.h"

namespace ui
{
	class GridBody;
	class UILIB_API Grid : public ScrollableBox
	{
		friend class GridBody;
	public:
		Grid();
		virtual ~Grid();
		virtual GridBody* CreateGridBody();		//继承类需要重载这个接口 并实现自定义GridBody
		virtual void Init() override;
	public:
		
		
	public: //pass to gridbody
		int GetColCount() const;
		void SetColCount(int count);

		int GetRowCount() const;
		void SetRowCount(int count);

		int GetFixedColCount() const;
		void SetFixedColCount(int fixed);

		int GetFixedRowCount() const;
		void SetFixedRowCount(int fixed);

		int GetHeaderHeight() const;
		void SetHeaderHeight(int height);

		int GetFixedColWidth() const;
		int GetFixedRowHeight() const;

		std::wstring GetFixedBkColor() const;
		void SetFixedBkColor(std::wstring color);

		std::wstring GetSelForeColor() const;
		void SetSelForeColor(std::wstring color);

		std::wstring GetGridLineColor() const;
		void SetGridLineColor(std::wstring color);

		std::wstring GetGridItemText(int row, int col);
		bool SetGridItemText(std::wstring text, int row, int col);

		bool IsGridItemFixed(int row, int col);

		GridItem* AddHeaderItem(std::wstring text, int width = 80);
		bool AddRow();

		GridItem *GetGridItem(int row, int col);

		bool RemoveRow(int row);
		bool RemoveCol(int col);
		void Clear(bool include_header);

		void AttachTextChange(const EventCallback& callback);

		bool LoadExcel(std::wstring file);
	protected:
		

	protected:
		virtual bool ButtonDown(EventArgs& msg) override;
		virtual void PaintChild(IRenderContext* pRender, const UiRect& rcPaint) override;
	protected:
		GridBody *m_pBody = nullptr;

		bool m_bPaintGridLine = true;
		bool m_bEditable = true;
	private:
		bool m_bIsInit = false;		
	};

	
}