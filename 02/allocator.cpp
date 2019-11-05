#include <cstdint>

class LinearAllocator
{
public:
	LinearAllocator(uint32_t maxSize);
	~LinearAllocator();
	char* alloc(uint32_t size);
	void reset();
private:
	char* buf = nullptr;
	uint32_t offset;
	uint32_t max_size;
};

LinearAllocator::LinearAllocator(uint32_t maxSize)
{
	buf = new char[maxSize];
	max_size = maxSize;
	offset = 0;
}

LinearAllocator::~LinearAllocator()
{
	delete[] buf;
}

char* LinearAllocator::alloc(uint32_t size)
{
	if (!buf || !size  || offset+size>max_size)
		return nullptr;
	char* ptr = buf + offset;
	offset += size;
	return ptr;
}

void LinearAllocator::reset()
{
	offset = 0;
	return;
}