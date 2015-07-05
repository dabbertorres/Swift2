#ifndef SWIFT_BASE_ALLOCATOR_HPP
#define SWIFT_BASE_ALLOCATOR_HPP

#include <cstddef>

namespace swift
{
	namespace mem
	{
		class BaseAllocator
		{
			public:
				explicit BaseAllocator(std::size_t s);
				virtual ~BaseAllocator();
				
				// for more user-friendly allocation.
				// override in a child class that only
				// allocates one type. Then, size and alignment
				// are known at compile time, allowing this 
				// function to call allocate(unsigned int, byte)
				// with the correct values
				// returns nullptr and makes no allocation by default
				virtual void* allocate();
				
				void* allocate(std::size_t s, std::size_t alignment);
				void deallocate(void* p, std::size_t s);

				std::size_t getSize() const;
				std::size_t getUsed() const;
				std::size_t getNumAllocations() const;

			protected:
				void* getStart() const;

			private:
				virtual void* allocateImpl(std::size_t s, std::size_t alignment) = 0;
				virtual void deallocateImpl(void* p) = 0;

				void* start;
				std::size_t size;
				std::size_t used;
				std::size_t numAllocations;
		};
	}
}

#endif // SWIFT_BASE_ALLOCATOR_HPP
