// dllmain.cpp : Defines the entry point for the DLL application.
#include "includes.h"

// hooking
#include "Hooks/MoreVideoOptionsLayer.hpp"
#include "Hooks/PauseLayer.hpp"

DWORD WINAPI MainThread(void* hModule) {
    MH_Initialize();
    
    MoreVideoOptionsLayer::mem_init();
    PauseLayer::mem_init();

    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, MainThread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}