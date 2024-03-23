//------------------------------------------------------------------------
// Copyright(c) 2024 Noah Dominic Miranda Silvio.
//------------------------------------------------------------------------

#include "NSimpleCrushercontroller.h"
#include "NSimpleCrushercids.h"
#include "base/source/fstreamer.h"


using namespace Steinberg;

namespace NoahDominic {

//------------------------------------------------------------------------
// NSimpleCrusherController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API NSimpleCrusherController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	// Here you could register some parameters
	parameters.addParameter(STR16("Pre-Gain"), STR16(""), 0, .5, Vst::ParameterInfo::kCanAutomate, NSimpleSaturatorParams::kParamPreGainId, 0);
	parameters.addParameter(STR16("Crush"), STR16(""), 0, 0., Vst::ParameterInfo::kCanAutomate, NSimpleSaturatorParams::kParamCrushId, 0);
	parameters.addParameter(STR16("Post-Gain"), STR16(""), 0, .5, Vst::ParameterInfo::kCanAutomate, NSimpleSaturatorParams::kParamPostGainId, 0);
	parameters.addParameter(STR16("Mix"), STR16("%"), 0, 1., Vst::ParameterInfo::kCanAutomate, NSimpleSaturatorParams::kParamMixId, 0);

	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NSimpleCrusherController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API NSimpleCrusherController::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;

	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer(state, kLittleEndian);
	float savedParams[] = { 0.f, 0.f, 0.f, 0.f };
	if (streamer.readFloatArray(savedParams, 4) == false)
	{
		return kResultFalse;
	}

	if (auto param = parameters.getParameter(NSimpleSaturatorParams::kParamPreGainId))
		param->setNormalized(savedParams[0]);
	if (auto param = parameters.getParameter(NSimpleSaturatorParams::kParamCrushId))
		param->setNormalized(savedParams[1]);
	if (auto param = parameters.getParameter(NSimpleSaturatorParams::kParamPostGainId))
		param->setNormalized(savedParams[2]);
	if (auto param = parameters.getParameter(NSimpleSaturatorParams::kParamMixId))
		param->setNormalized(savedParams[3]);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NSimpleCrusherController::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NSimpleCrusherController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API NSimpleCrusherController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
        return nullptr;
	}
	return nullptr;
}

//------------------------------------------------------------------------
} // namespace NoahDominic
