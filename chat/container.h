#pragma once
template <typename T> class Container
{
	int size;
	T* data;
public:
	Container();
	~Container()
	{
		delete[] data;
	}
};