#pragma once
#include <iostream>


template <typename T> class Container
{
	int _size{};
	T* _data{};
public:
	Container()
	{
		_size = 0;
		_data = nullptr;
	}
	Container(int size);
	~Container()
	{
		delete[] _data;
	}
	
	void insertBefore(T value, int index);
	void addItem(T value);
	T& operator[](int index);
	int getSize();
};


template <typename T> Container<T>::Container();
template < typename T> Container<T>::Container(int size) :
	_size{ size }
{
	_data = new T[size]{};
}
template < typename T> void Container<T>::insertBefore(T value, int index)
{

	T* data{ new T[_size + 1] };

	for (int before{ 0 }; before < index; ++before)
		data[before] = _data[before];

	data[index] = value;

	for (int after{ index }; after < _size; ++after)
		data[after + 1] = _data[after];

	delete[] _data;
	_data = data;
	++_size;
}
template <typename T> void Container<T>::addItem(T value)
{
	insertBefore(value, _size);
}
template < typename T> T& Container<T>::operator[](int index)
{
	return _data[index];
}
template < typename T> int Container<T>::getSize()
{
	return _size;
}