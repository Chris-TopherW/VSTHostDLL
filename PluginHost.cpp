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

#include "PluginHost.h"

int VstHost::loadEffect(std::string& path)
{
	std::shared_ptr<VSTEffect> vstEffect = std::make_shared<VSTEffect>(path, samplerate, blocksize);
	int vstIndex = audioEffects.size();
	
	vstEffect->setVstIndex(vstIndex);
	audioEffects.push_back(vstEffect);
	Debug::Log("audio effects array size = ");
	Debug::Log((int)audioEffects.size());
	return vstIndex;
}

void VstHost::setBlockSize(int p_blocksize)
{
	blocksize = p_blocksize;
}

std::shared_ptr<VSTEffect> VstHost::getEffect(int vstIndex)
{
	if (audioEffects.size() >= vstIndex)
	{
		return audioEffects[vstIndex];
	}
	else
	{
		Debug::Log("Error: trying to access non-existent audio effect");
		return audioEffects[vstIndex];
	}
}


void VstHost::clearVSTs()
{
	if(audioEffects.size() > 0)
		audioEffects.clear();
}
