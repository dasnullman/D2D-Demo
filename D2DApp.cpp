#include "D2DApp.h"
#include "Render.h"

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE hPrevInst,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    // HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
    // Heap corruption doesn't matter, NullMemory should handle it perfectly
    // In the case that it does, the hope is that revised NullMemory can discover it on it's own
    // And issue an invalidate memory directive, which can be appropriately handled by other code in the Null2dEngine

    if (SUCCEEDED(CoInitialize(NULL))) {
        {

            if (SUCCEEDED(Rendering::InitializeWindow())) {
                Rendering::MSGLoop();
                // Consider moving this out of rendering.
                // Deadline: never.
            }
        }
        CoUninitialize();
    }

    return 0;
}