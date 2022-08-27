#pragma once

#include "header.h"

/**
*A container class which can hold any datatype simillar to the std::vector with some specialised functions.
**/
template<typename T>
class Container {
public:

	Container();
	Container(int max_capacity);

	T get(int pos);
	int size();
	void add(T element);
	void remove(int pos);
	void clear();
	void swap(int pos_1, int pos_2);

	void setMaxCapacity(int max_capacity);

	int getMaxCapacity();

	~Container();


private:

	unsigned int max_capacity;
	std::vector<T> container;

};

//#include "container.tpp"