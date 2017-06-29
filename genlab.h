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

// Create the Makefile
std::string _init_makefile();

// Create the Project Directory & Files
bool _init_project(char**);



