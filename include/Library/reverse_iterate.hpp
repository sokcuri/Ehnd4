/*
	'Reverse iteration in C++11 range-based for loops' by arvidsson
	https://gist.github.com/arvidsson/7231973
*/

#ifndef INCLUDED_REVERSE_ITERATE_HPP
#define INCLUDED_REVERSE_ITERATE_HPP

/*
Template used for reverse iteration in C++11 range-based for loops.

std::vector<int> v = {1, 2, 3, 4, 5};
for (auto x : reverse_iterate(v))
std::cout << x << " ";
*/

template <typename T>
class reverse_range
{
	T &x;

public:
	reverse_range(T &x) : x(x) {}

	auto begin() const -> decltype(this->x.rbegin())
	{
		return x.rbegin();
	}

	auto end() const -> decltype(this->x.rend())
	{
		return x.rend();
	}
};

template <typename T>
reverse_range<T> reverse_iterate(T &x)
{
	return reverse_range<T>(x);
}

#endif