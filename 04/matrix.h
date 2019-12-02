#include <vector>

class Matrix
{
	std::vector<std::vector<int>> matrix;
public:
	Matrix(size_t n_rows, size_t n_col);
	~Matrix() {};
	size_t getRows() const;
	size_t getColumns() const;
	Matrix* operator *= (const int vol);
	bool operator == (const Matrix& other) const;
	bool operator != (const Matrix& other) const;
	class Proxy
	{
		std::vector<int>& rowPtr;
	public:
		Proxy(std::vector<int>& ptr) : rowPtr(ptr) {}
		int& operator [] (int j);
	};

	class constProxy
	{
		const std::vector<int>& rowPtr_const;
	public:
		constProxy(const std::vector<int>& ptr) : rowPtr_const(ptr) {}
		const int& operator [] (int j) const;
	};

	Proxy operator [] (int i);
	const constProxy operator [] (int i) const;
};
