#pragma once
#include <iostream>

template <typename T> class Container
{
	int _size{};
	T* _data{};
public:
	Container();
	Container(int size);
	~Container()
	{
		delete[] _data;
	}
	
	void insertBefore(T value, int index);
	void addItem(T value);
	T& operator[](int index);
	int getSize() const;
};