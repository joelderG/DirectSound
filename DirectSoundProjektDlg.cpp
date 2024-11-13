
// DirectSoundProjektDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "DirectSoundProjekt.h"
#include "DirectSoundProjektDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectSoundProjektDlg-Dialogfeld



CDirectSoundProjektDlg::CDirectSoundProjektDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIRECTSOUNDPROJEKT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectSoundProjektDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectSoundProjektDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_Test1, &CDirectSoundProjektDlg::OnBnClickedTest1)
	ON_BN_CLICKED(IDC_Stop, &CDirectSoundProjektDlg::OnBnClickedStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_264Hz, &CDirectSoundProjektDlg::OnBnClicked264hz)
	ON_BN_CLICKED(IDC_PCM, &CDirectSoundProjektDlg::OnBnClickedPcm)
	ON_BN_CLICKED(IDC_CDUR, &CDirectSoundProjektDlg::OnBnClickedCdur)
	ON_BN_CLICKED(IDC_Dreiklang, &CDirectSoundProjektDlg::OnBnClickedDreiklang)
	ON_BN_CLICKED(IDC_Ende, &CDirectSoundProjektDlg::OnBnClickedEnde)
	ON_BN_CLICKED(IDC_C, &CDirectSoundProjektDlg::OnBnClickedC)
	ON_BN_CLICKED(IDC_D, &CDirectSoundProjektDlg::OnBnClickedD)
	ON_BN_CLICKED(IDC_E, &CDirectSoundProjektDlg::OnBnClickedE)
	ON_BN_CLICKED(IDC_F, &CDirectSoundProjektDlg::OnBnClickedF)
	ON_BN_CLICKED(IDC_G, &CDirectSoundProjektDlg::OnBnClickedG)
	ON_BN_CLICKED(IDC_A, &CDirectSoundProjektDlg::OnBnClickedA)
	ON_BN_CLICKED(IDC_H, &CDirectSoundProjektDlg::OnBnClickedH)
	ON_BN_CLICKED(IDC_C2, &CDirectSoundProjektDlg::OnBnClickedC2)
END_MESSAGE_MAP()


// CDirectSoundProjektDlg-Meldungshandler

BOOL CDirectSoundProjektDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen
	if (!m_ds.Create(this))
		OnCancel();

	// create a 4 second sound buffer
	if ((lpDSBSecondary_CDUR1 = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary_264Hz = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();

	// Klavier sound buffer
	if ((lpDSBSecondary_Klavier[0] = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary_Klavier[1] = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary_Klavier[2] = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary_Klavier[3] = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary_Klavier[4] = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary_Klavier[5] = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary_Klavier[6] = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary_Klavier[7] = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();

	// Dreiklang sound buffer 
	if ((lpDSBSecondary_DreiklangC = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary_DreiklangE = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary_DreiklangG = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();

	// PCM sound buffer
	if ((lpDSBSecondary_PCM = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();

	// init major scale C
	int c = 264; //Hz
	ton[0] = c;
	ton[1] = c * 9 / 8.;
	ton[2] = c * 5 / 4.;
	ton[3] = c * 4 / 3.;
	ton[4] = c * 3 / 2.;
	ton[5] = c * 5 / 3.;
	ton[6] = c * 15 / 8.;
	ton[7] = c * 2;
	ton[8] = 0;
	// oder temperierte Stimmung
	// ton[0]= c;
	// ton[1]= c*pow(pow(2,1/12.),2);
	// ton[2]= c*pow(pow(2,1/12.),4);
	// ton[3]= c*pow(pow(2,1/12.),5);
	// ton[4]= c*pow(pow(2,1/12.),7);
	// ton[5]= c*pow(pow(2,1/12.),9);
	// ton[6]= c*pow(pow(2,1/12.),10);
	// ton[7]= c*pow(pow(2,1/12.),12);

	m_ds.GenerateSound(lpDSBSecondary_CDUR1, 0, 2, c);

	// generate C-Dur 
	m_ds.GenerateSound(lpDSBSecondary_CDUR1, 0, 1, 262);

	// generate 264 Hz
	m_ds.GenerateSound(lpDSBSecondary_264Hz, 0, 2, 264);

	// generate Klavier
	m_ds.GenerateSound(lpDSBSecondary_Klavier[0], 0, 1, ton[0]);
	m_ds.GenerateSound(lpDSBSecondary_Klavier[1], 0, 1, ton[1]);
	m_ds.GenerateSound(lpDSBSecondary_Klavier[2], 0, 1, ton[2]);
	m_ds.GenerateSound(lpDSBSecondary_Klavier[3], 0, 1, ton[3]);
	m_ds.GenerateSound(lpDSBSecondary_Klavier[4], 0, 1, ton[4]);
	m_ds.GenerateSound(lpDSBSecondary_Klavier[5], 0, 1, ton[5]);
	m_ds.GenerateSound(lpDSBSecondary_Klavier[6], 0, 1, ton[6]);
	m_ds.GenerateSound(lpDSBSecondary_Klavier[7], 0, 1, ton[7]);

	// generate Dreiklang
	m_ds.GenerateSound(lpDSBSecondary_DreiklangC, 0, 2, ton[0]);
	m_ds.GenerateSound(lpDSBSecondary_DreiklangE, 0, 2, ton[2]);
	m_ds.GenerateSound(lpDSBSecondary_DreiklangG, 0, 2, ton[4]);


	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDirectSoundProjektDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
// das minimierte Fenster mit der Maus zieht.
HCURSOR CDirectSoundProjektDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectSoundProjektDlg::OnBnClickedTest1()
{
	
}


void CDirectSoundProjektDlg::OnBnClickedStop()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	m_ds.Stop(lpDSBSecondary_CDUR1);
	m_ds.Stop(lpDSBSecondary_264Hz);
	m_ds.Stop(lpDSBSecondary_PCM);
}


void CDirectSoundProjektDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int j = 0, buffnr = 1, playpos;
	if ((playpos = m_ds.GetPlayPosition(lpDSBSecondary_CDUR1)) == -1) {
		KillTimer(1); return;
	}
	if (((playpos > 50) && (buffnr == 0)) || ((playpos < 50) && (buffnr == 1))) {
		if ((++j) == 9) { // major scale finished
			KillTimer(1);
			j = 0;
			if (!m_ds.Stop(lpDSBSecondary_CDUR1))
				return;
			return;
		}
		m_ds.GenerateSound(lpDSBSecondary_CDUR1, buffnr * 2, 2, ton[j]);
		if (buffnr == 1) buffnr = 0; // change buffer
		else buffnr = 1;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CDirectSoundProjektDlg::OnBnClicked264hz()
{
	if (!m_ds.Play(lpDSBSecondary_264Hz, true))
		OnCancel();
	SetTimer(1, 200, 0);
}


void CDirectSoundProjektDlg::OnBnClickedPcm()
{
	if (!m_ds.Play(lpDSBSecondary_PCM, true))
		OnCancel();
	m_ds.GeneratePCMSound(lpDSBSecondary_PCM, 0, 2, "sound.pcm", 0);

	SetTimer(2, 700, NULL);
}


void CDirectSoundProjektDlg::OnBnClickedCdur()
{
	if (!m_ds.Play(lpDSBSecondary_CDUR1, true))
		OnCancel();
	SetTimer(1, 700, 0);
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
}


void CDirectSoundProjektDlg::OnBnClickedDreiklang()
{
	if (!m_ds.Play(lpDSBSecondary_DreiklangC, false))
		OnCancel();
	if (!m_ds.Play(lpDSBSecondary_DreiklangE, false))
		OnCancel();
	if (!m_ds.Play(lpDSBSecondary_DreiklangG, false))
		OnCancel();
}


void CDirectSoundProjektDlg::OnBnClickedEnde()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
}


void CDirectSoundProjektDlg::OnBnClickedC()
{
	if (!m_ds.Play(lpDSBSecondary_Klavier[0], false))
		OnCancel();
}


void CDirectSoundProjektDlg::OnBnClickedD()
{
	if (!m_ds.Play(lpDSBSecondary_Klavier[1], false))
		OnCancel();
}


void CDirectSoundProjektDlg::OnBnClickedE()
{
	if (!m_ds.Play(lpDSBSecondary_Klavier[2], false))
		OnCancel();
}


void CDirectSoundProjektDlg::OnBnClickedF()
{
	if (!m_ds.Play(lpDSBSecondary_Klavier[3], false))
		OnCancel();
}


void CDirectSoundProjektDlg::OnBnClickedG()
{
	if (!m_ds.Play(lpDSBSecondary_Klavier[4], false))
		OnCancel();
}


void CDirectSoundProjektDlg::OnBnClickedA()
{
	if (!m_ds.Play(lpDSBSecondary_Klavier[5], false))
		OnCancel();
}


void CDirectSoundProjektDlg::OnBnClickedH()
{
	if (!m_ds.Play(lpDSBSecondary_Klavier[6], false))
		OnCancel();
}


void CDirectSoundProjektDlg::OnBnClickedC2()
{
	if (!m_ds.Play(lpDSBSecondary_Klavier[7], false))
		OnCancel();
}
