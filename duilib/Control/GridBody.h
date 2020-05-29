#pragma once

namespace ui
{
	class GridHeader;
	class Grid;
	class GridBody : public Box
	{
		friend class Grid;
	protected:
		GridBody() :Box(new Layout){};
		virtual ~GridBody(){};

		void DetachControl(){ m_pGrid = nullptr; m_pHeader = nullptr; };
		void SetDefaultRowHeight(int height){ m_defaultRowHeight = height; };
		bool AddRow();
		int GetTotalRowHeight(){}
	protected:
		virtual void PaintBorder(IRenderContext* pRender) override;
		virtual void PaintText(IRenderContext* pRender) override;
	protected:
		Grid *m_pGrid = nullptr;
		GridHeader *m_pHeader = nullptr;

		std::vector<int> m_vlayout;

		int m_defaultRowHeight = 24;
		bool m_bPaintGridLine = true;
	};
}