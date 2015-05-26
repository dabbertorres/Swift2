#ifndef LUA_CPP_HPP
#define LUA_CPP_HPP

#include "Details/State.hpp"

namespace lna
{
	template<typename F>
	F tieAssign(F v, F& r)
	{
		r = v;
		return v;
	}
	
	template<typename... Ts, int... N>
	void tie(const std::tuple<Ts...>& tup, detail::indices<N...>, Ts&... ts)
	{
		std::make_tuple(tieAssign(std::get<N>(tup), ts)...);
	}
	
	template<typename... Ts>
	void tie(Selection sel, Ts&... ts)
	{
		std::tuple<Ts...> tup = sel;
		tie(tup, typename detail::indicesBuilder<sizeof...(Ts)>::type{}, ts...);
	}
}

#endif // LUA_CPP_HPP
