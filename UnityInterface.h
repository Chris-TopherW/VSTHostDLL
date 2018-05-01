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

#pragma once
#include "PluginHost.h"
#define VSTEXPORT __declspec(dllexport) 
#define isUnityDLL 1

std::shared_ptr<VstHost> vstHost;
bool hostInitialised = false;

extern "C" {
	VSTEXPORT void initHost();
	VSTEXPORT int setSampleRate(long p_sampleRate);
	VSTEXPORT int setHostBlockSize(int p_blocksize);
	VSTEXPORT int loadEffect(const char* path);
	VSTEXPORT void processBuffer(int vstIndex, float* audioThrough, long numFrames, int numChannels);
	VSTEXPORT int getNumPluginInputs(int vstIndex);
	VSTEXPORT int getNumPluginOutputs(int vstIndex);
	VSTEXPORT int getNumParams(int vstIndex);
	VSTEXPORT float getParam(int vstIndex, int paramIndex);
	VSTEXPORT char* getParamName(int vstIndex, int paramIndex);
	VSTEXPORT int setParam(int vstIndex, int paramIndex, float p_value);
	VSTEXPORT void clearVSTs();
}
