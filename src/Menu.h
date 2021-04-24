#pragma once


#include "GUI_Button.h"
#include "GUI_Label.h"

class Menu  
{
	private:
		GUI_Button mCreateNew;
		GUI_Button mLoad;
		GUI_Button mQuit;
		GUI_Label mName;
		sf::Font mFont;
		sf::Texture mMadeTex;
		sf::Sprite mMadeSpr;

	public:

		Menu();
		~Menu();

		void render(sf::RenderWindow& window);
		void setup(sf::Font font, void (*f)(), void (*f1)(), void (*f2)());
		void checkForClicks(sf::Vector2i mousePos);
		bool checkForHover(sf::Vector2i mousePos);
};