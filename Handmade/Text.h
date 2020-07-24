#ifndef TEXT_H
#define TEXT_H

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Text
{

public:

	enum class FontSize { SMALL = 72, MEDIUM = 144, LARGE = 300 };  //based on 72DPI - keep in multiples of 6

public:

	static bool Initialize();
	static bool Load(const std::string& filename, 
		             const std::string& mapIndex, FontSize fontSize = FontSize::SMALL);
	static void Unload(const std::string& mapIndex = "");
	static void ShutDown();

public:

	Text();
	Text(const Text& copy);
	~Text();

public:

	const SDL_Point& GetSize() const;
	const std::string& GetText() const;

public:

	void SetSize(int width, int height);
	void SetText(const std::string& text);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	bool SetFont(const std::string& mapIndex);

public:

	void Draw(int positionX = 0, int positionY = 0);

private:

	void CreateText();

private:

	static std::map<std::string, TTF_Font*>* s_fonts;

private:

	std::string m_text;               //the raw string text that is used to created the text object to be rendered
	SDL_Point m_textSize;             //size (in pixels) of the rendered text in its entirety

	TTF_Font* m_font;                 //handle on the font in memory. This is only a reference (no need for copy ctor)
	SDL_Color m_color;                //color of the rendered text
	SDL_Texture* m_texture;           //handle on the text object after using font, color and string to create it

};

#endif