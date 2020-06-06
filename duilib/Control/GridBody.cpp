#include "StdAfx.h"
#include "GridBody.h"

namespace ui
{
	int GridBody::_SumIntList(const std::vector<int> &vec){
		int sum = 0;
		for (auto it = vec.cbegin(); it != vec.cend(); it++)
			sum += (*it);
		return sum;
	}
	GridRow* GridBody::_GetHeader() const
	{
		assert(m_vecRow.size() > 0);
		return m_vecRow[0];
	}
	void GridBody::_BeginEditGridItem(GridItem *item)
	{
		int row_index = item->row_index;
		int col_index = item->col_index;
		int posx = 0, posy = 0;
		assert(row_index < m_vLayout.size());
		for (size_t i = 0; i < row_index; i++)
			posy += m_vLayout[i];
		assert(col_index < m_hLayout.size());
		for (size_t j = 0; j < col_index; j++)
			posx += m_hLayout[j];
		if (item->type == GIT_String || item->type == GIT_Int || item->type == GIT_Double)
		{
			m_pReEdit->SetVisible_(true);
			m_pReEdit->SetFixedWidth(m_hLayout[col_index] - 1);
			m_pReEdit->SetFixedHeight(m_vLayout[row_index] - 1);
			m_pReEdit->SetMargin({ posx, posy, 0, 0 });
			m_pReEdit->SetText(item->text);
			m_pReEdit->SetFocus();
			m_pReEdit->SetSelAll();
			m_pReEditGridItem = item;
		}
		else if (item->type == GIT_Combo)
		{
			m_pComboEdit->SetVisible_(true);
			m_pComboEdit->SetFixedWidth(m_hLayout[col_index] - 1);
			m_pComboEdit->SetFixedHeight(m_vLayout[row_index] - 1);
			m_pComboEdit->SetMargin({ posx, posy, 0, 0 });

			m_pComboEdit->RemoveAll();
			for (size_t i = 0; i < item->combo_list.size(); i++)
			{
				ListContainerElement *combo_item = new ListContainerElement;
				combo_item->SetFixedHeight(20);
				combo_item->SetText(item->combo_list[i]);
				m_pComboEdit->Add(combo_item);
				if (item->text == item->combo_list[i])
					m_pComboEdit->SelectItem(i);
			}
			m_pComboEditGridItem = item;
		}
		else if (item->type == GIT_Date)
		{

		}
	}
	void GridBody::_EndEdit()
	{
		if (m_pComboEditGridItem)
		{
			assert(m_pComboEdit->IsVisible());
			m_pComboEditGridItem = nullptr;
			m_pComboEdit->SetVisible_(false);
		}
		if (m_pReEditGridItem)
		{
			assert(m_pReEdit->IsVisible());
			if (m_pReEditGridItem->text != m_pReEdit->GetText())
			{
				m_pReEditGridItem->text = m_pReEdit->GetText();
				m_pWindow->SendNotify(this, kEventTextChange, m_pReEditGridItem->row_index, m_pReEditGridItem->col_index);
			}
			m_pReEdit->SetVisible_(false);
			m_pReEditGridItem = nullptr;
		}
	}

	bool GridBody::_GetGridItemByMouse(CPoint pt, CPoint& position, bool fixed)
	{
		int fixed_row_height = GetFixedRowHeight();
		int fixed_col_width = GetFixedColWidth();
		CSize szOff = m_pGrid->GetScrollPos();

		pt.Offset(-m_rcItem.left, -m_rcItem.top);
		assert(pt.x > 0 && pt.y > 0);
		if (pt.x <= 0 || pt.y <= 0)
			return false;
		UiRect rcFixed({ 0, 0, fixed_col_width, fixed_row_height });
		UiRect rcFixedRow({ fixed_col_width, 0, m_pGrid->GetWidth(), fixed_row_height });
		UiRect rcFixedCol({ 0, fixed_row_height, fixed_col_width, m_pGrid->GetHeight() });
		if (rcFixed.IsPointIn(pt) || rcFixedRow.IsPointIn(pt) || rcFixedCol.IsPointIn(pt))		//in position of fixed row or fixed col
		{
			bool bFind = false;
			if (fixed)
			{
				int posx = 0, posy = 0;
				if (rcFixed.IsPointIn(pt))			//in position of fixed row or fixed col
					;
				else if (rcFixedRow.IsPointIn(pt))
					posx = -szOff.cx;
				else if (rcFixedCol.IsPointIn(pt))
					posy = -szOff.cy;
				CPoint pt_position;
				for (size_t i = 0; i < GetRowCount(); i++)
				{
					posy += m_vLayout[i];
					if (posy >= pt.y)
					{
						for (size_t j = 0; j < GetColCount(); j++)
						{
							posx += m_hLayout[j];
							if (posx >= pt.x)
							{
								pt_position.x = j;
								bFind = true;
								break;
							}
						}
						pt_position.y = i;
						break;
					}
				}
				assert(bFind);
				if (bFind)
				{
					position = pt_position;
				}
			}
			return bFind;
		}

		bool ret = false;
		//in position normal grid item
		assert(pt.x - fixed_col_width > 0 && pt.y - fixed_row_height > 0 && pt.x < m_pGrid->GetWidth() && pt.y < m_pGrid->GetHeight());
		if (pt.x - fixed_col_width > 0 && pt.y - fixed_row_height > 0 && pt.x < m_pGrid->GetWidth() && pt.y < m_pGrid->GetHeight())
		{
			CPoint ptOff = pt, pt_position;
			ptOff.Offset(szOff.cx, szOff.cy);
			int posx = 0, posy = 0;

			for (size_t i = 0; i < GetRowCount(); i++)
			{
				posy += m_vLayout[i];
				if (posy >= ptOff.y)
				{
					for (size_t j = 0; j < GetColCount(); j++)
					{
						posx += m_hLayout[j];
						if (posx >= ptOff.x)
						{
							ret = true;
							pt_position.x = j;
							break;
						}
					}
					pt_position.y = i;
					break;
				}
			}
			assert(ret);
			if (ret)
			{
				position = pt_position;
			}
		}
		return ret;
	}

	int GridBody::_GetGridItemTop(int row_index)
	{
		int posy = 0;
		assert(row_index < GetRowCount());
		if (row_index < GetRowCount())
		{
			for (size_t i = 0; i < row_index; i++)
			{
				posy += m_vLayout[i];
			}
		}
		return posy;
	}
	int GridBody::_GetGridItemLeft(int col_index)
	{
		int posx = 0;
		assert(col_index < GetColCount());
		if (col_index < GetColCount())
		{
			for (size_t i = 0; i < col_index; i++)
			{
				posx += m_hLayout[i];
			}
		}
		return posx;
	}
	UiRect GridBody::_GetGridItemPos(int row_index, int col_index)
	{
		int posx = _GetGridItemLeft(col_index), posy = _GetGridItemTop(row_index);
		return UiRect(posx, posy, posx + m_hLayout[col_index], posy + m_vLayout[row_index]);
	}

	GridBody::GridBody(Grid *pGrid) : m_selRange(this), m_pGrid(pGrid){
		m_vLayout.push_back(m_defaultRowHeight);		//insert header hegith
		m_vecRow.push_back(new GridRow());
		SetFixedHeight(m_defaultRowHeight);
		AddHeaderItem(L"行号", 30);
		SetFixedColCount(1);
		SetFixedRowCount(1);

		m_pReEdit = new RichEdit;
		m_pReEdit->SetAttribute(L"class", L"simple");
		m_pReEdit->SetAttribute(L"bkcolor", L"white");
		m_pReEdit->SetAttribute(L"align", L"vcenter");
		m_pReEdit->SetAttribute(L"padding", L"2,0,2,0");
		m_pReEdit->SetVisible_(false);
		Add(m_pReEdit);

		m_pComboEdit = new Combo;
		m_pComboEdit->SetAttribute(L"class", L"combo2");
		m_pComboEdit->SetAttribute(L"bkcolor", L"white");
		m_pComboEdit->SetVisible_(false);
		m_pComboEdit->AttachSelect(nbase::Bind(&GridBody::OnComboEditSelected, this, std::placeholders::_1));
		Add(m_pComboEdit);
	};

	int GridBody::GetColCount() const
	{
		assert(m_hLayout.size() == _GetHeader()->size());
		return m_hLayout.size();
	}
	void GridBody::SetColCount(int count)
	{

	}

	int GridBody::GetRowCount() const
	{
		assert(m_vLayout.size() == m_vecRow.size());
		return m_vLayout.size();
	}
	void GridBody::SetRowCount(int count)
	{
		assert(m_vLayout.size() == m_vecRow.size());
		if (count > GetRowCount())
		{
			int dis = count - GetRowCount();
			for (size_t i = 0; i < dis; i++)
			{
				AddRow();
			}
		}
		else if (count < GetRowCount())
		{
			for (size_t i = GetRowCount() - 1; i <= count; i--)
			{
				RemoveRow(i);
			}
		}
	}

	int GridBody::GetFixedColCount() const
	{
		return m_nFixedCol;
	}
	void GridBody::SetFixedColCount(int fixed)
	{
		assert(fixed <= GetColCount());
		if (fixed <= GetColCount() && fixed != m_nFixedCol)
		{
			m_nFixedCol = fixed;
			m_selRange.Clear();
			Invalidate();
		}
	}

	int GridBody::GetFixedRowCount() const
	{
		return m_nFixedRow;
	}
	void GridBody::SetFixedRowCount(int fixed)
	{
		assert(fixed <= GetRowCount());
		if (fixed <= GetRowCount() && fixed != m_nFixedRow)
		{
			m_nFixedRow = fixed;
			m_selRange.Clear();
			Invalidate();
		}
	}


	int GridBody::GetHeaderHeight() const
	{
		int height = 0;
		assert(m_vLayout.size() > 0);
		if (m_vLayout.size() > 0)
			height = m_vLayout[0];
		return height;
	}
	void GridBody::SetHeaderHeight(int height)
	{
		assert(m_vLayout.size() > 0);
		if (m_vLayout.size() > 0 && m_vLayout[0] != height)
		{
			m_vLayout[0] = height;
			SetFixedHeight(_SumIntList(m_vLayout));
			Invalidate();
		}
	}

	std::wstring GridBody::GetFixedBkColor() const
	{
		return m_strFixedBkColor;
	}
	void GridBody::SetFixedBkColor(std::wstring color)
	{
		m_strFixedBkColor = color;
		Invalidate();
	}

	std::wstring GridBody::GetSelForeColor() const
	{
		return m_strSelForeColor;
	}
	void GridBody::SetSelForeColor(std::wstring color)
	{
		m_strSelForeColor = color;
		Invalidate();
	}

	std::wstring GridBody::GetGridLineColor() const
	{
		return m_strGridLineColor;
	}
	void GridBody::SetGridLineColor(std::wstring color)
	{
		m_strGridLineColor = color;
		Invalidate();
	}

	int GridBody::GetFixedColWidth() const
	{
		int fixed_width = 0;
		assert(m_nFixedCol <= m_hLayout.size());
		for (size_t i = 0; i < m_nFixedCol; i++)
		{
			fixed_width += m_hLayout[i];
		}
		return fixed_width;
	}
	int GridBody::GetFixedRowHeight() const
	{
		int fixed_height = 0;
		assert(m_nFixedRow <= m_vLayout.size());
		for (size_t i = 0; i < m_nFixedRow; i++)
		{
			fixed_height += m_vLayout[i];
		}
		return fixed_height;
	}

	std::wstring GridBody::GetGridItemText(int row, int col)
	{
		std::wstring str;
		GridItem *item = GetGridItem(row, col);
		assert(item);
		if (item)
		{
			str = item->text;
		}
		return str;
	}
	bool GridBody::SetGridItemText(std::wstring text, int row, int col)
	{
		bool ret = false;
		GridItem *item = GetGridItem(row, col);
		assert(item);
		if (item)
		{
			item->text = text;
			ret = true;
		}
		return ret;
	}

	bool GridBody::IsGridItemFixed(int row, int col)
	{
		bool ret = false;
		if (row < m_nFixedRow || col < m_nFixedCol)
			ret = true;
		return ret;
	}

	GridItem* GridBody::AddHeaderItem(std::wstring text, int width)
	{
		assert(m_vecRow.size() > 0 && _GetHeader()->size() == m_hLayout.size());
		int col_index = _GetHeader()->size();
		GridItem *item = new GridItem(text, 0, col_index);
		_GetHeader()->push_back(item);
		m_hLayout.push_back(width);
		SetFixedWidth(_SumIntList(m_hLayout));
		for (size_t i = 1; i < m_vecRow.size(); i++)
		{
			m_vecRow[i]->push_back(new GridItem(L"", i, col_index));
		}

		m_selRange.Clear();
		Invalidate();
		return item;
	}

	bool GridBody::AddRow()
	{
		assert(m_hLayout.size() > 0);	//新增行前必须现有列
		int row_index = m_vecRow.size();
		GridRow *row = new GridRow();
		wchar_t buf[16] = {};
		for (size_t i = 0; i < m_hLayout.size(); i++)
		{
			GridItem *item = nullptr;
#if 0
			if (i == 0)
				item = new GridItem(_itow(m_vecRow.size(), buf, 10), row_index, i);
			else
				item = new GridItem(L"", row_index, i);
#else
			item = new GridItem(_itow(m_vecRow.size(), buf, 10), row_index, i);
#endif
			row->push_back(item);
			item->CopyType(GetGridItem(0, i));
		}

		m_vecRow.push_back(row);
		m_vLayout.push_back(m_defaultRowHeight);
		assert(m_vecRow.size() == m_vLayout.size());
		SetFixedHeight(_SumIntList(m_vLayout));

		m_selRange.Clear();
		Invalidate();
		return true;
	}

	GridItem *GridBody::GetGridItem(int row, int col)
	{
		assert(_GetHeader()->size() == m_hLayout.size() && m_vecRow.size() == m_vLayout.size());
		GridItem *item = nullptr;
		if (row >= 0 && row < m_vecRow.size() && col >= 0 && col < m_vecRow[row]->size())
		{
			item = m_vecRow[row]->at(col);
		}
		return item;
	}

	bool GridBody::RemoveRow(int row)
	{
		bool ret = false;
		_EndEdit();
		assert(m_vLayout.size() == m_vecRow.size());
		if (row > 0 && row < m_vecRow.size())
		{
			GridRow *grid_row = m_vecRow[row];
			for (size_t i = 0; i < grid_row->size(); i++)
			{
				delete grid_row->at(i);
			}
			delete grid_row;
			m_vecRow.erase(m_vecRow.begin() + row);
			//下面行的GridItem的row_index--
			for (size_t i = row; i < m_vecRow.size(); i++)
			{
				GridRow *row = m_vecRow[i];
				assert(row->at(0)->row_index - 1 == i);
				for (size_t j = 0; j < row->size(); j++)
				{
					row->at(j)->row_index = i;
				}
			}

			m_vLayout.erase(m_vLayout.begin() + row);

			if (m_nFixedRow >= row + 1)
			{
				m_nFixedRow--;
			}

			SetFixedHeight(_SumIntList(m_vLayout));
			Invalidate();
			ret = true;
		}

		return ret;
	}

	bool GridBody::RemoveCol(int col)
	{
		bool ret = false;
		return ret;
	}

	void GridBody::Clear(bool include_header)
	{
		_EndEdit();
		assert(m_vLayout.size() == m_vecRow.size());

		for (size_t i = m_vecRow.size() - 1; i > 0; i--)
		{
			RemoveRow(i);
		}

		if (include_header)		//移除header
		{

		}
	}

	void GridBody::HandleMessage(EventArgs& event)
	{
		if (!IsMouseEnabled() && event.Type > kEventMouseBegin && event.Type < kEventMouseEnd) {
			if (m_pParent != NULL) m_pParent->HandleMessageTemplate(event);
			else Box::HandleMessage(event);
			return;
		}
		bool bHandle = false;
		if (event.Type == kEventInternalDoubleClick)
		{
			OnMouseDoubleClick(event);
			bHandle = true;
		}
		if (!bHandle)
			__super::HandleMessage(event);
	}

	bool GridBody::ButtonDown(EventArgs& msg)
	{
		_EndEdit();
		CPoint position;
		bool bFind = _GetGridItemByMouse(msg.ptMouse, position, true);
		if (bFind)
		{
			printf("GridBody::ButtonDown item position{%d,%d}\n", position.x, position.y);
			if (position.x < m_nFixedCol && position.y < m_nFixedRow)
			{
				return true;
			}
			if (position.x < m_nFixedCol)			//点击fixed col	选择行
			{
				m_selRange.SetSelRow(position.y);	
			}
			else if (position.y < m_nFixedRow)		//点击fixed row 选择列
			{
				m_selRange.SetSelCol(position.x);
			}
			else
				m_selRange.SetSelItem(position.y, position.x);
		}
		return true;
	}

	bool GridBody::OnMouseDoubleClick(EventArgs& msg)
	{
		CPoint position;
		bool bFind = _GetGridItemByMouse(msg.ptMouse, position);
		if (bFind)
		{
			GridItem *item = GetGridItem(position.y, position.x);
			assert(item);
			if (item)
			{
				wprintf(L"GridBody::OnMouseDoubleClick {%d, %d} %s\n", position.x, position.y, item->text.c_str());
				_BeginEditGridItem(item);
			}
		}
		return true;
	}

	bool GridBody::OnComboEditSelected(EventArgs *args)
	{
		if (m_pComboEditGridItem && m_pComboEdit && m_pComboEdit->IsVisible())
		{
			if (m_pComboEditGridItem->text != m_pComboEdit->GetText())
			{
				m_pComboEditGridItem->text = m_pComboEdit->GetText();
				m_pWindow->SendNotify(this, kEventTextChange, m_pComboEditGridItem->row_index, m_pComboEditGridItem->col_index);
			}
		}
		return true;
	}

	void GridBody::PaintChild(IRenderContext* pRender, const UiRect& rcPaint)
	{
		UiRect rcTemp;
		if (!::IntersectRect(&rcTemp, &rcPaint, &m_rcItem)) return;

		for (auto it = m_items.begin(); it != m_items.end(); it++) {
			Control* pControl = *it;
			if (!pControl->IsVisible()) continue;
			/*if (pControl->IsFloat()) {
				pControl->AlphaPaint(pRender, rcPaint);
			}
			else */{
				CSize scrollPos = m_pGrid->GetScrollPos();
				UiRect rcNewPaint = GetPaddingPos();
				rcNewPaint.left += GetFixedColWidth();
				rcNewPaint.top += GetFixedRowHeight();
				if (rcNewPaint.left > rcNewPaint.right) rcNewPaint.left = rcNewPaint.right;
				if (rcNewPaint.top > rcNewPaint.bottom) rcNewPaint.top = rcNewPaint.bottom;
				AutoClip alphaClip(pRender, rcNewPaint, m_bClip);
				rcNewPaint.Offset(scrollPos.cx, scrollPos.cy);
				rcNewPaint.Offset(GetRenderOffset().x, GetRenderOffset().y);

				CPoint ptOffset(scrollPos.cx, scrollPos.cy);
				CPoint ptOldOrg = pRender->OffsetWindowOrg(ptOffset);
				pControl->AlphaPaint(pRender, rcNewPaint);
				pRender->SetWindowOrg(ptOldOrg);
			}
		}
	}

	void GridBody::PaintStatusColor(IRenderContext* pRender)
	{
		__super::PaintStatusColor(pRender);
		//paint fixed
		CSize szOff = m_pGrid->GetScrollPos();
		int fixed_row_height = GetFixedRowHeight();
		int fixed_col_width = GetFixedColWidth();
		int gridWidth = m_pGrid->GetWidth();
		int gridHeight = m_pGrid->GetHeight();
		if (fixed_row_height > 0)
		{
			UiRect rcPaint = GetPos();
			rcPaint.bottom = rcPaint.top + fixed_row_height;
			rcPaint.right = rcPaint.left + (GetFixedWidth() - szOff.cx > gridWidth ? gridWidth : GetFixedWidth() - szOff.cx);
			pRender->DrawColor(rcPaint, m_strFixedBkColor, 255);
		}
		if (fixed_col_width > 0)
		{
			UiRect rcPaint = GetPos();
			rcPaint.right = rcPaint.left + fixed_col_width;
			rcPaint.bottom = rcPaint.top + (GetFixedHeight() - szOff.cy > gridHeight ? gridHeight : GetFixedHeight() - szOff.cy);
			pRender->DrawColor(rcPaint, m_strFixedBkColor, 255);
		}
		//paint sel item
		UiRect rcClip = m_pGrid->GetPos();
		rcClip.left += GetFixedColWidth();
		rcClip.top += GetFixedRowHeight();;
		AutoClip clip(pRender, rcClip, m_bClip);

		UiRect rcPaint = GetPos();
		for (size_t i = 0; i < m_selRange.m_vecRange.size(); i++)
		{
			UiRect rcRange = m_selRange.m_vecRange[i];
			int posx = _GetGridItemLeft(rcRange.left);
			int posy = _GetGridItemTop(rcRange.top);
			for (size_t r = rcRange.top; r <= rcRange.bottom; r++)
			{
				posx = _GetGridItemLeft(rcRange.left);
				for (size_t l = rcRange.left; l <= rcRange.right; l++)
				{
					UiRect rcPos = { posx, posy, posx + m_hLayout[l], posy + m_vLayout[r] };
					rcPos.Offset(-szOff.cx, -szOff.cy);
					if (rcPos.right > fixed_col_width || rcPos.bottom > fixed_row_height){
						rcPos.Offset(rcPaint.left, rcPaint.top);
						rcPos.Deflate({ 1, 1, 2, 2, });
						pRender->DrawColor(rcPos, m_strSelForeColor, 255);
					}	
					posx += m_hLayout[l];
					if (posx - szOff.cx > gridWidth)
						break;
				}
				posy += m_vLayout[r];
				if (posy - szOff.cy > gridHeight)
					break;
			}
		}
	}

	void GridBody::PaintBorder(IRenderContext* pRender)
	{
		__super::PaintBorder(pRender);
		if (m_pGrid->m_bPaintGridLine && m_hLayout.size() > 0 && m_vLayout.size() > 0)
		{
			CSize szOff = m_pGrid->GetScrollPos();
			int posx = 0, posy = 0;
			int headerH = GetHeaderHeight();
			int fixedColWidth = GetFixedColWidth();
			int fixedRowHeight = GetFixedRowHeight();
			int gridWidth = m_pGrid->GetWidth();
			int gridHeight = m_pGrid->GetHeight();
			UiRect rcLineH, rcLineV;
			DWORD dwGridLineColor = GlobalManager::GetTextColor(m_strGridLineColor);

			CPoint ptOldOrg = pRender->OffsetWindowOrg({ -m_rcItem.left, -m_rcItem.top });
			{
				//draw fixed HLine
				rcLineH.left = 0;
				rcLineH.right = GetFixedWidth() - szOff.cx > gridWidth ? gridWidth : GetFixedWidth() - szOff.cx;
				assert(m_nFixedRow <= m_vLayout.size());
				for (size_t i = 0; i < m_nFixedRow; i++)
				{
					posy += m_vLayout[i];
					rcLineH.top = rcLineH.bottom = posy - 1;
					pRender->DrawLine(rcLineH, 1, dwGridLineColor);
				}
				//draw HLine
				for (size_t i = m_nFixedRow; i < m_vLayout.size(); i++)
				{
					posy += m_vLayout[i];
					if (posy - szOff.cy > gridHeight)	//超出grid高度
						break;
					if (posy - szOff.cy > fixedRowHeight && posy - szOff.cy < gridHeight)
					{
						rcLineH.top = rcLineH.bottom = posy - szOff.cy - 1;
						pRender->DrawLine(rcLineH, 1, dwGridLineColor);
					}
				}
			
				//draw fixed VLine
				rcLineV.top = 0;
				rcLineV.bottom = GetFixedHeight() - szOff.cy > gridHeight ? gridHeight : GetFixedHeight() - szOff.cy;
				assert(m_nFixedCol <= m_hLayout.size());
				for (size_t i = 0; i < m_nFixedCol; i++)
				{
					posx += m_hLayout[i];
					rcLineV.left = rcLineV.right = posx - 1;
					pRender->DrawLine(rcLineV, 1, dwGridLineColor);
				}
				//draw VLine
				for (size_t i = m_nFixedCol; i < m_hLayout.size(); i++)
				{
					posx += m_hLayout[i];
					if (posx - szOff.cx > gridWidth)		//超出grid宽度
						break;
					if (posx - szOff.cx > fixedColWidth)
					{
						rcLineV.left = rcLineV.right = posx - szOff.cx - 1;
						pRender->DrawLine(rcLineV, 1, dwGridLineColor);
					}
				}
			}
			
			pRender->SetWindowOrg(ptOldOrg);
		}
	}

	void GridBody::PaintText(IRenderContext* pRender)
	{
		CSize szOff = m_pGrid->GetScrollPos();
		int posx = 0;
		int posy = 0;
		int row_count = GetRowCount();
		int col_count = GetColCount();
		int fixedColWidth = GetFixedColWidth();
		int fixedRowHeight = GetFixedRowHeight();
		int gridWidth = m_pGrid->GetWidth();
		int gridHeight = m_pGrid->GetHeight();
		DWORD dwClrColor = GlobalManager::GetTextColor(L"textdefaultcolor");

		//draw fixed col && fixed row text
		for (int i = 0; i < m_nFixedRow; i++)
		{
			posx = 0;
			GridRow *grid_row = m_vecRow[i];
			for (size_t j = 0; j < m_nFixedCol; j++)
			{
				UiRect rc = { posx, posy, posx + m_hLayout[j], posy + m_vLayout[i] };
				rc.Offset({ m_rcItem.left, m_rcItem.top });
				pRender->DrawText(rc, grid_row->at(j)->text, dwClrColor, L"system_12", m_uTextStyle, 255, false);
				posx += m_hLayout[j];
			}
			posy += m_vLayout[i];
		}

		//draw fixed row text
		{
			UiRect rcClip = m_pGrid->GetPos();
			rcClip.left += GetFixedColWidth();
			rcClip.bottom = rcClip.top + GetFixedRowHeight();
			AutoClip clip(pRender, rcClip, m_bClip);
			posy = 0;
			for (int i = 0; i < m_nFixedRow; i++)
			{
				GridRow *grid_row = m_vecRow[i];
				posx = GetFixedColWidth();
				for (size_t j = m_nFixedCol; j < col_count; j++)
				{
					std::wstring str = grid_row->at(j)->text;
					if (!str.empty() && posx + m_hLayout[j] - szOff.cx > fixedColWidth)		//单元格右边线没有超过fixedColWidth
					{
						UiRect rc = { posx, posy, posx + m_hLayout[j], posy + m_vLayout[i] };
						rc.Offset({ m_rcItem.left - szOff.cx, m_rcItem.top });
						pRender->DrawText(rc, str, dwClrColor, L"system_12", m_uTextStyle, 255, false);
					}
					posx += m_hLayout[j];
					if (posx - szOff.cx > gridWidth)	//超出grid宽度
						break;
				}
				posy += m_vLayout[i];
				if (posy - szOff.cy > gridHeight)		//超出grid高度
					break;
			}
		}

		//draw fixed col text
		{
			UiRect rcClip = m_pGrid->GetPos();
			rcClip.top += GetFixedRowHeight();
			rcClip.right = rcClip.left + GetFixedColWidth();
			AutoClip clip(pRender, rcClip, m_bClip);
			posx = 0;
			for (int i = 0; i < m_nFixedCol; i++)
			{
				posy = GetFixedRowHeight();
				for (size_t j = m_nFixedRow; j < row_count; j++)
				{
					GridRow *grid_row = m_vecRow[j];
					std::wstring str = grid_row->at(i)->text;
					if (!str.empty() && posy + m_vLayout[j] - szOff.cy > fixedRowHeight)		//单元格下边线没有超过fixedRowHeight
					{
						UiRect rc = { posx, posy, posx + m_hLayout[i], posy + m_vLayout[j] };
						rc.Offset({ m_rcItem.left, m_rcItem.top - szOff.cy });
						pRender->DrawText(rc, str, dwClrColor, L"system_12", m_uTextStyle, 255, false);
					}
					posy += m_vLayout[j];
					if (posy - szOff.cy > gridHeight)	//超出grid高度
						break;
				}
				posx += m_hLayout[i];
				if (posx - szOff.cx > gridWidth)		//超出grid宽度
					break;
			}
		}

		//draw other text
		{
			UiRect rcClip = m_pGrid->GetPos();
			rcClip.left += GetFixedColWidth();
			rcClip.top += GetFixedRowHeight();;
			AutoClip clip(pRender, rcClip, m_bClip);
			posy = GetFixedRowHeight();
			for (int i = m_nFixedRow; i < row_count; i++)
			{
				if (posy + m_vLayout[i] - szOff.cy > fixedRowHeight)		//单元格下边线没有超过fixedRowHeight
				{
					GridRow *grid_row = m_vecRow[i];
					posx = GetFixedColWidth();
					for (size_t j = m_nFixedCol; j < col_count; j++)
					{
						std::wstring str = grid_row->at(j)->text;
						if (!str.empty() && posx + m_hLayout[j] - szOff.cx > fixedColWidth)		//单元格右边线没有超过fixedColWidth
						{
							UiRect rc = { posx, posy, posx + m_hLayout[j], posy + m_vLayout[i] };
							rc.Offset({ m_rcItem.left - szOff.cx, m_rcItem.top - szOff.cy });
							pRender->DrawText(rc, str, dwClrColor, L"system_12", m_uTextStyle, 255, false);
						}
						posx += m_hLayout[j];
						if (posx - szOff.cx > gridWidth)		//超出grid宽度
							break;
					}
				}
				posy += m_vLayout[i];
				if (posy - szOff.cy > gridHeight)			//超出grid高度
					break;
			}
		}
	}
}