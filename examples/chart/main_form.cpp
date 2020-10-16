#include "stdafx.h"
#include "main_form.h"
#include "ui_components\chart\ChartBase.h"

using namespace ui;

const std::wstring MainForm::kClassName = L"MainForm";

MainForm::MainForm()
{
}


MainForm::~MainForm()
{
}

std::wstring MainForm::GetSkinFolder()
{
	return L"chart";
}

std::wstring MainForm::GetSkinFile()
{
	return L"main_form.xml";
}

std::wstring MainForm::GetWindowClassName() const
{
	return kClassName;
}

Control* MainForm::CreateControl(const std::wstring& pstrClass)
{
	Control *pControl = nullptr;
	if (pstrClass == L"Chart")
	{
		pControl = new nim_comp::chart::Chart;
	}

	return pControl;
}

void MainForm::InitWindow()
{
	
}

LRESULT MainForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}


