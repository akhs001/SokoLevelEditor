#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <Windows.h>
#include <fstream>

namespace Utils {
	//Reading from .ini settings file
	void ReadResolution(int& X ,int& Y);
	void ReadFullscreen(bool& flag);
	//*******************************

	void ShowMessage(std::string msg, std::string title);

	std::vector<std::string> Split(const std::string str, const char delimiter);
}
