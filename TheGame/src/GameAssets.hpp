#ifndef GAMEASSETS_HPP
#define GAMEASSETS_HPP

#include "../src/ResourceManager/AssetManager.hpp"

namespace tg
{
	class GameAssets : public swift::AssetManager
	{
		public:
			GameAssets();
			~GameAssets();

		protected:
			virtual bool loadScript(const std::string& file);
	};
}

#endif // GAMEASSETS_HPP
