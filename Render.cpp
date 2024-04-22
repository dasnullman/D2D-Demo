#include "Render.h"
#include "Helpers.h"

void Rendering::MSGLoop() {
	MSG msg;
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HRESULT Rendering::InitializeWindow() {
	HRESULT hRes;

	hRes = D2D::CreateDeviceIndependentResources();

	if (SUCCEEDED(hRes)) {
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Rendering::WindowProcedure;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = TEXT("D2DDemoApp");

		RegisterClassEx(&wcex);

		D2D::hwnd = CreateWindow(
			TEXT("D2DDemoApp"),
			TEXT("Direct2d demo application for eel"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0, 
			0,
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			nullptr
		);
		
		if (D2D::hwnd) {
			float dpi = GetDpiForWindow(D2D::hwnd);
			// Scale window using DPI

			SetWindowPos(
				D2D::hwnd,
				NULL,
				NULL,
				NULL,
				static_cast<int>(ceil(640.f * dpi / 96.f)),
				static_cast<int>(ceil(480.f * dpi / 96.f)),
				SWP_NOMOVE);
			ShowWindow(D2D::hwnd, SW_SHOWNORMAL);
			UpdateWindow(D2D::hwnd);
		}
	}

    return hRes;
}

// Handle the Window Proc

LRESULT CALLBACK Rendering::WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {

        result = 1;
    }
    else
    {
        

        bool wasHandled = false;

        HRESULT thing = S_OK;
        HRESULT* pThing = &thing;

        // In essence this motherfuckering logic works around a pointer here
        // I don't want to change it because then I'd have to change indent level
        // So instead I'm going to create a useless ass pointer

        if (pThing)
        {
            switch (message)
            {
            case WM_SIZE:
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                Rendering::OnResize(width, height);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_DISPLAYCHANGE:
            {
                InvalidateRect(hwnd, NULL, FALSE);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_PAINT:
            {
                Rendering::OnRender();
                ValidateRect(hwnd, NULL);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_DESTROY:
            {
                PostQuitMessage(0);
            }
            result = 1;
            wasHandled = true;
            break;
            }
        }

        if (!wasHandled)
        {
            result = DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

    return result;
}

// Let's define OnRender, which will render.

HRESULT Rendering::OnRender() {
    HRESULT hRes = S_OK;
    hRes = D2D::CreateDeviceResources();

    if (SUCCEEDED(hRes)) {
        D2D::pRenderTarget->BeginDraw();
        D2D::pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        D2D::pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::AntiqueWhite));

        D2D1_SIZE_F rectSize = D2D::pRenderTarget->GetSize();

        int width = static_cast<int>(rectSize.width);
        int height = static_cast<int>(rectSize.height);

        for (int x = 0; x < width; x += 10)
        {
            D2D::pRenderTarget->DrawLine(
                D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
                D2D1::Point2F(static_cast<FLOAT>(x), rectSize.height),
                D2D::brushes.at(2),
                0.5f
            );
        }

        for (int y = 0; y < height; y += 10)
        {
            D2D::pRenderTarget->DrawLine(
                D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
                D2D1::Point2F(rectSize.width, static_cast<FLOAT>(y)),
                D2D::brushes.at(2),
                0.5f
            );
        }

        D2D1_RECT_F rectangle = D2D1::RectF(
            rectSize.width / 2 - 50.0f,
            rectSize.height / 2 - 50.0f,
            rectSize.width / 2 + 50.0f,
            rectSize.height / 2 + 50.0f
        );

        D2D::pRenderTarget->FillRectangle(&rectangle, D2D::brushes.at(1));

        hRes = D2D::pRenderTarget->EndDraw();

        if (hRes == D2DERR_RECREATE_TARGET) // FUCK
        {
            hRes = S_OK;
            D2D::DiscardResources();
        }
    }

    return hRes;
}

void Rendering::OnResize(UINT width, UINT height)
{
    if (D2D::pRenderTarget) {
        // This method can and will fail
        // But I don't give a damn.

        // Ples no resize though
        D2D::pRenderTarget->Resize(D2D1::SizeU(width, height));
    }
}