#ifndef CLASS_HPP
#define CLASS_HPP

#include <lua.hpp>

#include <string>
#include <unordered_map>

#include "CppFunction.hpp"

namespace lna
{
	template<typename CppClass>
	class Class
	{
		public:
			template<typename... CstrArgs, typename... Mems>
			Class(lua_State* s, const std::string& n, std::tuple<CstrArgs...>, Functions& fmap, Mems... mems);
			
			static void copy(void* addrNew, const CppClass& other);
			
			// returns className if this class has been created, otherwise returns an empty string
			static const std::string& getName();
			
			// returns true if class has been created, false otherwise
			static bool isValid();
			
			~Class() = default;

		private:
			// recursively add all members
			void addMembers();	// "zero condition"
			
			template<typename Mem, typename... Mems>
			void addMembers(const std::string& n, Mem mem, Mems... mems);	// more members to add
			
			// add functions
			template<typename Ret, typename... Args>
			void addMember(const std::string& funcName, Ret (CppClass::*func)(Args...));
			
			template<typename Ret, typename... Args>
			void addMember(const std::string& funcName, Ret (CppClass::*func)(Args...) const);
			
			// add variables
			// note: Lua can't access variables, only functions.
			// so, we create a getter function with the same name as the variable
			// and if the variables is NOT const, adds a setter named: "set_<var name>"
			// which takes a parameter of the same type as the variable
			template<typename T>
			void addMember(const std::string& name, T CppClass::*t);
			
			template<typename T>
			void addMember(const std::string& name, const T CppClass::*t);
			
			// called "new" in Lua, used as: "Class(args...)"
			template<typename... CstrArgs>
			static int newInstance(lua_State* s);
			
			// used to pass indices and call placement new
			template<typename... CstrArgs, int... N>
			static void factory(void* addr, const std::tuple<CstrArgs...>& args, detail::indices<N...>);
			
			lua_State* state;
			static std::string className;
			static Functions* functions;
			static bool valid;
	};
	
	template<typename CppClass>
	template<typename... CstrArgs, typename... Mems>
	Class<CppClass>::Class(lua_State* s, const std::string& n, std::tuple<CstrArgs...>, Functions& fmap, Mems... mems)
	:	state(s)
	{
		className = n;
		functions = &fmap;
		
		// create the metatable for our class
		luaL_newmetatable(state, className.c_str());
		
		// create Lua's constructor for this class
		lua_pushstring(state, "__call");
		lua_pushcfunction(state, &newInstance<CstrArgs...>);
		lua_rawset(state, -3);
		
		// assigning the __index metamethod of the metatable to the metatable
		lua_pushstring(state, "__index");
		lua_pushvalue(state, -2);			// put another copy of the metatable on the stack
		lua_rawset(state, -3);
		
		// add all members
		addMembers(mems...);
		
		// set the metatable of our class' metatable to className_meta
#if LUA_VERSION_NUM >= 502
		luaL_setmetatable(s, className.c_str());
#else
		luaL_getmetatable(s, className.c_str());
		lua_setmetatable(s, -2);
#endif
		
		// gives Lua access to the table
		lua_setglobal(state, className.c_str());
		
		valid = true;		// let it be known this class exists in Lua!
	}
	
	template<typename CppClass>
	void Class<CppClass>::copy(void* addrNew, const CppClass& other)
	{
		new (addrNew) CppClass(other);
	}
	
	template<typename CppClass>
	const std::string& Class<CppClass>::getName()
	{
		return className;
	}
	
	template<typename CppClass>
	bool Class<CppClass>::isValid()
	{
		return valid;
	}
	
	template<typename CppClass>
	void Class<CppClass>::addMembers()
	{}
	
	template<typename CppClass>
	template<typename Mem, typename... Mems>
	void Class<CppClass>::addMembers(const std::string& n, Mem mem, Mems... mems)
	{
		addMember(n, mem);
		addMembers(mems...);
	}
	
	template<typename CppClass>
	template<typename Ret, typename... Args>
	void Class<CppClass>::addMember(const std::string& funcName, Ret (CppClass::*func)(Args...))
	{
		// push and set to the table
		lua_pushstring(state, funcName.c_str());
		functions->emplace_back(new CppFunction<Ret, CppClass*, Args...>(state, func));	// closure is now on stack
		lua_rawset(state, -3);
	}
	
	template<typename CppClass>
	template<typename Ret, typename... Args>
	void Class<CppClass>::addMember(const std::string& funcName, Ret (CppClass::*func)(Args...) const)
	{
		// push and set to the table
		lua_pushstring(state, funcName.c_str());
		functions->emplace_back(new CppFunction<Ret, CppClass*, Args...>(state, func));	// closure is now on stack
		lua_rawset(state, -3);
	}
	
	template<typename CppClass>
	template<typename T>
	void Class<CppClass>::addMember(const std::string& name, T CppClass::*t)
	{
		// Lua works with member functions by having the first parameter be a pointer
		// to the class' instance. Thus, the CppClass* parameter.
		
		// setter
		std::function<void(CppClass*, T)> setter = [=](CppClass* self, T val)
		{
			self->*t = val;
		};
		
		std::string setterName = "set_" + name;
		lua_pushstring(state, setterName.c_str());
		functions->emplace_back(new CppFunction<void, CppClass*, T>(state, setter));	// closure is now on stack
		lua_rawset(state, -3);
		
		// getter
		std::function<T(const CppClass*)> getter = [=](const CppClass* self)
		{
			return self->*t;
		};
		
		lua_pushstring(state, name.c_str());
		functions->emplace_back(new CppFunction<T, const CppClass*>(state, getter));	// closure is now on stack
		lua_rawset(state, -3);
	}
	
	template<typename CppClass>
	template<typename T>
	void Class<CppClass>::addMember(const std::string& name, const T CppClass::*t)
	{
		std::function<T(const CppClass*)> getter = [=](const CppClass* self)
		{
			return self->*t;
		};
		
		lua_pushstring(state, name.c_str());
		functions->emplace_back(new CppFunction<T, const CppClass*>(state, getter));	// closure is now on stack
		lua_rawset(state, -3);
	}
	
	template<typename CppClass>
	template<typename... CstrArgs>
	int Class<CppClass>::newInstance(lua_State* s)
	{
		constexpr int nargs = sizeof...(CstrArgs);
		std::tuple<CstrArgs...> args = detail::getTuple<CstrArgs...>(s);
		
		lua_pop(s, 1 + nargs);	// pop the args, plus the "self" value
		
		// make our new class in Lua
		void* c = lua_newuserdata(s, sizeof(CppClass));
		
		factory(c, args, typename detail::indicesBuilder<sizeof...(CstrArgs)>::type{});
		
		// set our userdata to this type
#if LUA_VERSION_NUM >= 502
		luaL_setmetatable(s, className.c_str());
#else
		luaL_getmetatable(s, className.c_str());
		lua_setmetatable(s, -2);
#endif
		
		return 1;
	}
	
	template<typename CppClass>
	template<typename... CstrArgs, int... N>
	void Class<CppClass>::factory(void* addr, const std::tuple<CstrArgs...>& args, detail::indices<N...>)
	{
		// placement new to put a new instance of our class at the space Lua allocated for us
		new (addr) CppClass(std::get<N>(args)...);
	}
	
	template<typename CppClass>
	std::string Class<CppClass>::className = "";
	
	template<typename CppClass>
	Functions* Class<CppClass>::functions = nullptr;
	
	template<typename CppClass>
	bool Class<CppClass>::valid = false;
}

#endif // CLASS_HPP
