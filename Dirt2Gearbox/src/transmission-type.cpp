#include <gearbox.h>

void Dirt::adjustTransmissionType()
{
	Core::Pointer profileEntries = locateProfileEntries();
	Core::Pointer entryAfterLast = profileEntries.at(0x4); // _Mylast
	int numEntries = (entryAfterLast.as<uint32_t>() - profileEntries.as<uint32_t>()) / profileEntryLength;

	// Find transmission_type profile entry
	char* name = nullptr;
	for (int i = 0; i < numEntries; ++i)
	{
		// Name is first field
		char* tmp = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(profileEntries.deref().GetAddress()) + (i * profileEntryLength));
		if (strncmp(tmp, "transmission_type", 17) == 0)
		{
			name = tmp;
			break;
		}
	}

	if (name == nullptr)
	{
		MessageBoxA(NULL, "Failed to find transmission_type entry", "Error", 0);
		return;
	}

	// Transmission type value
	uint8_t* transmissionType = reinterpret_cast<uint8_t*>(name + 0x48);

	// Set the transmission type to manual with manual clutch.
	// Do this every second in case the controls get changed.
	while (true)
	{
		if (*transmissionType != 1)
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
