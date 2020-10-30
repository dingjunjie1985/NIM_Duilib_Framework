#include "stdafx.h"
#include "main_form.h"
#include "ui_components\chart\Chart.h"

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
	nim_comp::chart::Chart *pChart = static_cast<nim_comp::chart::Chart *>(FindControl(L"chart"));

	{
		float arrX[] = { 0.01, 0.1, 0.25, 0.4, 0.55, 0.7, 0.85, 0.95 };
		float arrValue[] = { 0.155, 0.165, 0.201, 0.377, 0.352, 0.222, 0.295, 0.325 };
		nim_comp::chart::DataSet *pDataSet = new nim_comp::chart::DataSet;
		pDataSet->base_color = GetTextColor(L"color_yellow");
		nim_comp::chart::DataInfo *pDataInfo;
		for (size_t i = 0; i < sizeof(arrX) / sizeof(arrX[0]); i++)
		{
			pDataInfo = new nim_comp::chart::DataInfo;
			pDataInfo->pos[0] = arrX[i];
			pDataInfo->value = arrValue[i];
			pDataSet->data_set.push_back(pDataInfo);
		}
		pChart->AddDataSet("demo1", pDataSet);
	}
	{
		float arrX[] = { 0.01, 0.1, 0.25, 0.4, 0.55, 0.7, 0.85, 0.95 };
		float arrValue[] = { 0.325, 0.295, 0.222, 0.352, 0.377, 0.201, 0.165, 0.155, };
		nim_comp::chart::DataSet *pDataSet = new nim_comp::chart::DataSet;
		pDataSet->base_color = GetTextColor(L"color_pink");
		nim_comp::chart::DataInfo *pDataInfo;
		for (size_t i = 0; i < sizeof(arrX) / sizeof(arrX[0]); i++)
		{
			pDataInfo = new nim_comp::chart::DataInfo;
			pDataInfo->pos[0] = arrX[i];
			pDataInfo->value = arrValue[i];
			pDataSet->data_set.push_back(pDataInfo);
		}
		pChart->AddDataSet("demo2", pDataSet);
	}

	{
		float arrX[] = {0.15, 0.30, 0.45, 0.60, 0.75, 0.90};
		float arrValue[] = {0.295, 0.222, 0.352, 0.377, 0.201, 0.165};
		nim_comp::chart::DataSet *pDataSet = new nim_comp::chart::DataSet;
		pDataSet->base_color = GetTextColor(L"color_pink");
		pDataSet->geometry_type = nim_comp::chart::DataGeometryType_Bar;
		nim_comp::chart::DataInfo *pDataInfo;
		for (size_t i = 0; i < sizeof(arrX) / sizeof(arrX[0]); i++)
		{
			pDataInfo = new nim_comp::chart::DataInfo;
			pDataInfo->pos[0] = arrX[i];
			pDataInfo->value = arrValue[i];
			pDataSet->data_set.push_back(pDataInfo);
		}
		pChart->AddDataSet("demo3", pDataSet);
	}

}

LRESULT MainForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}


