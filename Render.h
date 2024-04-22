#pragma once

#include "D2DApp.h"

namespace Rendering {

	HRESULT InitializeWindow();
	// Real

	void MSGLoop();

	HRESULT OnRender();
	void OnResize(UINT h, UINT w);

	static LRESULT CALLBACK WindowProcedure(
		HWND hWnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam
	);
	
};