#ifndef COMPONENT_HPP
#define COMPONENT_HPP

namespace swift
{
	class Component
	{
		public:
			Component(unsigned id);
			virtual ~Component();
			
			unsigned getID() const;
			
		private:
			unsigned ID;
	};
}

#endif // COMPONENT_HPP
