//// VSTHostUnity.cpp : Defines the exported functions for the DLL application.
////
//
//#include "stdafx.h"
//#include <algorithm>
//#include <Objbase.h>
//#include <tchar.h>
//#include "DebugCPP.h"
//
//extern "C" {
//	float** pluginInputs;
//	float** pluginOutputs;
//	unsigned int blocksize = 1024;
//	float outputHolder[1024];
//	char* pszReturn = NULL;
//	wchar_t* wc;
//	//hack in only one plugin for test purposes
//	AEffect* plugin = NULL;
//	int pluginNumInputs = -1;
//	int pluginNumOutputs = -1;
//	char** paramNames;
//
//	void shutdown()
//	{
//		plugin->dispatcher(plugin, effMainsChanged, 0, 0, NULL, 0.0f);
//		for (int i = 0; i < plugin->numParams; i++)
//		{
//			free(paramNames[i]);
//		}
//		free(paramNames);
//		
//		free(pszReturn);
//		free(wc);
//		for (int i = 0; i < getNumPluginInputs(); i++)
//		{
//			free(pluginInputs[i]);
//		}
//		for (int i = 0; i < getNumPluginOutputs(); i++)
//		{
//			free(pluginOutputs[i]);
//		}
//		free(pluginInputs);
//		free(pluginOutputs);
//	}
//
//	void setBlockSize(int p_blocksize)
//	{
//		blocksize = p_blocksize;
//	}
//
//	/*AEffect* */ void loadPlugin(/*char* path*/) {
//
//		HMODULE modulePtr = LoadLibrary(_T("C:\\Users\\chriswratt\\Documents\\UnityProjects\\UnityMidiLib\\VSTHostUnity\\VSTHostUnity\\TAL-Reverb-2.dll"));
//		//HMODULE modulePtr = LoadLibrary(_T("D:\\UnityProjects\\usingExternalCpp\\VSTHostUnity\\VSTHostUnity\\Reverb.dll"));
//
//		vstPluginFuncPtr mainEntryPoint;
//		if (modulePtr) {
//			mainEntryPoint = (vstPluginFuncPtr)GetProcAddress(modulePtr, "VSTPluginMain");
//			if (!mainEntryPoint)
//			{
//				Debug::Log("VSTPluginMain is null");
//			}
//			if (!mainEntryPoint) {
//				mainEntryPoint = (vstPluginFuncPtr)GetProcAddress(modulePtr, "VstPluginMain()");
//			}
//			if (!mainEntryPoint)
//			{
//				Debug::Log("VstPluginMain() is null");
//			}
//			if (!mainEntryPoint) {
//				mainEntryPoint = (vstPluginFuncPtr)GetProcAddress(modulePtr, "main");
//			}
//			if (!mainEntryPoint)
//			{
//				Debug::Log("main is null");
//			}
//		}
//		else
//		{
//			Debug::Log("C: Failed trying to load VST", Color::Black);
//			//return NULL;
//			plugin = NULL;
//			return;
//		}
//
//		plugin = mainEntryPoint(hostCallback); //for some reason this totally breaks in 64 bit build!
//		if (plugin == NULL)
//		{
//			Debug::Log("Error, falied to instantiate plugin");
//		}
//
//		pluginNumInputs = plugin->numInputs;
//		pluginNumOutputs = plugin->numOutputs;
//		return;
//	}
//
//	int configurePluginCallbacks(/*AEffect *plugin*/) {
//		// Check plugin's magic number
//		// If incorrect, then the file either was not loaded properly, is not a
//		// real VST plugin, or is otherwise corrupt.
//		if (plugin == NULL)
//		{
//			Debug::Log("Error, no plugin");
//			return 0;
//		}
//		if (plugin->magic != kEffectMagic) {
//			Debug::Log("C: Plugin's magic number is bad\n", Color::Black);
//			return -1;
//		}
//
//		// Create dispatcher handle
//		dispatcherFuncPtr dispatcher = (dispatcherFuncPtr)(plugin->dispatcher);
//		if (dispatcher == NULL)
//		{
//			Debug::Log("C: dispatcher is NULL\n", Color::Black);
//		}
//
//		paramNames = (char**)malloc(sizeof(char*) * plugin->numParams);
//		for (int i = 0; i < plugin->numParams; i++)
//		{
//			paramNames[i] = (char*)malloc(sizeof(char) * 128);
//			plugin->dispatcher(plugin, effGetParamName, i, 0, paramNames[i], 0);
//		}
//
//		// Set up plugin callback functions
//		plugin->getParameter = (getParameterFuncPtr)plugin->getParameter;
//		plugin->processReplacing = (processFuncPtr)plugin->processReplacing;
//		plugin->setParameter = (setParameterFuncPtr)plugin->setParameter;
//
//		return plugin->magic; //added 2/10. was just plugin...
//	}
//
//	int getNumParams()
//	{
//		if (plugin == NULL)
//		{
//			Debug::Log("Error, no plugin");
//			return 0;
//		}
//		return plugin->numParams;
//	}
//
//	void setParam(int paramIndex, float p_value)
//	{
//		plugin->setParameter(plugin, paramIndex, p_value);
//	}
//
//	float getParam(int index)
//	{
//		return plugin->getParameter(plugin, index);
//	}
//
//	char* getParamName(int index)
//	{
//		plugin->dispatcher(plugin, effGetParamName, index, 0, paramNames[index], 0);
//		return paramNames[index];
//	}
//
//	void startPlugin(/*AEffect *plugin*/) {
//		if (plugin == NULL)
//		{
//			Debug::Log("Error, no plugin in startPlugin()");
//			return;
//		}
//		plugin->dispatcher(plugin, effOpen, 0, 0, NULL, 0.0f);
//
//		// Set some default properties
//		float sampleRate = 44100.0f;
//		plugin->dispatcher(plugin, effSetSampleRate, 0, 0, NULL, sampleRate);
//		//int blocksize = 512;
//		plugin->dispatcher(plugin, effSetBlockSize, 0, blocksize, NULL, 0.0f);
//		//plugin->dispatcher(plugin, effSet)
//		resumePlugin(/*plugin*/);
//
//
//		silenceChannel(pluginInputs, getNumPluginInputs(), blocksize);
//		silenceChannel(pluginOutputs, getNumPluginOutputs(), blocksize);
//	}
//
//	void resumePlugin(/*AEffect *plugin*/) {
//		if (plugin == NULL)
//		{
//			Debug::Log("Error, no plugin in resumePlugin()");
//			return;
//		}
//		plugin->dispatcher(plugin, effMainsChanged, 0, 1, NULL, 0.0f);
//	}
//
//	void suspendPlugin(/*AEffect *plugin*/) {
//		if (plugin == NULL)
//		{
//			Debug::Log("Error, no plugin in suspendPlugin()");
//			return;
//		}
//		plugin->dispatcher(plugin, effMainsChanged, 0, 0, NULL, 0.0f);
//	}
//
//	bool canPluginDo(char *canDoString) {
//		if (plugin == NULL)
//		{
//			Debug::Log("Error, no plugin in canPluginDo()");
//			return false;
//		}
//		return (plugin->dispatcher(plugin, effCanDo, 0, 0, (void*)canDoString, 0.0f) > 0);
//	}
//
//	VstIntPtr VSTCALLBACK hostCallback(AEffect *effect, VstInt32 opcode, VstInt32 index,
//		VstIntPtr value, void *ptr, float opt) {
//		//Debug::Log("Opcode = ");
//		//Debug::Log(opcode);
//		switch (opcode) {
//		case audioMasterVersion:
//			return 2400;
//		case audioMasterIdle:
//			effect->dispatcher(effect, effEditIdle, 0, 0, 0, 0);
//			// Handle other opcodes here... there will be lots of them
//		default:
//			//debugMessage = "C: Plugin requested value of opcode %d\n";
//			break;
//		}
//	}
//	 
//	void initializeIO() {
//		pluginInputs = (float**)malloc(sizeof(float**) * plugin->numInputs);
//		pluginOutputs = (float**)malloc(sizeof(float**) * plugin->numOutputs);
//		for (int channel = 0; channel < plugin->numInputs; channel++) {
//			pluginInputs[channel] = (float*)malloc(sizeof(float) * blocksize);
//		}
//		for (int channel = 0; channel < plugin->numOutputs; channel++) {
//			pluginOutputs[channel] = (float*)malloc(sizeof(float) * blocksize);
//		}
//	}
//	
//	float* processAudio(float* audioThrough, long numFrames, int numChannels)
//	{
//		silenceChannel(pluginInputs, pluginNumInputs, numFrames);
//		silenceChannel(pluginOutputs, pluginNumOutputs, numFrames);
//
//		/////////de-interleaver////////
//		int j = 0;
//		for (int samp = 0; samp < numFrames * numChannels; samp += numChannels)
//		{
//			pluginInputs[0][j] = audioThrough[samp];
//			if (numChannels == 2)
//			{
//				if (pluginNumInputs == 2)
//				{
//					//add right chan for stereo in and out
//					pluginInputs[1][j] = audioThrough[samp + 1];
//				}
//				else if(pluginNumInputs == 1)
//				{
//					//sum left and right ins at half gain
//					pluginInputs[0][j] = audioThrough[samp] * 0.5f + audioThrough[samp + 1] * 0.5f;
//				}
//			}
//			else if (numChannels == 1 && pluginNumInputs == 2)
//			{
//				//send mono input to each plugin channel
//				pluginInputs[1][j] = audioThrough[samp];
//			}
//			j++;
//		}
//		
//		plugin->processReplacing(plugin, pluginInputs, pluginOutputs, numFrames);
//
//		/////////re-interleaver////////
//		j = 0;
//		for (int samp = 0; samp < numFrames * numChannels; samp += numChannels)
//		{
//			audioThrough[samp] = pluginOutputs[0][j];
//			if (numChannels == 2)
//			{
//				if (pluginNumOutputs == 2)
//				{
//					audioThrough[samp + 1] = pluginOutputs[1][j];
//				}
//				else if (pluginNumOutputs == 1)
//				{
//					//add plugin left output to right channel
//					audioThrough[samp + 1] = pluginOutputs[0][j];
//				}
//			}
//			else if (numChannels == 1 && pluginNumOutputs == 2)
//			{
//				//if mono out but plugin is stereo output, sum then half gain
//				audioThrough[samp] = pluginOutputs[0][j] * 0.5f + pluginOutputs[1][j] * 0.5f;
//			}
//			j++;
//		}
//		return audioThrough;
//	}
//
//	void silenceChannel(float **channelData, int numChannels, long numFrames) {
//		for (int channel = 0; channel < numChannels; ++channel) {
//			for (long frame = 0; frame < numFrames; ++frame) {
//				channelData[channel][frame] = 0.0f;
//			}
//		}
//	}
//
//	int getNumPluginInputs()
//	{
//		if (pluginNumInputs == -1)
//		{
//			Debug::Log("Error, plugin inputs not initialised");
//			return pluginNumInputs;
//		}
//		else
//		{
//			return pluginNumInputs;
//		}
//	}
//
//	int getNumPluginOutputs()
//	{
//		if (pluginNumOutputs == -1)
//		{
//			Debug::Log("Error, plugin outputs not initialised");
//			return pluginNumOutputs;
//		}
//		else
//		{
//			return pluginNumOutputs;
//		}
//	}
//
//	void processMidi(/*AEffect *plugin, */VstEvents *events) {
//		if (plugin == NULL) return;
//		plugin->dispatcher(plugin, effProcessEvents, 0, 0, events, 0.0f);
//	}
//
//	const wchar_t* GetWC(const char *c)
//	{
//		const size_t cSize = strlen(c) + 1;
//		if (wc != nullptr)
//		{
//			delete(wc);
//		}
//		wc = new wchar_t[cSize];
//		mbstowcs(wc, c, cSize);
//
//		return wc;
//	}
//}
