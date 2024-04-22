#pragma once

#include "D2DApp.h"

namespace D2D {


	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();

	void DiscardResources();

};