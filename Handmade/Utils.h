#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <Windows.h>
#include <fstream>


namespace Utils {
	void ReadResolution(int& X ,int& Y);
	void ReadFullscreen(bool& flag);
	void ReadTileSize(int& X, int& Y);
	void ShowMessage(std::string msg, std::string title);
	void draw();
	void lineBreak(int count);
	std::string space(int count);
	void clearConsole();
	void TypeWrite(const std::string& text, unsigned int delay);
	void Log(const std::string message);
	std::vector<std::string> Split(const std::string str, const char delimiter);
}
