#include <iostream>
#include <fstream>
#include <stdio.h>

#include <string>
#include <vector>

// Init the Project Directory
void arg_init(int, char**);

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

// Perform a system call and check exit code
int _check_call(std::string);

// Create the .gen File
std::string _init_genFile(int,char**);

// Create the Makefile
std::string _init_makefile();

// Create the Project Directory & Files
bool _init_project(char**);



