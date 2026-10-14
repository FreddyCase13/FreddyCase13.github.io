---
title: Algorithms and Data Structures
---

# Algorithms and Data Structures: CS 300 Course Planner

[Back to Home](./)

## Code

### Key Change: Before and After

**Before:** Insert called itself once for every level of the tree. With 2,000 sorted courses the tree was 2,000 levels deep, and the program crashed with a stack overflow.

```cpp
void BinarySearchTree::addNode(Node* node, Course course) {
    if (node->course.courseId.compare(course.courseId) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            this->addNode(node->left, course);   // recursive call
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            this->addNode(node->right, course);  // recursive call
        }
    }
}
```

**After:** Insert walks down the tree with a loop, so it uses the same memory no matter how deep the tree gets.

```cpp
Node* current = root;
while (true) {
    if (current->course.courseId.compare(course.courseId) > 0) {
        if (current->left == nullptr) {
            current->left = newNode;
            return;
        }
        current = current->left;
    }
    else {
        if (current->right == nullptr) {
            current->right = newNode;
            return;
        }
        current = current->right;
    }
}
```

### Benchmark Results (Search Time)

| Test | BST | Hash Table |
|---|---|---|
| 2,000 courses, sorted order | 116,021 µs | 4,852 µs |
| 2,000 courses, random order | 7,514 µs | 5,217 µs |

### Enhanced Files

- [CourseStore.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS300%20Course%20Planner/Enhanced/CourseStore.h) - Abstract base class with Insert, Search, and Remove so that the BST and hash table can be tested with the same code.
- [HashTable.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS300%20Course%20Planner/Enhanced/HashTable.h) - Declares the hash table that stores courses by using separate chaining.
- [HashTable.cpp](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS300%20Course%20Planner/Enhanced/HashTable.cpp) - Inserts, searches, and removes courses in the hash table by using 179 buckets and a multiply-by-31 hash.
- [BinarySearchTree.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS300%20Course%20Planner/Enhanced/BinarySearchTree.h) - Declares the binary search tree that stores courses sorted by course ID.
- [BinarySearchTree.cpp](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS300%20Course%20Planner/Enhanced/BinarySearchTree.cpp) - Binary search tree that inserts, searches, removes, and prints courses.
- [Course.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS300%20Course%20Planner/Enhanced/Course.h) - Holds the data for one course: ID, title, and prerequisites.
- [Project Two.cpp](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS300%20Course%20Planner/Enhanced/Project%20Two.cpp) - Loads the course file, runs the menu, and runs the benchmark.

### Original Files

- [Project Two.cpp](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS300%20Course%20Planner/Original/Project%20Two.cpp) - The original CS 300 program, all in one file.

### Narrative

- [Download narrative (Word)](https://github.com/FreddyCase13/FreddyCase13.github.io/raw/main/CS300%20Course%20Planner/CS499_Freddy_Case_Algorithms_Narrative.docx)

## Artifact Description

The artifact for this category is my Course Planner from CS 300: Data Structures and Algorithms, which was originally written in early 2025. This project is a C++ program that is for a fictional university advising office. It loads data from a CSV file into a Binary Search Tree, then lets the user print every course in order or look up a single course and its prerequisites.

## Justification for Inclusion

I selected this artifact because it allowed me to showcase my ability to produce two intricate data structures and algorithms while also allowing me to test a decision I made in CS 300. When I was planning the project, I had to choose which data structure would be the best one to use for solving the problem presented to me. My original thesis was that a hash table would be the better structure for looking up the courses. I was steered toward using the binary search tree instead of the hash table. This enhancement allowed me to build the hash table along with measurements to show which one would work better in this case.

The enhancement includes a hash table built from scratch using separate chaining to handle collisions. There is also a benchmark that times the insert, search, and remove functions of each structure. To make the comparison fair for each data structure, I created a shared base class called CourseStore that each data structure inherits from. The benchmark method only works with CourseStore, so each data structure runs through the same test code. I also took the original, long code file, and split it into separate files for the course data, the BST, and the hash table so that the code is easier to read and maintain.

The benchmark runs three tests. The first uses the original 8 course CSV to see how both structures handle the real data. The second test generates 2,000 courses in sorted order, which is the worst-case scenario for an unbalanced BST. This causes each new course to be added to the right, and the tree turns into a long line. The third test inserts the same 2,000 courses in random order which keeps the tree balanced and shows how it would perform in an average case.

The results showed that the hash table performed quicker on almost all measurements of the three tests. With the data from the CSV, the hash table was slightly faster on searches. The test with the 2,000 sorted courses showed that the tree took 116,021 microseconds to run all the searches, while the hash table took 4,852 microseconds. For test three, the same 2,000 courses were in random order and gave the BST a significant boost in compute time. In this case, the BST’s search time dropped to 7,514 microseconds, and the hash table was only slightly faster at 5,217 microseconds. These tests show that the BST’s real weakness is sorted input, since nothing in my tree keeps it balanced. Therefore, a BST that might get sorted data should have self-balancing logic to make it as efficient as possible.

These results line up with the Big-O time complexity of each data structure. When a binary search tree is balanced, searching through data takes O(log n) time because each step cuts the remaining tree in half. However, when the courses are inserted in a sorted order, the tree will turn into a long line and searching through it becomes O(n). This is why Test 2 took 116,021 microseconds. In Test 3, the random order kept the tree closer to being balanced which caused the BST (7,514 microseconds) to be closer in compute time with the hash table (5,217 microseconds). Conversely, a hash table searches in O(1) time on average because it will jump into one bucket instead of traversing through a whole structure. Its worst case is O(n) search time if every course lands in the same bucket. That is why it is important to improve the hash function by multiplying the running total by a prime number so that it reduces collisions.

Building the benchmark also exposed some bugs within the original code. The original BST’s remove function threw away the value that tells it where the new top of the tree is. Therefore, removing the top course left the program pointing at memory that was deleted. The original program didn’t catch this since nothing ever called remove. I also fixed an infinite loop in the menu that happened when a user types letters instead of a number. I ended up finding and fixing a bug where a file check only looked at the first line of the CSV.  Finally, I found and fixed a leftover line of code that converted each stored course ID to uppercase which wasn’t actually utilized, but ended up doubling how long each search took.

## Course Outcomes

I planned to meet outcomes three and four with this enhancement and I believe that I achieved both. For completing outcome three, I evaluated two data structures on the same problem and was able to measure the trade-off between them. The hash table is the better data structure in regards to speed, while the BST keeps the courses in sorted order and still performs well with small data sets. For meeting outcome four, I used object-oriented design and polymorphism principles to build a shared interface that both data structures could inherit from.

## Reflection

The hardest part of enhancing this artifact was wiring everything together by splitting one file into several classes. I had to ensure that the inheritance was set up correctly so that each data structure could be connected to main so that the tests could run on both. The biggest challenge I had was overcoming a stack overflow error. My insert function was calling itself once for every level of BST. This made the tree 2,000 levels deep which crashed the program. I then rewrote the insert method as a loop, which uses the same amount of memory regardless of how deep the tree gets. This artifact enhancement ended up showing me that an unbalanced tree is not only slow but can also crash a program.

I also learned that a hash function matters as much as the hash table. My first version added up the characters in each course ID, but there was an issue where IDs with the same characters in a different order ended up landing in the same bucket. Multiplying the sum by 31 before adding each character made the position of each character matter and ended up cutting the hash table’s search time from 7,395 to 5,217 microseconds. If there were any improvements I would make to this project after this enhancement, it would be returning courses by reference and sizing the table to the amount of data. Overall, this enhancement was a refresher for me since I had only built a hash table once before during the CS 300 class. Going back to that original code and building upon it showed me how much data structure choices matter and how much I have grown as a software engineer.

The feedback that I received from my instructor pointed out that adding a hash table that has separate chaining, improving the binary search tree, and constructing a benchmark shows a clear understanding of how each data structure stores, searches, and removes data. The feedback also states that my performance testing with different workloads gave insight into the strengths and weaknesses of each structure. No changes to my plan were requested by my instructor, which confirmed that my approach was sound. Before publishing the final version, I followed my course's guidance that algorithms should be backed by Big-O notation. I added comments to the insert, search, and remove functions of each data structure regarding its time complexity. I also explained how my benchmark results line up with the Big-O of each data structure. I added in code headers to each file so that other developers can see what each file does and what was enhanced.
