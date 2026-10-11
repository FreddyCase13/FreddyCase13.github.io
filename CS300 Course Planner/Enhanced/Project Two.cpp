/*
 * File:     Project Two.cpp
 * Author:   Freddy Case
 * Version:  2.0
 * Date:     September 2026 (CS 499 enhancement)
 * Original: CS 300 Data Structures and Algorithms, February 2025
 *
 * Purpose:  Loads the course file and runs the menu for the course planner.
 *
 * Changes:  Added menu input validation so letters no longer cause an infinite
 *           loop. File check now validates every line. Load function works
 *           with any CourseStore. Added menu option 4 to benchmark the BST
 *           against the hash table.
 */

#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits> // added for numeric_limits.
#include <algorithm> // added for remove() in strToDouble.
#include <chrono> // added for timing the operations.
#include <random> // added for generating random numbers.
#include <cstdio> // added for generating course IDs.
#include "Course.h" // Include the new Course.h header file.
#include "CourseStore.h" // Include the new CourseStore.h header file.
#include "BinarySearchTree.h" // Include the new BinarySearchTree.h header file.
#include "HashTable.h" // Include the new HashTable.h header file.

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

/**
 * Splits a string into a vector based on specified delimeter
 *
 * @param s The input string to be split.
 * @param delimiter The character used to split the string.
 * @return A vector containing the extracted substrings.
 */
vector<string> split(const string& s, char delimiter) {
    // Vector that stores split substrings
    vector<string> tokens;
    // string to hold token
    string token;
    // input string stream from the given string
    istringstream tokenStream(s);
    // read each substring separated by delimeter
    while (getline(tokenStream, token, delimiter)) {
        // add the extracted token to the vector
        tokens.push_back(token);
    }
    // if delimiter is the last character
    if (s.back() == delimiter) {
        // add empty string as last token
        tokens.push_back("");
    }
    // return vector 'tokens'
    return tokens;
}

//============================================================================
// Static methods used for testing
//============================================================================

bool validateFile(string filename) {
    //open file
    ifstream inFile(filename);
    // alerts user with errors opening file
    if (!inFile.is_open()) {
        cout << "Error opening file." << endl;
        return false;
    }
    string line;
    // while looking at each line in file
    while (getline(inFile, line)) {
        //partition each parameter between commas
        vector<string> tokens = split(line, ',');
        // if file has less than 2 parameters
        if (tokens.size() < 2) {
            // print “filename does not have enough parameters”
            cout << "filename does not have enough parameters" << endl;
            //close file
            inFile.close();
            return false;
        }
    }
    // close file. Every line was checked and passed.
    // was inside the loop previously. Now is outside the loop
	// to ensure the file is closed after all lines have been processed.
    inFile.close();
    return true;
}

/**
 * Reads course data from a CSV file and inserts it into a Binary Search Tree.
 *
 * @param csvPath The file path of the CSV file containing course data.
 * @param courses The Binary Search Tree to store the course data.
 */
 // was: void loadCourses(string csvPath, BinarySearchTree& courses) {
    vector<Course> readCourses(string csvPath) {
        vector<Course>courses;
    // checks to see if the csv file is valid using validater. If not, return.
     if (!validateFile(csvPath))
        return courses;
    //open csv file. Alerts user if file cannot open.
    ifstream inFile(csvPath);
    if (!inFile.is_open()) {
        cout << "Error opening file" << endl;
        return courses;
    }
    //
    string line;
    //for each line in validated file
    while (getline(inFile, line)) {
        //Create course newCourse
        Course newCourse;
        // partition each parameter between commas.
        vector<string> tokens = split(line, ',');
        // if there are fewer than 2 parameters, skip this line
        if (tokens.size() < 2)
            continue;
        //set newCourse.courseId to first partitioned parameter
        newCourse.courseId = tokens[0];
        //set newCourse.title to second partitioned parameter
        newCourse.title = tokens[1];
        // for all additional partitioned parameters
        for (size_t i = 2; i < tokens.size(); i++) {
            //  add to newCourse.prerequisite
            if (!tokens[i].empty()) {
                newCourse.prerequisite.push_back(tokens[i]);
            }
        }
        courses.push_back(newCourse);
    }
    // close file
    inFile.close();
    return courses;
}

/**
 * Loads courses from the CSV into BST and Hash Table
 * by reading the file once and inserting each course.
 */
    void loadCourses(string csvPath, CourseStore& courses) {
        for (const Course& course : readCourses(csvPath)) {
            courses.Insert(course);
        }
    }
 /**
 * Method to create a list of fake courses for testing purposes.
 * The IDs are sorted in order. Sorted input is the worst case
 * for a BST. This will be used to test the performance of the BST and Hash Table.
 */
    vector<Course> generateSortedCourses(int count) {
        vector<Course> courses;
        char courseId[16];
        for (int i = 1; i <= count; i++) {
            snprintf(courseId, sizeof(courseId), "TEST%05d", i);
            Course course;
            course.courseId = courseId;
            course.title = "Generated Test Course";
            courses.push_back(course);
        }
		return courses;
    }

/**
 * Benchmark Method to test the performance of the BST and Hash Table.
 * Times insert, search, and remove operations for both data structures.
 */
    void benchmark(string label, CourseStore& store, const vector<Course>& courses, int searchRounds) {
        // shuffle search and remove order so neither structure benefits from insert order.
        vector<Course> shuffled = courses;
        mt19937 randomGenerator(499);
        shuffle(shuffled.begin(), shuffled.end(), randomGenerator);

        auto start = chrono::steady_clock::now();
        for (const Course& course : courses) {
            store.Insert(course);
        }
        auto insertDone = chrono::steady_clock::now();

        for (int round = 0; round < searchRounds; round++) {
            for (const Course& course : shuffled) {
                store.Search(course.courseId);
            }
        }
        auto searchDone = chrono::steady_clock::now();

        for (const Course& course : shuffled) {
            store.Remove(course.courseId);
        }
        auto removeDone = chrono::steady_clock::now();

        auto insertTime = chrono::duration_cast<chrono::microseconds>(insertDone - start).count();
		auto searchTime = chrono::duration_cast<chrono::microseconds>(searchDone - insertDone).count();
        auto removeTime = chrono::duration_cast<chrono::microseconds>(removeDone - searchDone).count();

        cout << " " << label << endl;
        cout << " - Insert Time: " << insertTime << " microseconds" << endl;
        cout << " - Search Time : " << searchTime << " microseconds" << endl;
		cout << " - Remove Time: " << removeTime << " microseconds" << endl;
    }

/**
 * This Method runs two benchmark tests: the real course CSV, and a larger sorted data set
 * that shows what happens to an unbalanced BST in its worst case.
 */

    void runBenchmark(string csvPath) {
        vector<Course> realCourses = readCourses(csvPath);
        if (realCourses.empty()) {
            cout << "No courses loaded, benchmark cancelled." << endl;
            return;
        }

        const int realSearchRounds = 10000;
        cout << "Test 1: " << realCourses.size() << " courses from the CSV, search "
            << realSearchRounds << " times each" << endl;
        {
            BinarySearchTree bst;
            HashTable hashTable;
            benchmark("Binary Search Tree", bst, realCourses, realSearchRounds);
            benchmark("Hash Table", hashTable, realCourses, realSearchRounds);
        }
        cout << endl;

        const int generatedCount = 2000;
        vector<Course> sortedCourses = generateSortedCourses(generatedCount);
        cout << "Test 2: " << generatedCount << " generated courses inserted in sorted order" << endl;
        {
            BinarySearchTree bst;
            HashTable hashTable;
            benchmark("Binary Search Tree", bst, sortedCourses, 1);
            benchmark("Hash Table", hashTable, sortedCourses, 1);
        }
        cout << endl;

        // This test runs the same 2000 courses, but is shuffled before inserting.
        vector<Course> randomCourses = sortedCourses;
        mt19937 shuffleGenerator(2000);
        shuffle(randomCourses.begin(), randomCourses.end(), shuffleGenerator);
        cout << "Test 3: " << generatedCount << " generated courses inserted in random order" << endl;
        {
            BinarySearchTree bst;
            HashTable hashTable;
            benchmark("Binary Search Tree", bst, randomCourses, 1);
            benchmark("Hash Table", hashTable, randomCourses, 1);
        }
        cout << endl;
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        courseKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        courseKey = argv[2];
        break;
    default:
        csvPath = "CS 300 ABCU_Advising_Program_Input.csv";
        courseKey = "98223";
    }

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    cout << "Welcome to the Course Planner" << endl;
    cout << endl;

    while (choice != 9) {
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  4. Run Performance Benchmark" << endl;
        cout << "  9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";

        // If the user types something that is not a number, cin goes
        // into a fail state and runs an infinte loop.
        // This throws away bad input and prompts the user again.
		if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter a number from the menu." << endl;
            cout << endl;
            continue;
		}

        switch (choice) {

        case 1:

            // tells user program is loading the data structure
            cout << "Loading Data Structure..." << endl;

            // Complete the method call to load the bids
            loadCourses(csvPath, *bst);

            cout << "...Data loaded!" << endl;
            cout << endl;
            break;

        case 2:
            // tells user that they selected a sample schedule
            cout << "Here is a sample schedule: " << endl;
            cout << endl;
            // perform in order traversak if BST to print courses in sorted order
            bst->InOrder();
            cout << endl;
            break;

        case 3:
            // prompts user to enter the course they want to look up
            cout << "What course do you want to know about? ";
            // take user input
            cin >> courseKey;
            // search input in bst
            course = bst->Search(courseKey);
            //if course exists, print details
            if (!course.courseId.empty()) {
                bst->displayCourse(course);
                }
            // if course is not found, print error message
            else {
                cout << "Course '" << courseKey << "' not found. Please re-enter!" << endl;
            }
            break;

        case 4:
            cout << "Running benchmark..." << endl;
            cout << endl;
            runBenchmark(csvPath);
            break;

            // exits the program
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            cout << endl;
            return 0;

            // default to choice not being a valid option if a case number does not have a menu option.
        default:
            cout << choice << " is not a vaild option" << endl;
            cout << endl;
        }
    }

    return 0;
}
