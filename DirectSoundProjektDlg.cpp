
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
	if ((lpDSBSecondary1 = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary2 = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondary3 = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();

	//void* lpvPtr1, * lpvPtr2; DWORD dwBytes1, dwBytes2;
	//if (!m_ds.LockBuffer(lpDSBSecondary1, 0, 2, // we use the first 2 seconds
	//	&lpvPtr1, // get pointer 1
	//	&dwBytes1, // get bytes available there
	//	&lpvPtr2, // get pointer 2 (the buffer is circular)
	//	&dwBytes2)) // get bytes available there
	//	return false;

	//// write a sinus sound now (88040/63 = 1397 Hz)
	//DWORD i; short int* t; // points to 16 Bit
	//for (i = 0, t = (short int*)lpvPtr1; i < (dwBytes1 + dwBytes2); i += 4, t += 2) {
	//	if (i == dwBytes1) t = (short int*)lpvPtr2;
	//	// 2 channels with 16 Bit each
	//	*t = *(t + 1) = (short int)(sin(i / 10.0) * 30000);
	//}
	//if (!m_ds.UnlockBuffer(lpDSBSecondary1,
	//	lpvPtr1, // pointer 1
	//	dwBytes1, // bytes written there
	//	lpvPtr2, // pointer 2
	//	dwBytes2)) // bytes written there
	//	return false;

	m_ds.GenerateSound(lpDSBSecondary1, 0, 1, 262);
	m_ds.GenerateSound(lpDSBSecondary2, 1, 1, 330);
	m_ds.GenerateSound(lpDSBSecondary3, 2, 1, 392);

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

	m_ds.GenerateSound(lpDSBSecondary1, 0, 2, c);

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
	if (!m_ds.Play(lpDSBSecondary1, true))
		OnCancel();
	/*if (!m_ds.Play(lpDSBSecondary2, true))
		OnCancel();
	if (!m_ds.Play(lpDSBSecondary3, true))
		OnCancel();*/
	SetTimer(1, 700, 0);
}


void CDirectSoundProjektDlg::OnBnClickedStop()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	m_ds.Stop(lpDSBSecondary1);
	m_ds.Stop(lpDSBSecondary2);
	m_ds.Stop(lpDSBSecondary3);
}


void CDirectSoundProjektDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int j = 0, buffnr = 1, playpos;
	if ((playpos = m_ds.GetPlayPosition(lpDSBSecondary1)) == -1) {
		KillTimer(1); return;
	}
	if (((playpos > 50) && (buffnr == 0)) || ((playpos < 50) && (buffnr == 1))) {
		if ((++j) == 9) { // major scale finished
			KillTimer(1);
			j = 0;
			if (!m_ds.Stop(lpDSBSecondary1))
				return;
			return;
		}
		m_ds.GenerateSound(lpDSBSecondary1, buffnr * 2, 2, ton[j]);
		if (buffnr == 1) buffnr = 0; // change buffer
		else buffnr = 1;
	}
	CDialogEx::OnTimer(nIDEvent);
}
