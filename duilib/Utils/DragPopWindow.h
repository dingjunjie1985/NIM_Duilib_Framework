#pragma once

namespace ui
{
	class DragPopWindow : public WindowImplBase
	{
	public:
		static DragPopWindow *CreateAndShow(Box* pBox);
	protected:
		DragPopWindow(Box* pBox) :m_pBox(pBox){};
		virtual ~DragPopWindow(){};

		virtual std::wstring GetSkinFolder() override{ return L"drag_pop_window"; };
		virtual std::wstring GetSkinFile() override{ return L"drag_pop_window.xml"; };
		virtual std::wstring GetWindowClassName(void) const override{ return kClassName; };

		virtual void InitWindow() override;
	public :
		const std::wstring kClassName = L"DragPopWindow";
	protected:
		Box *m_pBox = nullptr;
	};

};



