#ifndef SWIFT_POOL_ALLOCATOR_HPP
#define SWIFT_POOL_ALLOCATOR_HPP

#include "BaseAllocator.hpp"

#include <memory>

namespace swift
{
	namespace mem
	{
		template<typename T>
		class PoolAllocator : public BaseAllocator
		{
			public:
				explicit PoolAllocator(std::size_t numOf);
				
				void* allocate() override;
				
			private:
				void* allocateImpl(std::size_t s, std::size_t alignment) override;
				void deallocateImpl(void* p) override;
				
				void** freeList;
		};
		
		template<typename T>
		PoolAllocator<T>::PoolAllocator(std::size_t numOf)
		:	BaseAllocator(sizeof(T) * numOf)
		{
			std::size_t newSize = sizeof(T) * numOf;
			*freeList = std::align(alignof(T), sizeof(T), *freeList, newSize);
			
			if(!freeList || !*freeList)
			{
				throw std::bad_alloc();
			}
			
			// gather all blocks into freeList
			for(std::size_t i = 0; i < numOf; i++)
			{
				*freeList = freeList + sizeof(T);
				freeList = static_cast<void**>(*freeList);
			}
			
			*freeList = nullptr;
			freeList = static_cast<void**>(getStart());
		}
		
		template<typename T>
		void* PoolAllocator<T>::allocate()
		{
			return BaseAllocator::allocate(sizeof(T), alignof(T));
		}
		
		template<typename T>
		void* PoolAllocator<T>::allocateImpl(std::size_t, std::size_t)
		{
			if(freeList == nullptr)
			{
				return nullptr;
			}
			
			// claim next free block for use
			void* p = freeList;
			
			// move to next free block
			freeList = static_cast<void**>(*freeList);
			
			return p;
		}
		
		template<typename T>
		void PoolAllocator<T>::deallocateImpl(void* p)
		{
			*static_cast<void**>(p) = freeList;
			
			freeList = static_cast<void**>(p);
		}
	}
}

#endif // SWIFT_POOL_ALLOCATOR_HPP
