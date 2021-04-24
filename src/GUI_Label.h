
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


class GUI_Label  
{
	private:
		std::string mTextStr;
		sf::Text mText;
		sf::Color mColor;
		sf::Font mFont;
		int mSize;
		sf::Vector2f mPosition;

	public:

		GUI_Label();
		~GUI_Label();

		void setup(std::string textStr,
		sf::Color color,
		sf::Font font,
		int size,
		sf::Vector2f position);
		void render(sf::RenderWindow& window);
		void setString(std::string s) {
			 this->mTextStr = s;
			 this->mText.setString(mTextStr);
		}


};