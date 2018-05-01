//Copyright 2018 Chris Wratt and Victoria University of Wellington
//This program is free software : you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.
//
// see <http://www.gnu.org/licenses/> for a full copy of the license.

#include "VSTBase.h"

VstBasicParams::VstBasicParams() :
	blocksize(1024),
	samplerate(44100)
{
}

VSTBase::VSTBase(std::string& pluginPath)
{
	if (loadPlugin(pluginPath))
	{
		if (configurePluginCallbacks() != -1)
		{
			pluginReady = true;
		}
		else Debug::Log("Error: Plugin Failed to configure callbacks"); 
	}
	else Debug::Log("Error, plugin failed to load");
}

void VSTBase::silenceChannel(std::vector<std::vector<float>> channelData) {

	for (int channel = 0; channel < channelData.size(); channel++) {
		for (long frame = 0; frame < channelData[channel].size(); frame++) {
			channelData[channel][frame] = 0.0f;
		}
	}
}

int VSTBase::loadPlugin(std::string& path) {
	Debug::Log("load plugin called");
	std::wstring widestr = std::wstring(path.begin(), path.end());
	const wchar_t* widecstr = widestr.c_str();
	HMODULE modulePtr = LoadLibrary(widecstr);

	vstPluginFuncPtr mainEntryPoint;
	if (modulePtr) {
		Debug::Log("Module pointer loaded");
		mainEntryPoint = (vstPluginFuncPtr)GetProcAddress(modulePtr, "VSTPluginMain");
		if (!mainEntryPoint)
		{
			Debug::Log("VSTPluginMain is null");
		}
		if (!mainEntryPoint) mainEntryPoint = (vstPluginFuncPtr)GetProcAddress(modulePtr, "VstPluginMain()"); 

		if (!mainEntryPoint) Debug::Log("VSTPluginMain() is null");

		if (!mainEntryPoint) mainEntryPoint = (vstPluginFuncPtr)GetProcAddress(modulePtr, "main"); 
		
		if (!mainEntryPoint) Debug::Log("main is null");
	}
	else
	{
		Debug::Log("C: Failed trying to load VST");
		plugin = NULL;
		return 0;
	}

	plugin = mainEntryPoint(hostCallback);
	if (plugin == NULL)
	{
		Debug::Log("Error, falied to instantiate plugin");
		return 0;
	}
	else Debug::Log("Plugin instantiated");
	pluginNumInputs = plugin->numInputs;
	pluginNumOutputs = plugin->numOutputs;
	Debug::Log("In out setup");
	return 1;
} 

int VSTBase::configurePluginCallbacks(/*AEffect *plugin*/) {
		// Check plugin's magic number
		// If incorrect, then the file either was not loaded properly, is not a
		// real VST plugin, or is otherwise corrupt.
		if (plugin == NULL)
		{
			Debug::Log("Error, no plugin");
			return 0;
		}
		if (plugin->magic != kEffectMagic) {
			Debug::Log("C: Plugin's magic number is bad\n");
			return -1;
		}

		// Create dispatcher handle
		dispatcherFuncPtr dispatcher = (dispatcherFuncPtr)(plugin->dispatcher);
		if (dispatcher == NULL)
		{
			Debug::Log("C: dispatcher is NULL\n");
			return -1;
		}

		//0 out char array
		for (int i = 0; i < TEMP_PARAM_NAME_SIZE; i++) tempParamName[i] = 0;	

		for (int i = 0; i < plugin->numParams; i++)
		{
			plugin->dispatcher(plugin, effGetParamName, i, 0, tempParamName, 0);
			std::string paramAsString(tempParamName);
			paramNames.push_back(paramAsString);
		}

		// Set up plugin callback functions
		plugin->getParameter = (getParameterFuncPtr)plugin->getParameter;
		plugin->processReplacing = (processFuncPtr)plugin->processReplacing;
		plugin->setParameter = (setParameterFuncPtr)plugin->setParameter;

		return plugin->magic; //added 2/10. was just plugin...
	}

int VSTBase::getNumParams()
{
	if (plugin == nullptr) return -1;

	else return plugin->numParams;
}

void VSTBase::setParam(int paramIndex, float p_value)
{
	plugin->setParameter(plugin, paramIndex, p_value);
}

float VSTBase::getParam(int index)
{
	return plugin->getParameter(plugin, index);
}

std::string& VSTBase::getParamName(int index)
{
	return paramNames[index];
}

void VSTBase::startPlugin(/*AEffect *plugin*/) {
	if (plugin == NULL)
	{
		Debug::Log("Error, no plugin in startPlugin()");
		return;
	}
	plugin->dispatcher(plugin, effOpen, 0, 0, NULL, 0.0f);

	// Set some default properties
	float sampleRate = 44100.0f; ////////////////////////////this needs to come from Unity!!!!!! 
	plugin->dispatcher(plugin, effSetSampleRate, 0, 0, NULL, sampleRate);
	plugin->dispatcher(plugin, effSetBlockSize, 0, blocksize, NULL, 0.0f);
	//plugin->dispatcher(plugin, effSet)
	resumePlugin(/*plugin*/);
}

void VSTBase::resumePlugin(/*AEffect *plugin*/) {
	if (plugin == NULL)
	{
		Debug::Log("Error, no plugin in resumePlugin()");
		return;
	}
	plugin->dispatcher(plugin, effMainsChanged, 0, 1, NULL, 0.0f);
}

void VSTBase::suspendPlugin(/*AEffect *plugin*/) {
	if (plugin == NULL)
	{
		Debug::Log("Error, no plugin in suspendPlugin()");
		return;
	}
	plugin->dispatcher(plugin, effMainsChanged, 0, 0, NULL, 0.0f);
}

bool VSTBase::canPluginDo(char *canDoString) {
	if (plugin == NULL)
	{
		Debug::Log("Error, no plugin in canPluginDo()");
		return false;
	}
	return (plugin->dispatcher(plugin, effCanDo, 0, 0, (void*)canDoString, 0.0f) > 0);
}

void VSTBase::setVstIndex(int p_index)
{
	vstIndex = p_index;
}

extern "C"
{
	VstIntPtr hostCallback(AEffect* effect, VstInt32 opcode, VstInt32 index, VstIntPtr value, void* ptr, float opt) {
		//Debug::Log("Opcode = ");
		//Debug::Log(opcode);
		switch (opcode) {
		case audioMasterVersion:
			return 2400;
		case audioMasterIdle:
			effect->dispatcher(effect, effEditIdle, 0, 0, 0, 0);
			// Handle other opcodes here... there will be lots of them
		default:
			//debugMessage = "C: Plugin requested value of opcode %d\n";
			break;
		}
	}
}
