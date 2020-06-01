#pragma once

namespace ui
{

	enum GridItemType
	{
		GIT_String = 0,
		GIT_Int,
		GIT_Double,
		GIT_Combo,
		GIT_Date,
	};
	
	class GridItem
	{
	public:
		int row_index;
		int col_index;
		GridItemType type;

		std::wstring text;
		int iValue;
		double dValue;
		std::vector<std::wstring> combo_list;
		std::wstring date;

		GridItem(std::wstring txt = L"", int row = -1, int col = -1, GridItemType item_type = GIT_String) : text(txt), row_index(row), col_index(col)\
			, type(item_type), iValue(0), dValue(0.0){
			
		};
		virtual ~GridItem(){};

		void InitTypeInt(int value){
			_ClearType();
			type = GIT_Int;
			iValue = value;
		}

		void InitTypeDouble(double value){
			_ClearType();
			type = GIT_Double;
			dValue = value;
		}

		void InitTypeCombo(const std::vector<std::wstring>& value){
			_ClearType();
			type = GIT_Combo;
			combo_list = value;
		}

		void InitTypeDate(std::wstring value){
			_ClearType();
			type = GIT_Date;
			date = value;
		}

		bool CopyType(GridItem *from){
			bool ret = false;
			if (from && type != from->type)
			{
				type = from->type;
				if (type == GIT_Combo)
					combo_list = from->combo_list;
				ret = true;
			}
			return ret;
		}

	protected:
		void _ClearType(){
			type = GIT_String;
			iValue = 0;
			dValue = 0.0;
			combo_list.clear();
			date = L"";
		}
	};

	

	
}