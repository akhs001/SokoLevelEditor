#ifndef MUSIC_H
#define MUSIC_H

#include <map>
#include <string>
#include <SDL_mixer.h>

class Music
{

public:

	enum class LoopType  { PLAY_ONCE = 1, PLAY_ENDLESS = -1 };
public:

	static void Output() {};
	static bool Initialize(int frequency = 44100, int chunkSize = 1024);
	static bool Load(const std::string& filename, const std::string& mapIndex);
	static void Unload(const std::string& mapIndex = "");
	static void ShutDown();

public:

	Music();

public:

	void SetVolume(int volume);
	bool SetMusic(const std::string& mapIndex);

public:

	bool Play(LoopType loopType = LoopType::PLAY_ONCE);
	void Pause();
	void Resume();
	void Stop();    			

private:

	static std::map<std::string, Mix_Music*>* s_music;

private:
	
	Mix_Music* m_music;
					
};

#endif