#pragma once
#include <iostream>

// template class created for my own dynamic memory management
template<class T>
class MVector
{
public:
	MVector();
	~MVector();

	void add(T* item);
	inline int getSize() const;
	inline T* getItem(int index) const;

private:
	const int maxcap = 100;

	T** data;
	int size;
};

template<class T>
MVector<T>::MVector()
{
	data = new T * [maxcap];
	size = 0;
}

template<class T>
MVector<T>::~MVector()
{
	for (int i = 0; i < size; i++)
		delete data[i];

	delete[] data;
}

template<class T>
void MVector<T>::add(T* item)
{
	// grow array
	if (size < maxcap)
	{
		size++; // update number of items
		data = (T**)realloc(data, sizeof(T**) * size); // resize array
		data[size-1] = item; // add item to the array 
	}
	else
	{
		std::cout << "\nVector has reached max capacity.\n";
	}
}

template<class T>
inline int MVector<T>::getSize() const { return size; }


template<class T>
T* MVector<T>::getItem(int index) const
{
	if (index >= 0 && index < maxcap)
	{
		return data[index]; // return item at chosen index
	}
	return NULL; // return null if index is invalid
}


