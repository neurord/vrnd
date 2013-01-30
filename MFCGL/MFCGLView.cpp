// MFCGLView.cpp : implementation of the CMFCGLView class
//

#include "afx.h"
#include "stdafx.h"
#include "MFCGL.h"
#include <stdlib.h>
#include <stdio.h>
#include "ParamDlg.h"
//#include <tchar.h>


#include "MFCGLDoc.h"
#include "MFCGLView.h"
//#include <omp.h> 
#include <ctime>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCGLView

IMPLEMENT_DYNCREATE(CMFCGLView, CView)

BEGIN_MESSAGE_MAP(CMFCGLView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_AUTO_RUN, &CMFCGLView::OnAutoRun)
	ON_COMMAND(ID_AUTO_STOP, &CMFCGLView::OnAutoStop)
	ON_COMMAND(ID_AUTO_SINGLECPU, &CMFCGLView::OnAutoSinglecpu)
	ON_COMMAND(ID_AUTO_ADDCPU, &CMFCGLView::OnAutoAddcpu)
	ON_COMMAND(ID_AUTO_MAXCPU, &CMFCGLView::OnAutoMaxcpu)
	ON_COMMAND(ID_AUTO_REMOVECPU, &CMFCGLView::OnAutoRemovecpu)
	ON_UPDATE_COMMAND_UI(ID_CPU_SINGLE, &CMFCGLView::OnUpdateCpuSingle)
	ON_COMMAND(ID_CPU_SINGLE, &CMFCGLView::OnCpuSingle)
	ON_UPDATE_COMMAND_UI(ID_CPU_DUAL, &CMFCGLView::OnUpdateCpuDual)
	ON_COMMAND(ID_CPU_DUAL, &CMFCGLView::OnCpuDual)
	ON_COMMAND(ID_CPU_QUAD, &CMFCGLView::OnCpuQuad)
	ON_UPDATE_COMMAND_UI(ID_CPU_QUAD, &CMFCGLView::OnUpdateCpuQuad)
	ON_COMMAND(ID_CPU_I7, &CMFCGLView::OnCpuI7)
	ON_UPDATE_COMMAND_UI(ID_CPU_I7, &CMFCGLView::OnUpdateCpuI7)
	ON_UPDATE_COMMAND_UI(ID_AUTO_RUN, &CMFCGLView::OnUpdateAutoRun)
	ON_COMMAND(ID_FILE_OPEN, &CMFCGLView::OnFileOpen)
	ON_COMMAND(ID_ADDDATA_ADDDATA, &CMFCGLView::OnAdddataAdddata)
	ON_COMMAND(ID_SEL_DATA, &CMFCGLView::OnSelData)
	ON_COMMAND(ID_SEL_INITIALIZE, &CMFCGLView::OnSelInitialize)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_SEL_ROTATE, &CMFCGLView::OnSelRotate)
	ON_COMMAND(ID_GRAPH_X, &CMFCGLView::OnGraphX)
	ON_COMMAND(ID_GRAPH_Y, &CMFCGLView::OnGraphY)
	ON_COMMAND(ID_SET_ORIGIN, &CMFCGLView::OnSetOrigin)
	ON_COMMAND(ID_DIALOGBOX_PARAMETERS, &CMFCGLView::OnDialogboxParameters)
//	ON_COMMAND(ID_AUTO_RUNSINGLESTEP, &CMFCGLView::OnAutoRunsinglestep)
	ON_COMMAND(ID_AUTO_FASTFORWARD, &CMFCGLView::OnAutoFastforward)
	ON_COMMAND(ID_AUTO_REWIND, &CMFCGLView::OnAutoRewind)
	ON_COMMAND(ID_AUTO_RUNSINGLESTEP, &CMFCGLView::OnAutoRunsinglestep)
	ON_COMMAND(ID_AUTO_PAUSE, &CMFCGLView::OnAutoPause)
	ON_COMMAND(ID_FILE_NEW, &CMFCGLView::OnFileNew)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_GRAPH_X_SAVE, &CMFCGLView::OnGraphXSave)
	ON_COMMAND(ID_GRAPH_Y_SAVE, &CMFCGLView::OnGraphYSave)
	ON_COMMAND(ID_PLOT_WHITEGRAY, &CMFCGLView::OnPlotWhitegray)
	ON_COMMAND(ID_PLOT_DECREASEREDGRADIENT, &CMFCGLView::OnPlotDecreaseredgradient)
	ON_COMMAND(ID_PLOT_DECREASEYELLOWGRADIENT, &CMFCGLView::OnPlotDecreaseyellowgradient)
	ON_COMMAND(ID_PLOT_INCREASEREDGRADIENT, &CMFCGLView::OnPlotIncreaseredgradient)
	ON_COMMAND(ID_PLOT_INCREASEYELLOWGRADIENT, &CMFCGLView::OnPlotIncreaseyellowgradient)
	ON_COMMAND(ID_PLOT_TRANSLATEX, &CMFCGLView::OnPlotTranslatex)
	ON_COMMAND(ID_PLOT_TRANSLATEY, &CMFCGLView::OnPlotTranslatey)
	ON_COMMAND(ID_PLOT_GRAPH_AVG, &CMFCGLView::OnPlotGraphAvg)
	ON_COMMAND(ID_AUTO_BACKSINGLESTEP, &CMFCGLView::OnAutoBacksinglestep)
	ON_COMMAND(ID_PLOT_ZOOMIN, &CMFCGLView::OnPlotZoomin)
	ON_COMMAND(ID_PLOT_ZOOMOUT, &CMFCGLView::OnPlotZoomout)
	ON_COMMAND(ID_PLOT_TRANSLATEDOWNY, &CMFCGLView::OnPlotTranslatedowny)
	ON_COMMAND(ID_PLOT_TRANSLATELEFTX, &CMFCGLView::OnPlotTranslateleftx)
END_MESSAGE_MAP()

// CMFCGLView construction/destruction

CMFCGLView::CMFCGLView()
{
	// TODO: add construction code here
	nRotate =0;  //0=fix, 1=Rotate,
	iCPU = 1;
	isRun=0;
	m_xTranslate = 0.0f;
	m_yTranslate = 0.0f;
	m_zTranslate = 0.0f;
	
	m_xRotate = 0.0f;
	m_yRotate = 0.0f;
	m_zRotate = 0.0f;

	xvar = 0;
	yvar = 0;

	start = 0;
	finish = 0;
	
	meshmode = 1;
	timestep = 0;
	
	//nElement = 24; // perkinje cell
	//totaltimesteps = 2000;
	//finterval = 50; //ms

	//nElement = 206; //rodrigo
	//totaltimesteps = 16;
	//finterval = 10000.0; //ms

	nElement = 0; //myung
	totaltimesteps = 0;
	finterval = 100; //ms
	//finterval = 1; //ms

	//nElement = 1362; // andrew
	//totaltimesteps = 1000;
	//finterval = 100; //ms
	//finterval = 1; //ms

	nEstart = 0;

	selx1 = 0.0f;
	sely1 = 0.0f;
	selx2 = 0.0f;
	sely1 = 0.0f;
	isselon = 0;

	isgraphx = 0;
	isgraphy = 0;

	mofx = 0.0f;
	mofy = 0.0f;

	offsetx[0] = 4.0f;
	offsety[0] = 2.0f;
	offsetx[1] = 8.0f;
	offsety[1] = 4.0f;

	graphavgmode = 0;		
	oclickcount = 0;

	islocatedomain = 0;;

	nmultimap = 0;
	ndom = 1;
	meshzoom = 1.0f;

	issetorigin = 0;

	nSelected = 0;

	ncord = 0;

	navg = 1;

	avgnormal = 0.0;
	avgnormalcount = 1.0;


	graph_base = 2.5f; 
	graph_max = 5.0f;

	
	redscale = 0.25f;
	yellowscale = 0.55f;

	nwhitegray = 0;


	relx = 0.0f;
	rely = 0.0f;

	spatialmax = -1.0;

	useravgmax = 0.0;

	isdatanumberofmolecule = 0; //  0 for concentration, 1 for number of molecules 

}

CMFCGLView::~CMFCGLView()
{
	KillFont();
}

BOOL CMFCGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

   //cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER;

   // Size the window to 1/3 screen size and center it
   cs.cy = ::GetSystemMetrics(SM_CYSCREEN) / 3;
   cs.cx = ::GetSystemMetrics(SM_CXSCREEN) / 3;

 //  cs.cy = 1350;
 //  cs.cx = 1560;

   cs.y = ((cs.cy * 3) - cs.cy) / 2;
   cs.x = ((cs.cx * 3) - cs.cx) / 2;


	return CView::PreCreateWindow(cs);
}

// CMFCGLView drawing

void CMFCGLView::OnDraw(CDC* /*pDC*/)
{
	CMFCGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//wglMakeCurrent(m_hDC, m_hRC);

	GLRenderScene();

	SwapBuffers(m_pDC->GetSafeHdc());


	//wglMakeCurrent(m_hDC, NULL);

	// TODO: add draw code for native data here
}


// CMFCGLView printing

BOOL CMFCGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCGLView diagnostics

#ifdef _DEBUG
void CMFCGLView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGLDoc* CMFCGLView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGLDoc)));
	return (CMFCGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCGLView message handlers

void CMFCGLView::OnSize(UINT nType, int cx, int cy)
{
//	cx = 2.0*cy;
	CView::OnSize(nType, cx, cy);

	GLdouble dAspect = (GLdouble) cx/ (GLdouble) cy;
	glMatrixMode(GL_PROJECTION);  // Projection Matrix Mode
	glLoadIdentity();             // Initilaze Matrix
	gluPerspective(60.0f, dAspect, 1.0, 40.0);   // Viewing volume //BHK VOLUME
	glViewport(0, 0, cx, cy);     // Set the size of viewport to entire domain

	// TODO: Add your message handler code here

	//VERIFY(wglMakeCurrent(m_hDC, m_hRC));
	
	//GLResize(cx,cy);

	//VERIFY(wglMakeCurrent(NULL, NULL));
	GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());



}

void CMFCGLView::GLResize(int cx, int cy) // No use
{

	GLfloat fAspect;

	if (cy == 0)
		cy = 1;

	glViewport(0,0,cx,cy); //, 모니터 전체 화면을 뷰포트 영역으로 잡아 준다

	fAspect = (GLfloat)cx / (GLfloat)cy;

	psizex = (GLfloat)cx;
	psizey = (GLfloat)cy;

	///here set the width// KBH!!!!!!!


	glMatrixMode(GL_PROJECTION); //원근 투영 임을 선언

	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 10000.0f); //관측 공간을 설정 해 준다
	//gluPerspective(60.0f, fAspect, 1.0f, 40.0f); //관측 공간을 설정 해 준다

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

int CMFCGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	m_pDC = new CClientDC(this); // Get device context
	
	if(NULL==m_pDC)
	{
		AfxMessageBox("Cannot get DC.\n");
		return FALSE;
	}
	
	if(!SetupPixelFormat())
	{  // Set up the fixel format
		::AfxMessageBox("SetupPixelFormat fail.\n");
		return FALSE;
	}

	// Get rendering context
	if(0==(m_hRC=wglCreateContext(m_pDC->GetSafeHdc())))
	{
		::AfxMessageBox("wglCreateContext fail.\n");
		return FALSE;
	}
	
	// make rendering context
	if(FALSE==wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC))
	{
		::AfxMessageBox("wglMakeCurrent fail.\n");
		return FALSE;
	}
	return 0;
}
// Set up the Pixel Format
BOOL CMFCGLView::SetupPixelFormat(PIXELFORMATDESCRIPTOR * pPFD)
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // PIXELFORMATDESCRIPTOR SIZE
		1,                              // Version
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL
		| PFD_DOUBLEBUFFER,             // support OpenGL
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ingored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ingored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

    int pixelformat;

	PIXELFORMATDESCRIPTOR* pPFDtoUse;


	// let the user override the default pixel format
	pPFDtoUse = (0 == pPFD)? &pfd : pPFD;

	if(0==(pixelformat=::ChoosePixelFormat(m_pDC->GetSafeHdc(), pPFDtoUse))) 
	{
		::AfxMessageBox("ChoosePixelFormat failed.");
		return FALSE;
	}
	
	if(FALSE==::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, pPFDtoUse)) 
	{
		::AfxMessageBox("SetPixelFormat failed.");
		return FALSE;
	}

	return TRUE;
}


GLvoid CMFCGLView::BuildFont(GLvoid)
{
    HFONT font;                           // <1>
    base = glGenLists(24);                // <2>
    font = CreateFont(-12,                // <3-1>  // fontsize
                        0,
                        0,
                        0,
                  FW_BOLD,                // <3-2>
                    FALSE,                // <3-3>
                    FALSE,                // <3-4>
                    FALSE,                // <3-5>
             ANSI_CHARSET,                // <3-6>
            OUT_TT_PRECIS,
      CLIP_DEFAULT_PRECIS,
      ANTIALIASED_QUALITY,
FF_DONTCARE|DEFAULT_PITCH,
                          "Courier New"); // <3-6>
   
    SelectObject(m_pDC->GetSafeHdc(), font);              // <4>
    wglUseFontBitmaps(m_pDC->GetSafeHdc(), 32, 96, base); // <5>
}
GLvoid CMFCGLView::KillFont(GLvoid)
{
    glDeleteLists(base, 96);
}

GLvoid CMFCGLView::glPrint(const char *text)
{
    glPushAttrib(GL_LIST_BIT);                         //<1>
    glListBase(base - 32);                             //<2>
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); //<3>
    glPopAttrib();                                     //<4>
}

int CMFCGLView::InitGL(GLvoid)
{
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   
    ///////////////////////// NEW //////////////////////////
    BuildFont();
    ///////////////////////// NEW //////////////////////////
   
    return TRUE;
}

void CMFCGLView::GLRenderScene(void)
{

	
	// LIGHT 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// DEPTH
	glEnable(GL_DEPTH_TEST);
	
	if (nwhitegray == 0) glClearColor(0.8f, 0.8f, 0.8f, 0.0);
	else glClearColor(1.0f, 1.0f, 1.0f, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// MATERIAL PROPERTY
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);

	// MATRIX MODE
	glMatrixMode(GL_MODELVIEW);

	//COORDINATE ROTATION
	glLoadIdentity();
 
	gluLookAt(0.0f, 0.0f, -4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);   //카메라 설정
	//카메라의 위치는 (0, 0, -1000) 에 있으며, 카메라가 바라보는 곳은 (0, 10, 0) 이다.
	//카메라의 Up Vector 는 (0, 1, 0) 이다.

	if (nRotate == 1)
	{
		m_zRotate+= 0.01f;
	
		m_xRotate+= 0.1f;
//		nElement = int(m_xRotate*0.5) ;
//		nEstart = nElement-1; 
		if (nElement == 255) nElement = 0;
	}

	if (m_yRotate >  420.0f)
	{

		nRotate =0;
//		nElement = 206;
//		nEstart = 0;
		OnSelInitialize();
	
	}

	glScalef(-1.0f, 1.0f, 1.0f); //Return origin


	glTranslatef(float(m_xTranslate),float(m_yTranslate),float(m_zTranslate));
	glRotatef(float(m_xRotate), 1.0, 0.0, 0.0);
	glRotatef(float(m_yRotate), 0.0, 1.0, 0.0);
    glRotatef(float(m_zRotate), 0.0, 0.0, 1.0);

/*
	glColor4f(1.0f, 0.0f, 0.0f,0.0f);
	glTranslatef(-0.5f, 0.25f, 0.0); //Target point
	auxSolidSphere(10.1f);         //Draw sphere
	glTranslatef(0.5f, -0.25f, 0.0);  //Return origin

	glColor4f(0.0f, 1.0f, 0.0f,0.0f);
	glTranslatef(-200.5-xvar, 0.25f, 0.0-xvar*2); //Target point
	auxSolidSphere(10.1f);         //Draw sphere
	glTranslatef(200.5+xvar, -0.25f, 0.0+xvar*2);  //Return origin

	glColor4f(0.0f, 0.0f, 1.0f,0.0f);
	glTranslatef(0.0f, 200.25f+yvar, 0.0+yvar*2); //Target point
	auxSolidSphere(10.1f);         //Draw sphere
	glTranslatef(0.0f, -200.25f-yvar, 0.0-yvar*2); //Return origin

	glColor4f(1.0f, 1.0f, 1.0f,0.0f); 
*/	
 //////////////////////////////DRAW HERE//////////////////////////////////////
/*	glBegin(GL_QUADS);
 		glVertex3f(-50,-50,0);
		glVertex3f(50,-50,0);
		glVertex3f(50,50,0);
		glVertex3f(-50,50,0);
 	glEnd();
*/



//////////////////////////////////////



	glTranslatef(-4.0f, -1.3f, 0.0f); //Return origin //moving coordinate start

	//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// gradient legend ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i= 0; i< 100; i++) // gradient legend
	{
			cnormal = 0.01*(float)i;
			setcolorscale();

			glTranslatef(0.0f, (float)(i*2+1)*0.015, 0.0f);
			
			glColor4f(0.0f, 0.0f, 0.0f,0.0f);
			glBegin(GL_LINE_LOOP); //sides
				glVertex3f(-0.4f,-0.015f,0.0f);
				glVertex3f(-0.2f,-0.015f,0.0f);
				glVertex3f(-0.2f,0.015f,0.0f);
				glVertex3f(-0.4f,0.015f,0.0f);
			glEnd();

			glColor4f(cred, cgreen, cblue,0.0f);
			glBegin(GL_QUADS); //sides
				glVertex3f(-0.4f,-0.015f,0.0f);
				glVertex3f(-0.2f,-0.015f,0.0f);
				glVertex3f(-0.2f,0.015f,0.0f);
				glVertex3f(-0.4f,0.015f,0.0f);
			glEnd();

			glTranslatef(-0.0f,-(float)(i*2+1)*0.015, 0.0f);
	} // gradient legendn -  end

	//gradient controller

			glTranslatef(0.0f, redscale*3.0f, 0.0f);
			glColor4f(0.0f, 0.0f, 0.0f,0.0f);
			glBegin(GL_LINE_LOOP); //sides
				glVertex3f(-0.48f,-0.04f,0.0f);
				glVertex3f(-0.41f,-0.04f,0.0f);
				glVertex3f(-0.41f,0.04f,0.0f);
				glVertex3f(-0.48f,0.04f,0.0f);
			glEnd();

			glColor4f(1.0f, 0.0f, 0.0f,0.0f);
			glBegin(GL_QUADS); //sides
				glVertex3f(-0.48f,-0.04f,0.0f);
				glVertex3f(-0.41f,-0.04f,0.0f);
				glVertex3f(-0.41f,0.04f,0.0f);
				glVertex3f(-0.48f,0.04f,0.0f);
			glEnd();
		glTranslatef(-0.0f,-redscale*3.0f, 0.0f);


		glTranslatef(0.0f, yellowscale*3.0f, 0.0f);
			glColor4f(0.0f, 0.0f, 0.0f,0.0f);
			glBegin(GL_LINE_LOOP); //sides
				glVertex3f(-0.19f,-0.04f,0.0f);
				glVertex3f(-0.12f,-0.04f,0.0f);
				glVertex3f(-0.12f,0.04f,0.0f);
				glVertex3f(-0.19f,0.04f,0.0f);
			glEnd();

			glColor4f(1.0f, 1.0f, 0.0f,0.0f);
			glBegin(GL_QUADS); //sides
				glVertex3f(-0.19f,-0.04f,0.0f);
				glVertex3f(-0.12f,-0.04f,0.0f);
				glVertex3f(-0.12f,0.04f,0.0f);
				glVertex3f(-0.19f,0.04f,0.0f);
			glEnd();
		glTranslatef(-0.0f,-yellowscale*3.0f, 0.0f);

	//

	//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// gradient legend- end ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// information text section ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			glColor4f(0.0f, 0.0f, 0.0f,1.0f);

//	char temp[30]= "VNRD 1.0 by Bohung Kim, CEN Lab @ Krasnow Institute";
	 glTranslatef(0.0f, -0.3f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
     glRasterPos2f(0.0f, 0.0f);   glPrint("VNRD 1.0 by Bohung Kim, CEN Lab @ Krasnow Institute");  //<3>
 	 glTranslatef(-0.0f, 0.3f, 0.0f);
	
	 

	 _gcvt( (double)meshzoom, 5, bufferzoom);

	 //_itoa(i+1, buffer, 10)
 

	glTranslatef(0.0f, -0.4f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("Zoom ratio:");  //<3>
	glTranslatef(-0.0f, 0.4f, 0.0f);
	glTranslatef(1.05f, -0.4f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
    glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
 	glTranslatef(-1.05f, 0.4f, 0.0f);

	_itoa( nElement, buffer, 10);
	glTranslatef(0.0f, -0.5f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("Compartment#: ");  //<3>
	glTranslatef(-0.0f, 0.5f, 0.0f);
	glTranslatef(1.05f, -0.5f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
    glRasterPos2f(0.0f, 0.0f);   glPrint(buffer);  //<3>
 	glTranslatef(-1.05f, 0.5f, 0.0f);

	_itoa(totaltimesteps, buffer, 10);
	glTranslatef(0.0f, -0.6f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("Totaltimesteps: ");  //<3>
	glTranslatef(-0.0f, 0.6f, 0.0f);
	glTranslatef(1.05f, -0.6f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
    glRasterPos2f(0.0f, 0.0f);   glPrint(buffer);  //<3>
 	glTranslatef(-1.05f, 0.6f, 0.0f);

		_itoa( timestep, buffer, 10);
	glTranslatef(0.0f, -0.7f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("Current step: ");  //<3>
	glTranslatef(-0.0f, 0.7f, 0.0f);
	glTranslatef(1.05f, -0.7f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
    glRasterPos2f(0.0f, 0.0f);   glPrint(buffer);  //<3>
 	glTranslatef(-1.05f, 0.7f, 0.0f);


	_gcvt( (double)finterval, 5, bufferzoom);
	glTranslatef(0.0f, -0.8f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("Frame rate(ms): ");  //<3>
	glTranslatef(-0.0f, 0.8f, 0.0f);
	glTranslatef(1.05f, -0.8f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
    glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
 	glTranslatef(-1.05f, 0.8f, 0.0f);





	//_gcvt( (double)graph_base, 5, bufferzoom);
	_itoa( nSelected, buffer, 10);
	glTranslatef(2.0f, -0.4f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("Selected #: ");  //<3>
	glTranslatef(-2.0f, 0.4f, 0.0f);
	glTranslatef(2.8f, -0.4f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
    glRasterPos2f(0.0f, 0.0f);   glPrint(buffer);  //<3>
 	glTranslatef(-2.8f, 0.4f, 0.0f);

	//_gcvt( (double)graph_max, 5, bufferzoom);
	glTranslatef(4.0f, -0.5f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("Data Type: ");  //<3>
	glTranslatef(-4.0f, 0.5f, 0.0f);
	glTranslatef(4.8f, -0.5f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	if (isdatanumberofmolecule == 1) {glRasterPos2f(0.0f, 0.0f);   glPrint("Number of Molecules");}  //<3>
	if (isdatanumberofmolecule == 0) {glRasterPos2f(0.0f, 0.0f);   glPrint("Concentration");}  //<3>
 	glTranslatef(-4.8f, 0.5f, 0.0f);

	
	_gcvt( (double)numberdatainfo, 5, bufferzoom);
    glTranslatef(2.0f, -0.5f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("Data : ");  //<3>
	glTranslatef(-2.0f, 0.5f, 0.0f);
	glTranslatef(2.8f, -0.5f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	if (numberdatainfo < 0){glRasterPos2f(0.0f, 0.0f);   glPrint("N/A");}  //<3>}
	else {glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);}   //<3>
	glTranslatef(-2.8f, 0.5f, 0.0f);

	_gcvt( (double)glcrossx, 5, bufferzoom);
	glTranslatef(2.0f, -0.8f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("x-coordinate: ");  //<3>
	glTranslatef(-2.0f, 0.8f, 0.0f);
	glTranslatef(2.95f, -0.8f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
    glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
 	glTranslatef(-2.95f, 0.8f, 0.0f);

	_gcvt( (double)glcrossy, 5, bufferzoom);
	glTranslatef(4.0f, -0.8f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("y-coordinate: ");  //<3>
	glTranslatef(-4.0f, 0.8f, 0.0f);
	glTranslatef(4.95f, -0.8f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
    glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
 	glTranslatef(-4.95f, 0.8f, 0.0f);

	//if (ns)

		CString tempinfo;
		tempinfo = "N/A";
		numberdatainfo = 0.0;
		float iymax,iymin;
		float ixmax,ixmin;
		numberdatainfo = -1.0;

	for(int ii = nEstart; ii<nElement ; ii++) 
	{
		 iymax = -100000.0f;
		 iymin = 100000.0f;
		 ixmax = -100000.0f;
		 ixmin = 100000.0f; 
		 
		 
		 for (int jj =0; jj<4; jj++)
		 {
			 if (iymax < Element[ii].y[jj]) iymax = Element[ii].y[jj];
			 if (iymin > Element[ii].y[jj]) iymin = Element[ii].y[jj];
			 if (ixmax < Element[ii].x[jj]) ixmax = Element[ii].x[jj];
			 if (ixmin > Element[ii].x[jj]) ixmin = Element[ii].x[jj];
		 }

	
		if (glcrossx > ixmin+relx && glcrossx < ixmax+relx)
		{
			if (glcrossy < iymax+rely && glcrossy > iymin+rely)
			{
				if (meshmode == 1) tempinfo = itoa(ii, buffer, 10);
				if (meshmode == 0) 
				{
					tempinfo = strinfo[ii];
					numberdatainfo = Edata[0][timestep].data[ii+1];

				}
			}
		}

	}


//	bufferzoom = strinfo[1].GetBuffer(strinfo[1].GetLength());
	glTranslatef(2.0f, -0.6f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint("Info: ");  //<3>
	glTranslatef(-2.0f, 0.6f, 0.0f);
	glTranslatef(2.8f, -0.6f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
	glRasterPos2f(0.0f, 0.0f);   glPrint(tempinfo);  //<3>
 	glTranslatef(-2.8f, 0.6f, 0.0f);


		glBegin(GL_LINES); //info text lines
				
		//outer line
				glVertex3f(-0.05f,-0.2f,0.0f); //top line
				glVertex3f(8.3f,-0.2f,0.0f);

				glVertex3f(-0.05f,-0.33f,0.0f); //2nd top line
				glVertex3f(8.3f,-0.33f,0.0f);


				glVertex3f(-0.05f,-0.85f,0.0f); //bottom line
				glVertex3f(8.3f,-0.85f,0.0f);

				glVertex3f(-0.05f,-0.2f,0.0f); //left line
				glVertex3f(-0.05f,-0.85f,0.0f);
				
				glVertex3f(8.3f,-0.2f,0.0f); //Right line
				glVertex3f(8.3f,-0.85f,0.0f);
		//outer line

				glVertex3f(-0.05f,-0.73f,0.0f); //progress line
				glVertex3f(8.3f,-0.73f,0.0f);

				glVertex3f(-0.05f,-0.63f,0.0f); //progress line
				glVertex3f(8.3f,-0.63f,0.0f);

		glEnd();


	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// information text section -end ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// outer blue crosshair ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//m_ParamDlg.nElement = nElement;
	//m_ParamDlg.totaltimesteps = totaltimesteps;
	//m_ParamDlg.finterval = (int)finterval;
	//m_ParamDlg.navg = navg;
	//m_ParamDlg.graph_base = (int) graph_base;
	//m_ParamDlg.graph_max = (int) graph_max;


	if (glcrossx < 0.0f || glcrossy < 0.0f)
	{
		glColor4f(0.0f, 0.0f, 1.0f,0.0f);
		glBegin(GL_LINES); // mouse pointer
				glVertex3f(meshzoom*(glcrossx-0.1f),meshzoom*glcrossy,0.0f);
				glVertex3f(meshzoom*(glcrossx+0.1f),meshzoom*glcrossy,0.0f);
				glVertex3f(meshzoom*glcrossx,meshzoom*(glcrossy-0.1f),0.0f);
				glVertex3f(meshzoom*glcrossx,meshzoom*(glcrossy+0.1f),0.0f);
		glEnd();
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// outer blue crosshair - end ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// timestep progress ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	float tmpprogbar;

	tmpprogbar = 7.0f*timestep/(totaltimesteps+1); // +1 for avoid zero
	if (tmpprogbar > 7.0f) tmpprogbar = 7.0f;
	if (totaltimesteps == 0) tmpprogbar = 0.0f;
		//progress marker
	glColor4f(0.1f, 0.1f, 0.1f,0.0f);
	glBegin(GL_QUADS); //front plane
		glVertex3f(1.2f+tmpprogbar,-0.72f,0.0f);
		glVertex3f(1.24f+tmpprogbar,-0.72,0.0f);
		glVertex3f(1.24f+tmpprogbar,-0.645f,0.0f);
		glVertex3f(1.2f+tmpprogbar,-0.645f,0.0f);
	glEnd();

	//progress bar
	glColor4f(0.9f, 0.6f, 0.9f,0.0f);
	glBegin(GL_QUADS); //front plane
		glVertex3f(1.2f,-0.72f,0.0f);
		glVertex3f(8.2f,-0.72,0.0f);
		glVertex3f(8.2f,-0.645f,0.0f);
		glVertex3f(1.2f,-0.645f,0.0f);
	glEnd();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// timestep progress - end ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// area average ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//selected area plot
/*
		nSelected = 0;
	for(int ii = nEstart; ii<nElement ; ii++) 
	{
		if(Element[ii].Issel == 1)
		{
			selectmap[nSelected] = ii;
			nSelected = nSelected+1;
		}
	}
*/

	if (useravgmax !=0 )avgmax = useravgmax;
	//useravgmax = from user input
	//avgmax = from data max


	if (graphavgmode == 1)
	{
		//tmpprogbar

		float ytop;
		float ybot;
		float xleft;
		float xright;
		float tmpscale;
		ytop = 3.3f;
		ybot = 1.3f;
		xleft = 0.7f;
		xright = 7.7f;
		tmpscale = xright - xleft; 


		_gcvt( (double)avgmax, 5, bufferzoom);
		glTranslatef(xleft, ytop+0.02, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
		glTranslatef(-xleft, -ytop-0.02, 0.0f);

		glTranslatef(xleft, ybot-0.08f, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint("0");  //<3>
		glTranslatef(-xleft, -ybot+0.08f, 0.0f);

		_itoa( totaltimesteps, buffer, 10);
		glTranslatef(xright, ybot-0.08, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(buffer);  //<3>
		glTranslatef(-xright, -ybot+0.08, 0.0f);

		_itoa( int(totaltimesteps/2), buffer, 10);
		glTranslatef(xleft+tmpscale/2.0f, ybot-0.08, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(buffer);  //<3>
		glTranslatef(-xleft-tmpscale/2.0f, -ybot+0.08, 0.0f);



		//avgdata[jj] fmax[0]
		float tmpplotx;
		float tmpploty;

		float tmpplotx1;
		float tmpploty1;

		glColor4f(0.6f, 0.0f, 0.0f,0.0f);

		glBegin(GL_LINES); // red progress line
				glVertex3f(tmpprogbar+0.7f,ybot,0.0f);
				glVertex3f(tmpprogbar+0.7f,ytop,0.0f);
		glEnd();

		glColor4f(0.0f, 0.0f, 0.0f,0.0f);
		
		glBegin(GL_LINES); // Black coordinate lines
				glVertex3f(xleft,ybot,0.0f);
				glVertex3f(xleft,ytop,0.0f);
			    glVertex3f(xleft,ybot,0.0f);
				glVertex3f(xright,ybot,0.0f);
		glEnd();

		glColor4f(0.6f, 0.6f, 0.6f,0.0f);
		glBegin(GL_LINES); // white out coordinate lines
				glVertex3f(xright,ybot,0.0f);
				glVertex3f(xright,ytop,0.0f);
			    glVertex3f(xleft,ytop,0.0f);
				glVertex3f(xright,ytop,0.0f);
		glEnd();

//		tmpprogbar = 7.0f*timestep/(totaltimesteps+1);
		
		glColor4f(0.6f, 0.0f, 0.0f,0.0f);
		for (int ii = 0; ii < totaltimesteps-1; ii++)
		{
			tmpplotx=7.0f*ii/(totaltimesteps+1); //xlength == 7
			tmpploty = 2.0*avgdata[ii]/avgmax;

			tmpplotx1=7.0f*(ii+1)/(totaltimesteps+1); //xlength == 7
			tmpploty1= 2.0*avgdata[ii+1]/avgmax;

				
			glBegin(GL_LINES); // red progress line
			glVertex3f(xleft+tmpplotx,ybot+tmpploty,0.0f);
			glVertex3f(xleft+tmpplotx1,ybot+tmpploty1,0.0f);
			glEnd();

//			glTranslatef(xleft+tmpplotx,ybot+tmpploty,0.0f);
			//auxSolidSphere(0.01f);  
//			glTranslatef(-xleft-tmpplotx,-ybot-tmpploty,-0.0f);
		}

//		glColor4f(0.6f, 0.6f, 0.6f,0.0f);
		glColor4f(1.0f, 1.0f, 1.0f,0.0f);
		glBegin(GL_QUADS); //front plane
			glVertex3f(xleft-0.2f,ybot-0.2f,0.0f);
			glVertex3f(xright+0.2,ybot-0.2f,0.0f);
			glVertex3f(xright+0.2,ytop+0.2,0.0f);
			glVertex3f(xleft-0.2f,ytop+0.2,0.0f);
		glEnd();
	}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// area average end ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// zoom region ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glScalef(meshzoom, meshzoom, 1.0f); //Return origin /// zoom/scaling in start /////////////////////////////////zoom region

///////////////////////////////////////////////////////////////// inner crosshair ////////////////////////////////////////////////////////////////////////////////
	if (glcrossx > 0.0f && glcrossy > 0.0f)
	{
		glColor4f(1.0f, 0.0f, 0.0f,0.0f);
		glBegin(GL_LINES); // mouse pointer
				glVertex3f(glcrossx-0.1f,glcrossy,0.0f);
				glVertex3f(glcrossx+0.1f,glcrossy,0.0f);
				glVertex3f(glcrossx,glcrossy-0.1f,0.0f);
				glVertex3f(glcrossx,glcrossy+0.1f,0.0f);
		glEnd();
	}
///////////////////////////////////////////////////////////////// inner crosshair - end ////////////////////////////////////////////////////////////////////////////////

	
		double tmpnavg1,tmpnavg2;
		tmpnavg1 = 0.0f;
		tmpnavg2 = 0.0f;
		int middlepoint1;
		int middlepoint2;

///////////////////////////////////////////////////////////////// spatial average along x dir ////////////////////////////////////////////////////////////////////////////////
	if (isgraphx == 1 && meshmode == 0 )
	{

			//glTranslatef(6.0f, -3.0f, 6.5f); //Return origin

		sortintoxdirection();


glTranslatef(relx,rely, 0.0f);

		glColor4f(1.0f, 0.0f, 0.0f,0.0f);//origin
		for (int ii = 0 ; ii < ncord-navg  ; ii= ii+ navg)
		{
			for (int p=0; p<navg; p++)
			{
			tmpnavg1 = tmpnavg1 +((float)xyout[ii+p].datasum/spatialmax);
			tmpnavg2 = tmpnavg2 +((float)xyout[ii+navg+p].datasum/spatialmax);
			}

			middlepoint1 = ii+(int)(navg/2);
			middlepoint2 = ii+navg+(int)(navg/2);
			if (middlepoint2 > ncord-1) middlepoint2 = ii+navg;

			tmpnavg1 = tmpnavg1/navg;
			if (middlepoint2 > ncord-1) tmpnavg2 = tmpnavg2/(ncord-(ii+navg+(int)(navg/2))); //need more work here
			else tmpnavg2 = tmpnavg2/navg;


			glBegin(GL_LINES); // red progress line
			glVertex3f((float)xyout[middlepoint1].cord,tmpnavg1*graph_max+graph_base,0.0f);
			glVertex3f((float)xyout[middlepoint2].cord,tmpnavg2*graph_max+graph_base,0.0f);
			glEnd();

			glTranslatef((float)xyout[middlepoint1].cord,tmpnavg1*graph_max+graph_base, 0.0f); //Target point
			auxSolidSphere(0.02f);         //Draw sphere
			glTranslatef(-(float)xyout[middlepoint1].cord,-(tmpnavg1*graph_max+graph_base), 0.0f); //Target point


			glTranslatef((float)xyout[middlepoint2].cord,tmpnavg2*graph_max+graph_base, 0.0f); //Target point
			auxSolidSphere(0.02f);         //Draw sphere
			glTranslatef(-(float)xyout[middlepoint2].cord,-(tmpnavg2*graph_max+graph_base), 0.0f); //Target point


			tmpnavg1 = 0.0f;
			tmpnavg2 = 0.0f;
		}


		glColor4f(0.0f, 0.0f, 0.0f,0.0f);
		


		_gcvt( (double)spatialmax, 5, bufferzoom);
		glTranslatef((float)xyout[0].cord, graph_max+graph_base+0.02, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
		glTranslatef(-(float)xyout[0].cord, -(graph_max+graph_base)-0.02, 0.0f);


		_gcvt( (double)xyout[0].cord, 5, bufferzoom);
		glTranslatef((float)xyout[0].cord,graph_base-0.2, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
		glTranslatef(-(float)xyout[0].cord,-graph_base+0.2, 0.0f);

		_gcvt( (double)xyout[ncord-1].cord, 5, bufferzoom);
		glTranslatef((float)xyout[ncord-1].cord,graph_base-0.2, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
		glTranslatef(-(float)xyout[ncord-1].cord,-graph_base+0.2, 0.0f);


		_gcvt( (double)xyout[(int)(ncord/2)].cord, 5, bufferzoom);
		glTranslatef((float)xyout[(int)(ncord/2)].cord,graph_base-0.2, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
		glTranslatef(-(float)xyout[(int)(ncord/2)].cord,-graph_base+0.2, 0.0f);


		glBegin(GL_LINES); // Black coordinate lines
				glVertex3f((float)xyout[0].cord,graph_base,0.0f);
				glVertex3f((float)xyout[0].cord,graph_max+graph_base,0.0f);
			    glVertex3f((float)xyout[0].cord,graph_base,0.0f);
				glVertex3f((float)xyout[ncord-1].cord,graph_base,0.0f);
		glEnd();

		glColor4f(0.6f, 0.6f, 0.6f,0.0f);
		glBegin(GL_LINES); // gray out coordinate lines
				glVertex3f((float)xyout[ncord-1].cord,graph_base,0.0f);
				glVertex3f((float)xyout[ncord-1].cord,graph_max+graph_base,0.0f);
			    glVertex3f((float)xyout[0].cord,graph_max+graph_base,0.0f);
				glVertex3f((float)xyout[ncord-1].cord,graph_max+graph_base,0.0f);
		glEnd();

			//glColor4f(0.6f, 0.6f, 0.6f,1.0f);
			glColor4f(1.0f, 1.0f, 1.0f,1.0f);
			glBegin(GL_QUADS); //sides
				glVertex3f((float)xyout[0].cord-0.2f,graph_base-0.2f,0.0f);
				glVertex3f((float)xyout[0].cord-0.2f,graph_max+graph_base+0.2f,0.0f);
				glVertex3f((float)xyout[ncord-1].cord+0.2f,graph_max+graph_base+0.2f,0.0f);
				glVertex3f((float)xyout[ncord-1].cord+0.2f,graph_base-0.2f,0.0f);
				
			
			glEnd();

glTranslatef(-relx,-rely, 0.0f);


	}//end drawing chart

///////////////////////////////////////////////////////////////// spatial average along x dir -end ////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////// spatial average along y dir -!!!! not done yet////////////////////////////////////////////////////////////////////////////////

	if (isgraphy == 1 && meshmode == 0 )
	{

			//glTranslatef(6.0f, -3.0f, 6.5f); //Return origin

		sortintoydirection();

glTranslatef(relx,rely, 0.0f);

		glColor4f(1.0f, 0.0f, 0.0f,0.0f);//origin
		for (int ii = 0 ; ii < ncord-navg  ; ii= ii+ navg)
		{
			for (int p=0; p<navg; p++)
			{
			tmpnavg1 = tmpnavg1 +((float)xyout[ii+p].datasum/spatialmax);
			tmpnavg2 = tmpnavg2 +((float)xyout[ii+navg+p].datasum/spatialmax);
			}

			middlepoint1 = ii+(int)(navg/2);
			middlepoint2 = ii+navg+(int)(navg/2);
			if (middlepoint2 > ncord-1) middlepoint2 = ii+navg;

			tmpnavg1 = tmpnavg1/navg;
			if (middlepoint2 > ncord-1) tmpnavg2 = tmpnavg2/(ncord-(ii+navg+(int)(navg/2))); //need more work here
			else tmpnavg2 = tmpnavg2/navg;


			glBegin(GL_LINES); // red progress line
			glVertex3f(tmpnavg1*graph_max+graph_base,(float)xyout[middlepoint1].cord,0.0f);
			glVertex3f(tmpnavg2*graph_max+graph_base,(float)xyout[middlepoint2].cord,0.0f);
			glEnd();

			glTranslatef(tmpnavg1*graph_max+graph_base,(float)xyout[middlepoint1].cord, 0.0f); //Target point
			auxSolidSphere(0.02f);         //Draw sphere
			glTranslatef(-(tmpnavg1*graph_max+graph_base),-(float)xyout[middlepoint1].cord, 0.0f); //Target point


			glTranslatef(tmpnavg2*graph_max+graph_base,(float)xyout[middlepoint2].cord, 0.0f); //Target point
			auxSolidSphere(0.02f);         //Draw sphere
			glTranslatef(-(tmpnavg2*graph_max+graph_base),-(float)xyout[middlepoint2].cord, 0.0f); //Target point


			tmpnavg1 = 0.0f;
			tmpnavg2 = 0.0f;
		}


		glColor4f(0.0f, 0.0f, 0.0f,0.0f);
		


		_gcvt( (double)spatialmax, 5, bufferzoom);
		glTranslatef(graph_max+graph_base+0.02,(float)xyout[0].cord,  0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
		glTranslatef(-(graph_max+graph_base)-0.02,-(float)xyout[0].cord,  0.0f);


		_gcvt( (double)xyout[0].cord, 5, bufferzoom);
		glTranslatef(graph_base-0.2,(float)xyout[0].cord, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
		glTranslatef(-graph_base+0.2,-(float)xyout[0].cord, 0.0f);

		_gcvt( (double)xyout[ncord-1].cord, 5, bufferzoom);
		glTranslatef(graph_base-0.2,(float)xyout[ncord-1].cord, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
		glTranslatef(-graph_base+0.2,-(float)xyout[ncord-1].cord, 0.0f);


		_gcvt( (double)xyout[(int)(ncord/2)].cord, 5, bufferzoom);
		glTranslatef(graph_base-0.2,(float)xyout[(int)(ncord/2)].cord, 0.0f); //  glColor3f(0.0f, 1.0f, 0.0f);      //<1>
		glRasterPos2f(0.0f, 0.0f);   glPrint(bufferzoom);  //<3>
		glTranslatef(-graph_base+0.2,-(float)xyout[(int)(ncord/2)].cord, 0.0f);


		glBegin(GL_LINES); // Black coordinate lines
				glVertex3f(graph_base,(float)xyout[0].cord,0.0f);
				glVertex3f(graph_max+graph_base,(float)xyout[0].cord,0.0f);
			    glVertex3f(graph_base,(float)xyout[0].cord,0.0f);
				glVertex3f(graph_base,(float)xyout[ncord-1].cord,0.0f);
		glEnd();

		glColor4f(0.6f, 0.6f, 0.6f,0.0f);
		glBegin(GL_LINES); // white out coordinate lines
				glVertex3f(graph_base,(float)xyout[ncord-1].cord,0.0f);
				glVertex3f(graph_max+graph_base,(float)xyout[ncord-1].cord,0.0f);
			    glVertex3f(graph_max+graph_base,(float)xyout[0].cord,0.0f);
				glVertex3f(graph_max+graph_base,(float)xyout[ncord-1].cord,0.0f);
		glEnd();

			//glColor4f(0.6f, 0.6f, 0.6f,1.0f);
			glColor4f(1.0f, 1.0f, 1.0f,1.0f);
			glBegin(GL_QUADS); //sides
				glVertex3f(graph_base-0.2f,(float)xyout[0].cord-0.2f,0.0f);
				glVertex3f(graph_base-0.2f,(float)xyout[ncord-1].cord+0.2f,0.0f);
				glVertex3f(graph_max+graph_base+0.2f,(float)xyout[ncord-1].cord+0.2f,0.0f);
				glVertex3f(graph_max+graph_base+0.2f,(float)xyout[0].cord-0.2f,0.0f);
			glEnd();
glTranslatef(-relx,-rely, 0.0f);

	}//end drawing chart




///////////////////////////////////////////////////////////////// spatial average along y dir -end ////////////////////////////////////////////////////////////////////////////////


	glTranslatef(relx, rely, 0.0f); //relative coordinate for morphology domain when move origin
///////////////////////////////////////////////////////////////// cooridnate number ticks ////////////////////////////////////////////////////////////////////////////////
	

	float coordi;
	for (int i = 0; i < 100 ; i++)
	{
	coordi = (float)(i+1);
	
	glTranslatef(coordi, -0.1f, 0.0f); //Target point
	//auxSolidSphere(0.01f);         //Draw sphere
	if (nwhitegray == 0) {glRasterPos2f(0.0f, 0.0f);   glPrint(itoa(i+1, buffer, 10));}  //<3>
	glTranslatef(-coordi, 0.1f, 0.0f); //Return origin

	glTranslatef(-0.1f, coordi, 0.0f); //Target point
	//auxSolidSphere(0.01f);         //Draw sphere
	if (nwhitegray == 0) {glRasterPos2f(0.0f, 0.0f);   glPrint(itoa(i+1, buffer, 10));}  //<3>
	glTranslatef(0.1f, -coordi, 0.0f); //Return origin
	}


//	glColor4f(0.0f, 0.0f, 1.0f,0.0f);//z
//	glTranslatef(0.0f, 0.0f, 1.0f); //Target point
//	auxSolidSphere(0.03f);         //Draw sphere
//	glTranslatef(0.0f, 0.0f, -1.0f); //Return origin

	glColor4f(0.0f, 1.0f, 0.0f,0.0f);
//	glTranslatef(0.01f*((float)timestep),0.0f, 0.0f); //Target point
	glTranslatef(0.01f,0.0f, 0.0f); //Target point
		if (nwhitegray == 0)  auxSolidSphere(0.03f);         //Draw sphere
	glTranslatef(-0.01f,0.0f, 0.0f); //Return origin
//	glTranslatef(-0.01f*((float)timestep),0.0f, 0.0f); //Return origin

//////////////////////////////////////////////////////////////// cooridnate number ticks - end ////////////////////////////////////////////////////////////////////////////////			


//////////////////////////////////////////////////////////////// Drawing morphology ////////////////////////////////////////////////////////////////////////////////			

	int mm;
	for (mm = 0; mm< ndom; mm++)// for multi domain.
	{
		mofx = 0.0f;
		mofy = 0.0f;
		if (mm == 1)
		{
			mofx = offsetx[0];
				mofy = offsety[0];
		}
		if (mm == 2)
		{
			mofx = offsetx[1];
				mofy = offsety[1];
		}


					colorcount = 0;

					int tmpselcount;
					tmpselcount = 0;
						
					for(int ii = nEstart; ii<nElement ; ii++) 
					{

						selcolor = 0.0f;
						if(Element[ii].Issel == 1) 
						{
							selcolor = -0.3f;
							selectmap[tmpselcount] = ii;
							tmpselcount = tmpselcount+1;

						}

						if (meshmode == 1 ) 
						{
						colorcount += 1;
						if (colorcount == 1)glColor4f(255.0f/255.0f-selcolor, 105.0f/255.0f-selcolor, 180.0f/255.0f-selcolor,0.0f);
						if (colorcount == 2)glColor4f(154.0f/255.0f-selcolor, 205.0f/255.0f-selcolor, 50.0f/255.0f-selcolor,0.0f);
						if (colorcount == 3)glColor4f(255.0f/255.0f-selcolor, 215.0f/255.0f-selcolor, 000.0f/255.0f-selcolor,0.0f);
						if (colorcount == 4)glColor4f(147.0f/255.0f-selcolor, 112.0f/255.0f-selcolor, 219.0f/255.0f-selcolor,0.0f);
						if (colorcount == 5)glColor4f(139.0f/255.0f-selcolor, 137.0f/255.0f-selcolor, 137.0f/255.0f-selcolor,0.0f);
						if (colorcount == 6)glColor4f(205.0f/255.0f-selcolor, 069.0f/255.0f-selcolor, 144.0f/255.0f-selcolor,0.0f);
						if (colorcount == 7)glColor4f(30.0f/255.0f-selcolor, 144.0f/255.0f-selcolor, 255.0f/255.0f-selcolor,0.0f);
						if (colorcount == 8)glColor4f(60.0f/255.0f-selcolor, 120.0f/255.0f-selcolor, 210.0f/255.0f-selcolor,0.0f);
						if (colorcount == 9)glColor4f(90.0f/255.0f-selcolor, 110.0f/255.0f-selcolor, 180.0f/255.0f-selcolor,0.0f);
						if (colorcount == 10)glColor4f(120.0f/255.0f-selcolor, 90.0f/255.0f-selcolor, 150.0f/255.0f-selcolor,0.0f);
						if (colorcount == 11){glColor4f(150.0f/255.0f-selcolor, 80.0f/255.0f-selcolor, 100.0f/255.0f-selcolor,0.0f);colorcount = 0;}
						}else
						{

						cnormal = (Edata[mm][timestep].data[ii+1]-fmin[mm])/(fmax[mm]-fmin[mm]); //data[ii+1] since data[0] is timesetp
						
						setcolorscale();

						glColor4f(cred-selcolor, cgreen-selcolor, cblue-selcolor,0.0f);

						//glColor4f(cnormal-selcolor, 107.0f/255.0f-selcolor, 47.0f/255.0f-selcolor,0.0f);

						//glColor4f((Edata[mm][4][timestep].data[ii+1]-fmin[mm])/(fmax[mm]-fmin[mm])-selcolor,0.0f,1.0f-(Edata[mm][4][timestep].data[ii+1]-fmin[mm])/(fmax[mm]-fmin[mm]),0.0f);
						//glColor4f((Edata[4][timestep].data[ii+1]-fmin)/(fmax-fmin), 0.0f, 0.0f,0.0f);
						//glColor4f((Edata[4][timestep].data[ii+1]-fmin)/(fmax-fmin), 0.0f, 0.0f,0.0f);
						}

					
					glBegin(GL_QUADS); //front plane
						glVertex3f(mofx+Element[ii].x[3],mofy+Element[ii].y[3],Element[ii].z[3]);
						glVertex3f(mofx+Element[ii].x[0],mofy+Element[ii].y[0],Element[ii].z[0]);
						glVertex3f(mofx+Element[ii].x[1],mofy+Element[ii].y[1],Element[ii].z[1]);
						glVertex3f(mofx+Element[ii].x[2],mofy+Element[ii].y[2],Element[ii].z[2]);
					glEnd();

					if (nRotate == 1)
					{
					glBegin(GL_LINE_LOOP); //back plane
						glVertex3f(mofx+Element[ii].x[3],mofy+Element[ii].y[3],Element[ii].z[3]+Element[ii].deltaZ);
						glVertex3f(mofx+Element[ii].x[0],mofy+Element[ii].y[0],Element[ii].z[0]+Element[ii].deltaZ);
						glVertex3f(mofx+Element[ii].x[1],mofy+Element[ii].y[1],Element[ii].z[1]+Element[ii].deltaZ);
						glVertex3f(mofx+Element[ii].x[2],mofy+Element[ii].y[2],Element[ii].z[2]+Element[ii].deltaZ);
					glEnd();

					glBegin(GL_LINES); //sides
						glVertex3f(mofx+Element[ii].x[3],mofy+Element[ii].y[3],Element[ii].z[3]+Element[ii].deltaZ);
						glVertex3f(mofx+Element[ii].x[3],mofy+Element[ii].y[3],Element[ii].z[3]);
						glVertex3f(mofx+Element[ii].x[0],mofy+Element[ii].y[0],Element[ii].z[0]+Element[ii].deltaZ);
						glVertex3f(mofx+Element[ii].x[0],mofy+Element[ii].y[0],Element[ii].z[0]);
						glVertex3f(mofx+Element[ii].x[1],mofy+Element[ii].y[1],Element[ii].z[1]+Element[ii].deltaZ);
						glVertex3f(mofx+Element[ii].x[1],mofy+Element[ii].y[1],Element[ii].z[1]);
						glVertex3f(mofx+Element[ii].x[2],mofy+Element[ii].y[2],Element[ii].z[2]+Element[ii].deltaZ);
						glVertex3f(mofx+Element[ii].x[2],mofy+Element[ii].y[2],Element[ii].z[2]);
					glEnd();
					}



					if (isselon == 1) // issel is on when lbutton down
					{
						glColor4f(1.0f, 0.0f, 0.0f,0.0f); //red line for select
						glBegin(GL_LINE_LOOP); //sides
							glVertex3f(mofx+selx1,mofy+sely1,0.0f);
							glVertex3f(mofx+selx2,mofy+sely1,0.0f);
							glVertex3f(mofx+selx2,mofy+sely2,0.0f);
							glVertex3f(mofx+selx1,mofy+sely2,0.0f);
						glEnd();
					}


					if (isselon == 1)
					{
						if (Element[ii].cx < selxMax && Element[ii].cx > selxMin)
						{
							if (Element[ii].cy < selyMax && Element[ii].cy > selyMin)
							{
									Element[ii].Issel = 1;
							}
						
						}

					}

	
				}//for(int ii = nEstart; ii<nElement ; ii++) 
						
				nSelected = tmpselcount;
		} //for multi domain




		

//////////////////////////////////////////////////////////////// Drawing morphology - end ////////////////////////////////////////////////////////////////////////////////			
	glTranslatef(-relx, -rely, 0.0f);//for relative coordinate in morphology domain when move origin -- end




//////////////////////////////////////////////////////////////////Drawing grid lines 

		if (nwhitegray == 0) glColor4f(1.0f, 1.0f, 1.0f, 0.0); // white background
		else glColor4f(0.8f, 0.8f, 0.8f, 0.0); //gray background


		if (nwhitegray == 0)
		{
		for (int i=0; i< 200; i++)
			{
				glBegin(GL_LINES); //sides
					glVertex3f(0.0f,float(i)*0.5f,0.0f);
					glVertex3f(100.0f,float(i)*0.5f,0.0f);
				glEnd();

							
				glBegin(GL_LINES); //sides
					glVertex3f(float(i)*0.5f,0.0f,0.0f);
					glVertex3f(float(i)*0.5f,100.0f,0.0f);
				glEnd();
			}
		
		}
/////////////////////////////////////////////////////////////////Drawing grid lines - End



	glScalef(1.0f/meshzoom, 1.0f/meshzoom, 1.0f); //Return origin /// zoom/scaling in start
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// zoom region -end ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	glFlush();

}

void CMFCGLView::OnDestroy()
{

	CView::OnDestroy();
	
	// TODO: Add your message handler code here

	if(FALSE==wglMakeCurrent(0, 0)) {  //Release current rendering context
		//::AfxMessageBox("wglMakeCurrent Fail.\n");
	}
	
	if(m_hRC && (FALSE==wglDeleteContext(m_hRC))) { // Removing rendering context
		//::AfxMessageBox("wglDeleteContext Fail.\n");
	}

	if(m_pDC) delete m_pDC;  // Remove the device context


	// TODO: Add your message handler code here
}

void CMFCGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

//working conversion

		// TODO: Add your message handler code here and/or call default
/*	int    vp[4];
	double mv[16], pm[16];
	float  winX, winY, winZ;
	double glX, glY, glZ;
	double x2, y2, z2;
	double y;
	CPoint cursor;

	GetCursorPos(&cursor);
	ScreenToClient(&cursor);

	glGetIntegerv(GL_VIEWPORT, vp);
	glGetDoublev(GL_MODELVIEW_MATRIX, mv);
	glGetDoublev(GL_PROJECTION_MATRIX, pm);

	winX = cursor.x;
	winY = cursor.y;
	y = (float) vp[3] - winY;

	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, y, 0.0f, mv, pm, vp, &glX, &glY, &glZ);
	gluUnProject(winX, y, 1.0f, mv, pm, vp, &x2, &y2, &z2);

	CString str;
	str.Format("%f, %f, %f", glX-x2, glY-y2, glZ-z2);
	AfxMessageBox(str);
*/

//	nRotate =1;  //0=fix, 1=Rotate, 
//	m_xRotate = m_xRotate+300.0;
//	m_xRotate=(double)point.y*30000.0;
//	m_yRotate=(double)point.x*30000.0;
//
//	GLRenderScene();
//	SwapBuffers(m_hDC);

/*
	if (issetorigin == 1) //no need anymore
	{
		if (oclickcount == 2)
		{
		pyy = (float)point.y;
		oclickcount += 1;
		issetorigin = 0;
		}

		if (oclickcount == 1)
		{
		pxx = (float)point.x;
		oclickcount += 1;
		}
		

		if (oclickcount == 0)
		{
		pox = (float)point.x;
		poy = (float)point.y;
		oclickcount += 1;
		}

		if (oclickcount == 3)
		{
		oclickcount = 0;
		issetorigin = 0;
		}
	
	}*/

	if (issetorigin == 1) //no need anymore
	{
		relx = 0.0;
		rely = 0.0;
		issetorigin = 0;
	}
	

	selx1 = glcrossx-relx;
	sely1 = glcrossy-rely;
	selx2 = glcrossx-relx;
	sely2 = glcrossy-rely;
	



	
	isselon = 1;

	if (selx1 < -relx) selx1 = -relx;
	if (sely1 < -rely) sely1 = -rely;

	

	islocatedomain = 0;


	CView::OnLButtonDown(nFlags, point);
}

void CMFCGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

//	nRotate =0;  //0=fix, 1=Rotate, 

	graphavgmode =0;
	isgraphx = 0;
	isgraphy = 0;

	selx1 = 0.0f;
	sely1 = 0.0f;
	selx2 = 0.0f;
	sely1 = 0.0f;
	isselon = 0;
GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());
	CView::OnLButtonUp(nFlags, point);
}

void CMFCGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

		int    vp[4];
	double mv[16], pm[16];
	float  winX, winY, winZ;
	double glX, glY, glZ;
	CPoint cursor;

	GetCursorPos(&cursor);
	ScreenToClient(&cursor);

	glGetIntegerv(GL_VIEWPORT, vp);
	glGetDoublev(GL_MODELVIEW_MATRIX, mv);
	glGetDoublev(GL_PROJECTION_MATRIX, pm);

	winX = cursor.x;
	winY = cursor.y;

	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, 0.0f, mv, pm, vp, &glX, &glY, &glZ);
	
	glcrossx = 4.0*(glX-3.002)/meshzoom;
	glcrossy = 4.0*(-glY+1.627)/meshzoom;


//	CString str;
//  str.Format("%f, %f, %f", glX, glY, glZ);
//	AfxMessageBox(str);


//	glcrossx = (point.x-pox)/(pxx-pox);
//	glcrossy = (point.y-poy)/(pyy-poy);



	if (isselon == 1)
	{
		//selx2 = (1.0f-(float)point.x/psizex)*8.0;
		//sely2 = (1.0f-(float)point.y/psizey)*4.0;

		selx2 = glcrossx-relx;
		sely2 = glcrossy-rely;

		if (selx2 < -relx) selx2 = -relx;
		if (sely2 < -rely) sely2 = -rely;


		//pox pxx
		//poy pyy

		if (selx1 > selx2)
		{
			selxMax = selx1;
			selxMin = selx2;
		}else
		{
			selxMax = selx2;
			selxMin = selx1;
		}

		if (sely1 > sely2)
		{
			selyMax = sely1;
			selyMin = sely2;
		}else
		{
			selyMax = sely2;
			selyMin = sely1;
		}


		//selx2 = selx2*meshzoom;
		//sely2 = sely2*meshzoom;
	}

	if (islocatedomain == 1)
	{
		offsetx[ndom-2] =glcrossx-1.0;
		offsety[ndom-2] =glcrossy-1.0;
	}


GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());

//	CView::OnMouseMove(nFlags, point);
}

void CMFCGLView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	graphavgmode =0;

	float testx,testy;

	testx = point.x;
	testy = point.y;
	
	if ( psizex/2.0f > point.x) // not necessary
	{
	//	relx += 1.0f;
	}else
	{
	//	relx -= 1.0f;
	}
	
	if ( psizey/2.0f > point.y)
	{
	//	rely += 1.0f;
	}else
	{
	//	rely -= 1.0f;
	}
	//psizex
	//psizey

	OnSelData();

	
	isgraphx = 0;
	isgraphy = 0;


	//timestep = timestep+1;
	//if (timestep >= totaltimesteps) timestep = 0;
GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());

	CView::OnRButtonDown(nFlags, point);
}

void CMFCGLView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//OMPTest();
	
	if (nRotate == 0)
	{
		timestep = timestep+1;
		if (timestep >= totaltimesteps) 
		{
			timestep = 0;
			//meshmode = 1;
			//OnAutoStop();
			GLRenderScene(); 
		}
	}
	
	
	//GLRenderScene(); 
	GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());


	CView::OnTimer(nIDEvent);

}

void CMFCGLView::OMPTest()
{

	
	double  duration;

	// Get the number of processors in this system
	//iCPU = omp_get_num_procs();

	//iCPU = 1;
	// Now set the number of threads
	//omp_set_num_threads(iCPU);
	
	start = clock();

		//#pragma omp parallel for
		for(int y = 0; y < 10000; y++) 
		{ 
		for(int x = 0; x< 10000; x++) 
			{ 
			} 
		}

	yvar = yvar +1;
	xvar = xvar +1;
	if (xvar > 100) xvar =10;
	if (yvar > 100) yvar =10;
	//m_xRotate=m_xRotate+10.0;
	//m_yRotate=m_yRotate+10.0;

	GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());


	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;

}

void CMFCGLView::OnAutoRun()
{
	// TODO: Add your command handler code here
	
	SetTimer(1,finterval,NULL);
	isRun=1;
}

void CMFCGLView::OnAutoStop()
{
	// TODO: Add your command handler code here
	KillTimer(1);
	timestep = 0;
//	meshmode = 1;

	GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());

//	isRun=0;
//	nmultimap = 0;
//	ndom = 1;
}

void CMFCGLView::OnAutoSinglecpu()
{
	// TODO: Add your command handler code here
	iCPU = 1;
}

void CMFCGLView::OnAutoAddcpu()
{
	// TODO: Add your command handler code here
	//int max = omp_get_num_procs();
	iCPU = iCPU + 1;
	if (iCPU == max) iCPU =max;
}

void CMFCGLView::OnAutoMaxcpu()
{
	// TODO: Add your command handler code here
	//iCPU = omp_get_num_procs();
}

void CMFCGLView::OnAutoRemovecpu()
{
	// TODO: Add your command handler code here
	iCPU = iCPU - 1;
	if (iCPU ==0 ) iCPU =1;
}

void CMFCGLView::OnUpdateCpuSingle(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here

	//if (iCPU ==1 ) 	{		pCmdUI->SetCheck(TRUE);	}	else	{		pCmdUI->SetCheck(FALSE);	}

}

void CMFCGLView::OnCpuSingle()
{
	// TODO: Add your command handler code here
	//int max = omp_get_num_procs();
	iCPU = 1;
	if (iCPU >= max) iCPU =max;
	
	nElement = 24;
	totaltimesteps = 2000;
	finterval = 50; //ms

}

void CMFCGLView::OnUpdateCpuDual(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//if (iCPU ==2 ) 	{		pCmdUI->SetCheck(TRUE);	}	else	{		pCmdUI->SetCheck(FALSE);	}
}

void CMFCGLView::OnCpuDual()
{
	// TODO: Add your command handler code here
	//int max = omp_get_num_procs();
	iCPU = 2;
	if (iCPU >= max) iCPU =max;


	nElement = 206;
	totaltimesteps = 16;
	finterval = 500.0; //ms
}

void CMFCGLView::OnCpuQuad()
{
	// TODO: Add your command handler code here
	//int max = omp_get_num_procs();
	iCPU = 4;
	if (iCPU >= max) iCPU =max;
}

void CMFCGLView::OnUpdateCpuQuad(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//if (iCPU ==4 ) 	{		pCmdUI->SetCheck(TRUE);	}	else	{		pCmdUI->SetCheck(FALSE);	}
}


void CMFCGLView::OnCpuI7()
{
	// TODO: Add your command handler code here
	//int max = omp_get_num_procs();
	iCPU = 8;
	if (iCPU >= max) iCPU =max;
}

void CMFCGLView::OnUpdateCpuI7(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//if (iCPU ==8 ) 	{		pCmdUI->SetCheck(TRUE);	}	else	{		pCmdUI->SetCheck(FALSE);	}
}

void CMFCGLView::OnUpdateAutoRun(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
	if (isRun==1) pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CMFCGLView::OnFileOpen()
{


	meshmode = 1; //meshmode off

	CFileDialog dlg(TRUE);
	dlg.DoModal();

	if (dlg.GetFileName() == "")
	{
		return;
	}

	CString temp,tmpnum,tmpcut;
	CString sp('A');

	temp = dlg.GetPathName();


	m_rfile.Open(temp,CFile::modeRead | CFile::shareDenyWrite);
	int ntempl;

	m_rfile.ReadString(temp); //pass 1st line column header

	

	if (temp.Find("element_index") != 0)
	{
		m_rfile.Close();
		AfxMessageBox("Not a mesh file!");
		return;
	}
	//ntempl = temp.GetLength();
//	m_rfile.ReadString(temp); //pass 1st line column header
//	m_rfile.ReadString(temp); //pass 1st line column header

	for(int ii = 0; ii<50000 ; ii++)  // maximum element number 50000
	{

	bool fileendread; 

	Element[ii].Issel = 0;
	fileendread = m_rfile.ReadString(temp);
	if(fileendread==0) //reaches end 
	{
		nElement = ii;
		break; 
	}
	temp.Replace(' ','A');
	
	tmpnum = temp.Left(temp.Find(sp));
	tmpcut = temp.Left(temp.Find(sp)+2);
	Element[ii].n =  atoi(tmpnum);
	temp = temp.Right(temp.GetLength()-tmpcut.GetLength());
	
		for(int jj = 0; jj<4 ; jj++) 
		{
		tmpnum = temp.Left(temp.Find(sp));
		tmpcut = temp.Left(temp.Find(sp)+1);
		Element[ii].x[jj] = strtod(tmpnum,NULL);
		temp = temp.Right(temp.GetLength()-tmpcut.GetLength());
		
		tmpnum = temp.Left(temp.Find(sp));
		tmpcut = temp.Left(temp.Find(sp)+1);
		Element[ii].y[jj] = strtod(tmpnum,NULL);
		temp = temp.Right(temp.GetLength()-tmpcut.GetLength());

		tmpnum = temp.Left(temp.Find(sp));
		tmpcut = temp.Left(temp.Find(sp)+1);
		Element[ii].z[jj] = strtod(tmpnum,NULL);
		temp = temp.Right(temp.GetLength()-tmpcut.GetLength());

		}

		Element[ii].cx = 0.25*(Element[ii].x[0] + Element[ii].x[1] + Element[ii].x[2] + Element[ii].x[3]);
		Element[ii].cy = 0.25*(Element[ii].y[0] + Element[ii].y[1] + Element[ii].y[2] + Element[ii].y[3]);

	
		tmpnum = temp.Left(temp.Find(sp));
		tmpcut = temp.Left(temp.Find(sp)+1);
		Element[ii].volume = strtod(tmpnum,NULL);
		temp = temp.Right(temp.GetLength()-tmpcut.GetLength());


		tmpnum = temp;
		//tmpcut = temp.Left(temp.Find(sp)+1);
		Element[ii].deltaZ = strtod(tmpnum,NULL);
		//temp = temp.Right(temp.GetLength()-tmpcut.GetLength());

	}

	m_rfile.Close();
	
GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());


}

void CMFCGLView::OnAdddataAdddata()
{


	if (nmultimap == 3) 
	{
		AfxMessageBox("Limited to the 3 molecules types in one window");
		return;
	}
	
	if (nElement == 0) 
	{
		AfxMessageBox("Open a mesh file first!");
		return;
	}

	meshmode = 0; //meshmode off
	timestep = 0;

	CFileDialog dlg(TRUE);
	dlg.DoModal();

	if (dlg.GetFileName() == "")
	{
		return;
	}

	CString temp,tmpnum,tmpcut;
	CString sp('$');

	temp = dlg.GetPathName();

	//	struct Element_Data            // Declare PERSON struct type
//	{
//	double   data[206];              // Declare member types
//	CString  strdata[206];             // 
//	};      

//	Element_Data Edata[5][16]; //[molecule type][timestep]

	m_rfile.Open(temp,CFile::modeRead | CFile::shareDenyWrite);
	int ntempl;

	m_rfile.ReadString(temp); //1st line column header need to get dend number and molecule name

		if (temp.Find("time") != 0)
	{
		m_rfile.Close();
		AfxMessageBox("Not a molecule data file!");
		return;
	}


	//ntempl = temp.GetLength();
	temp.Replace(' ','$');

	///////////////////////////////////for 1 molecule speces with many timesteps
	for(int ii = 0; ii<nElement+1 ; ii++)  //get 1st column string data //nElement+1 since 1st column is timesteps
	{
		tmpnum = temp.Left(temp.Find(sp));
		if (ii > 0) strinfo[ii-1] = tmpnum; 
		tmpcut = temp.Left(temp.Find(sp)+1);
//		Element[ii].n =  _wtoi(tmpnum);
		//Edata[nmultimap][15].strdata[ii] = tmpnum;
		temp = temp.Right(temp.GetLength()-tmpcut.GetLength());  //why am i doing this? for head information!!1
	}

	fmax[nmultimap] = -1000000000000000.0f;
	fmin[nmultimap] = 1000000000000000.0f;

	//fmin for base and fmax for normalization.

	avgnormal = 0.0;
	avgnormalcount = 1.0;

	for(int jj = 0; jj<80000 ; jj++)  //get 1st column string data //nElement+1 since 1st column is timesteps
	{
		bool stependread;

		stependread = m_rfile.ReadString(temp);
		if(stependread==0) //reaches end 
		{
			totaltimesteps = jj;
			break; 
		}

		temp.Replace(' ','$');

		for(int ii = 0; ii<nElement+1 ; ii++)  // element +1 because 1st column is timestep //get number data need to exculde 0 th because it is timestep
		{
			tmpnum = temp.Left(temp.Find(sp));
			tmpcut = temp.Left(temp.Find(sp)+1);
			if (isdatanumberofmolecule == 0) Edata[nmultimap][jj].data[ii]=  atof(tmpnum); //float for concentration
			if (isdatanumberofmolecule == 1) Edata[nmultimap][jj].data[ii]=  (double)atoi(tmpnum); //integer for concentration
				if (ii != 0)
				{
					if (Edata[nmultimap][jj].data[ii] > fmax[nmultimap]) fmax[nmultimap] = Edata[nmultimap][jj].data[ii];
					if (Edata[nmultimap][jj].data[ii] < fmin[nmultimap]) fmin[nmultimap] = Edata[nmultimap][jj].data[ii];
					
					if (Edata[nmultimap][jj].data[ii] != 0.0)
					{
					avgnormal = avgnormal + Edata[nmultimap][jj].data[ii]; //I am not using this.
					avgnormalcount = avgnormalcount + 1.0;
					}	
				}
			temp = temp.Right(temp.GetLength()-tmpcut.GetLength());
		}
	}


	//fmax[nmultimap] = 3.0*avgnormal/avgnormalcount;

	/*
	if (nmultimap == 0)
	{
		fmax[nmultimap] = (fmax[nmultimap]-fmin[nmultimap])*0.2 + fmin[nmultimap];
	}
	if (nmultimap == 1)
	{
		fmax[nmultimap] = (fmax[nmultimap]-fmin[nmultimap])*0.2 + fmin[nmultimap];
	}
	if (nmultimap == 2)
	{
		fmax[nmultimap] = (fmax[nmultimap]-fmin[nmultimap])*0.45 + fmin[nmultimap]; // for Ip35pp1
		fmin[nmultimap] = (fmax[nmultimap]-fmin[nmultimap])*0.25 + fmin[nmultimap];
	}

	*/


	///////////////////////////////////for 1 molecule speces with many timesteps - end

	m_rfile.Close();
	
GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());

	nmultimap =  nmultimap+1;
	if (nmultimap == 0) ndom = 1;
	if (nmultimap == 1) ndom = 1;
	if (nmultimap == 2) ndom = 2;
	if (nmultimap == 3) ndom = 3;

	if (ndom != 1)islocatedomain = 1;

}

void CMFCGLView::OnSelData()
{

//	for(int ii = 60; ii<160 ; ii++) 
//	{
//	Element[ii].Issel = 1;
//	}

	isselon = 0;

	for(int ii = 0; ii<nElement ; ii++) 
	{
	Element[ii].Issel = 0;
	}

	
	selx1 = 0.0f;
	sely1 = 0.0f;
	selx2 = 0.0f;
	sely1 = 0.0f;
	nSelected = 0;

		
	isgraphx = 0;
	isgraphy = 0;


GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());
	// TODO: Add your command handler code here
}

void CMFCGLView::OnSelInitialize()
{
	for(int ii = 0; ii<nElement ; ii++) 
	{
	Element[ii].Issel = 0;
	}
	// TODO: Add your command handler code here

	m_xRotate=0.0;
	m_yRotate=0.0;
	m_zRotate=0.0;
	m_zTranslate = 0.0;
	nRotate = 0;

	isgraphx = 0;
	isgraphy = 0;

	
	selx1 = 0.0f;
	sely1 = 0.0f;
	selx2 = 0.0f;
	sely1 = 0.0f;

	relx = 0.0f;
	rely = 0.0f;

	meshzoom = 1.0;

	OnAutoStop();
GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());
}

BOOL CMFCGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	//m_zTranslate +=0.2*zDelta/WHEEL_DELTA;

	meshzoom+=0.010*zDelta/WHEEL_DELTA;



	if (meshzoom < 0.2f) meshzoom = 0.2f;


	int    vp[4];
	double mv[16], pm[16];
	float  winX, winY, winZ;
	double glX, glY, glZ;
	CPoint cursor;

	GetCursorPos(&cursor);
	ScreenToClient(&cursor);

	glGetIntegerv(GL_VIEWPORT, vp);
	glGetDoublev(GL_MODELVIEW_MATRIX, mv);
	glGetDoublev(GL_PROJECTION_MATRIX, pm);

	winX = cursor.x;
	winY = cursor.y;

	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, 0.0f, mv, pm, vp, &glX, &glY, &glZ);
	
	glcrossx = 4.0*(glX-3.002)/meshzoom;
	glcrossy = 4.0*(-glY+1.627)/meshzoom;

	//GLRenderScene(); 
GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMFCGLView::OnSelRotate()
{

	nRotate = 1;
//	nElement = 0;
	SetTimer(1,50,NULL);
	// TODO: Add your command handler code here
}

void CMFCGLView::OnGraphX()
{

		graphavgmode = graphavgmode +1;
	if (graphavgmode == 2) graphavgmode =0;


	avgmax = 0.0;
	spatialmax = -1.0;

	if (graphavgmode == 1)
	{
		if (nSelected == 0) 
		{
			
			AfxMessageBox("No subdomain selected!");
			graphavgmode =0;
			return;
		}
	
	}

	graphavgmode =0;

	// TODO: Add your command handler code here
	CString temp;
	//char buffer[20];

	


	nSelected = 0;
	for(int ii = nEstart; ii<nElement ; ii++) 
	{
		if(Element[ii].Issel == 1)
		{
			selectmap[nSelected] = ii;
			nSelected = nSelected+1;
		}
	}



	for(int ii = 0; ii<1000 ; ii++) 
	{
		xyout[ii].cord = -1000.0;
		xyout[ii].datasum = 0.0f;
		xyout[ii].numberadd = 0.0f;
	}

	//now lets do grid sorting into xyout.

	//간단하게 일단 좌표 먼저 한번 정리해서 플롯 데이타에 넣자.

	int isfoundcord = 0;
	ncord = 0;


	for(int ii = 0; ii<nSelected ; ii++) 
	{
		for(int jj = 0; jj<1000 ; jj++) 
		{
			if ((float)xyout[jj].cord == (float)Element[selectmap[ii]].cx) //저장된 좌표와 엘리먼트 좌표가 일치하면
			{
				isfoundcord = 1;
		
				selmaptocord[ii] = jj;// mapping
		
			}
		}

		if (isfoundcord == 0) //찾았으면 그냥 중붹이니 넘어가고  // 못찾았으면 새코드에 추가한다
		{
		 xyout[ncord].cord = Element[selectmap[ii]].cx;
		 ncord = ncord+1;
			
		 selmaptocord[ii] = ncord-1; //maping
		}

		isfoundcord = 0;
	}
 



//	char buffer1[20];
//	char buffer2[20];

	m_wfile.Open("VNRD_selmap.txt",CFile::modeCreate | CFile::modeWrite); // fix here

	_itoa(nSelected, buffer, 10 );
	temp = CString(buffer);
	m_wfile.WriteString(temp);  //Write Number of selected cells
	m_wfile.WriteString("\n"); 
	m_wfile.WriteString("\n"); 

	for(int ii = 0; ii<nSelected ; ii++) 
	{

//		_itoa(ii, buffer, 10 );
//		temp = CString(buffer);
//		m_wfile.WriteString(temp);  //Write Number of selected cells
//		m_wfile.WriteString("\n");

		_itoa(selmaptocord[ii], buffer, 10 );
		temp = CString(buffer);
		m_wfile.WriteString(temp);  //mapping to grid
		m_wfile.WriteString("\n");

		_itoa(selectmap[ii], buffer, 10 );
		temp = CString(buffer);
		m_wfile.WriteString(temp);  //corresponding element number
		m_wfile.WriteString("\n");

		temp.Format("%lf",Element[selectmap[ii]].cx);
		m_wfile.WriteString(temp);  //corresponding element x coordi
		m_wfile.WriteString("\n");

		temp.Format("%lf",Element[selectmap[ii]].cy);
		m_wfile.WriteString(temp);  //corresponding element number
		m_wfile.WriteString("\n");

		temp.Format("%lf",Element[selectmap[ii]].volume);
		m_wfile.WriteString(temp);  //corresponding element number
		m_wfile.WriteString("\n");

		m_wfile.WriteString("\n");

	}

	m_wfile.Close();

	//m_wfile.Open(dlg.GetFileName(),CFile::modeCreate | CFile::modeWrite);
	m_wfile.Open("VNRD_xgraph.txt",CFile::modeCreate | CFile::modeWrite);

	_itoa(nSelected, buffer, 10 );
	temp = CString(buffer);
	m_wfile.WriteString(temp);  //Write Number of selected cells
	m_wfile.WriteString("\n"); 
	m_wfile.WriteString("\n"); 
	
	for(int ii = nEstart; ii<nElement ; ii++) 
	{
		if(Element[ii].Issel == 1) 
		{
				_itoa(Element[ii].n, buffer, 10 );
				temp = CString(buffer);
				m_wfile.WriteString(temp);  //Write Number of selected cells
				m_wfile.WriteString("\n") ;

				temp.Format("%lf",Element[ii].cx);
				m_wfile.WriteString(temp);  //Write Number of selected cells
				m_wfile.WriteString("\n");

				temp.Format("%lf",Element[ii].cy);
				m_wfile.WriteString(temp);  //Write Number of selected cells
				m_wfile.WriteString("\n") ;
				m_wfile.WriteString("\n"); 
		}

	}
	m_wfile.Close();

		//now lets do grid sorting into xyout.
	//sort는 일단 유닉스용 코드 출력하고 나서 하는걸로 하자. 유닉스용은 건들면 매핑까지 건드려야 되서 많이 복잡.
	//화면출력용으로는 그냥 윈도에서 하는걸로 충분함.
	//유닉스버전과 비교를 위해서는 이 소팅부분 커맨트처리 필요.
	//혹은 나중에 유닉스버전을 윈도버전과 동일하게 고치는거도 좋은 생각임..
	//왜냐면 이제 메시 파일을 읽으므로 간단하게 할수있음. 하지만 일단 나중문제.

	  bool swapped = true;
      int j = 0;
	  float tmp;
      while (swapped) 
	  {
            swapped = false;
            j++;
            for (int i = 0; i < ncord - j; i++) {
                  if (xyout[i].cord > xyout[i+1].cord) {
                        tmp = xyout[i].cord;
                        xyout[i].cord = xyout[i+1].cord;
                        xyout[i+1].cord = tmp;
                        swapped = true;
                  }
            }
      }

	  //!! 유닉스버전하고 결과비교시 소트는 제거하세요



	isgraphx = 1;
	//nSelected = 0;
	//for finding maximum for spatial average -end
	
	for(int jj = 0; jj<totaltimesteps ; jj++)
	{
		timestep = jj;

		sortintoxdirection();

			for(int ii = 0; ii<ncord ; ii++)  // get the average
				{
					if (xyout[ii].datasum > spatialmax) spatialmax = xyout[ii].datasum;
				}
	}
	timestep = 0;
	//for finding maximum for spatial average -end


	AfxMessageBox("VNRD_selmap.txt created!");

	GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());
}

void CMFCGLView::OnGraphY()
{

		graphavgmode = graphavgmode +1;
	if (graphavgmode == 2) graphavgmode =0;


	avgmax = 0.0;
	spatialmax = -1.0;

	if (graphavgmode == 1)
	{
		if (nSelected == 0) 
		{
			
			AfxMessageBox("No subdomain selected!");
			graphavgmode =0;
			return;
		}
	
	}

	graphavgmode =0;

	// TODO: Add your command handler code here
	CString temp;
	//char buffer[20];

	


	nSelected = 0;
	for(int ii = nEstart; ii<nElement ; ii++) 
	{
		if(Element[ii].Issel == 1)
		{
			selectmap[nSelected] = ii;
			nSelected = nSelected+1;
		}
	}



	for(int ii = 0; ii<1000 ; ii++) 
	{
		xyout[ii].cord = -1000.0;
		xyout[ii].datasum = 0.0f;
		xyout[ii].numberadd = 0.0f;
	}

	
	//간단하게 일단 좌표 먼저 한번 정리해서 플롯 데이타에 넣자.

	int isfoundcord = 0;
	ncord = 0;


	for(int ii = 0; ii<nSelected ; ii++) 
	{
		for(int jj = 0; jj<1000 ; jj++) 
		{
			if ((float)xyout[jj].cord == (float)Element[selectmap[ii]].cy) //저장된 y좌표와 엘리먼트 y좌표가 일치하면
			{
				isfoundcord = 1;
		
				selmaptocord[ii] = jj;// mapping
		
			}
		}

		if (isfoundcord == 0) //찾았으면 그냥 중붹이니 넘어가고  // 못찾았으면 새코드에 추가한다
		{
		 xyout[ncord].cord = Element[selectmap[ii]].cy;
		 ncord = ncord+1;
			
		 selmaptocord[ii] = ncord-1; //maping
		}

		isfoundcord = 0;
	}

//	char buffer1[20];
//	char buffer2[20];

	m_wfile.Open("VNRD_selmap.txt",CFile::modeCreate | CFile::modeWrite); // fix here

	_itoa(nSelected, buffer, 10 );
	temp = CString(buffer);
	m_wfile.WriteString(temp);  //Write Number of selected cells
	m_wfile.WriteString("\n"); 
	m_wfile.WriteString("\n"); 

	for(int ii = 0; ii<nSelected ; ii++) 
	{

//		_itoa(ii, buffer, 10 );
//		temp = CString(buffer);
//		m_wfile.WriteString(temp);  //Write Number of selected cells
//		m_wfile.WriteString("\n");

		_itoa(selmaptocord[ii], buffer, 10 );  //sorted coordinat order
		temp = CString(buffer);
		m_wfile.WriteString(temp);  //mapping to grid
		m_wfile.WriteString("\n");

		_itoa(selectmap[ii], buffer, 10 );
		temp = CString(buffer);
		m_wfile.WriteString(temp);  //corresponding element number
		m_wfile.WriteString("\n");

		temp.Format("%lf",Element[selectmap[ii]].cx);
		m_wfile.WriteString(temp);  //corresponding element x coordi
		m_wfile.WriteString("\n");

		temp.Format("%lf",Element[selectmap[ii]].cy);
		m_wfile.WriteString(temp);  //corresponding element number
		m_wfile.WriteString("\n");

		temp.Format("%lf",Element[selectmap[ii]].volume);
		m_wfile.WriteString(temp);  //corresponding element number
		m_wfile.WriteString("\n");

		m_wfile.WriteString("\n");

	}

	m_wfile.Close();

	//m_wfile.Open(dlg.GetFileName(),CFile::modeCreate | CFile::modeWrite);
	m_wfile.Open("VNRD_ygraph.txt",CFile::modeCreate | CFile::modeWrite);

	_itoa(nSelected, buffer, 10 );
	temp = CString(buffer);
	m_wfile.WriteString(temp);  //Write Number of selected cells
	m_wfile.WriteString("\n"); 
	m_wfile.WriteString("\n"); 
	
	for(int ii = nEstart; ii<nElement ; ii++) 
	{
		if(Element[ii].Issel == 1) 
		{
				_itoa(Element[ii].n, buffer, 10 );
				temp = CString(buffer);
				m_wfile.WriteString(temp);  //Write Number of selected cells
				m_wfile.WriteString("\n") ;

				temp.Format("%lf",Element[ii].cx);
				m_wfile.WriteString(temp);  //Write Number of selected cells
				m_wfile.WriteString("\n");

				temp.Format("%lf",Element[ii].cy);
				m_wfile.WriteString(temp);  //Write Number of selected cells
				m_wfile.WriteString("\n") ;
				m_wfile.WriteString("\n"); 
		}

	}
	m_wfile.Close();

	//now lets do grid sorting into xyout.
	//sort는 일단 유닉스용 코드 출력하고 나서 하는걸로 하자. 유닉스용은 건들면 매핑까지 건드려야 되서 많이 복잡.
	//화면출력용으로는 그냥 윈도에서 하는걸로 충분함.
	//유닉스버전과 비교를 위해서는 이 소팅부분 커맨트처리 필요.
	//혹은 나중에 유닉스버전을 윈도버전과 동일하게 고치는거도 좋은 생각임..
	//왜냐면 이제 메시 파일을 읽으므로 간단하게 할수있음. 하지만 일단 나중문제.

	//!! 유닉스버전하고 결과비교시 소트는 제거하세요

      bool swapped = true;
      int j = 0;
	  float tmp;
      while (swapped) 
	  {
            swapped = false;
            j++;
            for (int i = 0; i < ncord - j; i++) {
                  if (xyout[i].cord > xyout[i+1].cord) {
                        tmp = xyout[i].cord;
                        xyout[i].cord = xyout[i+1].cord;
                        xyout[i+1].cord = tmp;
                        swapped = true;
                  }
            }
      }




	isgraphy = 1;
	//nSelected = 0;
	//for finding maximum for spatial average -end
	
	for(int jj = 0; jj<totaltimesteps ; jj++)
	{
		timestep = jj;

		sortintoydirection();

			for(int ii = 0; ii<ncord ; ii++)  // get the average
				{
					if (xyout[ii].datasum > spatialmax) spatialmax = xyout[ii].datasum;
				}
	}
	timestep = 0;
	//for finding maximum for spatial average -end


	AfxMessageBox("VNRD_selmap.txt created!");

	GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());
}

void CMFCGLView::OnSetOrigin()
{
	// TODO: Add your command handler code here
	issetorigin = 1;
	relx = 0.0;
	rely = 0.0;
	GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());

}

void CMFCGLView::sortintoxdirection(void)
{

	// subroutine of OnGraphX()

	CString temp;
	//char buffer[20];


	for(int ii = 0; ii<ncord ; ii++)  // get the average
	{
	
			xyout[ii].datasum = 0.0f; 
			xyout[ii].numberadd = 0.0f; 
			xyout[ii].volumesum = 0.0f; 

	}

					

	for(int ii = 0; ii<nSelected ; ii++) 
	{
		//Element[selectmap[ii]].cx
		for(int jj = 0; jj<1000 ; jj++) 
		{
			if ((float)xyout[jj].cord == (float)Element[selectmap[ii]].cx) //저장된 좌표와 엘리먼트 좌표가 일치하면
			{
				if (isdatanumberofmolecule == 0) //concentration
				{
					xyout[jj].datasum = xyout[jj].datasum + Edata[0][timestep].data[selectmap[ii]+1]*(float)Element[selectmap[ii]].volume;//저장된 좌표에 해당 엘리먼트 데이타 추가 selectmap[ii]+1!!!!!!
					// data memebr는 첫 컬럼의 0th맴버가 타임스탭임.. 그래서 +1 필요
				}
				if (isdatanumberofmolecule == 1)
				{
					xyout[jj].datasum = xyout[jj].datasum + Edata[0][timestep].data[selectmap[ii]+1];//저장된 좌표에 해당 엘리먼트 데이타 추가 selectmap[ii]+1!!!!!!
				}

		

				xyout[jj].numberadd = xyout[jj].numberadd +1.0; //나중에 나누기 1()하나더 추가
				xyout[jj].volumesum = xyout[jj].volumesum + (float)Element[selectmap[ii]].volume; //나중에 나누기 1()하나더 추가
				//(float)Element[selectmap[ii]].volume;
			}
		}
	}




	for(int ii = 0; ii<ncord ; ii++)  // get the average
	{
	
		
		//if (isdatanumberofmolecule == 0) xyout[ii].datasum = xyout[ii].datasum / xyout[ii].volumesum; 
		//if (isdatanumberofmolecule == 1) xyout[ii].datasum = xyout[ii].datasum; // in case of number of molecule, just show total molecules !no final output is always concentration
		xyout[ii].datasum = xyout[ii].datasum / xyout[ii].volumesum; 
		//final output is always in concentration
	}

}

void CMFCGLView::sortintoydirection(void)
{
	
	// subroutine of OnGraphX()

	CString temp;
	//char buffer[20];


	for(int ii = 0; ii<ncord ; ii++)  // get the average
	{
	
			xyout[ii].datasum = 0.0f; 
			xyout[ii].numberadd = 0.0f; 
			xyout[ii].volumesum = 0.0f; 

	}

					

	for(int ii = 0; ii<nSelected ; ii++) 
	{
		//Element[selectmap[ii]].cy
		for(int jj = 0; jj<1000 ; jj++) 
		{
			if ((float)xyout[jj].cord == (float)Element[selectmap[ii]].cy) //저장된 좌표와 엘리먼트 좌표가 일치하면
			{
				if (isdatanumberofmolecule == 0) //concentration
				{
					xyout[jj].datasum = xyout[jj].datasum + Edata[0][timestep].data[selectmap[ii]+1]*(float)Element[selectmap[ii]].volume;//저장된 좌표에 해당 엘리먼트 데이타 추가 selectmap[ii]+1!!!!!!
					// data memebr는 첫 컬럼의 0th맴버가 타임스탭임.. 그래서 +1 필요
				}
				if (isdatanumberofmolecule == 1)
				{
					xyout[jj].datasum = xyout[jj].datasum + Edata[0][timestep].data[selectmap[ii]+1];//저장된 좌표에 해당 엘리먼트 데이타 추가 selectmap[ii]+1!!!!!!
				}

		

				xyout[jj].numberadd = xyout[jj].numberadd +1.0; //나중에 나누기 1()하나더 추가
				xyout[jj].volumesum = xyout[jj].volumesum + (float)Element[selectmap[ii]].volume; //나중에 나누기 1()하나더 추가
				//(float)Element[selectmap[ii]].volume;
			}
		}
	}




	for(int ii = 0; ii<ncord ; ii++)  // get the average
	{
	
		
		//if (isdatanumberofmolecule == 0) xyout[ii].datasum = xyout[ii].datasum / xyout[ii].volumesum; 
		//if (isdatanumberofmolecule == 1) xyout[ii].datasum = xyout[ii].datasum; // in case of number of molecule, just show total molecules !no final output is always concentration
		xyout[ii].datasum = xyout[ii].datasum / xyout[ii].volumesum; 
		//final output is always in concentration
	}

}

void CMFCGLView::OnDialogboxParameters()
{
	// TODO: Add your command handler code here

	//	nElement = 1362;
//	totaltimesteps = 1000;
//	finterval = 100; //ms
    //navg = 3;
	CParamDlg m_ParamDlg;

	m_ParamDlg.nElement = nElement;
	m_ParamDlg.totaltimesteps = totaltimesteps;
	m_ParamDlg.finterval = (int)finterval;
	m_ParamDlg.navg = navg;

	m_ParamDlg.graph_base = graph_base;
	m_ParamDlg.graph_max = graph_max;
	m_ParamDlg.useravgmax = useravgmax;

	m_ParamDlg.isdatanumberofmolecule = isdatanumberofmolecule;

	m_ParamDlg.DoModal();

	nElement= 	m_ParamDlg.nElement;
	totaltimesteps = m_ParamDlg.totaltimesteps;
	finterval = (float)m_ParamDlg.finterval;
	navg = m_ParamDlg.navg;
	
	graph_base = m_ParamDlg.graph_base; 
	graph_max = m_ParamDlg.graph_max;
	useravgmax = m_ParamDlg.useravgmax;

	isdatanumberofmolecule = m_ParamDlg.isdatanumberofmolecule;

}


void CMFCGLView::OnAutoFastforward()
{
	// TODO: Add your command handler code here
	timestep = timestep + 50;
	if (timestep > totaltimesteps) timestep=totaltimesteps;
	GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());
}

void CMFCGLView::OnAutoRewind()
{
	// TODO: Add your command handler code here
	timestep = timestep - 50;

	if (timestep < 0) timestep=0.0;
	GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());
}

void CMFCGLView::OnAutoRunsinglestep()
{
	timestep = timestep + 1;
	if (timestep > totaltimesteps) timestep=totaltimesteps;
	GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());
}

void CMFCGLView::OnAutoPause()
{
	// TODO: Add your command handler code here
		KillTimer(1);
}

void CMFCGLView::OnFileNew()
{
	// TODO: Add your command handler code here
	meshmode = 1;
	ndom = 1;
	nmultimap = 0;
	OnSelInitialize();
}

void CMFCGLView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CView::OnShowWindow(bShow, nStatus);
	BuildFont();

	// TODO: Add your message handler code here
}

void CMFCGLView::setcolorscale(void)
{
					cgreen = 0.0f;
					cblue = 0.0f;
					cred = 0.0f;

					//cred = cnormal;

	

				cred = cnormal*(1.0f/redscale);
				if (cred > 1.0f) cred = 1.0f;
						
				if (cnormal > 0.25f)
				{
					cgreen = (cnormal-redscale)*(1.0f/(yellowscale-redscale));
					if (cgreen > 1.0f) cgreen = 1.0f;
				}
				if (cnormal > 0.55)
				{
					cblue = (cnormal-yellowscale)*(1.0f/(1.0f-yellowscale));
					if (cblue > 1.0f) cblue = 1.0f;
				}


}

void CMFCGLView::OnGraphXSave()
{
	// TODO: Add your command handler code here

	if (meshmode == 1) return;
	CString temp;
	
	timestep = 0;

	m_wfile.Open("VNRD_xgraph_dataout.txt",CFile::modeCreate | CFile::modeWrite);



	
//	for(int ii = 0; ii<ncord ; ii++)  // do not print coordinate number since it is confusing.
//	{
//		_itoa(ii, buffer, 10 );
//		temp = CString(buffer);
//		m_wfile.WriteString(temp);
//		m_wfile.WriteString(" ");
//	}
//	m_wfile.WriteString("\n") ;


	for(int ii = 0; ii<ncord ; ii++)  // 1st row is coordinate
	{
		temp.Format("%lf",xyout[ii].cord);
		m_wfile.WriteString(temp);
		m_wfile.WriteString(" ");
	}
	m_wfile.WriteString("\n") ;


	
	for(int jj = 0; jj<totaltimesteps ; jj++) //print out spatial average
	{
		timestep = jj;

		sortintoxdirection();

			for(int ii = 0; ii<ncord ; ii++)  // get the average
				{
					temp.Format("%lf",xyout[ii].datasum);
					m_wfile.WriteString(temp);
					m_wfile.WriteString(" ");
				}

			m_wfile.WriteString("\n") ;
			//xyout[ii].datasum = xyout[ii].datasum / fmax[0];
	}

	timestep = 0;

	m_wfile.Close();


}

void CMFCGLView::OnGraphYSave()
{
	// TODO: Add your command handler code here

	if (meshmode == 1) return;
	CString temp;
	
	timestep = 0;

	m_wfile.Open("VNRD_ygraph_dataout.txt",CFile::modeCreate | CFile::modeWrite);



	
//	for(int ii = 0; ii<ncord ; ii++)  // do not print coordinate number since it is confusing.
//	{
//		_itoa(ii, buffer, 10 );
//		temp = CString(buffer);
//		m_wfile.WriteString(temp);
//		m_wfile.WriteString(" ");
//	}
//	m_wfile.WriteString("\n") ;


	for(int ii = 0; ii<ncord ; ii++)  // 1st row is coordinate
	{
		temp.Format("%lf",xyout[ii].cord);
		m_wfile.WriteString(temp);
		m_wfile.WriteString(" ");
	}
	m_wfile.WriteString("\n") ;


	
	for(int jj = 0; jj<totaltimesteps ; jj++)
	{
		timestep = jj;

		sortintoydirection();

			for(int ii = 0; ii<ncord ; ii++)  // get the average
				{
					temp.Format("%lf",xyout[ii].datasum);
					m_wfile.WriteString(temp);
					m_wfile.WriteString(" ");
				}

			m_wfile.WriteString("\n") ;
			//xyout[ii].datasum = xyout[ii].datasum / fmax[0];
	}

	timestep = 0;

	m_wfile.Close();


}

void CMFCGLView::OnPlotWhitegray()
{
	// TODO: Add your command handler code here

	nwhitegray = nwhitegray +1;

	if (nwhitegray == 2) nwhitegray = 0;

		GLRenderScene();

	SwapBuffers(m_pDC->GetSafeHdc());
}

void CMFCGLView::OnPlotDecreaseredgradient()
{

 redscale = redscale - 0.02f;
 	GLRenderScene();
	SwapBuffers(m_pDC->GetSafeHdc());

}

void CMFCGLView::OnPlotDecreaseyellowgradient()
{

 yellowscale = yellowscale - 0.02f;
 	GLRenderScene();
	SwapBuffers(m_pDC->GetSafeHdc());

}

void CMFCGLView::OnPlotIncreaseredgradient()
{

	redscale = redscale + 0.02f;
		GLRenderScene();
	SwapBuffers(m_pDC->GetSafeHdc());

}

void CMFCGLView::OnPlotIncreaseyellowgradient()
{
yellowscale = yellowscale + 0.02f;
	GLRenderScene();
	SwapBuffers(m_pDC->GetSafeHdc());

}

void CMFCGLView::OnPlotTranslatex()
{
	// TODO: Add your command handler code here

	relx = relx + 1.0f;

	GLRenderScene();
	SwapBuffers(m_pDC->GetSafeHdc());
}

void CMFCGLView::OnPlotTranslatey()
{
	// TODO: Add your command handler code here
	rely = rely + 1.0f;

	GLRenderScene();
	SwapBuffers(m_pDC->GetSafeHdc());

}

void CMFCGLView::OnPlotGraphAvg()
{

	double divnptonM;
	divnptonM = 0.6022141527;

	graphavgmode = graphavgmode +1;
	if (graphavgmode == 2) graphavgmode =0;


	avgmax = 0.0;

	if (graphavgmode == 1)
	{
		if (nSelected == 0) 
		{
			
			AfxMessageBox("No subdomain selected!");
			graphavgmode =0;
			return;
		}
	
	}


	if (graphavgmode == 1)
	{

//   avgdata[20000];              // Declare member types [elementnumber] <- data in

	m_wfile.Open("VNRD_Average_dataout.txt",CFile::modeCreate | CFile::modeWrite);
	CString temp;
	double tmpvolumesum;

		for(int jj = 0; jj<totaltimesteps ; jj++) 
		{
			tmpvolumesum = 0.0;
			avgdata[jj] =0.0;
			for(int ii = 0; ii<nSelected ; ii++) 
			{
				if (isdatanumberofmolecule == 0) //concentration
				{
					avgdata[jj] =avgdata[jj] + Edata[0][jj].data[selectmap[ii]+1]*(float)Element[selectmap[ii]].volume; 
					// data memebr는 첫 컬럼의 0th맴버가 타임스탭임.. 그래서 +1 필요
				}
				if (isdatanumberofmolecule == 1)
				{
					avgdata[jj] =avgdata[jj] + Edata[0][jj].data[selectmap[ii]+1]/divnptonM;
				}
				tmpvolumesum = tmpvolumesum + (float)Element[selectmap[ii]].volume; 

			}
			//avgdata[jj] = avgdata[jj]/(double)nSelected;
			//tmpvolumesum = 1.0; for test
			avgdata[jj] = avgdata[jj]/tmpvolumesum; //final output is always in concentration.


			//change case for concentration or number of molecules

			_itoa(jj, buffer, 10 );
			temp = CString(buffer);
			m_wfile.WriteString(temp);
			m_wfile.WriteString(" ");
			temp.Format("%lf",avgdata[jj]);
			m_wfile.WriteString(temp);
			m_wfile.WriteString("\n") ;

			if (avgdata[jj] > avgmax) avgmax = avgdata[jj];

		}

	m_wfile.Close();

			m_wfile.Open("VNRD_avg_selmap.txt",CFile::modeCreate | CFile::modeWrite); // fix here

			_itoa(nSelected, buffer, 10 );
			temp = CString(buffer);
			m_wfile.WriteString(temp);  //Write Number of selected cells
			m_wfile.WriteString("\n"); 
			m_wfile.WriteString("\n"); 

			for(int ii = 0; ii<nSelected ; ii++) 
			{

		//		_itoa(ii, buffer, 10 );
		//		temp = CString(buffer);
		//		m_wfile.WriteString(temp);  //Write Number of selected cells
		//		m_wfile.WriteString("\n");

				//_itoa(selmaptocord[ii], buffer, 10 );
				//temp = CString(buffer);
				m_wfile.WriteString("0");  //mapping to grid
				m_wfile.WriteString("\n");

				_itoa(selectmap[ii], buffer, 10 );
				temp = CString(buffer);
				m_wfile.WriteString(temp);  //corresponding element number
				m_wfile.WriteString("\n");

				temp.Format("%lf",Element[selectmap[ii]].cx);
				m_wfile.WriteString(temp);  //corresponding element x coordi
				m_wfile.WriteString("\n");

				temp.Format("%lf",Element[selectmap[ii]].cy);
				m_wfile.WriteString(temp);  //corresponding element number
				m_wfile.WriteString("\n");

				temp.Format("%lf",Element[selectmap[ii]].volume);
				m_wfile.WriteString(temp);  //corresponding element number
				m_wfile.WriteString("\n");

				m_wfile.WriteString("\n");

			}

			m_wfile.Close();

	}

	
	AfxMessageBox("VNRD_avg_selmap.txt created!");


	GLRenderScene();
	SwapBuffers(m_pDC->GetSafeHdc());

	// TODO: Add your command handler code here
}

void CMFCGLView::OnAutoBacksinglestep()
{
	// TODO: Add your command handler code here
	timestep = timestep - 1;

	if (timestep < 0) timestep=0.0;

		GLRenderScene();
	SwapBuffers(m_pDC->GetSafeHdc());
}

void CMFCGLView::OnPlotZoomin()
{
	// TODO: Add your command handler code here

		meshzoom+=0.050;



	if (meshzoom < 0.2f) meshzoom = 0.2f;


	int    vp[4];
	double mv[16], pm[16];
	float  winX, winY, winZ;
	double glX, glY, glZ;
	CPoint cursor;

	GetCursorPos(&cursor);
	ScreenToClient(&cursor);

	glGetIntegerv(GL_VIEWPORT, vp);
	glGetDoublev(GL_MODELVIEW_MATRIX, mv);
	glGetDoublev(GL_PROJECTION_MATRIX, pm);

	winX = cursor.x;
	winY = cursor.y;

	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, 0.0f, mv, pm, vp, &glX, &glY, &glZ);
	
	glcrossx = 4.0*(glX-3.002)/meshzoom;
	glcrossy = 4.0*(-glY+1.627)/meshzoom;

	//GLRenderScene(); 
GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());

}

void CMFCGLView::OnPlotZoomout()
{
	// TODO: Add your command handler code here

		meshzoom-=0.050;



	if (meshzoom < 0.2f) meshzoom = 0.2f;


	int    vp[4];
	double mv[16], pm[16];
	float  winX, winY, winZ;
	double glX, glY, glZ;
	CPoint cursor;

	GetCursorPos(&cursor);
	ScreenToClient(&cursor);

	glGetIntegerv(GL_VIEWPORT, vp);
	glGetDoublev(GL_MODELVIEW_MATRIX, mv);
	glGetDoublev(GL_PROJECTION_MATRIX, pm);

	winX = cursor.x;
	winY = cursor.y;

	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, 0.0f, mv, pm, vp, &glX, &glY, &glZ);
	
	glcrossx = 4.0*(glX-3.002)/meshzoom;
	glcrossy = 4.0*(-glY+1.627)/meshzoom;

	//GLRenderScene(); 
GLRenderScene(); SwapBuffers(m_pDC->GetSafeHdc());
}

void CMFCGLView::OnPlotTranslatedowny()
{
	rely = rely - 1.0f;

	if (rely < 0.0) rely = 0.0;
	
	GLRenderScene();
	SwapBuffers(m_pDC->GetSafeHdc());
}

void CMFCGLView::OnPlotTranslateleftx()
{

	relx = relx - 1.0f;
	if (relx < 0.0) relx = 0.0;

	GLRenderScene();
	SwapBuffers(m_pDC->GetSafeHdc());
}
