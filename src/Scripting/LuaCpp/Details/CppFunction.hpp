#ifndef CPP_FUNCTION_HPP
#define CPP_FUNCTION_HPP

#include <string>
#include <functional>
#include <memory>

#include "Details.hpp"

namespace lna
{
	// base class for all C++ functions that can be called by Lua.
	// this gives a common way to store all functions
	class BaseCppFunction
	{
		public:
			virtual int run(lua_State* state) = 0;
			
			static int luaDispatcher(lua_State* state);
	};
	
	// class template for standard C++ functions
	template<typename Ret, typename... Args>
	class CppFunction : public BaseCppFunction
	{
		public:
			CppFunction(lua_State* state, const std::function<Ret(Args...)>& f);
			
			int run(lua_State* state);

		private:
			const std::function<Ret(Args...)> function;
	};
	
	// class template for C++ functions with no return
	template<typename... Args>
	class CppFunction<void, Args...> : public BaseCppFunction
	{
		public:
			CppFunction(lua_State* state, const std::function<void(Args...)>& f);
			
			int run(lua_State* state);

		private:
			const std::function<void(Args...)> function;
	};
	
	// implementation
	
	inline int BaseCppFunction::luaDispatcher(lua_State* state)
	{
		BaseCppFunction* func = static_cast<BaseCppFunction*>(lua_touserdata(state, lua_upvalueindex(1)));
		return func->run(state);
	}
	
	template<typename Ret, typename... Args>
	CppFunction<Ret, Args...>::CppFunction(lua_State* state, const std::function<Ret(Args...)>& f)
	:	function(f)
	{
		lua_pushlightuserdata(state, static_cast<BaseCppFunction*>(this));
		lua_pushcclosure(state, &luaDispatcher, 1);
	}
	
	template<typename Ret, typename... Args>
	int CppFunction<Ret, Args...>::run(lua_State* state)
	{
		constexpr int nargs = sizeof...(Args);
		std::tuple<Args...> args = detail::getTuple<Args...>(state);
		lua_pop(state, nargs);
		Ret value = detail::tupleToPack(function, args);
		int nret = detail::pushValue(state, value);
		
		return nret;
	}
	
	template<typename... Args>
	CppFunction<void, Args...>::CppFunction(lua_State* state, const std::function<void(Args...)>& f)
	:	function(f)
	{
		lua_pushlightuserdata(state, static_cast<BaseCppFunction*>(this));
		lua_pushcclosure(state, &luaDispatcher, 1);
	}
	
	template<typename... Args>
	int CppFunction<void, Args...>::run(lua_State* state)
	{
		constexpr int nargs = sizeof...(Args);
		std::tuple<Args...> args = detail::getTuple<Args...>(state);
		lua_pop(state, nargs);
		detail::tupleToPack(function, args);
		
		return 0;
	}
	
	using Functions = std::vector<std::unique_ptr<BaseCppFunction>>;
}

#endif // CPP_FUNCTION_HPP
