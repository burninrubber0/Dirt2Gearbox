#pragma once

#include <Windows.h>
#include <Pointer.h>
#include <string>

class Dirt
{
public:
	static const uint32_t exeNameLength = 14;
	static const uint32_t base = 0xA20000;
	static const uint32_t appAddress = 0x01049C84;
	static const uint32_t appOffset = 0x90C;

private:
	Core::Pointer cmr6App = base + appAddress;
	void adjustTransmissionType();
	Core::Pointer locateProfileEntries();

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
