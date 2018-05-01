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

#include "VSTEffect.h"

VSTEffect::VSTEffect(std::string& path, int p_samplerate, int p_blocksize) : VSTBase(path)
{
	samplerate = p_samplerate;
	blocksize = p_blocksize;
	if (getPluginReady())
	{
		initializeIO();
		startPlugin();
		if (plugin->flags & effFlagsCanReplacing != effFlagsCanReplacing)
		{
			Debug::Log("Error: Plugin does not support audio input");
		}
	}
}

VSTEffect::~VSTEffect()
{
	plugin->dispatcher(plugin, effMainsChanged, 0, 0, NULL, 0.0f);
}

void VSTEffect::processAudio(float* audioThrough, long numFrames, int numUnityChans)
{
	if (pluginNumInputs == 0)
		return;
	if (plugin->flags & effFlagsCanReplacing != effFlagsCanReplacing)
		return;

	/////////de-interleaver////////
	int framesTimesChan = numFrames * numUnityChans;
	j = 0;
	if (numUnityChans == 2)
	{
		if (pluginNumInputs == 2)
		{
			for (int samp = 0; samp < framesTimesChan; samp += numUnityChans)
			{
				pluginInputs[0][j] = audioThrough[samp];
				pluginInputs[1][j++] = audioThrough[samp + 1];
			}
		}
		else if (pluginNumInputs == 1)
		{
			for (int samp = 0; samp < framesTimesChan; samp += numUnityChans)
			{
				//sum left and right ins at half gain
				pluginInputs[0][j++] = audioThrough[samp] * 0.5f + audioThrough[samp + 1] * 0.5f;
			}
		}
	}
	else if (numUnityChans == 1 && pluginNumInputs == 2)
	{
		for (int samp = 0; samp < framesTimesChan; samp += numUnityChans)
		{
			pluginInputs[0][j] = audioThrough[samp];
			pluginInputs[1][j++] = audioThrough[samp];
		}
	}

	plugin->processReplacing(plugin, pluginInputsStartPtr, pluginOutputsStartPtr, numFrames);

	/////////re-interleaver////////
	j = 0;
	if (numUnityChans == 2)
	{
		if (pluginNumOutputs == 2)
		{
			for (int samp = 0; samp < framesTimesChan; samp += numUnityChans)
			{
				audioThrough[samp] = pluginOutputs[0][j];
				audioThrough[samp + 1] = pluginOutputs[1][j++];
			}
		}
		else if (pluginNumOutputs == 1)
		{
			for (int samp = 0; samp < framesTimesChan; samp += numUnityChans)
			{
				audioThrough[samp] = pluginOutputs[0][j];
				audioThrough[samp + 1] = pluginOutputs[0][j++];
			}
		}
	}
	else if (numUnityChans == 1 && pluginNumOutputs == 2)
	{
		for (int samp = 0; samp < framesTimesChan; samp += numUnityChans)
		{
			//if mono out but plugin is stereo output, sum then half gain
			audioThrough[samp] = pluginOutputs[0][j] * 0.5f + pluginOutputs[1][j++] * 0.5f;
		}
	}
}

void VSTEffect::initializeIO() {
	
	std::vector<float> tempVect;
	tempVect.reserve(blocksize);
	for (int i = 0; i < blocksize; i++)
	{
		tempVect.push_back(0.0f);
	}

	for (int i = 0; i < plugin->numInputs; i++)
	{
		pluginInputs.push_back(tempVect);
	}
	for (int i = 0; i < plugin->numOutputs; i++)
	{
		pluginOutputs.push_back(tempVect);
	}
	
	//hold locations of starts of i/o vectors as raw float** in order to access for plugin.processReplacing
	std::vector<float*> target(pluginInputs.size());
	for (int i = 0; i < pluginInputs.size(); i++)
	{
		target[i] = &*pluginInputs[i].begin();
	}
	pluginInputsStartPtr = (float**)malloc((sizeof(float*) * 2));
	pluginInputsStartPtr[0] = target[0];
	pluginInputsStartPtr[1] = target[1];

	std::vector<float*> target2(pluginOutputs.size());
	for (int i = 0; i < pluginOutputs.size(); i++)
	{
		target2[i] = &*pluginOutputs[i].begin();
	}
	pluginOutputsStartPtr = (float**)malloc((sizeof(float*) * 2));
	pluginOutputsStartPtr[0] = target2[0];
	pluginOutputsStartPtr[1] = target2[1];
}

int VSTEffect::getNumPluginInputs()
{
	if (pluginNumInputs == -1)
	{
		Debug::Log("Error, plugin inputs not initialised");
		return pluginNumInputs;
	}
	else
	{
		return pluginNumInputs;
	}
}

int VSTEffect::getNumPluginOutputs()
{
	if (pluginNumOutputs == -1)
	{
		Debug::Log("Error, plugin outputs not initialised");
		return pluginNumOutputs;
	}
	else
	{
		return pluginNumOutputs;
	}
}
