#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <vector>

namespace swift
{
	template<typename E>
	class Factory
	{
		public:
			Factory()
			{
			}
			
			~Factory()
			{
				for(auto& e : entities)
					if(e)
						delete e;
			}
			
			E& create()
			{
				entities.emplace_back(new E);
				
				construction(*entities[entities.size() - 1]);
				
				return *entities[entities.size() - 1];
			}
			
			std::vector<E*>& getEntities()
			{
				return entities;
			}
			
			void setConstruction(const std::function<void(E&)>& construct)
			{
				construction = construct;
			}
			
			void setRemoveTest(const std::function<bool(E&)>& rTest)
			{
				removeTest = rTest;
			}

		private:
			std::vector<E*> entities;
			
			std::function<void(E&)> construction;
			std::function<bool(E&)> removeTest;
	};
}

#endif // FACTORY_HPP
