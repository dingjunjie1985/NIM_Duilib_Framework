#pragma once

namespace ui
{
	class GridHeader;
	class GridBody;
	class UILIB_API Grid : public ScrollableBox
	{
	public:
		Grid();
		virtual ~Grid();
		virtual void Init() override;

		inline int GetColCount();
		inline int GetRowCount();
	public:
		virtual void SetHeaderHeight(int height);
		virtual void SetHeaderBkColor(std::wstring bkcolor);
	public:
		virtual bool AddHeaderEle(std::wstring text, int width = 80);
		virtual bool AddRow();

	protected:
		int GetFixedColWidth();
		int GetFixedRowHeight();

	protected:
		virtual void ProcessVScrollBar(UiRect rc, int cyRequired) override;
		virtual void ProcessHScrollBar(UiRect rc, int cyRequired) override;
		virtual CSize CalcRequiredSize(const UiRect& rc) override;
		virtual void PaintChild(IRenderContext* pRender, const UiRect& rcPaint) override;
	protected:
		GridHeader *m_pHeader = nullptr;
		GridBody *m_pBody = nullptr;
	};

	
}