#ifndef CPP_FUNCTION_HPP
#define CPP_FUNCTION_HPP

#include <lua.hpp>

#include <string>
#include <functional>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "Details.hpp"

namespace lpp
{
	class BaseCppFunction
	{
		public:
			virtual int run(lua_State* state) = 0;
			
			static int luaDispatcher(lua_State* state)
			{
				BaseCppFunction* func = static_cast<BaseCppFunction*>(lua_touserdata(state, lua_upvalueindex(1)));
				return func->run(state);
			}
			
			static std::unordered_map<std::string, std::unique_ptr<BaseCppFunction>> functions;
	};
	
	template<typename Ret, typename... Args>
	class CppFunction : public BaseCppFunction
	{
		public:
			CppFunction(lua_State* s, const std::string& name, const std::function<Ret(Args...)>& f)
			:	state(s),
				function(f)
			{
				lua_pushlightuserdata(state, static_cast<BaseCppFunction*>(this));
				
				lua_pushcclosure(state, luaDispatcher, 1);
				
				lua_setglobal(state, name.c_str());
				
				lua_settop(state, 0);
			}
			
			~CppFunction() {}
			
			virtual int run(lua_State* state)
			{
				std::tuple<Args...> args = detail::getArgs<Args...>(state);
				Ret value = detail::tupleToPack(function, args);
				int nret = detail::pushValue(state, value);
				return nret;
			}

		private:
			lua_State* state;
			const std::function<Ret(Args...)> function;
	};
	
	template<typename... Args>
	class CppFunction<void, Args...> : public BaseCppFunction
	{
		public:
			CppFunction(lua_State* s, const std::string& name, const std::function<void(Args...)>& f)
			:	state(s),
				function(f)
			{
				lua_pushlightuserdata(state, static_cast<BaseCppFunction*>(this));
				
				lua_pushcclosure(state, luaDispatcher, 1);
				
				lua_setglobal(state, name.c_str());
				
				lua_settop(state, 0);
			}
			
			~CppFunction() {}
			
			virtual int run(lua_State* state)
			{
				std::tuple<Args...> args = detail::getArgs<Args...>(state);
				detail::tupleToPack(function, args);
				return 0;
			}

		private:
			lua_State* state;
			const std::function<void(Args...)> function;
	};
}

#endif // CPP_FUNCTION_HPP
