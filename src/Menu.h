#pragma once


#include "GUI_Button.h"
#include "GUI_Label.h"

class Menu  
{
	private:
		GUI_Button createNew;
		GUI_Button load;
		GUI_Button quit;
		GUI_Label name;
		sf::Font font;
		sf::Texture madeTex;
		sf::Sprite madeSpr;

	public:

		Menu();
		~Menu();

		void render(sf::RenderWindow *window);
		void setup(sf::Font font, void (*f)(), void (*f1)(), void (*f2)());
		void checkForClicks(sf::Vector2i mousePos);
		bool checkForHover(sf::Vector2i mousePos);
};