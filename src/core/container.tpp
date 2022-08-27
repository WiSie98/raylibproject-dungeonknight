#include "headerfiles/container.h"

//Constructors/Destructors

template<typename T>
Container<T>::Container() : max_capacity(0) {}

template<typename T>
Container<T>::Container(int max_capacity) {
	if (max_capacity > 0) {
		setMaxCapacity(max_capacity);
	}
	else {
		setMaxCapacity(0);
	}
}

template<typename T>
Container<T>::~Container() {}

//Functions

template<typename T>
T Container<T>::get(int pos) {
	return this->container[pos];
}

template<typename T>
int Container<T>::size() {
	return this->container.size();
}

template<typename T>
void Container<T>::add(T element) {
	if (this->max_capacity() == 0) {
		this->container.push_back(element);
	}
	else if (this->container.size() < this->max_capacity) {
		this->container.push_back(element);
	}
	else {
		std::cout << "ERROR: Element could not be added to the container!\n";
	}
}

template<typename T>
void Container<T>::remove(int pos) {
	if (this->container.size() == 1) {
		this->container.erase(container.begin());
	}
	else if (pos < this->container.size()) {
		this->container.erase(container.begin() + pos);
	}
	else {
		std::cout << "ERROR: Element could not be deleted!\n";
	}
}

template<typename T>
void Container<T>::clear() {
	this->container.clear();
}

template<typename T>
void Container<T>::swap(int pos_1, int pos_2) {
	T temp = this->container[pos_1];
	this->container[pos_1] = this->container[pos_2];
	this->container[pos_2] = temp;
}

//Getter/Setter

template<typename T>
void Container<T>::setMaxCapacity(int max_capacity) {
	if (max_capacity <= 0) {
		this->max_capacity = 0;
	}
	else {
		this->max_capacity = max_capacity;
	}
}

template<typename T>
int Container<T>::getMaxCapacity() {
	return this->max_capacity;
}