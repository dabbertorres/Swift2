#ifndef CLASS_HPP
#define CLASS_HPP

#include <lua.hpp>

#include <string>
#include <unordered_map>

#include "Details.hpp"

namespace lpp
{
	class Class
	{
		public:
			Class(lua_State* s, const std::string& n);
			~Class();

		private:
			lua_State* state;
	};
}

#endif // CLASS_HPP
