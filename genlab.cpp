#include "genlab.h"

int main(int argc, char* argv)
{
	// Route Command Line Arguments
	if (argc == 1)
	{
		arg_help();
	}
	else
	{
		if (std::string(argv[1]) == "--init" && argc > 2)
		{
			arg_int(argc, argv);
		}
		else if (std::string(argv[1]) == "--build")
		{
			arg_build();
		}
		else if (std::string(argv[1]) == "--run")
		{
			arg_run();
		}
		else if (std::string(argv[1]) == "--test")
		{
			arg_test();
		}
		else if (std::string(argv[1]) == "--pack")
		{
			arg_pack();
		}
		else
		{
			if (std::string(argv[1]) != "--help")
			{
				std::cout << "\nError: Invalid Argument '" << argv[1] << "'\n\n";
				arg_help();
			}
		}
	}
}


// Init the Project Directory
void arg_init(int c, char* vals[])
{
	// Create Root Directory	-> ./

	// Create Header Directory	-> ./include

	// Create Doc Directory		-> ./docs

	// Create Build Directory	-> ./bin

	// Create Pack Directory	-> ./package

	for (int i = 0; i < c; i++)
	{
		// Create Source Files
	}

	_init_genFile(c, vals);
	
}

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


// Init the .gen File
std::string _init_genFile(int c, std::char* vals[])
{
	std::string genFile, line;
	genFile= "";

	std::cout << "Author: ";
	cin >> genFile; genFile += "\n";

	std::cout << "Email: ";
	cin >> genFile; genFile += "\n";

	std::cout << "Tag: ";
	cin >> genFile; genFile += "\n";

	// Get Description for Project
	std::cout << "\nProject Description (Press <enter> twice to save entry):\n\n";
	do 
	{
		std::getline(std::cin, line);
		genFile += line;
	} while (line != "\n");

	for (int i = 3; i < c; i++)
	{
		// Get Descriptions for other files
		std::cout << "\nBrief Description For " << vals[i] << ":\n";
		std::getline(cin, line);
		genFile += line + "\n";
	}
	
	std::cout << "Enter Libraries for each file, seperated by spaces\n\n";
	std::cout << "\t" << vals[2] << ".h: ";
	std::getline(std::cin, line);

	genFile += line;

	std::cout << "\t" << vals[2] << ".cpp: ";
	std::getline(std::cin, line);

	genFile += line;

	for (int i = 3; i < c; i++)
	{
		std::cout << vals[i] << ": ";
		std::getline(std::cin, line);
		genFile += line;
	}

	std::cout << genFile;

	return "";
}