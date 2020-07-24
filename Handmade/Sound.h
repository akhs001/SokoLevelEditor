#ifndef SOUND_H
#define SOUND_H

#include <map>
#include <string>
#include <SDL_mixer.h>

class Sound
{

public:

	static void Output() {};
	static bool Load(const std::string& filename, const std::string& mapIndex);
	static void Unload(const std::string& mapIndex = "");

public:

	Sound();

public:

	void SetVolume(int volume);
	bool SetSound(const std::string& mapIndex);

public:

	bool Play(int loop = 0);			
	
private:

	static std::map<std::string, Mix_Chunk*>* s_sounds;

private:
	
	Mix_Chunk* m_sound;
					
};

#endif	