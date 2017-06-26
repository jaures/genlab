#include "genlab.h"

int main(int argc, char* argv[])
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
			arg_init(argc, argv);
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
void arg_init(int cnt, char* vals[])
{
	// Create Root Directory	-> ./

	// Create Header Directory	-> ./include

	// Create Doc Directory		-> ./docs

	// Create Build Directory	-> ./bin

	// Create Pack Directory	-> ./package

	for (int i = 0; i < cnt; i++)
	{
		// Create Source Files
	}

	_init_genFile(cnt, vals);
	
}

// Build and Compile the Project
void arg_build()
{
  
}

// Run the Project
void arg_run()
{
  
}
// Run documentation Wizard and produce output
void arg_doc()
{

}

// Run the Test Cases
void arg_test()
{

}


// Package the Project
void arg_pack()
{

}

// Produce the Help Message
void arg_help()
{
  std::cout << help << "\n";
}


// Init the .gen File
std::string _init_genFile(int cnt, char* vals[])
{
  std::string genFile = std::string(vals[2]);
  std::string line;

	std::cout << "Author: ";
	std::cin >> line; genFile += line + "\n";

	std::cout << "Email: ";
	std::cin >> line; genFile += line + "\n";

	std::cout << "Tag: ";
	std::cin >> line; genFile += line +"\n";

	// Get Description for Project
	std::cin.ignore(); // Flush buffer
	std::cout << "\nProject Description (Press <ENTER> twice to save entry):\n\n";
	do 
	{
		std::getline(std::cin, line);
		genFile += line + "\n";
	} while (!line.empty());

	// Cycle through the rest of the files
	for (int i = 3; i < cnt; i++)
	{
		// Get Descriptions for other files
		std::cout << "\nBrief Description For " << vals[i] << ":\n";
		getline(std::cin, line);
		genFile += line + "\n";
	}
	
	std::cout << "Enter Libraries for each file, seperated by spaces\n\n";
	std::cout << "\t" << vals[2] << ".h: ";
	getline(std::cin, line);

	genFile += line + "\n";

	std::cout << "\t" << vals[2] << ".cpp: ";
	getline(std::cin, line);

	genFile += line + "\n";

	for (int i = 3; i < cnt; i++)
	{
		std::cout << vals[i] << ": ";
		getline(std::cin, line);
		genFile += line + "\n";
	}

	std::cout << genFile;

	return "";
}
