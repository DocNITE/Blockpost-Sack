#include "Fov.h"
#include "framework/il2cpp-appdata.h"
#include "offsetsM.h"

app::PlayerData* GetPlayerDataSack(UINT32 i)
{

	offsetsM offsets;
	PlayerDataArray* pdataA = (PlayerDataArray*)(*app::PLH__TypeInfo)->static_fields->player;
	DWORD CHECK = (DWORD)pdataA->Player[i];
	if (CHECK < 0xfffff || CHECK == NULL || &CHECK == nullptr)
		return NULL;
	return pdataA->Player[i];
}

void FovView::Start()
{
	offsetsM offsets;
	if (offsets.GetPointerAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0xB35CA8, { 0x5C,0x0C, (UINT)0x10 + 0 * 4,  0x28 }) != reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0xB35CA8)
	{
		app::PlayerData* enemy = GetPlayerDataSack(0);
		if (enemy != nullptr)
		{
			if (enemy->fields.currweapon != nullptr)
			{
				if ((*app::Controll__TypeInfo)->static_fields->csCam != nullptr)
				{
					if ((*app::Controll__TypeInfo)->static_fields->inZoom == true)
					{
						app::Camera_set_fieldOfView((*app::Controll__TypeInfo)->static_fields->csCam, 25, nullptr);
					}
					else
					{
						app::Camera_set_fieldOfView((*app::Controll__TypeInfo)->static_fields->csCam, viewFov, nullptr);
					}
				}
			}
		}
		

	}
}