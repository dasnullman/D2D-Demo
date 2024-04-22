#pragma once

// Windows 
#include <windows.h>
#include <wincodec.h>

// CRT
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

// DirectX and related
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

// C++ STI
#include <vector>

// Compile against d2d lib
#pragma comment(lib, "d2d1.lib")


template<class Interface>
inline void UnsafeRelease(
    Interface** ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = NULL;
    }
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

namespace D2D {
    HWND hwnd;
    ID2D1Factory* pD2DFactory;
    ID2D1HwndRenderTarget* pRenderTarget;

    std::vector<ID2D1Brush*> brushes;
};