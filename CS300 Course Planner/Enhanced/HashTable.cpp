/*
 * File:     HashTable.cpp
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * New File: Created hash table class to test against the binary search tree.
 *
 * Purpose:  Inserts, searches, and removes courses in the hash table.
 *           Uses 179 buckets and a multiply-by-31 hash.
 */
#include "HashTable.h"

using namespace std;

/**
 * Constructor
 * Sets the table size and fills each bucket with nullptr.
 */
HashTable::HashTable(unsigned int size) {
	tableSize = size;
	nodes.resize(tableSize, nullptr);
}

/**
 * Destructor
 * Walks through each bucket and deletes all nodes in the chain.
 * This prevents memory leaks when the hash table is destroyed.
 */
	HashTable::~HashTable() {
		for (unsigned int i = 0; i < tableSize; ++i) {
			HashNode* current = nodes[i];
			while (current != nullptr) {
				// saves the next node before deleting the current node
				// to save place in chain.
				HashNode* nextNode = current->next;
				delete current;
				current = nextNode;
			}
		}
	}
/**
 * Method to turn courseId into a bucket index.
 * Multiplies the running total by 31 and adds each character code.
 * Takes the remainder after dividing by the table size.
 */
	unsigned int HashTable::hash(string key) {
		unsigned int sum = 0;
		for (char c : key) {
			// Multiply the running total by 31 before adding each character.
			// Therefore, the position of each character matters.
			// Without this, different IDs can add up to the same number and land in the same bucket.
			sum = sum * 31 + static_cast<unsigned char>(c);
		}
		return sum % tableSize;
	}

/**
* Method to insert a course into the hash table.
* Adds the course to the front of its bucket's chain.
* 
* Time complexity: O(1), since the course is added to the front
* of its bucket and the chain is never walked.
*/
	void HashTable::Insert(Course course) {
		unsigned int index = hash(course.courseId);
		HashNode* newNode = new HashNode(course);
		newNode->next = nodes[index];
		nodes[index] = newNode;
	}

/**
* Method to search for a course in the hash table.
* Searches by jumping into its bucket
* Then walking in that buckets chain.
* Returns empty course if not found.
* 
* Time complexity: O(1) on average, since it jumps straight to one bucket.
* Worst case O(n) if every course lands in the same bucket.
*/
	Course HashTable::Search(string courseId) {
		unsigned int index = hash(courseId);
		HashNode* current = nodes[index];
		while (current != nullptr) {
			if (current->course.courseId == courseId) {
				return current->course;
			}
			current = current->next;
		}
		return Course(); // return empty course if not found
	}

/**
* Method to remove a course from the hash table.
* Keeps track of the previous node so the chain
* is reconnected around the removed node.
* 
* Time complexity: O(1) on average, since it jumps straight to one bucket.
* Worst case O(n) if every course lands in the same bucket.
**/
	void HashTable::Remove(string courseId) {
		unsigned int index = hash(courseId);
		HashNode* current = nodes[index];
		HashNode* previous = nullptr;

		while (current != nullptr) {
			if (current->course.courseId == courseId) {
				if (previous == nullptr) {
					nodes[index] = current->next;
				}
				// else remove a node from the middle or end of the chain.
				else {
					previous->next = current->next;
				}
				delete current;
				return;
			}
			// move to the next node in the chain while keeping track of the previous node.
			previous = current;
			current = current->next;
		}
	}