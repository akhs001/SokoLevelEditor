#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"

class Background : public GameObject
{

public:

	Background(const std::string& imageFilename);
	virtual ~Background();

public:

	virtual void Update(int deltaTime) {}
	virtual bool Draw();

public:

	void PlayMusic();
	void StopMusic();

protected:

	bool m_isPlaying;
	std::string m_imageName;
	std::string m_audioName;

	Music m_music;
	Sprite m_image;

};

#endif
