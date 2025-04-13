#include <gearbox.h>

void Dirt::adjustSettings()
{
	Core::Pointer profileEntries = locateProfileEntries();
	Core::Pointer entryAfterLast = profileEntries.at(0x4); // _Mylast
	int numEntries = (entryAfterLast.as<uint32_t>() - profileEntries.as<uint32_t>()) / profileEntryLength;

	// Get values
	uint8_t* transmissionType = locateSetting("transmission_type", profileEntries, numEntries);
	uint8_t* clutchAsBrake = locateSetting("clutchAsBrake", profileEntries, numEntries);
	if (transmissionType == nullptr || clutchAsBrake == nullptr)
		return;

	// Set the transmission type to manual with manual clutch.
	// Also make the clutch act like a clutch instead of a brake.
	// Do this every second in case the controls get changed.
	while (true)
	{
		if (*transmissionType != 1)
			*transmissionType = 2;
		*clutchAsBrake = 0;
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

uint8_t* Dirt::locateSetting(const char* settingName, Core::Pointer profileEntries, int numEntries)
{
	// Find profile entry
	char* entry = nullptr;
	for (int i = 0; i < numEntries; ++i)
	{
		// Name is first field
		char* tmp = reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(profileEntries.deref().GetAddress()) + (i * profileEntryLength));
		if (strncmp(tmp, settingName, strlen(settingName)) == 0)
		{
			entry = tmp;
			break;
		}
	}

	if (entry == nullptr)
	{
		std::string e = std::string("Failed to find entry for ").append(settingName);
		MessageBoxA(NULL, e.data(), "Error", 0);
		return nullptr;
	}

	return reinterpret_cast<uint8_t*>(entry + 0x48); // m_data
}
