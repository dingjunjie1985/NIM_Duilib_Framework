#include "StdAfx.h"

namespace ui{

	DragPopWindow *DragPopWindow::CreateAndShow(Box* pBox)
	{
		if (!pBox)
			return nullptr;
		DragPopWindow *pWindow = new DragPopWindow(pBox);
		pWindow->Create(NULL, pWindow->kClassName.c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
		pWindow->CenterWindow();
		pWindow->ShowWindow();
		return pWindow;
	}

	void DragPopWindow::InitWindow()
	{
		ui::Box* root = static_cast<ui::Box*>(FindControl(L"root"));
		if (root && m_pBox)
		{
			int nWidth = m_pBox->GetWidth();
			int nHeight = m_pBox->GetHeight();
			root->Add(m_pBox);
			UiRect rc(0, 0, nWidth, nHeight + 35);
			SetPos(rc, true, 0);
		}
	}
}