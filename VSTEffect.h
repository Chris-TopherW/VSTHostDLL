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
#include "VSTBase.h"

class VSTEffect : public VSTBase
{
public:
	VSTEffect(std::string& path, int blocksize, int samplerate);
	~VSTEffect();
	void processAudio(float* audioThrough, long numFrames, int numChannels);
	int getNumPluginInputs();
	int getNumPluginOutputs();
	void initializeIO();

private:
	std::vector<std::vector<float>> pluginInputs;
	std::vector<std::vector<float>> pluginOutputs;
	std::string pluginPath;
	float** pluginInputsStartPtr = nullptr;
	float** pluginOutputsStartPtr = nullptr;
	int j = 0;

};
