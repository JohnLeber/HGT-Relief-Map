
// HGTReliefDlg.h : header file
//

#pragma once
#include "Legend.h"

#include "vector.h"//https://github.com/pelletier/vector3

struct CHGT
{
	std::vector< std::vector<WORD> > Height;
};

// CHGTReliefDlg dialog
class CHGTReliefDlg : public CDialogEx
{
// Construction
public:
	CHGTReliefDlg(CWnd* pParent = nullptr);	// standard constructor
	~CHGTReliefDlg();
	CMFCEditBrowseCtrl m_LoadFileEdit;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HGTRELIEF_DIALOG };
#endif
	CLegend m_Legend;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	CMFCColorPickerCtrl m_Color1;
	CPalette m_palSys;
	long m_nCurrentColorIndex;
	long m_bSupressEditEvents;
	void CalcHeightLabels();
	void UpdateEditBoxes(COLORREF color);
	void UpdateColorFromEditBoxes();
	void DrawColor(UINT nCtrlID, COLORREF clr);
	long m_selectedRadioButton;
	bool RadioSelectionChanged(long m_nCurrentColorIndex);
	void CreateMapImpl(CString strPath, bool bRelief);
	void CreateMap( bool bRelief);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	void ResetLegend();


	void OnColorPalette();
	afx_msg void OnBnClickedLegend1();
	afx_msg void OnBnClickedLegend2();
	afx_msg void OnBnClickedLegend3();
	afx_msg void OnBnClickedLegend4();
	afx_msg void OnBnClickedLegend5();
	afx_msg void OnBnClickedLegend6();
	afx_msg void OnBnClickedLegend7();
	afx_msg void OnBnClickedLegend8();
	afx_msg void OnBnClickedLegend9();
	afx_msg void OnBnClickedLegend10();
	afx_msg void OnBnClickedLegend11();
	afx_msg void OnBnClickedLegend12();
	afx_msg void OnBnClickedLegend13();
	afx_msg void OnBnClickedLegend14();
	afx_msg void OnBnClickedLegend15();
	afx_msg void OnBnClickedReset();
	afx_msg void OnEnChangeRed();
	afx_msg void OnEnChangeGreen();
	afx_msg void OnEnChangeBlue();
	afx_msg void OnEnChangeHighest();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	CHGT m_HGT;
	void DrawDEM(CHGT& hgt);
	bool LoadHGT(CString strPath, CHGT& hgt);
	bool SaveBitmapRGB(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile);
	int mixColors(int a, int b, float ratio);
	Vector3 GetNormal(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z);
	BYTE* m_pBMP;

	void CalcMapImage(CString strInput, CString strOutput, bool bReliefMap);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreateMap();

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCreateMap2();
};
