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

	tree_ = static_cast<TreeView*>(FindControl(L"tree"));
	ui::TreeNode* parent_node = nullptr;

	for (size_t i = 0; i < 30; i++)
	{
		ui::TreeNode* parent_node = new ui::TreeNode;
		parent_node->SetClass(L"listitem");
		parent_node->SetFixedHeight(20);
		parent_node->SetText(nbase::StringPrintf(L"Parent node %d", i));
		tree_->GetRootNode()->AddChildNode(parent_node);
		for (size_t j = 0; j < 50; j++)
		{
			ui::TreeNode* child_node = new ui::TreeNode;
			child_node->SetClass(L"listitem");
			child_node->SetFixedHeight(20);
			child_node->SetText(nbase::StringPrintf(L"Child node %d", j));
			parent_node->AddChildNode(child_node);

			for (size_t k = 0; k < 20; k++)
			{
				ui::TreeNode* leaf_node = new ui::TreeNode;
				leaf_node->SetClass(L"listitem");
				leaf_node->SetFixedHeight(20);
				leaf_node->SetText(nbase::StringPrintf(L"Leaf node %d", k));
				child_node->AddChildNode(leaf_node);
			}
		}
	}
	
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


