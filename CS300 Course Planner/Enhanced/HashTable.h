/*
 * File:     HashTable.h
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * New File: Created hash table class to test against the binary search tree.
 * 
 * Purpose:  Declares the hash table that stores courses using
 *           separate chaining.
 */
#pragma once

#include <string>
#include <vector>
#include "Course.h"
#include "CourseStore.h"

/**
 * Hash Table that stores courses.
 * Inherits from CourseStore and implements the Insert, Search, and Remove methods.
 * To be benchmarked against the Binay Search Tree.
 */

class HashTable : public CourseStore {

private:
	// A node in one bucket's chain.
	// Each bucket points to the NEXT node in the same bucket
	// instead of to child nodes.
	struct HashNode {
		Course course;
		HashNode* next;

		HashNode() {
			next = nullptr;
		}

		HashNode(Course aCourse) :
			HashNode() {
			course = aCourse;
		}
	};

	// The Hash Table
	std::vector<HashNode*> nodes;

	// number of buckets in the table
	unsigned int tableSize;

	// turns a courseId into a bucket index
	unsigned int hash(std::string key);

public:
	// Size of the hash table is set to a prime number to reduce collisions.
	HashTable(unsigned int size = 179);
	virtual ~HashTable();
	void Insert(Course course) override;
	Course Search(std::string courseId) override;
	void Remove(std::string courseId) override;
};