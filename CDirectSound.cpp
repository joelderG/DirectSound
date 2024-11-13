#include "pch.h"
#include "CDirectSound.h"

#pragma warning (disable: 4996)
#pragma warning (disable: 26495)

CDirectSound::CDirectSound() {
	CoInitialize(NULL); // init COM-Interface
	lpds = 0; lpDSBPrimary = 0;
}

CDirectSound::~CDirectSound() {
	if (lpds) {
		lpDSBPrimary->Release();
		lpDSBPrimary = 0;
		lpds->Release(); lpds = 0;
	}
	// falls es das einzige COM-Interface ist
	// CoUninitialize();
}

bool CDirectSound::Create(CWnd* wnd) {
	if (!lpds) {
		if (CoCreateInstance(CLSID_DirectSound, NULL, CLSCTX_ALL,
			IID_IDirectSound, (LPVOID*)&lpds) != DS_OK) {
			AfxMessageBox(L"DirectSound object not created.");
			return false;
		}
		if (lpds->Initialize(0) != DS_OK) {
			AfxMessageBox(L"Error: Initialize DirectSound-Interface");
			return false;
		}
		// be cooperativ (dringend empfohlen) !!!!
		if (lpds->SetCooperativeLevel(wnd->GetSafeHwnd(), DSSCL_NORMAL) != DS_OK) {
			AfxMessageBox(L"Application's Behavior not available");
			return false;
		}
		memset(&dsbd, 0, sizeof(dsbd));
		dsbd.dwSize = sizeof(dsbd);
		dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
		if (lpds->CreateSoundBuffer(&dsbd, &lpDSBPrimary, NULL) != DS_OK) {
			AfxMessageBox(L"Cannot create the primary buffer");
			return false;
		}
	}
	return true;
}

LPDIRECTSOUNDBUFFER CDirectSound::CreateSoundBuffer(WORD Channels, WORD BitsPerSample,
	DWORD SamplesPerSec, WORD seconds) {
	if (!lpds) return 0;
	WAVEFORMATEX pcmwf; LPDIRECTSOUNDBUFFER lpDSBuffer;
	memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT));
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = Channels; pcmwf.wBitsPerSample = BitsPerSample;
	pcmwf.nSamplesPerSec = SamplesPerSec;
	pcmwf.nBlockAlign = Channels * (BitsPerSample / 8); // for example 4 Byte
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	memset(&dsbd, 0, sizeof(dsbd)); dsbd.dwSize = sizeof(dsbd);
	dsbd.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY |
		DSBCAPS_GLOBALFOCUS;
	dsbd.dwBufferBytes = seconds * pcmwf.nAvgBytesPerSec;
	dsbd.lpwfxFormat = &pcmwf;
	// create the sound buffer now
	if (lpds->CreateSoundBuffer(&dsbd, &lpDSBuffer, NULL) != DS_OK) {
		AfxMessageBox(L"Cannot create a secondary buffer");
		return 0;
	}
	return lpDSBuffer;
}

bool CDirectSound::GetWaveFormat(LPDIRECTSOUNDBUFFER buf, WAVEFORMATEX* pcmwf)
{
	if (!buf) return false;
	if (buf->GetFormat(pcmwf, sizeof * pcmwf, NULL) != DS_OK) {
		AfxMessageBox(L"Cannot get audio format");
		return false;
	}
	return true;
}

bool CDirectSound::LockBuffer(LPDIRECTSOUNDBUFFER buf, DWORD offset, DWORD size,
	void** ptr1, DWORD* bytes1, void** ptr2, DWORD* bytes2) {
	WAVEFORMATEX pcmwf;
	if (!buf) return false;
	if (!GetWaveFormat(buf, &pcmwf)) return false;
	if (buf->Lock(offset * pcmwf.nAvgBytesPerSec, // a offset of some seconds
		size * pcmwf.nAvgBytesPerSec, // write size seconds
		ptr1, // get pointer 1
		bytes1, // get bytes available there
		ptr2, // get pointer 2 (the buffer is circular)
		bytes2, // get bytes available there
		NULL) != DS_OK) {
		AfxMessageBox(L"Cannot lock the secondary buffer");
		return false;
	}
	return true;
}

bool CDirectSound::UnlockBuffer(LPDIRECTSOUNDBUFFER buf,
	void* ptr1, DWORD bytes1, void* ptr2, DWORD bytes2) {
	if (!buf) return false;
	if (buf->Unlock(ptr1, bytes1, ptr2, bytes2) != DS_OK) {
		AfxMessageBox(L"Cannot unlock the secondary buffer");
		return false;
	}
	return true;
}

bool CDirectSound::Play(LPDIRECTSOUNDBUFFER buf, bool looped)
{
	if (!buf) return false;
	if (buf->Play(0, 0, looped ? DSBPLAY_LOOPING : 0) != DS_OK) {
		AfxMessageBox(L"Cannot play the secondary buffer");
		return false;
	}
	return true;
}

bool CDirectSound::Stop(LPDIRECTSOUNDBUFFER buf)
{
	if (!buf) return false;
	if (buf->Stop() != DS_OK) {
		AfxMessageBox(L"Cannot stop our playback");
		return false;
	}
	return true;
}

bool CDirectSound::GenerateSound(LPDIRECTSOUNDBUFFER buf,
	DWORD offset, DWORD length, int f) {
	WAVEFORMATEX pcmwf;
	if (!buf) return false;
	if (!GetWaveFormat(buf, &pcmwf))
		return false;
	void* lpvPtr1, * lpvPtr2; DWORD dwBytes1, dwBytes2;
	if (!this->LockBuffer(buf, offset, length,
		&lpvPtr1, &dwBytes1, // get pointer 1
		&lpvPtr2, &dwBytes2)) // get pointer 2 (the buffer is circular)
		return false;
	// write a sinus sound now
	DWORD i; short int* t; // points to 16 Bit
	for (i = 0, t = (short int*)lpvPtr1; i < (dwBytes1 + dwBytes2); i += 4, t += 2) {
		if (i == dwBytes1)
			t = (short int*)lpvPtr2;
		*t = *(t + 1) = (short int)(sin(i / (pcmwf.nAvgBytesPerSec / (6.283185 * f))) * 30000);
	}
	// unlock memory
	if (!this->UnlockBuffer(buf,
		lpvPtr1, dwBytes1, // pointer 1
		lpvPtr2, dwBytes2)) // pointer 2
		return false;
	return true;
}

bool CDirectSound::SetPlaybackVolume(LPDIRECTSOUNDBUFFER buf, LONG db)
{
	if (!buf) return false;
	if (buf->SetVolume(db) != DS_OK) {
		AfxMessageBox(L"Cannot change volume");
		return false;
	}
	return true;
}

bool CDirectSound::SetBalance(LPDIRECTSOUNDBUFFER buf, LONG db)
{
	if (!buf) return false;
	if (buf->SetPan(db) != DS_OK) {
		AfxMessageBox(L"Cannot change balance");
		return false;
	}
	return true;
}

int CDirectSound::GetPlayPosition(LPDIRECTSOUNDBUFFER buf) {
	DSBCAPS caps;
	caps.dwSize = sizeof(DSBCAPS);
	if (buf->GetCaps(&caps) != DS_OK) {
		AfxMessageBox(L"Cannot get buffer caps");
		return -1;
	}
	DWORD playPos;
	if (buf->GetCurrentPosition(&playPos, 0) != DS_OK) {
		AfxMessageBox(L"Cannot get the secondary buffer positions");
		return -1;
	}
	return ((playPos * 100) / caps.dwBufferBytes);
}

bool CDirectSound::GeneratePCMSound(LPDIRECTSOUNDBUFFER buf, DWORD offset, DWORD length, char* pszFileName, int section)
{
	WAVEFORMATEX pcmwf;
	if (!buf) return false;

	// Hole das Wellenformat für den Buffer
	if (!GetWaveFormat(buf, &pcmwf))
		return false;

	// Öffne die PCM-Datei im Binärmodus
	FILE* pcmFile = fopen(pszFileName, "rb");
	if (!pcmFile)
		return false;

	// Berechne die Position innerhalb der Datei für das gewünschte Segment
	DWORD bytesPerSecond = pcmwf.nAvgBytesPerSec;
	DWORD startPosition = section * 2 * bytesPerSecond;
	fseek(pcmFile, startPosition, SEEK_SET); // Setze die Leseposition

	// Berechne die Anzahl der zu lesenden Bytes für `durationSec`
	DWORD bytesToRead = bytesPerSecond * 2;

	// Sperre den Buffer und hole die Pufferzeiger
	void* lpvPtr1, * lpvPtr2; DWORD dwBytes1, dwBytes2;
	if (!this->LockBuffer(buf, offset, length,
		&lpvPtr1, &dwBytes1, // get pointer 1
		&lpvPtr2, &dwBytes2)) // get pointer 2 (the buffer is circular)
		return false;

	// Lese PCM-Daten und schreibe sie in den Buffer
	size_t bytesRead = fread(lpvPtr1, 1, dwBytes1, pcmFile);
	if (bytesRead < dwBytes1) {
		// Falls weniger Daten gelesen wurden, den Rest des Buffers mit Nullen füllen
		memset((char*)lpvPtr1 + bytesRead, 0, dwBytes1 - bytesRead);
	}

	// Wenn ein zweiter Teil des Buffers existiert, lese dort weiter
	if (dwBytes2 > 0) {
		bytesRead = fread(lpvPtr2, 1, dwBytes2, pcmFile);
		if (bytesRead < dwBytes2) {
			// Fülle den Rest des Buffers mit Nullen, falls weniger Daten gelesen wurden
			memset((char*)lpvPtr2 + bytesRead, 0, dwBytes2 - bytesRead);
		}
	}

	fclose(pcmFile);  // Schließe die Datei

	// unlock memory
	if (!this->UnlockBuffer(buf,
		lpvPtr1, dwBytes1, // pointer 1
		lpvPtr2, dwBytes2)) // pointer 2
		return false;
	return true;
}
