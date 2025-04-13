#include <gearbox.h>

static constexpr char k_ModName[] = "DirtGearbox";

Dirt Dirt::s_Instance;

Dirt::Dirt()
{
	
}

Dirt& Dirt::Get()
{
	return s_Instance;
}

void Dirt::OnProcessAttach()
{
	PTHREAD_START_ROUTINE loadThreadProc = [](LPVOID lpThreadParameter) -> DWORD
		{
			static_cast<Dirt*>(lpThreadParameter)->Load();
			return 0;
		};
	m_LoadThreadHandle = CreateThread(nullptr, 0, loadThreadProc, this, 0, nullptr);
}

void Dirt::OnProcessDetach()
{
	Unload();
	CloseHandle(m_LoadThreadHandle);
}

void Dirt::Load()
{
	try
	{
		while (true)
		{
			if (cmr6App.as<void*>() != nullptr)
				break;
			Sleep(1000);
		}

		cmr6App = cmr6App.deref().at(appOffset); // CMR6::Application

		Sleep(20000);
		adjustTransmissionType();
	}
	catch (const std::exception& e)
	{
		MessageBoxA(NULL, e.what(), k_ModName, MB_ICONERROR);
	}
}

void Dirt::Unload()
{
	try
	{
		
	}
	catch (const std::exception& e)
	{
		MessageBoxA(NULL, e.what(), k_ModName, MB_ICONERROR);
	}
}
