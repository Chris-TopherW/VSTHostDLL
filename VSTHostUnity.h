//#pragma once
//
//#include "stdafx.h"
//
//#define VSTEXPORT __declspec(dllexport) 
//
//extern "C"
//{
//	const wchar_t* GetWC(const char *c); 
//	VSTEXPORT void setBlockSize(int p_blocksize); 
//	// Main host callback
//	VstIntPtr VSTCALLBACK hostCallback(AEffect *effect, VstInt32 opcode, VstInt32 index,
//		VstIntPtr value, void *ptr, float opt); 
//	VSTEXPORT /*AEffect* */ void loadPlugin(/*char* path*/); 
//	VSTEXPORT int configurePluginCallbacks(/*AEffect *plugin*/); 
//	VSTEXPORT void startPlugin(/*AEffect *plugin*/); 
//	VSTEXPORT void resumePlugin(/*AEffect *plugin*/); 
//	VSTEXPORT void suspendPlugin(/*AEffect *plugin*/); 
//	VSTEXPORT int getNumParams(); 
//	VSTEXPORT void setParam(int paramIndex, float p_value); 
//	VSTEXPORT float getParam(int index); 
//	VSTEXPORT char* getParamName(int index); 
//	VSTEXPORT void initializeIO(); 
//	VSTEXPORT float* processAudio(float* in, long numFrames, int numChannels); 
//	VSTEXPORT void silenceChannel(float **channelData, int numChannels, long numFrames); 
//	VSTEXPORT void midiEvent(int status, int mess1, int mess2, long delaySamps); 
//	//VSTEXPORT void processMidi(/*AEffect *plugin, */VstEvents *events); n
//	VSTEXPORT void shutdown(); 
//	VSTEXPORT int getNumPluginInputs(); 
//	VSTEXPORT int getNumPluginOutputs(); 
//}
//
////debugger
//extern "C"
//{
//	//Create a callback delegate
//	typedef void(*FuncCallBack)(const char* message, int color, int size);
//	static FuncCallBack callbackInstance = nullptr;
//	VSTEXPORT void RegisterDebugCallback(FuncCallBack cb);
//}
//
//
//// Plugin's entry point
//typedef AEffect *(*vstPluginFuncPtr)(audioMasterCallback host);
//// Plugin's dispatcher function
//typedef VstIntPtr(*dispatcherFuncPtr)(AEffect *effect, VstInt32 opCode,
//	VstInt32 index, VstInt32 value, void *ptr, float opt);
//// Plugin's getParameter() method
//typedef float(*getParameterFuncPtr)(AEffect *effect, VstInt32 index);
//// Plugin's setParameter() method
//typedef void(*setParameterFuncPtr)(AEffect *effect, VstInt32 index, float value);
//// Plugin's processEvents() method
//typedef VstInt32(*processEventsFuncPtr)(VstEvents *events);
//// Plugin's process() method
//typedef void(*processFuncPtr)(AEffect *effect, float **inputs,
//	float **outputs, VstInt32 sampleFrames);
//
//
