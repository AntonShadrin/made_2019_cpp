
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



