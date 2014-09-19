#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>

#include "Widget.hpp"

namespace cstr
{
	class Container : public Widget
	{
		public:
			Container(sf::IntRect r, bool s)
				:	Widget(r),
					border(0),
				    isVisible(true),
				    scrollable(s)
			{
			}
			
			Container(sf::Vector2i size, bool s)
				:	Widget({0, 0, size.x, size.y}),
					border(0),
					isVisible(true),
					scrollable(s)
			{
			}

			virtual ~Container()
			{
				for(auto& w : widgets)
					delete w;
			}
			
			template<typename W>
			W& addWidget(W* w)
			{
				static_assert(std::is_base_of<Widget, W>::value, "W must be a child of cstr::Widget");
				
				widgets.push_back(w);
				
				reposition();
				
				return *w;
			}
			
			sf::FloatRect getGlobalBounds() const
			{
				return static_cast<sf::FloatRect>(rect);
			}
			
			bool isContainer() const
			{
				return true;
			}
			
			void setBorderSize(int b)
			{
				border = b;
			}
			
			int getBorderSize() const
			{
				return border;
			}

			void show(bool v)
			{
				isVisible = v;
			}
			
			bool isScrollable() const
			{
				return scrollable;
			}
			
			virtual void update(sf::Event& event) = 0;
		
		protected:
			void updateWidgets(sf::Event& event)
			{
				if(isVisible)
				{
					for(auto& w : widgets)
					{
						w->update(event);
					}
				}
			}
			
			const std::vector<Widget*>& getWidgets() const
			{
				return widgets;
			}

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				if(isVisible)
				{
					for(auto& w : widgets)
					{
						target.draw(*w, states);
					}
				}
			}

			virtual void reposition() = 0;
			virtual void scroll(float amount) = 0;

			std::vector<Widget*> widgets;

			int border;
			bool isVisible;
			bool scrollable;
	};
}

#endif // CONTAINER_HPP
