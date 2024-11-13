
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
	LPDIRECTSOUNDBUFFER lpDSBSecondary_CDUR1, lpDSBSecondary_264Hz;
	LPDIRECTSOUNDBUFFER lpDSBSecondary_Klavier[8];
	LPDIRECTSOUNDBUFFER lpDSBSecondary_DreiklangC, lpDSBSecondary_DreiklangE, lpDSBSecondary_DreiklangG;
	LPDIRECTSOUNDBUFFER lpDSBSecondary_PCM;
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
	afx_msg void OnBnClicked264hz();
	afx_msg void OnBnClickedPcm();
	afx_msg void OnBnClickedCdur();
	afx_msg void OnBnClickedDreiklang();
	afx_msg void OnBnClickedEnde();
	afx_msg void OnBnClickedC();
	afx_msg void OnBnClickedD();
	afx_msg void OnBnClickedE();
	afx_msg void OnBnClickedF();
	afx_msg void OnBnClickedG();
	afx_msg void OnBnClickedA();
	afx_msg void OnBnClickedH();
	afx_msg void OnBnClickedC2();
};
