/*
 * File:     BinarySearchTree.cpp
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * New File: New standalone class. Insert now uses a loop instead
 *           of recursion to stop a stack overflow on sorted data.
 *           Remove now saves the new root. Removed unused functions.
 *
 * Purpose:  Binary search tree that inserts, searches, removes, 
 *           and prints courses.
 */
#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

/**
 * Converts all characters in a selected string to upper case
 *
 * @param str The input string to be converted.
 * @return A new string where all characters are uppercase.
 */
string toUpperCase(string str) {
    // Iterate through each character in string
    for (size_t i = 0; i < str.length(); i++) {
        // convert each string to uppercase
        str[i] = toupper(str[i]);
    }
    // return new uppercase string
    return str;
}

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    while (root != nullptr) {
        Remove(root->course.courseId);
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root
    this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root
    this->preOrder(root);
}

/**
 * Method to insert a course.
 * Updated to walk down the tree with a loop instead of recursion.
 * This new method allows a BST with an order sorted with a long line to
 * not overflow the stack.
 * 
 * Time complexity: O(log n) on average when the tree is balanced.
 * Worst case is O(n) when courses are inserted in sorted order,
 * because the tree turns into one long line.
 */
void BinarySearchTree::Insert(Course course) {
    Node* newNode = new Node(course);
    
    // Empty tree. The new course becomes the root.
    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* current = root;
    while (true) {

        // If new course is smaller, go left.
        if (current->course.courseId.compare(course.courseId) > 0){
            
            // Found an open spot on the left.
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            }
            current = current->left;
        }

        // Else new course is larger or equal, go right.
        else {

            // Found an open spot on the right.
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            }
            current = current->right;
        }
    }
}

/**
 * Remove a course
 * 
 * Time complexity: O(log n) on average.
 * O(n) worst case on a tree built from sorted data.
 */
void BinarySearchTree::Remove(string courseId) {
    // remove node root courseID
	root = removeNode(root, courseId); // update root in case it changes
}

/**
 * Search for a course
 * 
 * Time complexity: O(log n) on average. Each step cuts the remaining tree in half. 
 * Worst case is O(n) on sorted data, which is what benchmark Test 2 measures.
 */
Course BinarySearchTree::Search(string courseId) {
    // converts user input for courseId to upper case
    courseId = toUpperCase(courseId);
    // set current node equal to root
    Node* current = root;
    // keep looping downwards until bottom reached or matching courseId found
    while (current != nullptr) {
        // if match found, return current course
        if (current->course.courseId == courseId) {
            return current->course;
        }
        // if course is smaller than current node then traverse left
        if (courseId.compare(current->course.courseId) < 0) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }
    // return empty course if not found
    return Course();
}

/**
 * Recursively searches for a course in the binary search tree.
 *
 * @param node Pointer to the current node being examined.
 * @param courseId The unique course ID to search for.
 * @return Pointer to the node containing the course if found, otherwise nullptr.
 */
Node* BinarySearchTree::searchRecursive(Node* node, string courseId) {
    //if node is nullptr, course was not found
    if (node == nullptr)
        return nullptr;
    //if current nodes courseID matches search Id, return node
    if (node->course.courseId == courseId)
        return node;
    // if courseID is less than the current nodes courseID, search left subtree
    if (courseId.compare(node->course.courseId) > 0)
        //return searchRecursive(node.left, courseId)
        return searchRecursive(node->left, courseId);
    else
        // else search right subtree
        return searchRecursive(node->right, courseId);

}

/**
 * Performs an in-order traversal of the binary search tree.
 * This traversal visits nodes in ascending order (left, root, right).
 *
 * @param node Pointer to the current node being processed.
 */
void BinarySearchTree::inOrder(Node* node) {
    // if node is not null continue traversal
    if (node != nullptr) {
        // recursively traverse left subtree
        inOrder(node->left);
        // output courseId, title
        cout << node->course.courseId << ", "
            << node->course.title << endl;
        // recursively traverse right subtree
        inOrder(node->right);
    }
}

/**
 * Performs a post-order traversal of the binary search tree.
 * This traversal visits nodes in the following order: left subtree, right subtree, then root.
 *
 * @param node Pointer to the current node being processed.
 */
void BinarySearchTree::postOrder(Node* node) {
    // if node is not null continue traversal
    if (node != nullptr) {
        // recursively traverse left subtree first
        postOrder(node->left);
        // recursively traverse right subtree next
        postOrder(node->right);
        // output courseID, title
        cout << node->course.courseId << " : "
            << node->course.title << endl;
    }
}

/**
 * Perform a pre-order traversal of the binary search tree.
 * In pre-order traversal, the node is processed before its child nodes.
 *
 * @param node The current node being processed.
 */
void BinarySearchTree::preOrder(Node* node) {
    // check if the node is not null
    if (node != nullptr) {
        // output courseID, title
        cout << node->course.courseId << " : "
            << node->course.title << endl;
        // recursively process the left subtree
        preOrder(node->left);
        // recursively process the right subtree
        preOrder(node->right);
    }
}

/**
 * Remove a course from some node (recursive)
 *
 * @param node The current node being examined.
 * @param courseId The ID of the course to be removed.
 * @return The updated node after removal.
 */
Node* BinarySearchTree::removeNode(Node* node, const string& courseId) {
    // if node is null, return null
    if (node == nullptr) {
        return node;
    }
    // otherwise recurse down the left subtree
    if (courseId.compare(node->course.courseId) < 0) {
        // check for match and if so, remove left node using recursive call
        node->left = removeNode(node->left, courseId);
    }
    // otherwise recurse down the right subtree
    else if (courseId.compare(node->course.courseId) > 0) {
        // check for match and if so, remove right node using recursive call
        node->right = removeNode(node->right, courseId);
    }
    // found node to be deleted
    else {
        // case 1: node is a leaf node with no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        // case 2: node has only a left node
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        // case 3: node has only a right node
        else if (node->left == nullptr && node->right != nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        // case 4: node has two children
        else {
            // create temp node to right
            Node* temp = node->right;
            // while left node is not nullptr keep moving temp left
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            // make node bid (right) equal to temp bid (left)
            node->course = temp->course;
            // remove right node using recursive call
            node->right = removeNode(node->right, temp->course.courseId);
        }
    }
    // return node
    return node;
}

/**
 * Recursively traverses BST to check for missing prerequisites.
 * This function verifies if each course's prerequisites exist in the tree.
 *
 * @param node The current node being examined in the traversal.
 */
void BinarySearchTree::traverseTree(Node* node) {
    // if node is null, return
    if (node == nullptr)
        return;
    // Iterate through each prerequisite of current course
    for (const auto& pr : node->course.prerequisite) {
        // Search for prerequisites in BST
        if (this->Search(pr).courseId == "") {
            //  if not count, print error
            cout << "course " << pr << "has missing prerequisite." << endl;
        }
    }
    // recursively traverse the left subtree
    traverseTree(node->left);
    // recursively traverse the right subtree
    traverseTree(node->right);
}

/**
 * Validates courses in the binary search tree by checking if all prerequisites exist.
 *
 * @param courses The BinarySearchTree containing all the courses to validate.
 */
void BinarySearchTree::validateCourses(BinarySearchTree& courses) {
    // traverse tree from the root to check for missing prerequisites
    traverseTree(courses.root);

}

/**
 * Displays course ID, title, and prerequisites (if any).
 *
 * @param course The Course object containing course information.
 */
void BinarySearchTree::displayCourse(Course course) {
    // print courseID and title
    cout << course.courseId << ", " << course.title << endl;
    // if there are any prereuisites
    if (!course.prerequisite.empty()) {
        // print "Prerequisites: "
        cout << "Prerequisites: ";
        // itereate through prerequisites for course and print each one
        for (size_t i = 0; i < course.prerequisite.size(); i++) {
            // print prereuisite
            cout << course.prerequisite[i];
            // adds comma between each prerequisite
            if (i < course.prerequisite.size() - 1) {
                // comma separator between prerequisites
                cout << ", ";
            }
        }
        // add a new line after adding all prerequisites
        cout << endl;
    }
}

/**
 * Searches for a course in the binary search tree and displays its details.
 *
 * @param courses The BinarySearchTree object containing course data.
 * @param courseId The ID of the course to search for.
 */
void BinarySearchTree::searchCourse(BinarySearchTree& courses, string courseId) {
    // have node correspond to courseId using recursive search
    Node* courseNode = courses.searchRecursive(courses.root, courseId);
    // if the courseNode is not null
    if (courseNode != nullptr) {
        //print out the course information
        displayCourse(courseNode->course);
    }
    // else print that the course was not found.
    else {
        cout << "course not found" << endl;
    }
}

/**
 * Prints all courses in the Binary Search Tree (BST) in alphanumeric order.
 *
 * @param tree The BinarySearchTree object containing the course data.
 */
void BinarySearchTree::printCourse(BinarySearchTree& tree) {
    // print courses in sorted traversal order
    inOrderTraversal(tree.root);
}

/**
 * Performs an in-order traversal of the Binary Search Tree (BST)
 * to print course details in sorted order.
 *
 * @param node The current node being processed in the BST.
 */
void BinarySearchTree::inOrderTraversal(Node* node) {
    // if node is null, return to stop recursion
    if (node == nullptr)
        return;
    // traverse though the left subtree
    inOrderTraversal(node->left);
    // print current nodes course information
    cout << node->course.courseId << ": " << node->course.title;
    // if the course has no prerequisites
    if (node->course.prerequisite.empty()) {
        // print "No prerequisites"
        cout << "No prerequisites" << endl;
    }
    // else print prerequisites
    else {
        cout << "Prerequisite(s): ";
        for (const auto& pr : node->course.prerequisite)
            // print space after every prerequisite
            cout << pr << " " << endl;
    }
    // traverse the right subtree
    inOrderTraversal(node->right);
}