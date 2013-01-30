// ParamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCGL.h"
#include "ParamDlg.h"


// CParamDlg dialog

IMPLEMENT_DYNAMIC(CParamDlg, CDialog)

CParamDlg::CParamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParamDlg::IDD, pParent)
{

		
//	nElement = 1362;
//	totaltimesteps = 1000;
//	finterval = 100; //ms
//	navg = 3;



}

CParamDlg::~CParamDlg()
{


}

void CParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CParamDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CParamDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_nElement, &CParamDlg::OnEnChangenelement)
	ON_WM_CREATE()
	ON_WM_INITMENU()
	ON_EN_CHANGE(IDC_graph_max, &CParamDlg::OnEnChangegraphmax)
END_MESSAGE_MAP()


// CParamDlg message handlers

void CParamDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

//	nElement = 1362;
//	totaltimesteps = 1000;
//	finterval = 100; //ms
//	navg = 3;


	nElement = GetDlgItemInt(IDC_nElement);
	totaltimesteps = GetDlgItemInt(IDC_totaltimesteps);
    finterval = GetDlgItemInt(IDC_finterval);
	navg = GetDlgItemInt(IDC_navg);
	isdatanumberofmolecule = GetDlgItemInt(IDC_ISDATANUMBEROFMOLECULE);

	CString sTmp;

	GetDlgItemText(IDC_graph_base,sTmp);
	graph_base = atof(sTmp);
	sTmp.Empty();

	GetDlgItemText(IDC_graph_max,sTmp);
	graph_max = atof(sTmp);
	sTmp.Empty();

	GetDlgItemText(IDC_graph_avgmax,sTmp);
	useravgmax = atof(sTmp);
	sTmp.Empty();

// UINT WINAPI GetDlgItemText(
//  __in   HWND hDlg,
//  __in   int nIDDlgItem,
//  __out  LPTSTR lpString, string that recives text
//  __in   int nMaxCount
//);

	//if (isdatanumberofmolecule == 0) Edata[nmultimap][jj].data[ii]=  atof(tmpnum); //float for concentration
	//if (isdatanumberofmolecule == 1) Edata[nmultimap][jj].data[ii]=  (double)atoi(tmpnum); //integer for concentration

//
	OnOK();
}

void CParamDlg::OnEnChangenelement()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

int CParamDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	// TODO:  Add your specialized creation code here

	return 0;
}


void CParamDlg::OnInitMenu(CMenu* pMenu)
{
	CDialog::OnInitMenu(pMenu);



	// TODO: Add your message handler code here
}

BOOL CParamDlg::OnInitDialog() 
{
   CDialog::OnInitDialog();

   //CString sTmp;
   //sTmp.Format("%.2f",fMyVal);
   //SetDlgItemText ( ...., sTmp);

//BOOL WINAPI SetDlgItemText(
//  __in  HWND hDlg,
//  __in  int nIDDlgItem,
//  __in  LPCTSTR lpString
//);




   	SetDlgItemInt(IDC_nElement,nElement);
	SetDlgItemInt(IDC_totaltimesteps,totaltimesteps);
	SetDlgItemInt(IDC_finterval,finterval);
	SetDlgItemInt(IDC_navg,navg);
	SetDlgItemInt(IDC_ISDATANUMBEROFMOLECULE,isdatanumberofmolecule);

	CString sTmp;

	sTmp.Format("%.2f",graph_base);
	SetDlgItemText(IDC_graph_base,sTmp);
	sTmp.Empty();
	
	sTmp.Format("%.2f",graph_max);
	SetDlgItemText(IDC_graph_max,sTmp);
	sTmp.Empty();

	sTmp.Format("%.2f",useravgmax);
	SetDlgItemText(IDC_graph_avgmax,sTmp);
	sTmp.Empty();

	

   return TRUE;   // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CParamDlg::OnEnChangegraphmax()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
