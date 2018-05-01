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

#include "VSTHostUnity.h"
#include <string>

#define VSTEXPORT __declspec(dllexport)

//Color Enum
//enum class Color { Red, Green, Blue, Black, White, Yellow, Orange };

class  Debug
{
public:
	static void Log(const char* message);
	static void Log(const std::string message);
	static void Log(const int message);
	static void Log(const char message);
	static void Log(const float message);
	static void Log(const double message);
	static void Log(const bool message);

private:
	static void send_log(const std::stringstream &ss);
};

//debugger
extern "C"
{
	//Create a callback delegate
	typedef void(*FuncCallBack)(const char* message, int size);
	static FuncCallBack callbackInstance = nullptr;
	VSTEXPORT void RegisterDebugCallback(FuncCallBack cb);
}
