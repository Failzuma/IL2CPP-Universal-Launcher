#include <windows.h>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // this is to hide the debug console, just comment this line if you want to see the debug console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    HMODULE unityPlayerModule = LoadLibraryA("UnityPlayer.dll");
    if (!unityPlayerModule) {
        return 1;
    }
    int (*unityMainFunc)(HINSTANCE, HINSTANCE, LPWSTR, int) =
        reinterpret_cast<int (*)(HINSTANCE, HINSTANCE, LPWSTR, int)>(
            GetProcAddress(unityPlayerModule, "UnityMain"));
    if (unityMainFunc) {
        return unityMainFunc(hInstance, hPrevInstance, GetCommandLineW(), nShowCmd);
    }
    FreeLibrary(unityPlayerModule);
    return 1;
}
