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

#include "UnityInterface.h"

void initHost()
{
	if (!hostInitialised)
	{
		vstHost = std::make_shared<VstHost>();
		hostInitialised = true;
	}
	else
	{
		Debug::Log("Error: host already initialised, exiting initHost()");
	}
}

int setSampleRate(long p_sampleRate)
{
	if (hostInitialised)
	{
		vstHost->samplerate = p_sampleRate;
		return 1;
	}
	else
	{
		Debug::Log("Host not initialised, set sr failed");
		return 0;
	}
}

int setHostBlockSize(int p_blocksize)
{
	if (hostInitialised)
	{
		vstHost->blocksize = p_blocksize;
		return 1;
	}
	else
	{
		Debug::Log("Host not initialised, set blocksize failed");
		return 0;
	}
}

int loadEffect(const char* path)
{
	if (hostInitialised)
	{
		std::string effectLocation(path);
		Debug::Log("Effect location is: ");
		Debug::Log(effectLocation);
		int effectIndex = vstHost->loadEffect(effectLocation);
		//error catcher
		if (vstHost->getEffect(effectIndex)->getPluginReady() != true) return -1;
			
		return effectIndex;
	}
	else
	{
		Debug::Log("Host not initialised, load effect failed");
		return -1;
	}
}

void processBuffer(int vstIndex, float* audioThrough, long numFrames, int numChannels)
{
	vstHost->getEffect(vstIndex)->processAudio(audioThrough, numFrames, numChannels);
}

int getNumPluginInputs(int vstIndex)
{
	return vstHost->getEffect(vstIndex)->getNumPluginInputs();
}

int getNumPluginOutputs(int vstIndex)
{
	return vstHost->getEffect(vstIndex)->getNumPluginOutputs();
}

//////////////////////////////////////Parameters/////////////////////////////////////////////////////////

int getNumParams(int vstIndex)
{
	return vstHost->getEffect(vstIndex)->getNumParams();
}

float getParam(int vstIndex, int paramIndex)
{
	return vstHost->getEffect(vstIndex)->getParam(paramIndex);
}

char* getParamName(int vstIndex, int paramIndex)
{
	const char *cstr = vstHost->getEffect(vstIndex)->getParamName(paramIndex).c_str();
	return const_cast<char*>(cstr); //this could be dangerous...?
}

int setParam(int vstIndex, int paramIndex, float p_value)
{
	if (hostInitialised)
	{
		vstHost->getEffect(vstIndex)->setParam(paramIndex, p_value);
		return 1;
	}
	else return 0;
}

void clearVSTs()
{
	vstHost->clearVSTs();
}
