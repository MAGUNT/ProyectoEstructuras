#pragma once
#include <stdexcept>

template
<
	typename T
>

class MultiNode
{

	template <typename T> friend class MultiplyList;

private:
	
	T data;
	MultiNode<T>** nexts;
	MultiNode<T>** prevs;
	unsigned size;
	
	MultiNode(unsigned, const T&);
	//MultiNode(unsigned, T&&);
	MultiNode(unsigned);
	

	~MultiNode();
	MultiNode<T>* getNext(unsigned) const;
	void setNext(unsigned, MultiNode<T>*);
	
	MultiNode<T>* getPrev(unsigned) const;
	void setPrev(unsigned, MultiNode<T>*);

	void check(unsigned) const;
};

template<typename T>
MultiNode<T>::MultiNode(unsigned psize, const T& pdata) 
	: data(pdata), nexts(new MultiNode<T>*[psize]), prevs(new MultiNode<T>*[psize]), size(psize)
{

}



template<typename T>
MultiNode<T>::MultiNode(unsigned psize)
	:MultiNode(psize, T())
{
	
}

template<typename T>
void MultiNode<T>::check(unsigned index) const
{
	if ( index >= size)
		throw new std::out_of_range("out of range");
}

template<typename T>
MultiNode<T>::~MultiNode()
{
	delete[] nexts;
	delete[] prevs;
}

template<typename T>
MultiNode<T>* MultiNode<T>::getNext(unsigned index) const
{
	check(index);
	return nexts[index];
}

template<typename T>
void MultiNode<T>::setNext(unsigned index, MultiNode<T>* node)
{
	check(index);
	nexts[index] = node;
}

template<typename T>
MultiNode<T>* MultiNode<T>::getPrev(unsigned index) const
{
	check(index);
	return prevs[index];
}

template<typename T>
void MultiNode<T>::setPrev(unsigned index, MultiNode<T>* node)
{
	check(index);
	prevs[index] = node;
}