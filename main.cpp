#include <thread>
#include <cstdio>

#include <Windows.h>
#include <jni.h>

#include "JNI.h"
#include "Hooks.h"

#include "gui.h"
#include "globals.h"



void MainThread(HMODULE module)
{
    p_jni = std::make_unique<JNI>();
    p_hooks = std::make_unique<Hooks>();

    printf("INTLS v0.4 loaded!\n");
    printf("To detach press PGUP\n");

    printf("[!]Set RightClick Delay to 0 will only work if you dont get an error saying: [Failed to get Minecraft class pointer!]\n");
    

    gui::createHWindow("INTLS", "INTLS class");
    gui::CreateDevice();
    gui::CreateImGui();

    while (gui::exit)
    {
        gui::BeginRender();
        gui::Render();
        gui::EndRender();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    gui::DerstroyImGui();
    gui::DestroyDevice();
    gui::destroyHWindow();

    printf("[+]Selected modules should be active now!\n");
    while (!GetAsyncKeyState(VK_PRIOR))
    {
        if (g_Globals.rcDelay == true)
        {
            p_jni->p_cminecraft->SetRightClickDelay(0);
        }
        if (g_Globals.autoclick == true)
        {
            if (GetAsyncKeyState(VK_XBUTTON1))
            {
                p_jni->p_crobot->mousePress(16);
                p_jni->p_crobot->mouseRelease(16);
                
                p_jni->p_crobot->delay(g_Globals.autoClickDelay + g_Globals.autoClickRandomness);
                
            }
            if (GetAsyncKeyState(VK_XBUTTON2))
            {
                p_jni->p_crobot->mousePress(4096);
                p_jni->p_crobot->mouseRelease(4096);
                
                p_jni->p_crobot->delay(g_Globals.autoClickDelay + g_Globals.autoClickRandomness);

            }
        }
    }
    
    FreeLibrary(module);
}

bool __stdcall DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    static FILE* p_file{ nullptr };
    static std::thread main_thread;

    if (reason == DLL_PROCESS_ATTACH)
    {
        AllocConsole();
        freopen_s(&p_file, "CONOUT$", "w", stdout);

        main_thread = std::thread([instance] { MainThread(instance); });
        if (main_thread.joinable())
            main_thread.detach();
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        fclose(p_file);
        FreeConsole();
    }

    return true;
}