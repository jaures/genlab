#include "genlab.h"
#include "templates.h"

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
				std::cout << "\nError: Invalid Usgae or Unrecognized Argument: '" << argv[1] << "'\n\n";
			}

			arg_help();
		}
	}
}


// Init the Project Directory
void arg_init(int cnt, char* vals[])
{
	bool init_res = false;
	std::string prj = std::string(vals[2]);
	std::string info[cnt + 2];

	for( int i = 0; i < 8; i++)
	{
		// Create and Check for errors
		if (mkdir( str_replace(buildCMD[i], "{project}", prj).c_str(), MOD777))
		{
			std::cout << "Error: Failed to Create Project Directory\n\t"
				<< "Failed to create: " << buildCMD[i] << "\n";
			return;
		}
	}

	// Go through Wizard and Generate genFile
	std::fstream genFile;
	genFile.open( (prj + "/.genFile").c_str(), std::fstream::trunc);

    if(genFile.bad())
    {
        // Exit on error
        std::cout << "Error: Failed to create genFile."
            << "May not have sufficient permissions.\n\n";
        return;
    }
	else if(!genFile.eof())
	{
		// Exit on project already existing
			std::cout << "Error: This project already exists.\n\n";
	}

	std::string gf_str = _init_genFile(cnt, vals, info);
	genFile << gf_str;

	//Close file
	genFile.close();

	//Reopen for parsing through & to make sure everything saved properly
	genFile.open( (prj + "/.genFile").c_str(), std::fstream::in);
	
	std::string tkn;

	do
	{
		getline(genFile, tkn);
		
		
	}while(tkn != "####" || !genFile.eof() || !genFile.bad());

	// Create Initial header and source files
	std::cout << "Creating Project Header and Source Files...\n";

	std::fstream fw;

	fw.open( (prj + "/src/" +  prj + ".cpp".c_str(), std::fstream::out);



	
  for (int i = 0; i < cnt; i++)
  	{
    	// Create Source Files
  	}
  
  
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

	// Check to make sure project has been initialized
	if(!_check_init())
	{
			// Exit on Error: Project was not init
			std::cout << "No project found in this directory. Make sure to --init the project first.\n";
			return;
	}

    // Open Test File
    std::fstream testFile;
    testFile.open("bin/test/.tests", std::fstream::out | std::fstream::app);

    if(testFile.fail())
    {
        // Exit on Error
        std::cout << "Error: Unable to access tests\n\n";
        return;
    }


    std::string tests = "";
    std::string choice;

    std::cout << "Run Test Wizard? (y/n): ";
    getline(std::cin, choice);

    // Run Through Test Wizard if yes
    while(std::string("YESYesyes").find(choice) != std::string::npos)
    {
		std::cout << "\nType 'list' to list current tests or 'clear' to clear all test cases\n"
			<< "\tNew test: ";

		getline(std::cin, choice);

		std::cout << "ECHO:" << choice;

		// File Content should be Cleared
		if (choice == "clear" || choice == "Clear")
		{
			if(testFile.is_open())
			{
				testFile.close();
			}	
		
			testFile.open("bin/test/.tests", std::fstream::trunc);

			testFile.close();
		}
		// File Content should be listed
		else if (choice == "list" || choice == "List")
		{
			if(testFile.is_open())
			{
				testFile.close();
			}

			testFile.open("bin/test/.tests", std::fstream::in);
		
			// Read and print full content of the file
			char buff[MAXBUFF];
			while(!testFile.eof() || !testFile.fail())
			{
				testFile.read(buff, MAXBUFF);
				std::cout << std::string(buff);
				//std::cout << testFile.peek();
			}
		
			testFile.close();

		}	
		else
		{	
			// Open file for writing
			if(testFile.is_open())
			{
				testFile.close();
			}
			
			testFile.open("bin/test/.tests", std::fstream::in | std::fstream::app);

			std::cout << "\n\t> Test " << choice 
				<< "\n\tlines begining with '$' are sent to STDIN"
				<< "\n\tleave the line empty to  save test\n";
				
			testFile <<"#%" << choice << "\n";

			// Get Lines for the test
			do
			{
				std::cout << "\t\t==> ";
				getline(std::cin, choice);
				testFile << choice << "\n";

			}while(!choice.empty());

		}

		std::cout << "\nContinue with Test Wizard? (y/n): ";
		getline(std::cin, choice);
	}

    if(testFile.is_open()){ testFile.close(); }

	std::cout << "Testing now...\n\n";

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
std::string _init_genFile(int cnt, char* vals[], std::string genInfo[])
{
  	std::string line;

	// Add List of Project Files
	genInfo[0] = std::string(vals[2]) + ".h " + std::string(vals[2]) + ".cpp ";

  	for(int i = 3; i < cnt; i++)
  	{ 
    	genInfo[0] += std::string(vals[i]) + ' ';
  	}

  	// Get Header Information 
	genInfo[1] = "";
  
  	std::cout << "Author: ";
  	std::cin >> line; genInfo[1] += "Author:\t" + line + "\n";

  	std::cout << "Email: ";
  	std::cin >> line; genInfo[1]+= "Email:\t" + line + "\n";

  	std::cout << "Tag: ";
  	std::cin >> line; genInfo[1] += line +"\n";

  	// Get Project Description
  	std::cin.ignore(); // Flush buffer
  	std::cout << "\nProject Description (Press <ENTER> twice to save entry):\n\n";
  	do 
  	{
      	std::getline(std::cin, genInfo[2]);


    } while (!line.empty());
  
	std::cout << "\tInclude Libraries for " << vals[2] 
			<< ".h (seperated by spaces): ";

	getline(std::cin, line);
	genInfo[3] += ("\n#include <" + str_replace(line, " ", ">\n#include <")
				+ ">\n\n"); 
  	
	// Cycle through the rest of the files
  	for (int i = 3; i < cnt; i++)
	{
    	// Get Descriptions for other files
   		std::cout << "\nBrief Description For " << vals[i] << ":\n";
  		getline(std::cin, genInfo[1+i]);

		// Get Includes for file
		std::cout << "\tIncluded Libraries (seperate by space): ";

		getline(std::cin, line);
		genInfo[1+i] += ("\n#include <" + str_replace(line, " ", ">\n#include <")
				+ ">\n\n");
  	}	

 	std::cout << (genInfo[0] + '\n' + genInfo[1] + '\n' + genInfo[2]);

  	return genInfo[0] + '\n' + genInfo[1] + '\n' + genInfo[2];
}

// Check if Project has been Initialized
bool _check_init()
{
	return std::ifstream(".genFile"); 
}


int _check_call(std::string cmd )
{
  // Open a stream to a process's outputs
  cmd.append(" 2>&1");
  FILE * cmd_stream = popen(cmd.c_str(), "r");

  char buff[1024];
  while(std::fgets(buff, 1024, cmd_stream) != NULL )
  {
    std::cout << std::string(buff);
  }

  std::cout << buff << "\n";
  
  return  pclose(cmd_stream);
}

