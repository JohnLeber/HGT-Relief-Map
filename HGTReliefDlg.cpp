
// HGTReliefDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
 
#include "HGTRelief.h"
#include "HGTReliefDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
//--------------------------------------------------------------------------------//
const long HGTRes = 3601;
const long BMPRes = 1200;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHGTReliefDlg dialog
//---------------------------------------------------------------------------------------//
CHGTReliefDlg::CHGTReliefDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HGTRELIEF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCurrentColorIndex = 0;
	m_bSupressEditEvents = false;
	m_selectedRadioButton = -1;
	m_pBMP = 0;
}
//---------------------------------------------------------------------------------------//
CHGTReliefDlg::~CHGTReliefDlg()
{
	if (m_pBMP)
	{
		delete[] m_pBMP;
		m_pBMP = 0;
	}
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR1, m_Color1);
}
//---------------------------------------------------------------------------------------//
BEGIN_MESSAGE_MAP(CHGTReliefDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE_MAP, &CHGTReliefDlg::OnBnClickedCreateMap)
	ON_BN_CLICKED(IDC_COLOR1, OnColorPalette)
	ON_BN_CLICKED(IDC_LEGEND_1, &CHGTReliefDlg::OnBnClickedLegend1)
	ON_BN_CLICKED(IDC_LEGEND_2, &CHGTReliefDlg::OnBnClickedLegend2)
	ON_BN_CLICKED(IDC_LEGEND_3, &CHGTReliefDlg::OnBnClickedLegend3)
	ON_BN_CLICKED(IDC_LEGEND_4, &CHGTReliefDlg::OnBnClickedLegend4)
	ON_BN_CLICKED(IDC_LEGEND_5, &CHGTReliefDlg::OnBnClickedLegend5)
	ON_BN_CLICKED(IDC_LEGEND_6, &CHGTReliefDlg::OnBnClickedLegend6)
	ON_BN_CLICKED(IDC_LEGEND_7, &CHGTReliefDlg::OnBnClickedLegend7)
	ON_BN_CLICKED(IDC_LEGEND_8, &CHGTReliefDlg::OnBnClickedLegend8)
	ON_BN_CLICKED(IDC_LEGEND_9, &CHGTReliefDlg::OnBnClickedLegend9)
	ON_BN_CLICKED(IDC_LEGEND_10, &CHGTReliefDlg::OnBnClickedLegend10)
	ON_BN_CLICKED(IDC_LEGEND_11, &CHGTReliefDlg::OnBnClickedLegend11)
	ON_BN_CLICKED(IDC_LEGEND_12, &CHGTReliefDlg::OnBnClickedLegend12)
	ON_BN_CLICKED(IDC_LEGEND_13, &CHGTReliefDlg::OnBnClickedLegend13)
	ON_BN_CLICKED(IDC_LEGEND_14, &CHGTReliefDlg::OnBnClickedLegend14)
	ON_BN_CLICKED(IDC_LEGEND_15, &CHGTReliefDlg::OnBnClickedLegend15)
	ON_BN_CLICKED(IDC_RESET, &CHGTReliefDlg::OnBnClickedReset)
	ON_EN_CHANGE(IDC_RED, &CHGTReliefDlg::OnEnChangeRed)
	ON_EN_CHANGE(IDC_GREEN, &CHGTReliefDlg::OnEnChangeGreen)
	ON_EN_CHANGE(IDC_BLUE, &CHGTReliefDlg::OnEnChangeBlue)
	ON_EN_CHANGE(IDC_HIGHEST, &CHGTReliefDlg::OnEnChangeHighest)
	ON_EN_CHANGE(IDC_EDIT1, &CHGTReliefDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_CREATE_MAP2, &CHGTReliefDlg::OnBnClickedCreateMap2)
END_MESSAGE_MAP()

//---------------------------------------------------------------------------------------//
// CHGTReliefDlg message handlers
BOOL CHGTReliefDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Create system palette:
	CClientDC dc(this);
	int nColors = 256; // Use 256 first entries
	UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
	LOGPALETTE* pLP = (LOGPALETTE*) new BYTE[nSize];

	pLP->palVersion = 0x300;
	pLP->palNumEntries = (USHORT)nColors;

	::GetSystemPaletteEntries(dc.GetSafeHdc(), 0, nColors, pLP->palPalEntry);

	m_palSys.CreatePalette(pLP);
	//m_wndLum.SetType(CMFCColorPickerCtrl::LUMINANCE);

	m_Color1.SetType(CMFCColorPickerCtrl::PICKER);
	m_Color1.SetPalette(&m_palSys);
	// set the color, hue, luminance and saturation of the color picker control
	m_Color1.SetColor(RGB(0, 255, 0));
	m_Color1.SetHue(0.5);
	m_Color1.SetLuminance(2.5);
	//m_Color1.SetLuminanceBarWidth(10);
	m_Color1.SetSaturation(0.5);

	ResetLegend();
	m_bSupressEditEvents = true;
	CheckDlgButton(IDC_LEGEND_1, BST_CHECKED);
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	DrawColor(IDC_LEGEND_1 + m_nCurrentColorIndex, m_Legend.m_Color[m_nCurrentColorIndex]);

	SetDlgItemInt(IDC_RED, GetRValue(m_Legend.m_Color[m_nCurrentColorIndex]));
	SetDlgItemInt(IDC_GREEN, GetGValue(m_Legend.m_Color[m_nCurrentColorIndex]));
	SetDlgItemInt(IDC_BLUE, GetBValue(m_Legend.m_Color[m_nCurrentColorIndex]));
	m_bSupressEditEvents = false;

	SetDlgItemInt(IDC_HIGHEST, 2800);

	// TODO: Add extra initialization here
	m_LoadFileEdit.SubclassDlgItem(IDC_EDIT1, this);
	m_LoadFileEdit.EnableFileBrowseButton(NULL, _T("HGT Files (*.hgt)|*.hgt|All Files (*.*)|*.*||"));

	CheckDlgButton(IDC_JPEG, BST_CHECKED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
//---------------------------------------------------------------------------------------//
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHGTReliefDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	 

		CPaintDC dc(this); // device context for painting
				   // TODO: Add your message handler code here
				   // Do not call CDialog::OnPaint() for painting messages

		DrawColor(IDC_LEGEND_1, m_Legend.m_Color[0]);
		DrawColor(IDC_LEGEND_2, m_Legend.m_Color[1]);
		DrawColor(IDC_LEGEND_3, m_Legend.m_Color[2]);
		DrawColor(IDC_LEGEND_4, m_Legend.m_Color[3]);
		DrawColor(IDC_LEGEND_5, m_Legend.m_Color[4]);
		DrawColor(IDC_LEGEND_6, m_Legend.m_Color[5]);
		DrawColor(IDC_LEGEND_7, m_Legend.m_Color[6]);
		DrawColor(IDC_LEGEND_8, m_Legend.m_Color[7]);
		DrawColor(IDC_LEGEND_9, m_Legend.m_Color[8]);
		DrawColor(IDC_LEGEND_10, m_Legend.m_Color[9]);
		DrawColor(IDC_LEGEND_11, m_Legend.m_Color[10]);
		DrawColor(IDC_LEGEND_12, m_Legend.m_Color[11]);
		DrawColor(IDC_LEGEND_13, m_Legend.m_Color[12]);
		DrawColor(IDC_LEGEND_14, m_Legend.m_Color[13]);
		DrawColor(IDC_LEGEND_15, m_Legend.m_Color[14]);

		CDialogEx::OnPaint();
	}
}
//---------------------------------------------------------------------------------------//
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHGTReliefDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//---------------------------------------------------------------------------------------//
// CHGTReliefDlg message handlers
void CHGTReliefDlg::OnColorPalette()
{
	m_bSupressEditEvents = true;
	COLORREF color = m_Color1.GetColor();

	//m_strRGB.Format(_T("%d,%d,%d"), GetRValue(color), GetGValue(color), GetBValue(color));

	m_Legend.m_Color[m_nCurrentColorIndex] = color;
	DrawColor(IDC_LEGEND_1 + m_nCurrentColorIndex, color);
	SetDlgItemInt(IDC_RED, GetRValue(color));
	SetDlgItemInt(IDC_GREEN, GetGValue(color));
	SetDlgItemInt(IDC_BLUE, GetBValue(color));
	//UpdateData(FALSE);
	m_bSupressEditEvents = false;
}
//---------------------------------------------------------------------------------------//
bool CHGTReliefDlg::RadioSelectionChanged(long nID)
{
	if (IsDlgButtonChecked(IDC_LEGEND_1 + nID) != BST_CHECKED) return false;
	return true;
} 
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::CalcHeightLabels()
{
	long nHighest = 2800;
	if (nHighest < 100)
	{
		AfxMessageBox(L"Maximum altitude is too small");
		return;
	}
	nHighest = GetDlgItemInt(IDC_HIGHEST);
	for (int h = 1; h <= nNumLegendDiv; h++)
	{
		long nHeight = h * nHighest / nNumLegendDiv;
		CString str;
		str.Format(L"%d meters", nHeight);
		GetDlgItem(IDC_LEGEND_1 + h)->SetWindowText(str);
	}
	GetDlgItem(IDC_LEGEND_1)->SetWindowText(L"Water");
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::DrawColor(UINT nCtrlID, COLORREF color)
{
	CRect rtWnd;
	GetDlgItem(nCtrlID)->GetWindowRect(rtWnd);
	ScreenToClient(rtWnd);
	long nWidth = rtWnd.Width();
	rtWnd.right = rtWnd.left + 0.8 * nWidth;//make a little narrower
	rtWnd.OffsetRect(nWidth + 4, 0);
	CClientDC dc(this);
	dc.FillSolidRect(rtWnd, color);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::UpdateEditBoxes(COLORREF color)
{
	m_bSupressEditEvents = true;
	SetDlgItemInt(IDC_RED, GetRValue(m_Legend.m_Color[m_nCurrentColorIndex]));
	SetDlgItemInt(IDC_GREEN, GetGValue(m_Legend.m_Color[m_nCurrentColorIndex]));
	SetDlgItemInt(IDC_BLUE, GetBValue(m_Legend.m_Color[m_nCurrentColorIndex]));
	m_bSupressEditEvents = false;
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend1()
{
	if (!RadioSelectionChanged(0)) return;
	m_nCurrentColorIndex = 0;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend2()
{
	if (!RadioSelectionChanged(1)) return;
	m_nCurrentColorIndex = 1;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend3()
{
	if (!RadioSelectionChanged(2)) return;
	m_nCurrentColorIndex = 2;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend4()
{
	if (!RadioSelectionChanged(3)) return;
	m_nCurrentColorIndex = 3;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend5()
{
	if (!RadioSelectionChanged(4)) return;
	m_nCurrentColorIndex = 4;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend6()
{
	if (!RadioSelectionChanged(5)) return;
	m_nCurrentColorIndex = 5;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend7()
{
	if (!RadioSelectionChanged(6)) return;
	m_nCurrentColorIndex = 6;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend8()
{
	if (!RadioSelectionChanged(7)) return;
	m_nCurrentColorIndex = 7;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend9()
{
	if (!RadioSelectionChanged(8)) return;
	m_nCurrentColorIndex = 8;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend10()
{
	if (!RadioSelectionChanged(9)) return;
	m_nCurrentColorIndex = 9;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend11()
{
	if (!RadioSelectionChanged(10)) return;
	m_nCurrentColorIndex = 10;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend12()
{
	if (!RadioSelectionChanged(11)) return;
	m_nCurrentColorIndex = 11;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend13()
{
	if (!RadioSelectionChanged(12)) return;
	m_nCurrentColorIndex = 12;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend14()
{
	if (!RadioSelectionChanged(13)) return;
	m_nCurrentColorIndex = 13;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedLegend15()
{
	if (!RadioSelectionChanged(14))return;
	m_nCurrentColorIndex = 14;
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::ResetLegend()
{
	m_Legend.Reset();
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedReset()
{
	ResetLegend();
	InvalidateRect(0);
	m_Color1.SetColor(m_Legend.m_Color[m_nCurrentColorIndex]);
	UpdateEditBoxes(m_Legend.m_Color[m_nCurrentColorIndex]);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnEnChangeRed()
{
	UpdateColorFromEditBoxes();
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnEnChangeGreen()
{
	UpdateColorFromEditBoxes();
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnEnChangeBlue()
{
	UpdateColorFromEditBoxes();
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::UpdateColorFromEditBoxes()
{
	if (m_bSupressEditEvents) return;

	long nRed = GetDlgItemInt(IDC_RED);
	long nGreen = GetDlgItemInt(IDC_GREEN);
	long nBlue = GetDlgItemInt(IDC_BLUE);

	m_bSupressEditEvents = true;
	if (nRed > 255) {
		nRed = 255;
		SetDlgItemInt(IDC_RED, nRed);
	}
	if (nGreen > 255) {
		nGreen = 255;
		SetDlgItemInt(IDC_GREEN, nGreen);
	}
	if (nBlue > 255) {
		nBlue = 255;
		SetDlgItemInt(IDC_BLUE, nBlue);
	}
	m_bSupressEditEvents = false;

	COLORREF color = RGB(nRed, nGreen, nBlue);
	m_Legend.m_Color[m_nCurrentColorIndex] = color;
	m_Color1.SetColor(color);
	DrawColor(IDC_LEGEND_1 + m_nCurrentColorIndex, m_Legend.m_Color[m_nCurrentColorIndex]);

}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnEnChangeHighest()
{
	CalcHeightLabels();
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnEnChangeEdit1()
{

}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedCreateMap()
{
	CreateMap(true);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::CreateMap(bool bRelief)
{
	CWaitCursor wait;
	CString strPath;//e.g. L"D:\\HGT2\\S44E170.hgt"
	GetDlgItemText(IDC_EDIT1, strPath);
	strPath.MakeLower();

	if (IsDlgButtonChecked(IDC_ALL_FILES) == BST_UNCHECKED)
	{
		CreateMapImpl(strPath, bRelief);
	}
	else
	{ 
		//Option to scan all HGT files in the selected folder rather than just one file at a time
		if (strPath.Right(4) == L".hgt")
		{
			int nRight = strPath.ReverseFind(L'\\');
			strPath = strPath.Left(nRight);
		}

		CFileFind finder;
		CString strWildcard = strPath;
		strWildcard += _T("\\*.hgt");
		long nImageIndex = 0;
		bool bNext = false;
		BOOL bWorking = finder.FindFile(strWildcard);
		CString strImageFilePrev;
		long nFileCount = 0;
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			// skip . and .. files; otherwise, we'd recur infinitely! 
			if (finder.IsDots())
				continue;

			// if it's a directory, recursively search it 
			if (finder.IsDirectory())
			{
				continue;
			}
			CString strFile = finder.GetFilePath();
			CreateMapImpl(strFile, bRelief);
			nFileCount++;
		}
		finder.Close();
	}
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::OnBnClickedCreateMap2()
{
	CreateMap(false);
}
//---------------------------------------------------------------------------------------//
void CHGTReliefDlg::CreateMapImpl(CString strPath, bool bRelief)
{ 
	if (strPath.Right(4) == L".hgt")
	{
		CString strOutputBMP = strPath;//L"D:\\HGT2\\_Output\\ReliefMap.bmp"
		CString strOutputJPG = strPath;
		strOutputBMP.Replace(L".hgt", L".bmp");
		strOutputJPG.Replace(L".hgt", L".jpg");
		CalcMapImage(strPath, strOutputBMP, bRelief);
		
		if (IsDlgButtonChecked(IDC_JPEG) == BST_CHECKED)
		{
			//comvert bmp to jpeg
			CImage image;
			if (image.Load(strOutputBMP) == S_OK)
			{ 
				std::vector<BYTE> buf;
				IStream* stream = NULL;
				HRESULT hr = CreateStreamOnHGlobal(0, TRUE, &stream);
				image.Save(stream, Gdiplus::ImageFormatJPEG);
				ULARGE_INTEGER liSize;
				IStream_Size(stream, &liSize);
				DWORD len = liSize.LowPart;
				IStream_Reset(stream);
				buf.resize(len);
				IStream_Read(stream, &buf[0], len);
				stream->Release();

				// just testing if the buf contains the correct data
				std::fstream fi;
				fi.open(strOutputJPG, std::fstream::binary | std::fstream::out);
				fi.write(reinterpret_cast<const char*>(&buf[0]), buf.size() * sizeof(BYTE));
				fi.close();
			}
		}
	}
	else
	{
		AfxMessageBox(L"Please make sure a .hgt file is selected");
	}
}
//---------------------------------------------------------------------------------------//
bool CHGTReliefDlg::LoadHGT(CString strPath, CHGT& hgt)
{
	bool bResult = false;
	CFile f;
	if (f.Open(strPath, CFile::modeRead))
	{
		ULONGLONG nFileSize = f.GetLength();
		if (nFileSize == 25934402)//2601 * 3601 * 2 ( height stored as two bytes - 16 bits)
		{
			bResult = true;
			//hgt.Height.reserve(36HGTRes01);
			hgt.Height.resize(HGTRes);
			for (int h = 0; h < HGTRes; h++)
			{
				hgt.Height[h].resize(HGTRes);
				UINT nNumRead = f.Read(&(hgt.Height[h][0]), HGTRes * 2);
				long ert = 0;
			}
		}
		else
		{
			//wring size (only take 1 arc sec for now...)
			AfxMessageBox(L"Expecting file size to be 25934402 bytes. Only 1 arc second HGT files are supported.");
			return false;
		}
		//flip the byte order around for each word to get the height
		for (int h = 0; h < HGTRes; h++)
		{
			for (int j = 0; j < HGTRes; j++)
			{
				WORD w = hgt.Height[h][j];
				hgt.Height[h][j] = MAKEWORD(HIBYTE(w), LOBYTE(w));
			}
		}
		f.Close();
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------//
void CHGTReliefDlg::CalcMapImage(CString strInput, CString strOutput, bool bReliefMap)
{
	if (!LoadHGT(strInput, m_HGT))
	{
		AfxMessageBox(L"Failed to load HGT file");
		return;
	}
	else
	{
		if (m_pBMP)
		{
			delete[] m_pBMP;
			m_pBMP = 0;
		}
		m_pBMP = new BYTE[BMPRes * BMPRes * 3];
		std::map<long, COLORREF> ColorMap;
		ColorMap[0] = m_Legend.m_Color[0];//water

		//find highest point and scale legend
		long nHighestHGT = 0;
		for (int h = 0; h < HGTRes; h++)
		{
			for (int j = 0; j < HGTRes; j++)
			{
				if (nHighestHGT < m_HGT.Height[h][j])
				{
					nHighestHGT = m_HGT.Height[h][j];
				}
			}
		}

		//calculate the color map from the legend data for each elevation point used in the HGT file
		m_Legend.m_nMaxHeight = nHighestHGT + 0;
		for (int h = 1; h < nHighestHGT; h++)
		{
			long nPrevHeight = 0;
			float nHeightDiv = (float)m_Legend.m_nMaxHeight / (float)nNumLegendDiv;
			for (int j = 1; j <= nNumLegendDiv; j++)
			{
				long nHeight = j * m_Legend.m_nMaxHeight / nNumLegendDiv;
				if (h >= nPrevHeight && h < j * m_Legend.m_nMaxHeight / nNumLegendDiv)
				{
					ColorMap[h] = m_Legend.m_Color[j];
					if (j < nNumLegendDiv)
					{
						ColorMap[h] = mixColors(m_Legend.m_Color[j], m_Legend.m_Color[j + 1], (h - nPrevHeight) / nHeightDiv);
					}
					break;
				}
				nPrevHeight = nHeight;
			}
		}

		std::vector<std::vector<WORD>> Height;
		for (int h = 0; h < BMPRes + 1; h++)
		{
			Height.resize(BMPRes + 1);
			for (int j = 0; j < BMPRes + 1; j++)
			{
				Height[h].resize(1201);
				WORD w = m_HGT.Height[h * 3][j * 3];
				Height[h][j] = w;
			}
		}

		for (int h = 0; h < BMPRes; h++)
		{
			for (int j = 0; j < BMPRes; j++)
			{
				WORD w = Height[h][j];
				//get normals of the two triangles of the current quad and average them
				Vector3 v3a = GetNormal(h, j, Height[h][j], h + 1, j, Height[h + 1][j], h, j + 1, Height[h][j + 1]);
				Vector3 v3b = GetNormal(h + 1, j, Height[h + 1][j], h + 1, j + 1, Height[h + 1][j + 1], h, j + 1, Height[h][j + 1]);
				Vector3 vNormal = (v3a + v3b) / 2;
				vNormal = vNormal.normalize();

				Vector3 vLight(1, -1, 1);
				vLight = vLight.normalize();

				float dot = vNormal.dot(vLight);
				float nAngle = acos(dot);
				dot = cos(nAngle);

				float nD = 0.25;
				float nMix = nD + (1 - nD) * abs(dot);//ratio of unshaded and shaded
				COLORREF clr = ColorMap[w];
				if (bReliefMap)
				{
					m_pBMP[(BMPRes - h - 1) * BMPRes * 3 + j * 3 + 0] = GetBValue(clr) * (nMix + (1 - nMix) * dot);
					m_pBMP[(BMPRes - h - 1) * BMPRes * 3 + j * 3 + 1] = GetGValue(clr) * (nMix + (1 - nMix) * dot);
					m_pBMP[(BMPRes - h - 1) * BMPRes * 3 + j * 3 + 2] = GetRValue(clr) * (nMix + (1 - nMix) * dot);
				}
				else
				{
					//save normal map in tangent mode format
					m_pBMP[(BMPRes - h - 1) * BMPRes * 3 + j * 3 + 0] = 255 * (0.5 + 0.5 * vNormal.z);
					m_pBMP[(BMPRes - h - 1) * BMPRes * 3 + j * 3 + 1] = 255 * (0.5 + 0.5 * -1 * vNormal.y);//invert green axis
					m_pBMP[(BMPRes - h - 1) * BMPRes * 3 + j * 3 + 2] = 255 * (0.5 + 0.5 * vNormal.x);
				}
			}
		}
		SaveBitmapRGB(m_pBMP, BMPRes, BMPRes, BMPRes * BMPRes * 3, strOutput);
	}
}
//--------------------------------------------------------------------------------//
Vector3 CHGTReliefDlg::GetNormal(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z)
{
	float nMinIgnore = 0;
	p1x = p1x * 90;
	p1y = p1y * 90;
	p2x = p2x * 90;
	p2y = p2y * 90;
	p3x = p3x * 90;
	p3y = p3y * 90;
	if (abs(p1z - p2z) < nMinIgnore || abs(p2z - p3z) < nMinIgnore)
	{
		p2z = p1z;
		p3z = p1z;
	}
	float Ax = p2x - p1x;
	float Ay = p2y - p1y;
	float Az = p2z - p1z;
	float Bx = p3x - p1x;
	float By = p3y - p1y;
	float Bz = p3z - p1z;
	float Nx = Ay * Bz - Az * By;
	float Ny = Az * Bx - Ax * Bz;
	float Nz = Ax * By - Ay * Bx;

	Vector3 v3(Nx, Ny, Nz);
	v3 = v3.normalize();
	return v3;
}
//--------------------------------------------------------------------------------//
int CHGTReliefDlg::mixColors(int a, int b, float ratio)
{
	int mask1 = 0xff00ff;
	int mask2 = 0x00ff00;

	int f2 = (int)(256 * ratio);
	int f1 = 256 - f2;

	return (((((a & mask1) * f1) + ((b & mask1) * f2)) >> 8) & mask1)
		| (((((a & mask2) * f1) + ((b & mask2) * f2)) >> 8) & mask2);
}
//--------------------------------------------------------------------------------//
bool CHGTReliefDlg::SaveBitmapRGB(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile)
{
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER info;
	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&info, 0, sizeof(BITMAPINFOHEADER));

	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paddedsize;
	bmfh.bfOffBits = 0x36;

	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;
	info.biBitCount = 24;
	info.biCompression = BI_RGB;
	info.biSizeImage = 0;
	info.biXPelsPerMeter = 0x0ec4;
	info.biYPelsPerMeter = 0x0ec4;
	info.biClrUsed = 0;
	info.biClrImportant = 0;
	HANDLE file = CreateFile(bmpfile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (NULL == file)
	{
		CloseHandle(file);
		return false;
	}

	unsigned long bwritten;
	if (WriteFile(file, &bmfh, sizeof(BITMAPFILEHEADER),
		&bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}

	if (WriteFile(file, &info, sizeof(BITMAPINFOHEADER),
		&bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}

	if (WriteFile(file, Buffer, paddedsize, &bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}

	CloseHandle(file);
	return true;
}
//---------------------------------------------------------------------------------------//
