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

#include "DebugCPP.h"
#include <sstream>
#include <iostream>
using namespace std;
//#define isConsoleVersion 1
#define isUnityDLL 1

//-------------------------------------------------------------------
void  Debug::Log(const char* message) {
	
#ifdef isConsoleVersion
	cout << message << endl;
#elif isUnityDLL
	if (callbackInstance != nullptr)
		callbackInstance(message, (int)strlen(message));
#endif
}

void  Debug::Log(const std::string message) {
	
#ifdef isConsoleVersion
	cout << message << endl;
#elif isUnityDLL
	const char* tmsg = message.c_str();
	if (callbackInstance != nullptr)
		callbackInstance(tmsg, (int)strlen(tmsg));
#endif
}

void  Debug::Log(const int message) {
	
#ifdef isConsoleVersion
	cout << message << endl;
#elif isUnityDLL
	std::stringstream ss;
	ss << message;
	send_log(ss);
#endif
}

void  Debug::Log(const char message) {
	
#ifdef isConsoleVersion
	cout << message << endl;
#elif isUnityDLL
	std::stringstream ss;
	ss << message;
	send_log(ss);
#endif
}

void  Debug::Log(const float message) {
	
#ifdef isConsoleVersion
	cout << message << endl;
#elif isUnityDLL
	std::stringstream ss;
	ss << message;
	send_log(ss);
#endif
}

void  Debug::Log(const double message) {
	
#ifdef isConsoleVersion
	cout << message << endl;
#elif isUnityDLL
	std::stringstream ss;
	ss << message;
	send_log(ss);
#endif
}

void Debug::Log(const bool message) {
	
#ifdef isConsoleVersion
	cout << message << endl;
#elif isUnityDLL
	std::stringstream ss;
	if (message)
		ss << "true";
	else
		ss << "false";

	send_log(ss);
#endif
}

void Debug::send_log(const std::stringstream &ss) {
	const std::string tmp = ss.str();
	const char* tmsg = tmp.c_str();
	if (callbackInstance != nullptr)
		callbackInstance(tmsg, (int)strlen(tmsg));
}
//-------------------------------------------------------------------

//Create a callback delegate
void RegisterDebugCallback(FuncCallBack cb) {
	callbackInstance = cb;
}
