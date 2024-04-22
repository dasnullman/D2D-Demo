#include "Helpers.h"

HRESULT D2D::CreateDeviceIndependentResources() {
	HRESULT hRes = S_OK;

	hRes = D2D1CreateFactory(
#ifdef NULL_MULTI_THREADED
		D2D1_FACTORY_TYPE_MULTI_THREADED
#else
		D2D1_FACTORY_TYPE_SINGLE_THREADED
#endif
		,

		&D2D::pD2DFactory
	);

	return hRes;
}

HRESULT D2D::CreateDeviceResources() {
	HRESULT hRes = S_OK; 
	// What if I'm not okay? \
	What if I want to brutally murder the man who made Unity?

	if (!D2D::pRenderTarget) {

		RECT rect;
		GetClientRect(D2D::hwnd, &rect);

		D2D1_SIZE_U size = D2D1::SizeU(
			rect.right - rect.left,
			rect.bottom - rect.top
		);

		// Lmao even

		hRes = D2D::pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),

			D2D1::HwndRenderTargetProperties(
				D2D::hwnd,
				size
			),

			&D2D::pRenderTarget
		);

		if (SUCCEEDED(hRes)) {
			// Let's make a brush
			ID2D1SolidColorBrush* brush;
			hRes = D2D::pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Azure) // HAHAHAHAHAHA MICROSOFT AZURE \
										FUNNY, SO FUNNY. HAHAHAHA THIS IS PEAK COMEDY HAHAHAHAHAHA

				,

				&brush
			);

			D2D::brushes.push_back(brush);
			brush = nullptr;
			// DO NOT RELEASE BRUSH
			// Simply set our current reference to it to be null pointer
			// When it's not required anymore it'll be released by the system


			// Let's make another brush too. To fuck around obviously

			if (SUCCEEDED(hRes)) {
				hRes = D2D::pRenderTarget->CreateSolidColorBrush(
					D2D1::ColorF(D2D1::ColorF::Coral),
					&brush
				);

				D2D::brushes.push_back(brush);
				brush = nullptr;
			}
		}
	}
	// In essence, this code can get called whenever by whoever and they will continue to call this code
	// So we have to get it over with once
	

	return hRes;
}

void D2D::DiscardResources() {
	UnsafeRelease(&D2D::pD2DFactory);
	UnsafeRelease(&D2D::pRenderTarget);

	for (ID2D1Brush* brush : D2D::brushes) {
		UnsafeRelease(&brush);
	}

	// How can we make this worse?
	// Use a very large statically sized array zeroed out with no bounds checking
	// Guarantee we attempt to release a null pointer unless we've filled our large array
	// In which case we're just fucking around
	// Fortunately, UnsafeRelease, for it's name is in fact not that bad

}