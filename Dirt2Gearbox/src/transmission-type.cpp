#include <gearbox.h>

void Dirt::adjustTransmissionType()
{
	Core::Pointer profileEntries = locateProfileEntries();

	// Find transmission_type
	char* name = nullptr;
	for (int i = 0; i < 150; ++i)
	{
		// Each entry is 0x128 long, name is first field
		char* tmp = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(profileEntries.deref().GetAddress()) + (i * 0x128));
		if (strncmp(tmp, "transmission_type", 17) == 0)
			name = tmp;
	}

	if (name == nullptr)
	{
		MessageBoxA(NULL, "Failed to find transmission_type entry", "Error", 0);
		return;
	}

	uint8_t* transmissionType = reinterpret_cast<uint8_t*>(name + 0x48);
	while (true)
	{
		*transmissionType = 2;
		Sleep(1000);
	}
}

Core::Pointer Dirt::locateProfileEntries()
{
	return cmr6App.at(0xA8) // UpdateTask* m_updateTask
		.deref().at(0x2284) // SaveGameManager* m_savegameManager
		.deref()            // PlayerProfile m_playerManager
		.at(0x20)           // vector<profileEntry> m_entries
		.at(0x4);           // pointer _Myfirst
}
