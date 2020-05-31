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
	std::wstring header[] = { L"�к�", L"����", L"����", L"����", L"����", L"˳���",
		L"�༭ģʽ", L"�Ƿ���ʾ", L"��������", L"����ֵ", L"Ĭ��ֵ" };
	for (int i = 0; i < sizeof(header) / sizeof(header[0]); i++)
	{
		if (i == 0)
			grid->AddHeaderItem(header[i], 30);
		else
			grid->AddHeaderItem(header[i]);
	}

	for (size_t i = 0; i < 100; i++)
	{
		grid->AddRow();
	}

	grid->SetFixedColCount(1);
	grid->SetFixedRowCount(1);

	RichEdit *re_fixed_row = static_cast<RichEdit*>(FindControl(L"re_fixed_row"));
	RichEdit *re_fixed_col = static_cast<RichEdit*>(FindControl(L"re_fixed_col"));
	re_fixed_row->SetText(nbase::IntToString16(grid->GetFixedRowCount()));
	re_fixed_col->SetText(nbase::IntToString16(grid->GetFixedColCount()));
	re_fixed_row->AttachReturn([this, grid, re_fixed_row](ui::EventArgs* args){
		std::wstring text = re_fixed_row->GetText();
		if (!text.empty())
		{
			int fixed = 0;
			if (nbase::StringToInt(text, &fixed) && fixed != grid->GetFixedRowCount())
			{
				grid->SetFixedRowCount(fixed);
			}
		}
		return true;
	});

	re_fixed_col->AttachReturn([this, grid, re_fixed_col](ui::EventArgs* args){
		std::wstring text = re_fixed_col->GetText();
		if (!text.empty())
		{
			int fixed = 0;
			if (nbase::StringToInt(text, &fixed) && fixed != grid->GetFixedColCount())
			{
				grid->SetFixedColCount(fixed);
			}
		}
		return true;
	});

	tree_ = static_cast<TreeView*>(FindControl(L"tree"));
#if 0
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
#endif
#if 0
	ListBox *list = static_cast<ListBox*>(FindControl(L"list"));
	for (size_t i = 0; i < 30000; i++)
	{
		ui::ListContainerElement* item = new ui::ListContainerElement;
		item->SetClass(L"listitem");
		item->SetFixedHeight(20);
		item->SetText(nbase::StringPrintf(L"Leaf node %d", i));
		list->Add(item);
	}
#endif
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


