#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>
#include <string>
#include <vector>


// mode_t Value for all permissions (777)
#define MOD777  S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP |\
	S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH


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

// Check to Ensure genFile has been created/project has been init
bool _check_init();

// Perform a system call and check exit code
int _check_call(std::string);

// Create the .gen File
std::vector<std::string> _init_genFile(int,char**);

// Returns a Vector of String Representing a Parsed GenFile
std::vector<std::string> _parse_genFile();

// Returns a 2D Vector of String Representing a Parsed TestFile
std::vector<std::vector<std::string> > _parse_testFile();

// Naive implementation of Integer to String
std::string itoa(unsigned int);

// Create the Makefile
bool _init_makefile(std::string);

// Create the test files
void _init_testFiles(std::vector<std::vector<std::string> >);

// Create the test file documentation
std::string _docTest(std::vector<std::vector<std::string> > );

// Create the Project Directory & Files
bool _init_project(char**);



