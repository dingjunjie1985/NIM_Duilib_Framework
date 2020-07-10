#include "StdAfx.h"

namespace ui
{
	void GridSelRange::Clear() {
		if (m_vecRange.size() > 0)
		{
			m_pBody->_UnSelRange(m_vecRange[0]);
			m_vecRange.clear();
		}

		for (auto it = m_mapSelRow.cbegin(); it != m_mapSelRow.cend(); it++)
		{
			m_pBody->_SelRow(it->first, false);
		}
		m_mapSelRow.clear();  
		
		for (auto it = m_mapSelCol.cbegin(); it != m_mapSelCol.cend(); it++)
		{
			m_pBody->_SelCol(it->first, false);
		}
		m_mapSelCol.clear(); 
	}
	

	void GridSelRange::SetSelItem(int row_index, int col_index, bool connect){
		if (!connect)
		{
			Clear();
			m_vecRange.push_back(UiRect(col_index, row_index, col_index, row_index));
			m_pBody->_SelItem(row_index, col_index, true);
			m_pBody->Invalidate();
		}
	}

	void GridSelRange::SetSelRange(UiRect rc, bool connect)
	{
		if (!connect)
		{
			Clear();
			m_vecRange.push_back(rc);
			m_pBody->_SelRange(rc, true);
			m_pBody->Invalidate();
		}
	}

	void GridSelRange::SetSelRow(int row_index, int row_index_end, bool connect){
		assert(row_index <= row_index_end);
		if (row_index < row_index_end)
			return;
		if (!connect)
		{
			Clear();
			for (int row = row_index; row <= row_index_end; row++)
			{
				if (m_mapSelRow.find(row) == m_mapSelRow.end())
				{
					m_pBody->_SelRow(row, true);
					m_mapSelRow[row] = nullptr;
				}
			}
			m_pBody->Invalidate();
			/*int fix_col = m_pBody->GetFixedColCount();
			int col_count = m_pBody->GetColCount();
			assert(fix_col <= col_count);
			if (fix_col < col_count)
			{
				m_mapSelRow[row_index] = nullptr;
				m_pBody->Invalidate();
			}*/
		}
	}

	void GridSelRange::SetSelCol(int col_index, int col_index_end, bool connect)
	{
		assert(col_index <= col_index_end);
		if (col_index < col_index_end)
			return;
		if (!connect)
		{
			Clear();
			for (int col = col_index; col <= col_index_end; col++)
			{
				if (m_mapSelCol.find(col) == m_mapSelCol.cend())
				{
					m_pBody->_SelCol(col, true);
					m_mapSelCol[col] = nullptr;
				}
			}
			m_pBody->Invalidate();
		}
	}
	
	bool GridSelRange::IsItemSelected(int row_index, int col_index)
	{
		if (IsRowSelected(row_index) || IsColSelected(col_index))
			return true;
		bool ret = false;
		CPoint pt(col_index, row_index);
		for (auto it = m_vecRange.cbegin(); it != m_vecRange.cend(); it++)
		{
			UiRect rc = *it;
			if (rc.IsPointIn(pt))
			{
				ret = true;
				break;
			}
		}
		return ret;
	}

	bool GridSelRange::IsRowSelected(int row_index)
	{
		return m_mapSelRow.find(row_index) != m_mapSelRow.cend();
	}

	bool GridSelRange::IsColSelected(int col_index)
	{
		return m_mapSelCol.find(col_index) != m_mapSelCol.cend();
	}

}