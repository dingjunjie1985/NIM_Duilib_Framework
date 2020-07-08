#pragma once
#include "GridBase.h"

namespace ui
{
	class Grid;
	class GridBody : public Box
	{
		friend class Grid;
		friend class GridSelRange;
	protected:
		GridBody(Grid *pGrid);
		virtual ~GridBody(){};

		void SetDefaultRowHeight(int height){ m_defaultRowHeight = height; };
		void SetDefaultColWidth(int width){ m_defaultColWidth = width; };
		int GetTotalRowHeight(){}

	protected:	//pass by grid
		/**
		* @brief ������
		*/
		int GetColCount() const;
		void SetColCount(int count);

		/**
		* @brief ������
		*/
		int GetRowCount() const;
		void SetRowCount(int count);

		/**
		* @brief �̶�����
		*/
		int GetFixedColCount() const;
		void SetFixedColCount(int fixed);

		/**
		* @brief �̶�����
		*/
		int GetFixedRowCount() const;
		void SetFixedRowCount(int fixed);

		/**
		* @brief �п�;
		* @param[in] col_index: �ڼ���,base on 0;
		*/
		int GetColumnWidth(int col_index) const;
		void SetColumnWidth(int col_index, int width);

		/**
		* @brief ��ͷ�߶�
		*/
		int GetHeaderHeight() const;
		void SetHeaderHeight(int height);

		/**
		* @brief �̶����еı���ɫ
		*/
		std::wstring GetFixedBkColor() const;
		void SetFixedBkColor(std::wstring color);

		/**
		* @brief ѡ�е�Ԫ���ǰ��ɫ
		*/
		std::wstring GetSelForeColor() const;
		void SetSelForeColor(std::wstring color);

		/**
		* @brief ��������ɫ
		*/
		std::wstring GetGridLineColor() const;
		void SetGridLineColor(std::wstring color);
	
		int GetFixedColWidth() const;
		int GetFixedRowHeight() const;

		/**
		* @brief ����/��ȡ��Ԫ���ı�����;
		* @param[in] row_index: �ڼ���,base on 0;
		* @param[in] col_index: �ڼ���,base on 0;
		*/
		std::wstring GetGridItemText(int row_index, int col_index);
		bool SetGridItemText(std::wstring text, int row_index, int col_index);

		/**
		* @brief �жϵ�Ԫ���Ƿ�fixed;
		* @param[in] row_index: �ڼ���,base on 0;
		* @param[in] col_index: �ڼ���,base on 0;
		*/
		bool IsGridItemFixed(int row_index, int col_index);

		/**
		* @brief �������ڱ�����;
		* @param[in] text: ��ͷ�ı�;
		* @param[in] width: �п��;
		* @return �����¼ӵı�ͷ��Ԫ�����ָ��,null��ʾδ�ɹ�;
		*/
		GridItem* AddCol(std::wstring text, int width = 80);

		/**
		* @brief �������ڱ�����
		* @return ���� trueΪ�ɹ���false Ϊʧ��
		*/
		bool AddRow();

		/**
		* @brief ��ȡ��Ԫ�����
		* @param[in] row_index: �ڼ���,base on 0;
		* @param[in] col_index: �ڼ���,base on 0;
		* @return ���ص�Ԫ�����ָ��,null��ʾδ�ҵ�;
		*/
		GridItem *GetGridItem(int row_index, int col_index);

		/**
		* @brief �Ƴ�һ��
		* @param[in] row_index: �ڼ���,base on 0;
		* @return ���� trueΪ�ɹ���false Ϊʧ��
		*/
		bool RemoveRow(int row_index);

		/**
		* @brief �Ƴ�һ��
		* @param[in] col_index: �ڼ���,base on 0;
		* @return ���� trueΪ�ɹ���false Ϊʧ��
		*/
		bool RemoveCol(int col_index);

		/**
		* @brief �������
		* @param[in] include_header: true��ʾ���header, false��ʾ����header;
		*/
		void Clear(bool include_header);

		/**
		* @brief ������ݱ����Ļص�ע��
		* @param[in] callback
		*/
		void AttachTextChange(const EventCallback& callback)	{ this->OnEvent[kEventTextChange] += callback; }

		/**
		* @brief ����excel
		* @param[in] file:	excel·��;
		* @param[in] sheet_num:	�����excel�ĵڼ�ҳ, base on 0;
		* @param[in] touch_header: true��ʾexcel�ĵ�һ����ΪGrid��Header����
		* @return ���� trueΪ�ɹ���false Ϊʧ��
		*/
		bool LoadExcel(std::wstring file, int sheet_num, bool touch_header);

		/**
		* @brief �и��������Զ��������
		* @param[in] col_index:	Ҫ�����������, base on 0;
		* @param[in] min_width:	��С���;
		* @param[in] max_width: �����, -1����û������;
		* @return ���� trueΪ�ɹ���false Ϊʧ��;
		*/
		bool AutoFixColWidth(int col_index, int min_width = 30, int max_width = -1);

	protected:
		virtual void HandleMessage(EventArgs& event) override;
		virtual bool ButtonDown(EventArgs& msg) override;
		virtual bool ButtonUp(EventArgs& msg) override;
		virtual bool OnMouseDoubleClick(EventArgs& msg);		//no override
		virtual bool OnMouseMove(EventArgs& msg);				//no override

		virtual void PaintChild(IRenderContext* pRender, const UiRect& rcPaint) override;
		virtual void PaintStatusColor(IRenderContext* pRender) override;
		virtual void PaintText(IRenderContext* pRender) override;
		virtual void PaintBorder(IRenderContext* pRender) override;
	protected:
		/**
		* @brief �༭�ĵ�Ԫ��ΪCombo����ʱ, ѡ����ComboItem����;
		* @return ���ؼ�;
		*/
		bool OnComboEditSelected(EventArgs *args);

	protected:
		/*
		* @brief ����vector<int>֮��;
		* @return ��;
		*/
		int _SumIntList(const std::vector<int> &vec);

		/*
		* @brief ��ȡ��ͷ����Ϣ;
		* @return ��ͷ����Ϣ;
		*/
		GridRow* _GetHeader() const;

		virtual void _BeginEditGridItem(GridItem *item);
		virtual void _EndEdit();
		bool _GetGridItemByMouse(CPoint pt, CPoint& position, bool fixed = false);
		int _GetGridItemTop(int row_index);
		int _GetGridItemLeft(int col_index);

		/*
		* @brief ����༭��ѡ��״̬;
		*/
		UiRect _GetGridItemPos(int row_index, int col_index);

		/*
		* @brief ����༭��ѡ��״̬;
		*/
		void _ClearModifyAndSel();
	protected:
		Grid *m_pGrid = nullptr;

		/* �����п� */
		GridLayout m_hLayout;

		/* �����и� */
		GridLayout m_vLayout;

		/* ��������Ϣ, ��һ��ΪHeader */
		std::vector<GridRow*> m_vecRow;

		/* �̶���/���� */
		unsigned int m_nFixedCol = 0;
		unsigned int m_nFixedRow = 0;

		/* ����ѡ����Ϣ */
		GridSelRange m_selRange;

		/* �϶���ͷ��� */
		//bool m_bDragColumn = false;
		int m_nDragColmun = -1;
		CPoint m_ptDragColumnStart;
		int m_nDrawDragColumnMovingOffX = 0;			// = m_nDragColmun���ұ߽� -  m_ptDragColumnMoving.x; Ϊ�˱�֤�϶��ߵ�λ��׼ȷ��
		CPoint m_ptDragColumnMoving;

		/* һЩ���� */
		int m_defaultRowHeight = 24;
		int m_defaultColWidth = 80;
		std::wstring m_strFixedBkColor = L"splitline_level2";
		std::wstring m_strSelForeColor = L"grid_sel_fore";
		std::wstring m_strGridLineColor = L"grid_line";
		std::wstring m_strGridFont = L"system_12";
		UINT	m_uTextStyle = DT_CENTER | DT_CENTER | DT_VCENTER | DT_SINGLELINE;
		
		/* �༭ʱ���RichEdit/Combo�ؼ� */
		RichEdit *m_pReEdit = nullptr;
		Combo *m_pComboEdit = nullptr;

		GridItem *m_pReEditGridItem = nullptr;
		GridItem *m_pComboEditGridItem = nullptr;
	};
}