#include "includes.h"
#include <cmath>
#include <array>
#include <iostream>
#include "Vector.h"


class AngleView
{
private:
    Vector3 distA, angleXA, angleYA;
};

Vector2 AimBot::GetDistanceAndAngle(Vector3 startPOS, app::Vector3 endPOS)
{
    float deltaX = endPOS.x - startPOS.x;
    float deltaY = endPOS.y - startPOS.y - 0.1f;
    float deltaZ = endPOS.z - startPOS.z;

    float dist = sqrt(
        pow((endPOS.x - startPOS.x), 2.0) +
        pow((endPOS.y - startPOS.y), 2.0) +
        pow((endPOS.z - startPOS.z), 2.0));
    if (dist < 0)
    {
        dist = dist * -1;
    }

    float xzlength = sqrt((deltaX * deltaX) + (deltaZ * deltaZ));
    float angleX = atan2(deltaY, xzlength) * (-57.2957795);
    float angleY = atan2(deltaX, deltaZ) * (57.2957795);
    Vector2 ANAL = { angleX,angleY,dist };
    return  ANAL;
}


void SetView(Vector2 pos)
{
    app::Controll__StaticFields* controll = (*app::Controll__TypeInfo)->static_fields;
    controll->rx = pos.y;
    controll->ry = pos.x;
}

app::PlayerData* GetsPlayerData(UINT32 i)
{

    offsetsM offsets;
    PlayerDataArray* pdataA = (PlayerDataArray*)(*app::PLH__TypeInfo)->static_fields->player;
    DWORD CHECK = (DWORD)pdataA->Player[i];
    if (CHECK < 0xfffff || CHECK == NULL || &CHECK == nullptr || CHECK == 0x00000800 || CHECK == 2048 || &CHECK == (DWORD*)0x00000800)
        return NULL;
    return pdataA->Player[i];

}

void AimBot::Render()
{   
    AngleView view;
    offsetsM offsets;
    uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
    app::Controll__StaticFields* controll = (*app::Controll__TypeInfo)->static_fields;

    for (ULONG i = 0; i < 40; i++)
    {
        if (offsets.GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + i * 4,  0x28 }) == baseModule + EntListBase2)
            continue;

        app::PlayerData* enemy = GetsPlayerData(i); // saksak 
        cscamera* mycam = (cscamera*)(*app::Controll__TypeInfo)->static_fields->csCam;

        if (enemy->fields.currPos.x == 0)
            continue;
        if (enemy->fields.team == (*app::Controll__TypeInfo)->static_fields->pl->fields.team && teamcheck == true)
            continue;


        while (true)
        {
            if (!GetAsyncKeyState(VK_LBUTTON) && !GetAsyncKeyState(VK_LSHIFT) && toggle == true)
                break;
            if (enemy->fields.spawnprotect)
                break;
            if (mycam->camira == nullptr)
                break;
            if (enemy->fields.bstate == 5)
                break;

           
            if (mycam->camira->campos.x != -1 && mycam->camira->campos.y != -1 && mycam->camira->campos.z != -1)
            {
                
                if (enemy->fields.bstate != 5)
                {
                    Vector2 AngletoTarger = GetDistanceAndAngle(mycam->camira->campos, enemy->fields.currPos);


                    if (AngletoTarger.d <= distanceFov)
                    {
                        
                        dist = AngletoTarger.d;
                        float x = controll->rx;
                        float y = controll->ry;
                        float normdis = AngletoTarger.x;
                        float mysacky = controll->ry - normdis;

                        if (AngletoTarger.y < 0)
                        {
                            AngletoTarger.y = 360 + AngletoTarger.y;
                        }
                        if (x < 0)
                        {
                            x = 360 + x;
                        }
                       float  mysackx = AngletoTarger.y - x;


                        if (mysackx < -fov || mysackx > fov || mysacky < -fov || mysacky > fov)
                        {
                            break;
                        }
                        else {                                                
                                SetView(AngletoTarger);
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
}