#pragma once
const long nNumLegendDiv = 14;
// COptionsDlg dialog

struct CLegend
{
	CLegend()
	{
		m_nMaxHeight = 2800;
		Reset();
	}
	COLORREF m_Color[nNumLegendDiv + 1];//0 is water
	long m_nMaxHeight;

	void Reset()
	{
		m_Color[0] = RGB(60, 80, 100);//water 
		m_Color[1] = RGB(140, 146, 112);
		m_Color[2] = RGB(160, 160, 118);
		m_Color[3] = RGB(178, 172, 120);
		m_Color[4] = RGB(196, 186, 128);
		m_Color[5] = RGB(216, 200, 135);
		m_Color[6] = RGB(208, 190, 128);
		m_Color[7] = RGB(202, 180, 120);
		m_Color[8] = RGB(196, 170, 114);
		m_Color[9] = RGB(190, 160, 108);
		m_Color[10] = RGB(184, 150, 100);
		m_Color[11] = RGB(180, 154, 112);
		m_Color[12] = RGB(176, 158, 126);
		m_Color[13] = RGB(170, 162, 138);
		m_Color[14] = RGB(168, 168, 150);
	}
};  
