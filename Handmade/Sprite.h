#ifndef SPRITE_H
#define SPRITE_H

#include <map>
#include <string>
#include <SDL_render.h>

class Sprite
{

public:

	enum class FlipType { NO_FLIP = SDL_FLIP_NONE, 
		                  HORIZONTAL = SDL_FLIP_HORIZONTAL, 
		                  VERTICAL = SDL_FLIP_VERTICAL };

public:

	static bool Load(const std::string& filename, const std::string& mapIndex);
	static void Unload(const std::string& mapIndex = "");

public:

	Sprite();           

public:

	bool IsAnimationDead();
	void IsAnimated(bool flag);
	bool IsAnimationLooping();
	void IsAnimationLooping(bool flag);

public:

	void SetImageCel(int column, int row);
	void SetAnimationVelocity(float velocity);
	bool SetImage(const std::string& mapIndex);
	void SetSpriteDimension(int width, int height);
	void SetImageDimension(int columns, int rows, int width, int height);
	
public:

	void Update(int deltaTime);
	void Draw(int positionX = 0, int positionY = 0, double angle = 0.0, 
		      FlipType flipType = FlipType::NO_FLIP);

private:

	static std::map<std::string, SDL_Texture*>* s_images;

private:

	int m_imageIndex;
	float m_animationVelocity;
	
	bool m_isAnimated;
	bool m_isAnimationDead;
	bool m_isAnimationLooping;
	bool m_isAnimationLoopFinal;

	SDL_Texture* m_image;               //handle on the image in memory. This is only a reference (no need for copy ctor)
	SDL_Point m_celDimension;           //dimension (in pixels) of the individual image 'cutout' 
	SDL_Point m_imageDimension;         //dimension (in pixels) of the image on the hard-drive (resolution)
	SDL_Point m_spriteDimension;        //dimension (in pixels) of the sprite image rendered on-screen

};

#endif