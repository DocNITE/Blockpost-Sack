#include "includes.h"
#include <vector>

DWORD  offsetsM::GetPointerAddress(DWORD ptr, std::vector<DWORD> offsets)
{
    DWORD addr = ptr;
    DWORD da = 24;
    if (&addr != nullptr && &addr != &da )
    {
        for (int i = 0; i < offsets.size(); ++i)
        {
            if (&addr != nullptr && addr != da )
            {
                addr = *(DWORD*)addr;
                if (addr && &addr != nullptr && addr != NULL)
                {
                    addr += offsets[i];
                }
                else
                {
                    return ptr;
                }
                
            }
        }
        return addr;
    }

}
