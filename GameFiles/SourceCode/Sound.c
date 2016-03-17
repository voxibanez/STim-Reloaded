#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#include "bass.h"

HWND win = NULL;
DWORD music;
OPENFILENAME ofn;

void sound();
DWORD GetFlags();
void loadDLL();

void sound()
{
	loadDLL();
	BASS_MusicFree(music); // free the current music
	music = BASS_MusicLoad(FALSE, "background.xm", 0, 0, GetFlags(), 1); // load the new music

	BASS_ChannelPlay(music, FALSE); // start it
	return 0;
}

DWORD GetFlags()
{
	DWORD flags = BASS_MUSIC_POSRESET; // stop notes when seeking
	
		//flags |= BASS_MUSIC_NONINTER; // no interpolation

		flags |= BASS_MUSIC_SINCINTER; // sinc interpolation
	
		//flags |= BASS_MUSIC_RAMP; // ramping
		
		flags |= BASS_MUSIC_RAMPS; // "sensitive" ramping

	
		//flags |= BASS_MUSIC_SURROUND; // surround

		//flags |= BASS_MUSIC_SURROUND2; // "mode2"

	return flags;
}

void loadDLL(){
	HMODULE libHandle;

	if ((libHandle = LoadLibrary(TEXT("BASS.dll"))) == NULL)
	{
		printf("load failed\n");
		return;
	}
	if (GetProcAddress(libHandle, "send") == NULL)
	{
		printf("GetProcAddress failed\n");
		printf("%d\n", GetLastError());
		return;
	}
}