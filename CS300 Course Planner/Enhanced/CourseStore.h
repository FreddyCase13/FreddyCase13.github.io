/*
 * File:     CourseStore.h
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * New File: Abstract base class for any data structure that stores courses.
 * 
 * Purpose:  Abstract base class with Insert, Search, and Remove so the
 *           BST and hash table can be tested with the same code.
 */
#pragma once

#include <string>
#include "Course.h"

// Base class for any data structure that stores courses.
// Both BinarySearchTree and HashTable will inherit from this class.
// The benchmark can test the performance of both data structures by using this base class.

class CourseStore {
public:
	// virtual destructor to so the correct derived desctructor
	// runs when a structure is deleted through a pointer to the base class.
	virtual ~CourseStore() {}

	// every course must be able to add, find, and remove a course.
	// each derived class will write its own version of these methods using "= 0".
	virtual void Insert(Course course) = 0;
	virtual Course Search(std::string courseId) = 0;
	virtual void Remove(std::string courseId) = 0;
};
