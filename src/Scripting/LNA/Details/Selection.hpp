#ifndef LNA_SELECTION_HPP
#define LNA_SELECTION_HPP

#include <string>
#include <functional>
#include <vector>
#include <map>
#include <memory>

#include "Class.hpp"
#include "CppFunction.hpp"

#if LUA_VERSION_NUM < 502
#	define LUA_OK 0
#endif

namespace lna
{
	class Selection
	{
		friend class State;
		
		public:
			~Selection() = default;
			
			// assigning C++ objects
			template<typename T, typename... Args, typename... Funcs>
			void setClass(Funcs... funcs);
			
			decltype(LUA_TNUMBER) getType() const;
			
			// Lua function call
			template<typename... Args>
			Selection operator()(Args... args);
			
			// assigning Lua variable to C++ function
			template<typename Ret, typename... Args>
			void operator =(const std::function<Ret(Args...)>& f);
			
			template<typename Ret, typename... Args>
			void operator =(Ret (*f)(Args...));
			
			// assigning objects
			template<typename T>
			void operator =(const T& t);
			
			// cast to tuple for multiple returns
			template<typename... Ret>
			operator std::tuple<Ret...>();
			
			// casting to types
			template<typename T>
			operator T();
			
			template<typename T>
			operator T*();
			
			// casting from tables
			template<typename T>
			operator std::vector<T>();
			
			template<typename K, typename V>
			operator std::map<K, V>();
			
			// operator chaining
			Selection operator [](const std::string& n);
			Selection operator [](int i);

		private:
			// if this Selection is part of a table, idx will not be 0, and will be the index in the stack of the table this Selection is part of
			Selection(lua_State* s, const std::string& n, Functions& funcs, int idx = 0);
			
			lua_State* state;
			std::string name;
			int index;
			
			Functions& functions;
	};
	
	// assigning C++ objects
	template<typename T, typename... Args, typename... Funcs>
	void Selection::setClass(Funcs... funcs)
	{
		// initialize the Class for Lua
		Class<T>(state, name, std::tuple<Args...>{}, functions, funcs...);
	}
	
	inline decltype(LUA_TNUMBER) Selection::getType() const
	{
		return lua_type(state, index);
	}
	
	// calling Lua function
	template<typename... Args>
	Selection Selection::operator()(Args... args)
	{
		if(index == 0)
			lua_getglobal(state, name.c_str());
		
		detail::distributeArgs(state, args...);
		
		constexpr int nargs = sizeof...(Args);
		
		if(lua_pcall(state, nargs, LUA_MULTRET, 0) != LUA_OK)
		{
			std::size_t size;
			const char* buff = luaL_checklstring(state, -1, &size);
			std::string msg = {buff, size};
			luaL_error(state, msg.c_str());
		}
		
		const int nrets = lua_gettop(state);
		
		if(nrets == 0)
			return Selection(state, "", functions);
		else
			return Selection(state, name + " return", functions, -nrets);
	}
	
	// assignment of Lua variable to C++ function
	template<typename Ret, typename... Args>
	void Selection::operator =(const std::function<Ret(Args...)>& f)
	{
		functions.emplace_back(new CppFunction<Ret, Args...>(state, f));
		lua_setglobal(state, name.c_str());
	}
	
	template<typename Ret, typename... Args>
	void Selection::operator =(Ret (*f)(Args...))
	{
		functions.emplace_back(new CppFunction<Ret, Args...>(state, f));
		lua_setglobal(state, name.c_str());
	}
	
	// pushing
	template<typename T>
	void Selection::operator =(const T& t)
	{
		detail::pushValue(state, t);
		lua_setglobal(state, name.c_str());
	}
	
	// casting
	template<typename T>
	Selection::operator T()
	{
		T t;
		
		if(index == 0)
		{
			lua_getglobal(state, name.c_str());
			t = detail::checkGet(detail::id<T>{}, state);
		}
		else
			t = detail::checkGet(detail::id<T>{}, state, index);
		
		lua_settop(state, 0);
		
		return t;
	}
	
	template<typename T>
	Selection::operator T*()
	{
		T* t = nullptr;
		
		if(index == 0)
		{
			lua_getglobal(state, name.c_str());
			t = detail::checkGet(detail::id<T*>{}, state);
		}
		else
			t = detail::checkGet(detail::id<T*>{}, state, index);
		
		lua_settop(state, 0);
		
		return t;
	}
	
	template<typename... Ret>
	Selection::operator std::tuple<Ret...>()
	{
		constexpr int nret = sizeof...(Ret);
		const int top = lua_gettop(state);
		
		if(nret > top)
		{
			std::string msg = "Lua stack (size: " + std::to_string(top) + ") does not have " + std::to_string(nret) + " values!";
			luaL_error(state, msg.c_str());
		}
		
		std::tuple<Ret...> tup = detail::getTuple<Ret...>(state);
		
		lua_settop(state, 0);
		
		return tup;
	}
	
	template<typename T>
	Selection::operator std::vector<T>()
	{
		std::vector<T> vec;
		
		if(index == 0)
		{
			lua_getglobal(state, name.c_str());
			vec = detail::checkGet(detail::id<std::vector<T>>{}, state);
		}
		else
			vec = detail::checkGet(detail::id<std::vector<T>>{}, state, index);
		
		lua_settop(state, 0);
		
		return vec;
	}
			
	template<typename K, typename V>
	Selection::operator std::map<K, V>()
	{
		std::map<K, V> map;
		
		if(index == 0)
		{
			lua_getglobal(state, name.c_str());
			map = detail::checkGet(detail::id<std::map<K, V>>{}, state);
		}
		else
			map = detail::checkGet(detail::id<std::map<K, V>>{}, state, index);
		
		lua_settop(state, 0);
		
		return map;
	}
	
	/* Selection operators */
	inline Selection Selection::operator [](const std::string& n)
	{
		if(index == 0)
			lua_getglobal(state, name.c_str());
		
		std::string newName = name + '.' + n;
		
		if(!lua_istable(state, -1))
			luaL_error(state, "Value on top of stack is not a table");
		
		lua_pushstring(state, n.c_str());
		lua_rawget(state, -2);
		
		return Selection(state, newName, functions, -1);
	}
	
	inline Selection Selection::operator [](int i)
	{
		if(index == 0)
			lua_getglobal(state, name.c_str());
			
		std::string newName = name + '[' + std::to_string(i) + ']';
		
		if(!lua_istable(state, -1))
			luaL_error(state, "Value on top of stack is not a table");
		
		lua_rawgeti(state, -1, i);
		
		return Selection(state, newName, functions, -1);
	}
	
	inline Selection::Selection(lua_State* s, const std::string& n, Functions& funcs, int idx)
	:	state(s),
		name(n),
		index(idx),
		functions(funcs)
	{}
}

#endif // LNA_SELECTION_HPP
