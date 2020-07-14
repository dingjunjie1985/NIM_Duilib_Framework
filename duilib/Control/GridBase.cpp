#include "StdAfx.h"

namespace ui
{
	void GridSelRange::Clear() {
		if (m_vecRange.size() > 0)
		{
			m_pBody->_SelRange(m_vecRange[0], false);
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
	

	void GridSelRange::SetSelItem(int row_index, int col_index, bool ctrl, bool shift){
		assert(m_vecRange.size() < 2);

		GridItem *pItem = m_pBody->GetGridItem(row_index, col_index);
		assert(pItem);
		if (!pItem)
			return;
		bool bSelected = pItem->IsSelected();

		if (ctrl && shift)
		{
			ctrl = false;
			shift = false;
		}

		if (ctrl)
		{
			UiRect rc(-1,-1,-1,-1);
			if (m_vecRange.size() > 0)
				rc = m_vecRange[0];
			
			bool bInSelRow = false;
			bool bInSelCol = false;

			if (m_mapSelRow.find(row_index) != m_mapSelRow.end())	//row_index为选中状态
			{
				assert(bSelected);
				bInSelRow = true;
				rc.left = m_pBody->GetFixedColCount();
				rc.right = m_pBody->GetColCount() - 1;
				if (rc.top < row_index)
					rc.top = row_index;
				if (rc.bottom > row_index)
					rc.bottom = row_index;
				m_mapSelRow.erase(row_index);
				//pItem->SetSelected(false);
			}

			if (m_mapSelCol.find(col_index) != m_mapSelCol.end())	//col_index为选中状态
			{
				assert(bSelected);
				bInSelCol = true;
				rc.top = m_pBody->GetFixedRowCount();
				rc.bottom = m_pBody->GetRowCount() - 1;
				if (rc.left < col_index)
					rc.left = col_index;
				if (rc.right > col_index)
					rc.left = col_index;
				m_mapSelCol.erase(col_index);
				//pItem->SetSelected(false);
			}

			if (rc.left > col_index || rc.right < col_index || rc.top > row_index || rc.bottom < row_index)		//不位于rc中
			{
				//assert(!bSelected);
				rc.left = min(rc.left, col_index);
				rc.top = min(rc.top, row_index);
				rc.right = max(rc.right, col_index);
				rc.bottom = max(rc.bottom, row_index);
			}

			if (m_vecRange.empty())
				m_vecRange.push_back(rc);
			else
				m_vecRange[0] = rc;
			pItem->SetSelected(!bSelected);
			m_pBody->Invalidate();
		}
		else if (shift)
		{
			if (m_vecRange.size() == 0)
			{
				assert(!bSelected);
				UiRect rc(col_index, row_index, col_index, row_index);
				m_vecRange.push_back(rc);
				m_pBody->_SelItem(row_index, col_index, true);
				m_pBody->Invalidate();
			}
			else
			{
				UiRect rc = m_vecRange[0];
				rc.left = min(rc.left, col_index);
				rc.top = min(rc.top, row_index);
				rc.right = max(rc.right, col_index);
				rc.bottom = max(rc.bottom, row_index);
				m_vecRange[0] = rc;
				m_pBody->_SelRange(rc, true);
				m_pBody->Invalidate();
			}
		}
		else
		{
			Clear();
			m_vecRange.push_back(UiRect(col_index, row_index, col_index, row_index));
			m_pBody->_SelItem(row_index, col_index, true);
			m_pBody->Invalidate();
		}
	}

	void GridSelRange::SetSelItemRange(UiRect rc, bool ctrl, bool shift)
	{
		assert(m_vecRange.size() < 3);
		if (ctrl && shift)
		{
			ctrl = false;
			shift = false;
		}

		if (!ctrl)
		{
			Clear();
			m_vecRange.push_back(rc);
			m_pBody->_SelRange(rc, true);
			m_pBody->Invalidate();
		}
		else
		{
			assert(m_vecRange.size() > 0);		//ButtonDown时应该调用了SetSelItem, 给m_vecRange赋值
			if (m_vecRange.size() == 0)
			{
				m_vecRange.push_back(rc);
				m_pBody->_SelRange(rc, true);
				m_pBody->Invalidate();
			}
			else
			{
				if (m_vecRange.size() == 1)
				{
					m_pBody->_SelRange(rc, true);
					m_vecRange.push_back(rc);
				}
				else if (m_vecRange.size() == 2)
				{
					m_pBody->_SelRange(m_vecRange[1], false);
					//m_pBody->_SelRange(m_vecRange[0], true);
					m_pBody->_SelRange(rc, true);
					m_vecRange.pop_back();
					m_vecRange.push_back(rc);
				}	
				m_pBody->Invalidate();
			}
		}
	}

	void GridSelRange::SetSelRow(int row_index, bool ctrl, bool shift)
	{
		assert(m_vecRange.size() < 2);
		if (ctrl && shift)
		{
			ctrl = false;
			shift = false;
		}

		if (ctrl)
		{
			if (m_mapSelRow.find(row_index) == m_mapSelRow.end())
			{
				m_pBody->_SelRow(row_index, true);
				m_mapSelRow[row_index] = nullptr;
			}
			else
			{
				m_pBody->_SelRow(row_index, false);
				m_mapSelRow.erase(row_index);
			}
			m_pBody->Invalidate();
		}
		else if (shift)
		{
			if (m_mapSelRow.size() == 0)
			{
				m_pBody->_SelRow(row_index, true);
				m_mapSelRow[row_index] = nullptr;
				m_pBody->Invalidate();
			}
			else
			{
				bool bChange = false;
				int min_row_index = 0, max_row_index = 0;
				min_row_index = m_mapSelRow.begin()->first;
				max_row_index = m_mapSelRow.rbegin()->first;		

				min_row_index = min(min_row_index, row_index);
				max_row_index = max(max_row_index, row_index);

				for (int row = min_row_index; row <= max_row_index; row++)
				{
					if (m_mapSelRow.find(row) == m_mapSelRow.end())
					{
						bChange = true;
						m_pBody->_SelRow(row, true);
						m_mapSelRow[row] = nullptr;
					}
				}
				if (bChange)
					m_pBody->Invalidate();
			}
		}
		else
		{
			Clear();
			m_pBody->_SelRow(row_index, true);
			m_mapSelRow[row_index] = nullptr;
			m_pBody->Invalidate();
		}
	}

	void GridSelRange::SetSelRowRange(int row_index, int row_index_end, bool ctrl, bool shift)
	{

		assert(m_vecRange.size() < 2);
		assert(row_index <= row_index_end);
		if (row_index > row_index_end)
			return;
		if (ctrl || shift)		//直接返回不处理了, 搞不清逻辑了
			return;
#if 0
		if (ctrl && shift)
		{
			ctrl = false;
			shift = false;
		}

		if (ctrl)
		{
			bool bChange = false;
			for (int row = row_index; row <= row_index_end; row++)
			{
				if (m_mapSelRow.find(row) == m_mapSelRow.end())
				{
					bChange = true;
					m_pBody->_SelRow(row, true);
					m_mapSelRow[row] = nullptr;
				}
			}
			if (bChange)
				m_pBody->Invalidate();
		}
		else if (shift)
		{
			bool bChange = false;
			int min_row_index = 0, max_row_index = 0;
			if (m_mapSelRow.size() > 0){
				min_row_index = m_mapSelRow.begin()->first;
				max_row_index = m_mapSelRow.rbegin()->first;
			}
				
			min_row_index = min(min_row_index, row_index);
			max_row_index = max(max_row_index, row_index_end);

			for (int row = min_row_index; row <= max_row_index; row++)
			{
				if (m_mapSelRow.find(row) == m_mapSelRow.end())
				{
					bChange = true;
					m_pBody->_SelRow(row, true);
					m_mapSelRow[row] = nullptr;
				}
			}
			if (bChange)
				m_pBody->Invalidate();
		}
		else
#endif
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
		}
	}

	void GridSelRange::SetSelCol(int col_index, bool ctrl, bool shift)
	{
		assert(m_vecRange.size() < 2);
		if (ctrl && shift)
		{
			ctrl = false;
			shift = false;
		}

		if (ctrl)
		{
			if (m_mapSelCol.find(col_index) == m_mapSelCol.end())
			{
				m_pBody->_SelCol(col_index, true);
				m_mapSelCol[col_index] = nullptr;
			}
			else
			{
				m_pBody->_SelCol(col_index, false);
				m_mapSelCol.erase(col_index);
			}
			m_pBody->Invalidate();
		}
		else if (shift)
		{
			if (m_mapSelCol.size() == 0)
			{
				m_pBody->_SelCol(col_index, true);
				m_mapSelCol[col_index] = nullptr;
				m_pBody->Invalidate();
			}
			else
			{
				bool bChange = false;
				int min_col_index = 0, max_col_index = 0;
				min_col_index = m_mapSelCol.begin()->first;
				max_col_index = m_mapSelCol.rbegin()->first;

				min_col_index = min(min_col_index, col_index);
				max_col_index = max(max_col_index, col_index);

				for (int col = min_col_index; col <= max_col_index; col++)
				{
					if (m_mapSelCol.find(col) == m_mapSelCol.end())
					{
						bChange = true;
						m_pBody->_SelCol(col, true);
						m_mapSelCol[col] = nullptr;
					}
				}
				if (bChange)
					m_pBody->Invalidate();
			}
		}
		else
		{
			Clear();
			m_pBody->_SelCol(col_index, true);
			m_mapSelCol[col_index] = nullptr;
			m_pBody->Invalidate();
		}
	}

	void GridSelRange::SetSelColRange(int col_index, int col_index_end, bool ctrl, bool shift)
	{
		assert(m_vecRange.size() < 2);
		assert(col_index <= col_index_end);
		if (col_index > col_index_end)
			return;
		if (ctrl || shift)		//直接返回不处理了, 搞不清逻辑了
			return;
#if 0
		if (ctrl && shift)
		{
			ctrl = false;
			shift = false;
		}

		if (ctrl)
		{
			bool bChange = false;
			for (int col = col_index; col <= col_index_end; col++)
			{
				if (m_mapSelCol.find(col) == m_mapSelCol.end())
				{
					bChange = true;
					m_pBody->_SelCol(col, true);
					m_mapSelCol[col] = nullptr;
				}
			}
			if (bChange)
				m_pBody->Invalidate();
		}
		else if (shift)
		{
			bool bChange = false;
			int min_col_index = 0, max_col_index = 0;
			if (m_mapSelCol.size() > 0){
				min_col_index = m_mapSelCol.begin()->first;
				max_col_index = m_mapSelCol.rbegin()->first;
			}

			min_col_index = min(min_col_index, col_index);
			max_col_index = max(max_col_index, col_index_end);

			for (int col = min_col_index; col <= max_col_index; col++)
			{
				if (m_mapSelCol.find(col) == m_mapSelCol.end())
				{
					bChange = true;
					m_pBody->_SelCol(col, true);
					m_mapSelCol[col] = nullptr;
				}
			}
			if (bChange)
				m_pBody->Invalidate();
		}
		else
#endif
		{
			Clear();
			for (int col = col_index; col <= col_index_end; col++)
			{
				if (m_mapSelCol.find(col) == m_mapSelCol.end())
				{
					m_pBody->_SelCol(col, true);
					m_mapSelCol[col] = nullptr;
				}
			}
			m_pBody->Invalidate();
		}
	}

	void GridSelRange::MergeRange()
	{
		assert(m_vecRange.size() < 3);
		if (m_vecRange.size() == 2)
		{
			UiRect rc = m_vecRange[0];
			UiRect rc1 = m_vecRange[1];
			rc.left = min(rc.left, rc1.left);
			rc.top = min(rc.top, rc1.top);
			rc.right = max(rc.right, rc1.right);
			rc.bottom = max(rc.bottom, rc1.bottom);
			m_vecRange.pop_back();
			m_vecRange[0] = rc;
		}
	}
	
	/*bool GridSelRange::IsItemSelected(int row_index, int col_index)
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
	}*/

	bool GridSelRange::IsRowSelected(int row_index)
	{
		return m_mapSelRow.find(row_index) != m_mapSelRow.cend();
	}

	bool GridSelRange::IsColSelected(int col_index)
	{
		return m_mapSelCol.find(col_index) != m_mapSelCol.cend();
	}

}