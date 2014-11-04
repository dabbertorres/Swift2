#include "Observable.hpp"

namespace swift
{
	template<typename T>
	typename Observable<T>::MessageQueue Observable<T>::getMessages()
	{
		return messages;
	}
}
