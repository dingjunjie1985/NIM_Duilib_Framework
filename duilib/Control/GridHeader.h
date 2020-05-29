#pragma once

namespace ui
{
	template<typename InheritType = Label>
	class GridHeadEleTemplate : public InheritType{
		friend class Grid;
		friend class GridHeader;
	protected:
		GridHeadEleTemplate(std::wstring text, int width){  
			m_sText = text;
			SetFixedWidth(width);
		};
		virtual ~GridHeadEleTemplate(){ 
		};
		void SetIndex(int nIndex){ m_nIndex = nIndex; };

		virtual void HandleMessage(EventArgs& msg) override;

		virtual void PaintText(IRenderContext* pRender) override;
		//virtual void PaintBorder(IRenderContext* pRender) override;
	protected:
		int m_nIndex = -1;
		std::wstring	m_sText;
		UiRect			m_rcTextPadding;
		UINT			m_uTextStyle;

		GridHeader* m_pHeader = nullptr;
	};

	typedef GridHeadEleTemplate<Control> GridHeadEleControl;
	//typedef GridHeadEleTemplate<Box> GridHeadEleBox;

	class Grid;
	class GridBody;
	class GridHeader : public HBox
	{
		friend class Grid;
		friend class GridBody;
		friend class GridHeadEleTemplate<Control>;
	protected:
		GridHeader(){ 
			m_ptStartResize.x = m_ptStartResize.y = -1; 
		};
		virtual ~GridHeader(){};

		void DetachControl(){ m_pGrid = nullptr; m_pBody = nullptr; };

		virtual bool AddHeaderEle(std::wstring text, int width);

		void DoResizeMessage(EventArgs& msg);
	protected:
		virtual void PaintBorder(IRenderContext* pRender) override;

	protected:
		//int m_nCapacity = 8;
		Grid *m_pGrid = nullptr;
		GridBody *m_pBody = nullptr;
		POINT m_ptStartResize;

		std::wstring m_strHeaderBkColor;

		std::vector<int> m_hlayout;
	};
	
}