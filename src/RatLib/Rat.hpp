#ifndef RAT_HPP
#define RAT_HPP

#include <SFML/Graphics.hpp>

namespace swift
{
	enum class Origin
	{
	    Center,
	    TopLeft,
	    TopRight,
	    BottomLeft,
	    BottomRight
	};

	class Rat : public sf::Drawable
	{
		public:
			Rat(sf::Window& w) : window(w)
			{
				drawCursor = false;
				drawToolTip = false;
				toolTipSize.x = 0;
				toolTipSize.y = 0;
				keepInWindow = false;
			}

			~Rat()
			{
				window.setMouseCursorVisible(true);
			}

			void update(sf::Event& event)
			{
				if(event.type == sf::Event::MouseMoved)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);

					if(keepInWindow)
					{
						if(mousePos.x < 0)
							sf::Mouse::setPosition(sf::Vector2i(0, sf::Mouse::getPosition(window).y), window);
						else if(static_cast<unsigned>(mousePos.x) > window.getSize().x - 1)
							sf::Mouse::setPosition(sf::Vector2i(window.getSize().x - 1, sf::Mouse::getPosition(window).y), window);

						if(mousePos.y < 0)
							sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(window).x, 0), window);
						else if(static_cast<unsigned>(mousePos.y) > window.getSize().y - 1)
							sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(window).x, window.getSize().y - 1), window);


						mousePos = sf::Mouse::getPosition(window);
					}
					
					cursorSprite.setPosition(static_cast<sf::Vector2f>(mousePos));
					toolTipText.setPosition(mousePos.x + cursorSprite.getGlobalBounds().width - toolTipText.getLocalBounds().left,
					                        mousePos.y - toolTipText.getLocalBounds().top);
				}
			}

			// Args:
			// 		'file' - string to image file to load as cursor
			// 		'scale' - float to specify scale of sprite
			// Returns:
			// 		true if image was loaded
			// 		false if otherwise
			bool loadCursor(const std::string& file, float scale)
			{
				if(!cursorTexture.loadFromFile(file))
					return false;

				cursorTexture.setSmooth(true);
				cursorSprite.setTexture(cursorTexture);
				cursorSprite.setScale(scale, scale);
				sf::Mouse::setPosition(sf::Vector2i(0, 0), window);
				cursorSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

				drawCursor = true;

				return true;
			}

			void setCursorOrigin(Origin center)
			{
				switch(center)
				{
					case Origin::Center:
						cursorSprite.setOrigin(cursorSprite.getLocalBounds().width / 2, cursorSprite.getLocalBounds().height / 2);
						break;
					case Origin::TopLeft:
						cursorSprite.setOrigin(0, 0);
						break;
					case Origin::TopRight:
						cursorSprite.setOrigin(cursorSprite.getLocalBounds().width - 1, 0);
						break;
					case Origin::BottomLeft:
						cursorSprite.setOrigin(0, cursorSprite.getLocalBounds().height - 1);
						break;
					case Origin::BottomRight:
						cursorSprite.setOrigin(cursorSprite.getLocalBounds().width - 1, cursorSprite.getLocalBounds().height - 1);
						break;
				}
			}

			void lockToWindow(bool w)
			{
				keepInWindow = w;
			}

			const sf::FloatRect getCursorDims() const
			{
				return cursorSprite.getGlobalBounds();
			}

			void setDrawCursor(bool d)
			{
				drawCursor = d;
				window.setMouseCursorVisible(!d);
			}

			bool loadToolTip(const std::string& file, sf::Color color = sf::Color::White)
			{
				if(!toolTipFont.loadFromFile(file))
					return false;

				toolTipText.setFont(toolTipFont);
				toolTipText.setColor(color);
				toolTipText.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

				drawToolTip = true;

				return true;
			}

			bool loadToolTip(const sf::Font& font, sf::Color color = sf::Color::White)
			{
				toolTipFont = font;
				toolTipText.setFont(toolTipFont);
				toolTipText.setColor(color);
				toolTipText.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

				drawToolTip = true;

				return true;
			}

			void setToolTipBounds(sf::Vector2f size)
			{
				toolTipSize = size;
				toolTipText.setCharacterSize(std::min(	toolTipText.getCharacterSize() * (toolTipSize.x / toolTipText.getGlobalBounds().width), 
														toolTipText.getCharacterSize() * (toolTipSize.y / toolTipText.getGlobalBounds().height)));
			}

			void setToolTipText(const std::string& t)
			{
				toolTipText.setString(t);
				if(toolTipSize.x != 0 && toolTipSize.y != 0)
					toolTipText.setScale(toolTipSize.x / toolTipText.getLocalBounds().width, toolTipSize.y / toolTipText.getLocalBounds().height);
				else
					toolTipText.setScale(1, 1);
			}

			void setDrawToolTip(bool d)
			{
				drawToolTip = d;
			}

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				window.setMouseCursorVisible(false);
				if(drawCursor)
					target.draw(cursorSprite);
				if(drawToolTip)
					target.draw(toolTipText);
			}

			sf::Window& window;

			// cursor variables
			bool drawCursor;
			std::string cursorFile;
			sf::Texture cursorTexture;
			sf::Sprite cursorSprite;

			// tool tip variables
			bool drawToolTip;
			sf::Vector2f toolTipSize;
			sf::Text toolTipText;
			sf::Font toolTipFont;

			// misc variables
			bool keepInWindow;
	};
}

#endif // RAT_HPP
