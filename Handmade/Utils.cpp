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

void Utils::ReadTileSize(int& X, int& Y)
{
	ifstream settings("Assets/settings.ini");

	string line;

	while (getline(settings, line))
	{
		int i = line.find("tilesize");

		if (i < line.length())
		{
			//resolution found , get the =
			int eq = line.find("=");
			if (eq < line.length())
			{

				string tilesize = line.substr(eq + 1, line.length());
				vector<string> r = Split(tilesize, ',');

				X = stoi(r[0]);
				Y = stoi(r[1]);

			}
			else
			{
				X = 50; 
				Y = 50;
			}

			break;
		}
		else
		{
			X = 50;
			Y = 50;
		}
	}

	settings.close();
}



void Utils::ShowMessage(std::string msg, std::string title)
{
	MessageBoxA(0, msg.c_str(), title.c_str(), MB_OK);
}

void Utils::draw()
{
		std::cout << "#===========================================#" << std::endl;
		std::cout << "#     #           #####                      " << std::endl;
		std::cout << "##   ## #   #    #     # #    #   ##   ##### " << std::endl;
		std::cout << "# # # #  # #     #       #    #  #  #    #   " << std::endl;
		std::cout << "#  #  #   #      #       ###### #    #   #   " << std::endl;
		std::cout << "#     #   #      #       #    # ######   #   " << std::endl;
		std::cout << "#     #   #      #     # #    # #    #   #   " << std::endl;
		std::cout << "#     #   #       #####  #    # #    #   #   " << std::endl;
		std::cout << "#===========================================#" << std::endl;
	
}



void Utils::lineBreak(int count)
{
	for (int i = 0; i < count; i++)
	{
		std::cout << std::endl;
	}
}

std::string Utils::space(int count)
{
	std::string result = "";

	for (int i = 0; i < count; i++)
	{
		result += " ";
	}
	return result;
}

void Utils::clearConsole()
{
	system("cls");
	draw();
}

void Utils::TypeWrite(const std::string& text, unsigned int delay)
{
	//This is A function that i wrote to make an animated text like typewriter whitch is really cool.
//Hope you like it Karsten

		//I loop though all the chars
	for (const char c : text)
	{
		std::cout << c;		//Print the char
		SDL_Delay(delay);	//Wait 
	}
	//If the print finished I go to next line
	lineBreak(1);

}


void Utils::Log(const std::string message)
{
	std::cout << message << std::endl;
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


