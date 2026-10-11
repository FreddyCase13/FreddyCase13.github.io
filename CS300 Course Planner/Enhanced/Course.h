/*
 * File:     Course.h
 * Author:   Freddy Case
 * Version:  1.0
 * Date:     September 2026 (CS 499 enhancement)
 * New File: Moved code out of Project Two.cpp into its own file. Both
 *           data structures share it.
 * 
 * Purpose:  Holds the data for one course: ID, title, and prerequisites.
 */
#pragma once

#include <string>
#include <vector>

// Structure to hold course information
struct Course {
    std::string courseId;                  // unique identifier
    std::string title;
    std::vector<std::string> prerequisite;
};