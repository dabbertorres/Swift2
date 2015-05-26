#ifndef DETAILS_HPP
#define DETAILS_HPP

#include <lua.hpp>

#include <vector>
#include <map>
#include <functional>

namespace lna
{
	template<typename T>
	class Class;
	
	namespace detail
	{
		// forward declaration
		template<typename First, typename... Args>
		int distributeArgs(lua_State* state, First first, Args... args);

		// indices building
		template<int... Is>	// will contain 0..N from below
		struct indices
		{};
		
		// recursive inheritance until N = 0
		// builds indices 0, 0..N
		template<int N, int... Is>
		struct indicesBuilder : indicesBuilder<N - 1, N - 1, Is...>
		{};
		
		// where the final inheritance is here
		template<int... Is>
		struct indicesBuilder<0, Is...>
		{
			using type = indices<Is...>;	// only 0..N (skipping the first 0)
		};
		
		// pushing (returns the number of values left on the Lua stack)

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

		inline int pushValue(lua_State* state, lua_Number n)
		{
			lua_pushnumber(state, n);
			return 1;
		}

		inline int pushValue(lua_State* state, const std::string& s)
		{
			lua_pushstring(state, s.c_str());
			return 1;
		}

		// pushing vectors
		// "i + 1" here is to convert to Lua's tables starting at 1, not 0
		template<typename T>
		int pushValue(lua_State* state, const std::vector<T>& vec)
		{
			lua_createtable(state, vec.size(), 0);

			for(std::size_t i = 0; i < vec.size(); i++)
			{
				pushValue(state, vec[i]);
				lua_rawseti(state, -2, i + 1);
			}

			return 1;
		}

		// pushing maps
		template<typename K, typename V>
		int pushValue(lua_State* state, const std::map<K, V>& map)
		{
			lua_createtable(state, 0, map.size());

			for(auto& v : map)
			{
				pushValue(state, v.first);
				pushValue(state, v.second);
				lua_rawset(state, -3);
			}

			return 1;
		}
		
		// push tuple
		template<typename... Ts>
		int pushValue(lua_State* state, const std::tuple<Ts...>& tup)
		{
			return pushValue(state, tup, typename indicesBuilder<sizeof...(Ts)>::type{});
		}
		
		template<typename... Ts, int... N>
		int pushValue(lua_State* state, const std::tuple<Ts...>& tup, indices<N...>)
		{
			return distributeArgs(state, std::get<N>(tup)...);
		}

		// pushing objects
		template<typename T, typename std::enable_if<std::is_class<T>::value>::type* = nullptr>
		int pushValue(lua_State* state, const T& t)
		{
			// if such a type has been exposed to Lua, push it and give it 
			if(Class<T>::isValid())
			{
				// create new T, and call it's copy constructor with the passed object
				void* addr = lua_newuserdata(state, sizeof(Class<T>));
				Class<T>::copy(addr, t);
				
#if LUA_VERSION_NUM >= 502
				luaL_setmetatable(state, Class<T>::getName().c_str());
#else
				luaL_getmetatable(state, Class<T>::getName().c_str());
				lua_setmetatable(state, -2);
#endif

				return 1;
			}
			
			luaL_error(state, "Attempted push of unknown type.");
			return 0;
		}
		
		inline int pushValue(lua_State* state, std::nullptr_t)
		{
			lua_pushnil(state);
			return 1;
		}
		
		template<typename T, typename std::enable_if<std::is_class<T>::value>::type* = nullptr>
		int pushValue(lua_State* state, T* t)
		{
			if(Class<T>::isValid())
			{
				lua_pushlightuserdata(state, t);
				
#if LUA_VERSION_NUM >= 502
				luaL_setmetatable(state, Class<T>::getName().c_str());
#else
				luaL_getmetatable(state, Class<T>::getName().c_str());
				lua_setmetatable(state, -2);
#endif
				
				return 1;
			}
			
			luaL_error(state, "Attempted push of unknown type.");
			return 0;
		}
		
		// recursive argument distribution
		inline int distributeArgs(lua_State*)
		{
			return 0;
		}

		template<typename First, typename... Args>
		int distributeArgs(lua_State* state, First first, Args... args)
		{
			int total = 0;
			total += pushValue(state, first);
			total += distributeArgs(state, args...);
			return total;
		}
		
		// id's a type for picking the correct overload
		template<typename T>
		struct id {};

		// getter functions (leaves the value on the stack)
		
		// primitives
		inline bool checkGet(id<bool>, lua_State* state, int idx = -1)
		{
			return lua_toboolean(state, idx);
		}

		inline int checkGet(id<int>, lua_State* state, int idx = -1)
		{
			return luaL_checkinteger(state, idx);
		}

		inline lua_Number checkGet(id<lua_Number>, lua_State* state, int idx = -1)
		{
			return luaL_checknumber(state, idx);
		}
		
		inline std::string checkGet(id<std::string>, lua_State* state, int idx = -1)
		{
			// if we want a string, but Lua doesn't have a string, copy it, and then convert it to a string
			if(lua_type(state, idx) != LUA_TSTRING)
			{
				lua_pushvalue(state, idx);
				idx = -1;
			}
			
			std::size_t size;
			const char* buff = lua_tolstring(state, idx, &size);
			return {buff, size};
		}

		// tables
		template<typename T>
		std::vector<T> checkGet(id<std::vector<T>>, lua_State* state, int idx = -1)
		{
			if(!lua_istable(state, idx))
			{
				std::string msg = "Value at " + std::to_string(idx) + " of stack is not a table";
				luaL_error(state, msg.c_str());
			}

			std::vector<T> newVec;

#if LUA_VERSION_NUM >= 502
			std::size_t tableLength = lua_rawlen(state, idx);
#else
			std::size_t tableLength = lua_objlen(state, idx);
#endif
			for(unsigned int i = 1; i <= tableLength; i++)
			{
				lua_rawgeti(state, idx, i);

				newVec.push_back(checkGet(id<T>{}, state));
				
				lua_pop(state, 1);	// pop the pushed value
			}

			return newVec;
		}

		template<typename K, typename V>
		std::map<K, V> checkGet(id<std::map<K, V>>, lua_State* state, int idx = -1)
		{
			if(!lua_istable(state, idx))
			{
				std::string msg = "Value at " + std::to_string(idx) + " of stack is not a table";
				luaL_error(state, msg.c_str());
			}
			
			std::map<K, V> newMap;
			
			// give lua_next nil to get the first key
			lua_pushnil(state);
			
			// "idx - 1" because the key is above the table
			while(lua_next(state, idx - 1))	// pushes key, then value
			{
				// copy the key so it doesn't get popped
				lua_pushvalue(state, -2);

				K key = checkGet(id<K>{}, state);

				V val = checkGet(id<V>{}, state, -2);

				newMap.emplace(key, val);
				
				lua_pop(state, 2);	// pop key and value
			}
			
			lua_pop(state, 1);	// pop the last key
			
			return newMap;
		}
		
		// objects
		template<typename T, typename std::enable_if<!std::is_pod<T>::value>::type* = nullptr>
		T* checkGet(id<T*>, lua_State* state, int idx = -1)
		{
			using Type = typename std::remove_const<T>::type;
			
			if(Class<Type>::isValid())
				return static_cast<T*>(luaL_checkudata(state, idx, Class<Type>::getName().c_str()));
			
			luaL_error(state, "Attempted read of unknown type.");
			return nullptr;
		}
		
		template<typename T, typename std::enable_if<!std::is_pod<T>::value>::type* = nullptr>
		T checkGet(id<T>, lua_State* state, int idx = -1)
		{
			using Type = typename std::remove_const<T>::type;
			
			if(Class<Type>::isValid())
				return *static_cast<T*>(luaL_checkudata(state, idx, Class<Type>::getName().c_str()));
			
			luaL_error(state, "Attempted read of unknown type.");
			return {};
		}
		
		// tuples
		
		// tuple helper method
		template<typename... T, int... N>
		std::tuple<T...> getTuple(lua_State* state, indices<N...>)
		{
			constexpr int size = static_cast<int>(sizeof...(T));
			(void)state;	// friggin weird error about "state being unused"
			return std::make_tuple(checkGet(id<T>{}, state, N - size)...);
		}
		
		template<typename... T>
		std::tuple<T...> getTuple(lua_State* state)
		{
			return getTuple<T...>(state, typename indicesBuilder<sizeof...(T)>::type{});
		}

		// tuple to pack conversion
		template<typename Ret, typename... Args, int... N>
		Ret tupleToPack(const std::function<Ret(Args...)>& func, const std::tuple<Args...>& args, indices<N...>)
		{
			return func(std::get<N>(args)...);
		}

		template<typename Ret, typename... Args>
		Ret tupleToPack(const std::function<Ret(Args...)>& func, const std::tuple<Args...> args)
		{
			return tupleToPack(func, args, typename indicesBuilder<sizeof...(Args)>::type{});
		}
	}
}

#endif // DETAILS_HPP
