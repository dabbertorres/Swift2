#ifndef KEYBOARDMANAGER_HPP
#define KEYBOARDMANAGER_HPP

#include <map>
#include <string>
#include <functional>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace swift
{
	class KeyboardManager
	{
		public:
			KeyboardManager() {};
			~KeyboardManager() {};

			void newBinding(const std::string& n, sf::Keyboard::Key k, std::function<void()> f = [](){return true;}, bool onPress = false)
			{
				bindings.emplace(std::make_pair(n, KeyBinding(k, f, onPress)));
			}
			
			void call(const std::string& k)
			{
				if(bindings.find(k) != bindings.end())
					bindings.at(k).call();
			}

			bool operator()(sf::Event& e)
			{
				for(auto& k : bindings)
				{
					if(k.second(e))
						return k.second.call();
				}
				
				return false;
			}

		private:
			class KeyBinding
			{
				public:
					explicit KeyBinding(sf::Keyboard::Key k, std::function<void()> f, bool p)
						:	key(k),
							func(f),
							onPress(p)
					{
					}

					~KeyBinding()
					{
					}

					sf::Keyboard::Key getKey() const
					{
						return key;
					}

					bool operator()(sf::Event& e)
					{
						return ((e.type == sf::Event::KeyPressed && onPress) || (e.type == sf::Event::KeyReleased && !onPress)) && e.key.code == key;
					}
					
					bool call()
					{
						if(!func)
							return false;

						func();

						return true;
					}

				private:
					sf::Keyboard::Key key;

					std::function<void()> func;

					bool onPress;	// if true, means if key is pressed, if false, means if key is released
			};

			std::map<std::string, KeyBinding> bindings;
	};
}

#endif // KEYBOARDMANAGER_HPP
