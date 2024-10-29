
// DirectSoundProjekt.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CDirectSoundProjektApp:
// Siehe DirectSoundProjekt.cpp für die Implementierung dieser Klasse
//

class CDirectSoundProjektApp : public CWinApp
{
public:
	CDirectSoundProjektApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDirectSoundProjektApp theApp;
