#include <memory>
#include <iostream>
#include <stdexcept>
//#include <vector>
//using std::vector

template <class T>
class Iterator
{
	friend class vector;
public:
	using value_type = T;
	using reference = value_type & ;
	using difference_type = std::ptrdiff_t;


	Iterator(value_type* p) : p_(p) {}
	Iterator(const Iterator &it) : p_(it.p) {}
	bool operator!=(Iterator const& other) const
	{
		return p_ != other.p_;
	}
	bool operator==(Iterator const& other) const
	{
		return p_ == other.p;
	}
	reference operator*() const
	{
		return *p_;
	}
	Iterator& operator++()
	{
		++p_;
		return *this;
	}
	Iterator& operator--()
	{
		--p_;
		return *this;
	}

	reference operator[](difference_type n)
	{
		return *(p_ + n);
	}

private:
	value_type* p_;
};

template<class T, class Allocator = std::allocator<T>>
class Vector
{
public:
	using value_type = T;
	using allocator_type = Allocator;
	using size_type = size_t;
	using iterator = Iterator<T>;
	using reference = value_type& ;
	using pointer = value_type* ;

	explicit Vector(const allocator_type& alloc = allocator_type())
		: alloc_(alloc)
	{
		capacity_ = 0;
		size_ = 0;
	}
	Vector(size_type count, const value_type& value, const allocator_type& alloc = allocator_type())
		: alloc_(alloc)
	{
		if (count <= alloc_.max_size())
		{
			p_ = alloc_.allocate(count);
			capacity_ = count;
			size_ = count;
		}
		else
		{
			throw std::length_error("count > alloc_.max_size().");
		}
		for (size_type i = 0; i < size_; i++)
		{
			alloc_.construct(p_ + i, value);
		}
	}

	~Vector()
	{
		for (size_type i = 0; i < size_; ++i)
			alloc_.destroy(p_ + i);
		alloc_.deallocate(p_, capacity_);
		p_ = nullptr;
	}

	reference operator[](size_type pos)
	{
		if (pos >= size_)
		{
			throw std::out_of_range("pos >= size_");
		}
		return p_[pos];
	}
	//const_reference operator[](size_type pos) const
	//{
	//}

	void push_back(const value_type& value)
	{
		if (size_ >= capacity_ * 3 / 4)
		{
			this->resize(capacity_ * 2);
		}
		alloc_.construct(p_ + size_, value);
		size_++;
	}
	void push_back(value_type&& value)
	{
		if (size_ >= capacity_ * 3 / 4)
		{
			this->resize(capacity_ * 2);
		}
		alloc_.construct(p_ + size_, std::forward<value_type>(value));
		size_++;
	}

	void pop_back()
	{
		if (size_ > 0)
		{
			alloc_.destroy(p_ + size);
			size_--;
		}
	}

	bool empty() const
	{
		return (size_ == 0);
	}

	size_type size() const
	{
		return size_;
	}

	void clear()
	{
		for (size_type i = 0; i < size_; ++i)
			alloc_.destroy(p_ + i);
		size_ = 0;
	}

	iterator begin()
	{
		return iterator(p_);
	}
	//const_iterator cbegin() const
	//{
	//}

	iterator end()
	{
		return iterator(p_ + size_);
	}
	//const_iterator cend() const
	//{
	//}

	iterator rbegin()
	{
		return iterator(p_ + size_ - 1);
	}
	//const_reverse_iterator crbegin() const
	//{
	//}

	iterator rend()
	{
		return iterator(p_ - 1);
	}
	//const_reverse_iterator crend() const
	//{
	//}

	void reserve(size_type count)
	{
		if (count <= alloc_.max_size())
		{
			if (!p_)
			{
				p_ = alloc_.allocate(count);
				capacity_ = count;
				size_ = 0;
			}
			else
			{
				if (capacity_ < count)
				{
					pointer tmp_p = alloc_.allocate(count);
					for (size_type i = 0; i < size_; i++)
					{
						alloc_.construct(tmp_p + i, p_[i]);
					}
					for (size_type i = 0; i < size_; ++i)
						alloc_.destroy(p_ + i);
					alloc_.dellallocate(p_, capacity_);
					p_ = tmp_p;
					capacity_ = count;
				}
			}
		}
		else
		{
			throw std::length_error("count > alloc_.max_size().");
		}
	}

	void resize(size_type count)
	{
		if (count <= alloc_.max_size())
		{
			if (!p_)
			{
				p_ = alloc_.allocate(count);
				capacity_ = count;
				size_ = 0;
			}
			else
			{
				if (capacity_ < count)
				{
					pointer tmp_p = alloc_.allocate(count);
					for (size_type i = 0; i < size_; i++)
					{
						alloc_.construct(tmp_p + i, p_[i]);
					}
					for (size_type i = 0; i < size_; ++i)
						alloc_.destroy(p_ + i);
					alloc_.deallocate(p_, capacity_);
					p_ = tmp_p;
					capacity_ = count;
				}
				else
				{
					if (capacity_ > count)
					{
						pointer tmp_p = alloc_.allocate(count);
						if (size_ > count)
						{
							for (size_type i = count; i < size_; ++i)
								alloc_.destroy(p_ + i);
							size_ = count;
						}
						for (size_type i = 0; i < size_; i++)
						{
							alloc_.construct(tmp_p + i, p_[i]);
						}
						for (size_type i = 0; i < size_; ++i)
							alloc_.destroy(p_ + i);
						alloc_.deallocate(p_, capacity_);
						p_ = tmp_p;
						capacity_ = count;
					}
				}
			}
		}
		else
		{
			throw std::length_error("count > alloc_.max_size().");
		}
	}
	void resize(size_type count, const value_type& value)
	{
		if (count <= alloc_.max_size())
		{
			if (!p_)
			{
				p_ = alloc_.allocate(count);
				capacity_ = count;
				size_ = 0;
			}
			else
			{
				if (capacity_ < count)
				{
					pointer tmp_p = alloc_.allocate(count);
					for (size_type i = 0; i < size_; i++)
					{
						alloc_.construct(tmp_p + i, p_[i]);
					}
					for (size_type i = size_; i < count; i++)
					{
						alloc_.construct(tmp_p + i, value);
					}
					for (size_type i = 0; i < size_; ++i)
						alloc_.destroy(p_ + i);
					alloc_.dellallocate(p_, capacity_);
					p_ = tmp_p;
					capacity_ = count;
				}
				else
				{
					if (capacity_ > count)
					{
						pointer tmp_p = alloc_.allocate(count);
						if (size_ > count)
						{
							for (size_type i = count; i < size_; ++i)
								alloc_.destroy(p_ + i);
							size_ = count;
						}
						for (size_type i = 0; i < size_; i++)
						{
							alloc_.construct(tmp_p + i, p_[i]);
						}
						for (size_type i = size_; i < count; i++)
						{
							alloc_.construct(tmp_p + i, value);
						}
						for (size_type i = 0; i < size_; ++i)
							alloc_.destroy(p_ + i);
						alloc_.dellallocate(p_, capacity_);
						p_ = tmp_p;
						capacity_ = count;
					}
				}
			}
		}
		else
		{
			throw std::length_error("count > alloc_.max_size().");
		}
	}

private:
	size_type capacity_ = 0;
	size_type size_ = 0;
	pointer p_ = nullptr;
	allocator_type alloc_;

	void destroy(pointer p, size_type size)
	{
		for (size_type i = 0; i < size; ++i)
			alloc_.destroy(p + i);
	}
};

bool test()
{
	Vector<int> vec(5, 0);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);

	int vec_res[10] = { 0,0,0,0,0,5,6,7,8,9 };
	if (vec.size() != 10)
		return false;
	// begin -> end check
	auto it_begin = vec.begin();
	int indx = 0;
	while (it_begin != vec.end())
	{
		if (vec_res[indx] != *it_begin)
			return false;
		++it_begin;
		++indx;
	}
	if (indx != 10)
		return false;

	// rbegin -> rend check
	auto it_rbegin = vec.rbegin();
	indx = 9;
	while (it_rbegin != vec.rend())
	{
		if (vec_res[indx] != (*it_rbegin))
			return false;
		--it_rbegin;
		--indx;
	}
	if(indx!=-1)
		return false;

	// test for(value : my_vector)...
	indx = 0;
	for (auto value : vec)
	{
		if (vec_res[indx] != value)
			return false;
		++indx;
	}
	if (indx != 10)
		return false;

	//clear
	vec.clear();
	if (vec.size() != 0)
		return false;

	return true;
}

int main()
{
	if (!test())
		std::cout << "Failed tests!\n";
	std::cout << "All tests completed!\n";
	return 0;
}
