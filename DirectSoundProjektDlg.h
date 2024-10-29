
// DirectSoundProjektDlg.h: Headerdatei
//

#pragma once
#include "CDirectSound.h"

// CDirectSoundProjektDlg-Dialogfeld
class CDirectSoundProjektDlg : public CDialogEx
{
// Konstruktion
public:
	CDirectSoundProjektDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIRECTSOUNDPROJEKT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	CDirectSound m_ds;
	LPDIRECTSOUNDBUFFER lpDSBSecondary1, lpDSBSecondary2, lpDSBSecondary3;
	double ton[9];

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTest1();
	afx_msg void OnBnClickedStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
