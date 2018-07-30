#include "../main.h"
#include "../Hacks/skinchanger.h"

void InitializeInterfaces() {
    pSurface = GetInterface<ISurface>("./bin/osx64/vguimatsurface.dylib", "VGUI_Surface");
    pPanel = GetInterface<IPanel>("./bin/osx64/vgui2.dylib", "VGUI_Panel");
    pGameEventManager = GetInterface<IGameEventManager2>("./bin/osx64/engine.dylib", "GAMEEVENTSMANAGER002", true);
    pCvar = GetInterface<ICvar>("./bin/osx64/materialsystem.dylib", "VEngineCvar");
    pClient = GetInterface<IBaseClientDLL>("./csgo/bin/osx64/client.dylib", "VClient");
    pEngine = GetInterface<IEngineClient>("./bin/osx64/engine.dylib", "VEngineClient");
    pEntList = GetInterface<IClientEntityList>("./csgo/bin/osx64/client.dylib", "VClientEntityList");
    pOverlay = GetInterface<IVDebugOverlay>("./bin/osx64/engine.dylib", "VDebugOverlay");
    pEngineTrace = GetInterface<IEngineTrace>("./bin/osx64/engine.dylib", "EngineTraceClient");
    pModelInfo = GetInterface<IVModelInfo>("./bin/osx64/engine.dylib", "VModelInfoClient");
}


void InitializeVMTs() {
    game_event_vmt = new VMT(pGameEventManager);
    testvmt = new VMT(pPanel);
    client_vmt = new VMT(pClient);
}

extern bool hkFireEventClientSide(void* thisptr, IGameEvent* event);

void InitializeHooks() {
    game_event_vmt->HookVM((void*)hkFireEventClientSide, 11);
    game_event_vmt->ApplyVMT();
    client_vmt->HookVM((void*)hkFrameStage, 37);
    client_vmt->ApplyVMT();

    g_pSequence = (RecvVarProxyFn)NetVarManager::HookProp("DT_BaseViewModel", "m_nSequence", HSequenceProxyFn);

}

void PrintInfo() {
    pCvar->ConsoleColorPrintf(Color::Yellow(),   "Noriaela Version 1\n");
    pCvar->ConsoleColorPrintf(Color::Yellow(),   "Coded by :\n");
    pCvar->ConsoleColorPrintf(Color::Yellow(),   "Warlauke\n");
}
