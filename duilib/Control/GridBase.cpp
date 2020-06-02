#include "StdAfx.h"

namespace ui
{
	void GridSelRange::SetSelItem(int row_index, int col_index, bool connect){
		if (!connect)
		{
			m_vecRange.clear();
			m_vecRange.push_back(UiRect(col_index, row_index, col_index, row_index));
			m_pBody->Invalidate();
		}
	}

	void GridSelRange::SetSelRow(int row_index, bool connect){
		if (!connect)
		{
			m_vecRange.clear();
			int fix_col = m_pBody->GetFixedColCount();
			int col_count = m_pBody->GetColCount();
			assert(fix_col <= col_count);
			if (fix_col < col_count)
			{
				m_vecRange.push_back(UiRect(fix_col, row_index, col_count - 1, row_index));
				m_pBody->Invalidate();
			}
		}
	}

	void GridSelRange::SetSelCol(int col_index, bool connect)
	{
		if (!connect)
		{
			m_vecRange.clear();
			int fix_row = m_pBody->GetFixedRowCount();
			int row_count = m_pBody->GetRowCount();
			assert(fix_row <= row_count);
			if (fix_row < row_count)
			{
				m_vecRange.push_back(UiRect(col_index, fix_row, col_index, row_count - 1));
				m_pBody->Invalidate();
			}
		}
	}
	
	
}