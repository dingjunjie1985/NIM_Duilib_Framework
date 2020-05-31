#pragma once

namespace ui
{

	/*enum GridItemType
	{

	};*/
	
	class GridItem
	{
	public:
		int row_index;
		int col_index;
		std::wstring text;

		GridItem(std::wstring txt = L"", int row = -1, int col = -1) : text(txt), row_index(row), col_index(col){};
		virtual ~GridItem(){};
	};

	

	
}