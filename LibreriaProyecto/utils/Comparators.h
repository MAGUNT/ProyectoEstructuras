#pragma once
#include <memory>


template<typename T>
struct DefaultComparator
{
	int operator()(const T&, const T&)const;
private:
	int compare(const T &, const T &)const;
	int compare(T*, T*)const;
	int compare(std::shared_ptr<T> a, std::shared_ptr<T> b)const;
};

template<typename T>
int DefaultComparator<T>::operator()(const T& a, const T& b) const
{
	return compare(a, b);
}

template<typename T>
int DefaultComparator<T>::compare(const T &a, const T &b)const
{
	std::less<T> func;
	if (func(a, b)) return -1;
	if (func(b, a)) return 1;
	return 0;
}
template<typename T>
int DefaultComparator<T>::compare(T* a, T* b)const
{
	return compare(*a, *b);
}

template<typename T>
int DefaultComparator<T>::compare(std::shared_ptr<T> a, std::shared_ptr<T> b)const
{
	return compare(*a, *b);
}


