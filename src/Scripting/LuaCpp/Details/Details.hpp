#ifndef DETAILS_HPP
#define DETAILS_HPP

#include <lua.hpp>

#include <vector>
#include <map>
#include <functional>

namespace detail
{
	template<typename First, typename... Args>
	void distributeArgs(lua_State* state, First first, Args... args);
	
	// indice building
	template<std::size_t... Is>
	struct indices {};

	template<std::size_t N, std::size_t... Is>
	struct indicesBuilder : indicesBuilder<N - 1, N - 1, Is...> {};

	template<std::size_t... Is>
	struct indicesBuilder<0, Is...>
	{
		using type = indices<Is...>;
	};
	
	// pushing primitives
	inline int pushValue(lua_State* state, bool b)
	{
		lua_pushboolean(state, b);
		return 1;
	}
	
	inline int pushValue(lua_State* state, int i)
	{
		lua_pushinteger(state, i);
		return 1;
	}
	
	inline int pushValue(lua_State* state, unsigned int ui)
	{
		lua_pushunsigned(state, ui);
		return 1;
	}
	
	inline int pushValue(lua_State* state, lua_Number n)
	{
		lua_pushnumber(state, n);
		return 1;
	}
	
	inline int pushValue(lua_State* state, const std::string& s)
	{
		lua_pushlstring(state, s.c_str(), s.size());
		return 1;
	}
	
	// pushing vectors
	// "i + 1" here is to convert to Lua's tables starting at 1, not 0
	template<typename T>
	inline int pushValue(lua_State* state, const std::vector<T>& vec)
	{
		lua_createtable(state, vec.size(), 0);
		
		for(unsigned int i = 0; i < vec.size(); i++)
		{
			pushValue(state, vec[i]);
			lua_rawseti(state, -2, i + 1);
		}
		
		return 1;
	}
	
	// pushing maps
	template<typename K, typename V>
	inline int pushValue(lua_State* state, const std::map<K, V>& map)
	{
		lua_createtable(state, map.size(), 0);
		
		for(auto& v : map)
		{
			pushValue(state, v.first);
			pushValue(state, v.second);
			lua_rawset(state, -3);
		}
		
		return 1;
	}
	
	// pushing objects
	template<typename T>
	inline int pushValue(lua_State* state, T* t)
	{
		if(t)
			lua_pushlightuserdata(state, t);
		else
			lua_pushnil(state);
		
		return 1;
	}
	
	template<typename T>
	inline int pushValue(lua_State* state, T& t)
	{
		lua_pushlightuserdata(state, &t);
		return 1;
	}
	
	// push tuple
	template<typename... Ts>
	inline int pushValue(lua_State* state, std::tuple<Ts...>& tup)
	{
		return pushValue(state, tup, typename indicesBuilder<sizeof...(Ts)>::type());
	}
	
	template<typename... Ts, std::size_t... N>
	inline int pushValue(lua_State* state, const std::tuple<Ts...>& tup, indices<N...>)
	{
		distributeArgs(state, std::get<N>(tup)...);
		return sizeof...(Ts);
	}
	
	// recursive argument distribution
	inline void distributeArgs(lua_State*) {};
			
	template<typename First, typename... Args>
	inline void distributeArgs(lua_State* state, First first, Args... args)
	{
		pushValue(state, first);
		distributeArgs(state, args...);
	}
	
	// getter functions
	template<typename T>
	struct id {};
	
	// primitives
	inline int checkGet(id<int>, lua_State* state, int idx = -1)
	{
		return luaL_checkint(state, idx);
	}

	inline unsigned int checkGet(id<unsigned int>, lua_State* state, int idx = -1)
	{
		return luaL_checkunsigned(state, idx);
	}

	inline lua_Number checkGet(id<lua_Number>, lua_State* state, int idx = -1)
	{
		return luaL_checknumber(state, idx);
	}

	inline std::string checkGet(id<std::string>, lua_State* state, int idx = -1)
	{
		std::size_t size;
		const char* buff = luaL_checklstring(state, idx, &size);
		return {buff, size};
	}
	
	// tables
	template<typename T>
	inline std::vector<T> checkGet(id<std::vector<T>>, lua_State* state, int idx = -1)
	{
		if(!lua_istable(state, idx))
		{
			std::string msg = "Value at " + std::to_string(idx) + " of stack is not a table";
			luaL_error(state, msg.c_str());
		}
		
		std::vector<T> newVec;
		
		std::size_t tableLength = lua_rawlen(state, idx);
		
		for(unsigned int i = 1; i <= tableLength; i++)
		{
			lua_rawgeti(state, idx, i);
			
			T t = checkGet(id<T>{}, state);
			
			newVec.push_back(t);
			
			lua_pop(state, 1);
		}
		
		return newVec;
	}
	
	template<typename K, typename V>
	inline std::map<K, V> checkGet(id<std::map<K, V>>, lua_State* state, int idx = -1)
	{
		if(!lua_istable(state, idx))
		{
			std::string msg = "Value at " + std::to_string(idx) + " of stack is not a table";
			luaL_error(state, msg.c_str());
		}
		
		std::map<K, V> newMap;
		
		lua_pushnil(state);
		while(lua_next(state, idx - 1))
		{
			// copy the key so it doesn't get converted, making lua_next fail
			lua_pushvalue(state, -2);
			
			K key = checkGet(id<K>{}, state);
			
			V val = checkGet(id<V>{}, state, -2);
			
			newMap.emplace(key, val);
			lua_pop(state, 2);
		}
		
		return newMap;
	}
	
	// objects
	template<typename T>
	inline T checkGet(id<T>, lua_State* state, int idx = -1)
	{
		return static_cast<T>(lua_touserdata(state, idx));
	}

	template<typename T>
	inline T* checkGet(id<T*>, lua_State* state, int idx = -1)
	{
		return static_cast<T*>(lua_touserdata(state, idx));
	}

	template<typename T>
	inline T& checkGet(id<T&>, lua_State* state, int idx = -1)
	{
		return *static_cast<T*>(lua_touserdata(state, idx));
	}

	// getting arguments
	template<typename... T, std::size_t... N>
	std::tuple<T...> getArgs(lua_State* state, indices<N...>)
	{
		return std::make_tuple(checkGet(id<T>{}, state, N + 1)...);
	}

	template<typename... T>
	std::tuple<T...> getArgs(lua_State* state)
	{
		constexpr std::size_t nargs = sizeof...(T);

		return getArgs<T...>(state, typename indicesBuilder<nargs>::type());
	}

	// tuple to pack conversion
	template<typename Ret, typename... Args, std::size_t... N>
	inline Ret tupleToPack(const std::function<Ret(Args...)>& func, const std::tuple<Args...>& args, indices<N...>)
	{
		return func(std::get<N>(args)...);
	}

	template<typename Ret, typename... Args>
	inline Ret tupleToPack(const std::function<Ret(Args...)>& func, const std::tuple<Args...> args)
	{
		return tupleToPack(func, args, typename indicesBuilder<sizeof...(Args)>::type());
	}
}

#endif // DETAILS_HPP
