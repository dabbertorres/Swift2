#ifndef GAMEASSETS_HPP
#define GAMEASSETS_HPP

#include "ResourceManager/AssetManager.hpp"

namespace tg
{
	class GameAssets : public swift::AssetManager
	{
		public:
			GameAssets() = default;
			~GameAssets() = default;

		protected:
			virtual bool loadScript(const gfs::Path& file);
	};
}

#endif // GAMEASSETS_HPP
