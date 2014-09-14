#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

namespace Swift
{
	class World
	{
		public:
			World();
			~World();
			
			virtual void update(float dt) = 0;
		
		private:
			//std::vector
	};
}

#endif // WORLD_HPP
