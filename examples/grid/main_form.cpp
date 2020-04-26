#include "stdafx.h"
#include "main_form.h"

#include <fstream>

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
	return L"grid";
}

std::wstring MainForm::GetSkinFile()
{
	return L"main_form.xml";
}

std::wstring MainForm::GetWindowClassName() const
{
	return kClassName;
}

void MainForm::InitWindow()
{
	Grid *grid = static_cast<Grid*>(FindControl(L"grid"));
	grid->AddHeaderEle(L"第一列");
	grid->AddHeaderEle(L"第二列");

	//Label *tooltip = (Label*)FindControl(L"tooltip");
	//Button *btn = (Button*)FindControl(L"btn");
	//btn->AttachClick([this, tooltip](ui::EventArgs *args){
	//	std::wstring str = tooltip->GetText();
	//	tooltip->SetText(str + L"A");
	//	return true;
	//});
}

LRESULT MainForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}


