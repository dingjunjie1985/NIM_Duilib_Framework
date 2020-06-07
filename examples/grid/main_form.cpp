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
	std::wstring header[] = { L"代码", L"名称", L"类型", L"长度", L"顺序号",
		L"编辑模式", L"是否显示", L"参数类型", L"参数值", L"默认值" };

	std::vector <std::wstring> vecTypeString;
	vecTypeString.push_back(L"String");
	vecTypeString.push_back(L"Integer");
	vecTypeString.push_back(L"Float");
	vecTypeString.push_back(L"Date");
	vecTypeString.push_back(L"DateTime");
	vecTypeString.push_back(L"File");
	vecTypeString.push_back(L"List");
	vecTypeString.push_back(L"Text");
	vecTypeString.push_back(L"LongText");
	vecTypeString.push_back(L"Lua");

	std::vector <std::wstring> vecEditModeString;
	vecEditModeString.push_back(L"Normal");
	vecEditModeString.push_back(L"Drop");

	std::vector <std::wstring> vecParamTypeString;
	vecParamTypeString.push_back(L"List");
	vecParamTypeString.push_back(L"TreeList");
	vecParamTypeString.push_back(L"SQLList");
	vecParamTypeString.push_back(L"AutoUnique");
	vecParamTypeString.push_back(L"AutoComplete");
	vecParamTypeString.push_back(L"AutoC***eCode");
	vecParamTypeString.push_back(L"CheckTreeList");
	vecParamTypeString.push_back(L"SQLChe***eeList");

	for (int i = 0; i < sizeof(header) / sizeof(header[0]); i++)
	{
		GridItem *header_item = grid->AddHeaderItem(header[i]);
		if (i == 2)
		{
			header_item->InitTypeCombo(vecTypeString);
		}
		else if (i == 5)
		{
			header_item->InitTypeCombo(vecEditModeString);
		}
		else if (i == 7)
		{
			header_item->InitTypeCombo(vecParamTypeString);
		}
	}

	grid->SetRowCount(30);

	/*for (size_t i = 0; i < 100; i++)
	{
		grid->AddRow();
	}*/

	RichEdit *re_row = static_cast<RichEdit*>(FindControl(L"re_row"));
	RichEdit *re_col = static_cast<RichEdit*>(FindControl(L"re_col"));
	RichEdit *re_fixed_row = static_cast<RichEdit*>(FindControl(L"re_fixed_row"));
	RichEdit *re_fixed_col = static_cast<RichEdit*>(FindControl(L"re_fixed_col"));
	re_row->SetText(nbase::IntToString16(grid->GetRowCount()));
	re_col->SetText(nbase::IntToString16(grid->GetColCount()));
	re_fixed_row->SetText(nbase::IntToString16(grid->GetFixedRowCount()));
	re_fixed_col->SetText(nbase::IntToString16(grid->GetFixedColCount()));
	
	re_row->AttachBubbledEvent(kEventKillFocus, [this, grid, re_row](ui::EventArgs* args){
		std::wstring text = re_row->GetText();
		if (!text.empty())
		{
			int row = 0;
			if (nbase::StringToInt(text, &row))
			{
				grid->SetRowCount(row);
			}
		}
		return true;
	});

	re_col->AttachBubbledEvent(kEventKillFocus, [this, grid, re_col](ui::EventArgs* args){
		std::wstring text = re_col->GetText();
		if (!text.empty())
		{
			int col = 0;
			if (nbase::StringToInt(text, &col))
			{
				grid->SetColCount(col);
			}
		}
		return true;
	});
	
	re_fixed_row->AttachBubbledEvent(kEventKillFocus, [this, grid, re_fixed_row](ui::EventArgs* args){
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

	re_fixed_col->AttachBubbledEvent(kEventKillFocus, [this, grid, re_fixed_col](ui::EventArgs* args){
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


