// MFCGLView.h : interface of the CMFCGLView class
//


#pragma once


class CMFCGLView : public CView
{
protected: // create from serialization only
	CMFCGLView();
	DECLARE_DYNCREATE(CMFCGLView)

// Attributes
public:
	CMFCGLDoc* GetDocument() const;

	CStdioFile m_rfile; //Read file
	CStdioFile m_wfile; //Read file

	//Input dialog

	 char bufferzoom[20];
	 char buffer[20];
	 

	int max;
	int nRotate;
	int iCPU;
	int isRun;
	int navg;
	int isdatanumberofmolecule;

	int ncord;
	
	int nwhitegray;

	float m_xTranslate;
	float m_yTranslate;
	float m_zTranslate;

	double avgnormal;
	double avgnormalcount;
	double numberdatainfo;
		
	float m_xRotate;
	float m_yRotate;
	float m_zRotate;
	float xvar,yvar;
	float selx1,sely1;
	float selx2,sely2;
	float glcrossx,glcrossy;
	float relx,rely;



	

	float selxMax,selyMax;
	float selxMin,selyMin;


	float mofx;
	float mofy;
	float offsetx[2];
	float offsety[2];
	float fmax[3];
	float fmin[3];

	float graph_base;
	float graph_max;

	float spatialmax;


	int islocatedomain;
	int issetorigin;
	int oclickcount;

	float meshzoom;

	float psizex;
	float psizey;

	float finterval;

	int nmultimap;

	int isselon;
	int isgraphx,isgraphy;
	int nSelected;

	int nElement;
	int nEstart;
	int colorcount;

	int ndom;
	double avgmax;
	double useravgmax;
	


	double ewidth,eheight,edepth,ecenterx,ecentery,ecenterz;
	float selcolor;

	float cnormal,cred,cgreen,cblue;
	float redscale,yellowscale;
	

	clock_t start, finish;

	struct Element_Struct            // Declare PERSON struct type
	{
	int n;
	int Issel;
	double   x[4];              // Declare member types
	double   y[4];              // Declare member types
	double   z[4];              // Declare member types
	double   cx;              // Declare member types
	double   cy;              // Declare member types
	double   volume;              // Declare member types
	double   deltaZ;              // Declare member types
	};      

	Element_Struct Element[200]; //element[element number]

	//2000 ele and   25000 step maximum
	//adjusting 1500 ele and 10000 step maximum
	//adjusting 200 ele and 70000 step maximum
	
	


	struct Element_Data            //nElement+1 since 1st column is timesteps
	{
	double   data[200];              // Declare member types [elementnumber] <- data in
	//CString  strdata[2000];             // 
	};      

	Element_Data Edata[3][70000]; //[multiple_map][timestep]

	double   avgdata[70000];              // Declare member types [elementnumber] <- data in

	struct xyout_Data            //nElement+1 since 1st column is timesteps
	{
	double   cord;              // Declare member types [elementnumber] <- data in
	double	 datasum;
	double	 numberadd;
	double	 volumesum;
	};      

	xyout_Data xyout[200];

	//int nSelected;
	int selectmap[200]; //[selected numbering 0~nSelected] <- element number
	int selmaptocord[200];


	CString strinfo[200];

	// upto 2000 elements and 20,000 timesteps



	int meshmode;
	int viewmode;
	int timestep;
	int totaltimesteps;
	int graphavgmode;


// Operations
public:

	CDC* m_pDC;   // 디바이스 컨텍스트(DC)
	HGLRC m_hRC;  // 렌더링 컨텍스트(RC)
//	HDC m_hDC;

	BOOL SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD=0);
	GLuint base;
	GLvoid BuildFont(GLvoid);
	int InitGL(GLvoid);
	GLvoid glPrint(const char *text);
	GLvoid KillFont(GLvoid);



// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


// Implementation
public:
	virtual ~CMFCGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnSize(UINT nType, int cx, int cy);
	void GLResize(int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void GLRenderScene(void);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OMPTest(void);
	afx_msg void OnAutoRun();
	afx_msg void OnAutoStop();
	afx_msg void OnAutoSinglecpu();
	afx_msg void OnAutoAddcpu();
	afx_msg void OnAutoMaxcpu();
	afx_msg void OnAutoRemovecpu();
	afx_msg void OnUpdateCpuSingle(CCmdUI *pCmdUI);
	afx_msg void OnCpuSingle();
	afx_msg void OnUpdateCpuDual(CCmdUI *pCmdUI);
	afx_msg void OnCpuDual();
	afx_msg void OnCpuQuad();
	afx_msg void OnUpdateCpuQuad(CCmdUI *pCmdUI);
	afx_msg void OnCpuI7();
	afx_msg void OnUpdateCpuI7(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAutoRun(CCmdUI *pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnAdddataAdddata();
	afx_msg void OnSelData();
	afx_msg void OnSelInitialize();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSelRotate();
	afx_msg void OnGraphX();
	afx_msg void OnGraphY();
	afx_msg void OnSetOrigin();
	void sortintoxdirection(void);
	void sortintoydirection(void);
	afx_msg void OnDialogboxParameters();
//	afx_msg void OnAutoRunsinglestep();
	afx_msg void OnAutoFastforward();
	afx_msg void OnAutoRewind();
	afx_msg void OnAutoRunsinglestep();
	afx_msg void OnAutoPause();
	afx_msg void OnFileNew();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void setcolorscale(void);
	afx_msg void OnGraphXSave();
	afx_msg void OnGraphYSave();
	afx_msg void OnPlotWhitegray();
	afx_msg void OnPlotDecreaseredgradient();
	afx_msg void OnPlotDecreaseyellowgradient();
	afx_msg void OnPlotIncreaseredgradient();
	afx_msg void OnPlotIncreaseyellowgradient();
	afx_msg void OnPlotTranslatex();
	afx_msg void OnPlotTranslatey();
	afx_msg void OnPlotGraphAvg();
	afx_msg void OnAutoBacksinglestep();
	afx_msg void OnPlotZoomin();
	afx_msg void OnPlotZoomout();
	afx_msg void OnPlotTranslatedowny();
	afx_msg void OnPlotTranslateleftx();
};

#ifndef _DEBUG  // debug version in MFCGLView.cpp
inline CMFCGLDoc* CMFCGLView::GetDocument() const
   { return reinterpret_cast<CMFCGLDoc*>(m_pDocument); }
#endif

