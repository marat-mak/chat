#include "container.h"
template <typename T> Container<T>::Container() = default;
template < typename T> Container<T>::Container(int size) :
	_size{ size }
{	
	_data = new T[size] {};
}
template < typename T> void Container<T>::insertBefore(T value, int index)
{
	/*if (index < 0) { throw BadRange(); }
	if (index > m_length) { throw BadRange(); }*/

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
	//if (index < 0) { throw BadRange(); }
	//if (index > m_length) { throw BadRange(); }
	return _data[index];
}
template < typename T> int Container<T>::getSize() const
{
	return _size;
}