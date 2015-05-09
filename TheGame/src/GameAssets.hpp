#ifndef GAMEASSETS_HPP
#define GAMEASSETS_HPP

#include "../src/ResourceManager/AssetManager.hpp"

namespace tg
{
	class GameAssets : public swift::AssetManager
	{
		public:
			GameAssets(const std::string& rp);
			~GameAssets() = default;

		private:
			virtual bool loadScript(const std::string& file);

			std::string resPath;
	};
}

#endif // GAMEASSETS_HPP
