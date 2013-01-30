#pragma once


// CParamDlg dialog

class CParamDlg : public CDialog
{
	DECLARE_DYNAMIC(CParamDlg)

public:
	CParamDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CParamDlg();
	virtual BOOL OnInitDialog();


	int nElement;
	int finterval;
	int totaltimesteps;
	int navg;
	int isdatanumberofmolecule;

	float graph_base;
	float graph_max;
	float useravgmax;



// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangenelement();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnEnChangegraphmax();
};
