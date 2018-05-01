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

#include "VSTEffect.h"

class VstHost : public VstBasicParams
{
public:
	void setBlockSize(int p_blocksize);
	int loadEffect(std::string& path); //returns index
	std::shared_ptr<VSTEffect> getEffect(int index);
	static std::vector<std::vector<float>> inputsHolder;
	static std::vector<std::vector<float>> outputsHolder;
	inline int getAudioFxVecSize() { return audioEffects.size(); }
	void clearVSTs();
		
private:
	std::vector<std::shared_ptr<VSTEffect>> audioEffects;
};


// Plugin's entry point
typedef AEffect *(*vstPluginFuncPtr)(audioMasterCallback host);
// Plugin's dispatcher function
typedef VstIntPtr(*dispatcherFuncPtr)(AEffect *effect, VstInt32 opCode,
	VstInt32 index, VstInt32 value, void *ptr, float opt);
// Plugin's getParameter() method
typedef float(*getParameterFuncPtr)(AEffect *effect, VstInt32 index);
// Plugin's setParameter() method
typedef void(*setParameterFuncPtr)(AEffect *effect, VstInt32 index, float value);
// Plugin's processEvents() method
typedef VstInt32(*processEventsFuncPtr)(VstEvents *events);
// Plugin's process() method
typedef void(*processFuncPtr)(AEffect *effect, float **inputs,
	float **outputs, VstInt32 sampleFrames);

