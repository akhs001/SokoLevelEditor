#include "Utils.h"

using namespace std;

void Utils::ReadResolution(int& X, int& Y)
{
	ifstream settings("Assets/settings.ini");

	string line;

	while (getline(settings, line))
	{
		int i = line.find("resolution");

		if (i < line.length())
		{
			//resolution found , get the =
			int eq = line.find("=");
			if (eq < line.length())
			{
				//= found.Get the resolution
				string resolution = line.substr(eq + 1, line.length());
				vector<string> r = Split(resolution, ',');

				X = stoi(r[0]);
				Y = stoi(r[1]);
				break;
			}
			else
			{
				//Set default resolution
				X = 800;
				Y = 600;
			}
		}
		else
		{
			//Set default resolution
			X = 800;
			Y = 600;
		}
	}

	settings.close();
}

void Utils::ReadFullscreen(bool& flag)
{
	ifstream settings("Assets/settings.ini");

	string line;

	while (getline(settings, line))
	{
		int i = line.find("fullscreen");

		if (i < line.length())
		{
			//resolution found , get the =
			int eq = line.find("=");
			if (eq < line.length())
			{
				int fs = stoi(line.substr(eq + 1, line.length()));

				switch (fs)
				{
				case 0:
					flag =false;
					break;
				case 1:
					flag = true;
					break;
				}
			
			}
			else
			{
				flag = false;
			}

			break;
		}
		else
		{
			flag = false;
		}
	}

	settings.close();
}

void Utils::ShowMessage(std::string msg, std::string title)
{
	MessageBoxA(0, msg.c_str(), title.c_str(), MB_OK);
}


//Because C++ doesnt have a string.Split function I want to Create my own.
//My idea is to have a string like "thanos:Athanasiadis" and i want to seperate the string 
//using the delimiter ":" so my result is a vector Array of strings with 
//0-> Thanos
//1-> Athanasiadis
//I want to use this method to pass everything via a message, like Color,names,message.
std::vector<std::string> Utils::Split( const std::string str , const char delimiter)
{
	//store the string for spliting in a temp string
	std::string temp = str;
	std::vector<std::string> result;

	int ind=0;
	do
	{
		ind= temp.find(delimiter);
		//Get the left part and store it in the vector array
		result.push_back(temp.substr(0, ind));
		// remove this part from the string so we can go to the next delimiter +1 is for removing the delimiter as well
		temp.erase(0, ind+1);

	} while (ind > 0);
	
	//If its the lastOne addIt to the list as welll
	//result.push_back(temp);


	return result;



}


