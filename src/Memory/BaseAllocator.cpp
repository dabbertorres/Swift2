#include "BaseAllocator.hpp"

#include <stdexcept>
#include <cstdlib>

namespace swift
{
	namespace mem
	{
		BaseAllocator::BaseAllocator(std::size_t s)
		:	size(s),
			used(0),
			numAllocations(0)
		{
			void* start = std::malloc(size);
			
			if(!start)
			{
				throw std::bad_alloc();
			}
		}

		BaseAllocator::~BaseAllocator()
		{
			std::free(start);
		}
		
		void* BaseAllocator::allocate()
		{
			return nullptr;
		}

		void* BaseAllocator::allocate(std::size_t s, std::size_t alignment)
		{
			void* ret = allocateImpl(s, alignment);
			
			if(ret)
			{
				used += s;
				numAllocations++;
				
				return ret;
			}
			else
			{
				return nullptr;
			}
		}

		void BaseAllocator::deallocate(void* p, std::size_t s)
		{
			deallocateImpl(p);
			
			used -= s;
		}

		std::size_t BaseAllocator::getSize() const
		{
			return size;
		}

		std::size_t BaseAllocator::getUsed() const
		{
			return used;
		}

		std::size_t BaseAllocator::getNumAllocations() const
		{
			return numAllocations;
		}

		void* BaseAllocator::getStart() const
		{
			return start;
		}
	}
}
