#pragma once
#include <memory>

namespace Comparators
{

	template<typename T> int comparar(const T &, const T &);
	template<typename T>  int comparar(const T* , const T* );
	template<typename T>  int comparar(T* , T* );
	template<typename T>  int comparar(std::shared_ptr<T> a, std::shared_ptr<T> b);
	

	template<typename T>
	int comparar(const T &a, const T &b)
	{
		std::less<T> func;

		if (func(a, b)) return -1;
		if (func(b, a)) return 1;
		return 0;
	}

	template<typename T>
	int comparar(const T* a, const T* b)
	{
		return comparar(*a, *b);
	}

	template<typename T>
	int comparar(T* a, T* b)
	{
		return comparar(*a, *b);
	}

	template<typename T>
	int comparar(std::shared_ptr<T> a, std::shared_ptr<T> b)
	{
		return comparar(*a, *b);
	}

}
