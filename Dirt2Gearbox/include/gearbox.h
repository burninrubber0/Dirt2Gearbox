#pragma once

#include <Windows.h>
#include <Pointer.h>
#include <string>

class Dirt
{
public:
	uint32_t base = 0;
	static const uint32_t appAddress = 0x01049C84;
	static const uint32_t appOffset = 0x90C;
	static const uint32_t exeNameLength = 14;
	static const uint32_t profileEntryLength = 0x128;

private:
	Core::Pointer cmr6App = nullptr;
	void adjustSettings();
	Core::Pointer locateProfileEntries();
	uint8_t* locateSetting(const char* settingName, Core::Pointer profileEntries, int numEntries);

private:
	Dirt();

public:
	static Dirt& Get();

public:
	void OnProcessAttach();
	void OnProcessDetach();

private:
	void Load();
	void Unload();

private:
	static Dirt s_Instance;

private:
	HANDLE m_LoadThreadHandle = NULL;
};
