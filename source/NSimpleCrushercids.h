//------------------------------------------------------------------------
// Copyright(c) 2024 Noah Dominic Miranda Silvio.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace NoahDominic {
//------------------------------------------------------------------------
static const Steinberg::FUID kNSimpleCrusherProcessorUID (0x7BC0FB63, 0xA6BB5AEA, 0x85F01321, 0x9101B41E);
static const Steinberg::FUID kNSimpleCrusherControllerUID (0x0AAFCDD5, 0xA59A527A, 0x9F9B1927, 0x490DC18E);

#define NSimpleCrusherVST3Category "Fx"

enum NSimpleSaturatorParams : Steinberg::Vst::ParamID
{
	kParamPreGainId,
	kParamCrushId,
	kParamPostGainId,
	kParamMixId,
};

//------------------------------------------------------------------------
} // namespace NoahDominic
