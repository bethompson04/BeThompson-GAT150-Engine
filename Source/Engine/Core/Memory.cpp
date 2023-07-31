#include "Memory.h"
#include <iostream>

namespace MEN
{
	bool MemoryTracker::Initialize()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		return true;
	}

	void MemoryTracker::DisplayInfo()
	{
		_CrtMemDumpAllObjectsSince(NULL);
	}
}

//#include "Memory.h"
//#include <iostream>
//
//MEN::MemoryTracker MEN::g_memoryTracker;
//
//// Allocate Memory (new operator overload)
//void* operator new (size_t size)
//{
//	void* ptr = malloc(size);
//
//	MEN::g_memoryTracker.Add(ptr, size);
//
//	return ptr;
//}
//
//// Deallocate Memory (delete operator overload)
//void operator delete (void* address, size_t size)
//{
//	MEN::g_memoryTracker.Remove(address, size);
//
//	free(address);
//}
//
//namespace MEN 
//{
//	void MemoryTracker::Add(void* address, size_t size)
//	{
//		m_bytesAllocated += size;
//		m_numAllocations++;
//	}
//
//	void MemoryTracker::Remove(void* address, size_t size)
//	{
//		m_bytesAllocated -= size;
//		m_numAllocations--;
//	}
//
//	void MemoryTracker::DisplayInfo()
//	{
//		std::cout << "Current Bytes Allocated: " << m_bytesAllocated << std::endl;
//		std::cout << "Current Number Of Allocations: " << m_numAllocations << std::endl;
//	}
//}