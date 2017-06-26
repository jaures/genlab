#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include "templates.h"

// Init the Project Directory
void arg_init(int c, char* v[]);

// Build and Compile the Project
void arg_build();

// Run the Project
void arg_run();

// Run documentation Wizard and produce output
void arg_doc();

// Run the Test Cases
void arg_test();

// Package the Project
void arg_pack();

// Produce the Help Message
void arg_help();


// Create the .gen File
std::string _init_genFile();

// Create the Makefile
std::string _init_makefile();