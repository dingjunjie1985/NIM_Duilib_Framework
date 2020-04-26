#pragma once

namespace ui
{
	struct GridHeadEleInfo{
		std::wstring strText;
		UiRect	rcTextPadding;
		UINT	uTextStyle;
	};

	template<typename InheritType = Control>
	class GridHeadEleTemplate : public InheritType{
		friend class Grid;
		friend class GridHeader;
	protected:
		GridHeadEleTemplate(){ m_pEleInfo = new GridHeadEleInfo; };
		virtual ~GridHeadEleTemplate(){ 
			delete m_pEleInfo;
			m_pEleInfo = nullptr;
		};
		void SetIndex(int nIndex){ m_nIndex = nIndex; };

		virtual void HandleMessage(EventArgs& msg) override;

		virtual void PaintText(IRenderContext* pRender) override;
		virtual void PaintBorder(IRenderContext* pRender) override;
	protected:
		int m_nIndex = -1;
		GridHeadEleInfo *m_pEleInfo = nullptr;
		GridHeader* m_pHeader = nullptr;
	};

	typedef GridHeadEleTemplate<Control> GridHeadEleControl;
	//typedef GridHeadEleTemplate<Box> GridHeadEleBox;

	class GridHeader : public HBox
	{
		friend class Grid;
		friend class GridHeadEleTemplate<Control>;
	protected:
		GridHeader(){ 
			SetHeaderBkColor(L"splitline_level2"); 
			m_ptStartResize.x = m_ptStartResize.y = -1; 
		};
		virtual ~GridHeader(){};

		virtual bool Add(Control* pControl) override;

		void SetHeaderBkColor(std::wstring bkcolor);
		void DoResizeMessage(EventArgs& msg);

	protected:
		//int m_nCapacity = 8;
		Grid *m_pOwner = nullptr;
		POINT m_ptStartResize;

		std::wstring m_strHeaderBkColor;
	};

	class GridBody : public ScrollableBox
	{
		friend class Grid;
	protected:
		GridBody() :ScrollableBox(new Layout){};
		virtual ~GridBody(){};
	protected:
		Grid *m_pOwner = nullptr;
		GridHeader *m_pHeader = nullptr;
	};

	class UILIB_API Grid : public VBox
	{
	public:
		Grid();
		virtual ~Grid();

		virtual void Init() override;

	public:
		virtual void SetHeaderHeight(int height);
		virtual void SetHeaderBkColor(std::wstring bkcolor);
	public:
		virtual bool AddHeaderEle(std::wstring text);

	protected:
		GridHeader *m_pHeader = nullptr;
		GridBody *m_pBody = nullptr;
	};

	
}