/*
 * File:     BinarySearchTree.h
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * New File: Binary search tree moved into its own file.
 *           Now, it inherits from CourseStore. Removed unused functions.
 *
 * Purpose:  Declares the binary search tree that stores courses
 *           sorted by course ID.
 */
#pragma once

#include <string>
#include "Course.h"
#include "CourseStore.h"

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 * Binary search tree that stores courses sorted by course ID.
 * Inherits form COurseStore so that it is bechmarked against the hash table.
 */
class BinarySearchTree : public CourseStore {

private:
    Node* root;

    Node* searchRecursive(Node* node, std::string courseId);
    Node* removeNode(Node* node, const std::string& courseId);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    void traverseTree(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course course) override;
    void Remove(std::string courseId) override;
    Course Search(std::string courseId) override;
    void InOrder();
    void PostOrder();
    void PreOrder();
    void validateCourses(BinarySearchTree& courses);
    void displayCourse(Course course);
    void searchCourse(BinarySearchTree& courses, std::string courseId);
    void printCourse(BinarySearchTree& tree);
    void inOrderTraversal(Node* node);
};