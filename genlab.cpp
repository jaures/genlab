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
				std::cout << "\nError: Invalid Usgae or Unrecognized Argument: '" 
						<< argv[1] << "'\n\n";
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
				<< "Failed to create: " << 
				str_replace(buildCMD[i], "{project}", vals[2]) 
				<< "\n";

			return;
		}
	}

	// Go through Wizard and Generate genFile
	std::fstream genFile;
	genFile.open( (prj + "/.genFile").c_str(), std::fstream::out | std::fstream::trunc);

    if(genFile.bad())
    {
        // Exit on error
        std::cout << "Error: Failed to create genFile."
            << "May not have sufficient permissions.\n\n";
        return;
    }

    std::vector<std::string> gf_str = _init_genFile(cnt, vals);

	for(int i =0 ; i < cnt; i++)
	{
		std::cout << gf_str[i] << "\n";
	}

	std::cout << "Here is what I'm working with:\n" << gf_str[0];

	genFile << gf_str[0];

	//Close file
	genFile.close();

	//Reopen for parsing through & to make sure everything saved properly
	genFile.open( (prj + "/.genFile").c_str(), std::fstream::in);
	
	// Create Initial header and source files
	std::cout << "Creating Project Header and Source Files...\n";

	std::fstream fw;

	fw.open( (prj + "/src/" +  prj + ".cpp").c_str(), std::fstream::out);



	
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

			std::cout << (std::remove("bin/test/.tests")) ? 
					("Tests Successfully Cleared.\n") : 
					("Failed to clear tests.\n");
	

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
				testFile.getline(buff, MAXBUFF, '\0');
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
std::vector<std::string> _init_genFile(int cnt, char* vals[])
{
  	std::string line;
	std::vector<std::string> genInfo;

  	// Get Header Information 
  
  	std::cout << "Author: ";
  	getline(std::cin, line);
	// Create first item in genInfo for holding general project information
	genInfo.push_back("Author:\t" + line + "\n");

  	std::cout << "Email: ";
  	getline(std::cin, line); 
	// Append Onto the first item Developer Email
	genInfo[0]+= "Email:\t" + line + "\n";

  	std::cout << "Tag: ";
  	getline(std::cin, line); 
	// Append Project Tag Onto the first Item
	genInfo[0] += line +"\n";

    
	genInfo.push_back("Description: \n");

	// Get Project Description
  	std::cout <<"\nProject Description (Leave blank line to save entry):\n";
	do 
  	{
      	std::getline(std::cin, line);
        genInfo[1] += line + '\n';

    } while (!line.empty());

	// Add All Project Files

    // Add Project Header File
	genInfo.push_back(std::string(vals[2]) + ".h");
	
    // Get Descriptions for Project Header file
   	std::cout << "\nBrief Description For " << genInfo.back() << ":\n> ";
  	getline(std::cin, line);
	genInfo.push_back(line);
	// Get Included Libraries
	std::cout << "Libraries to Include (seperate by space):\n> ";
	getline(std::cin, line);
	genInfo[2] += ("\n#include <" + str_replace(line, " ", ">\n#include <")
				+ ">\n\n");

    // Add Project Source File
	genInfo.push_back(std::string(vals[2]) + ".cpp ");
	
    // Get Descriptions for Project Source file
   	std::cout << "\nBrief Description For " << genInfo.back() << ":\n> ";
  	getline(std::cin, line);
	genInfo.push_back(line);
	// Get Included Libraries
	std::cout << "Libraries to Include (seperate by space):\n> ";
	getline(std::cin, line);
	genInfo[4] += ("\n#include <" + str_replace(line, " ", ">\n#include <")
				+ ">\n\n");

	// Cycle through and add rest of files
  	for(int i = 5; i < cnt * 2 - 3; i += 2)
  	{ 
     	genInfo.push_back( std::string(vals[i]) ); // Adds Files to Vector

	 	std::cout << "\nBrief Description For " << genInfo[i] << ":\n> ";
  		getline(std::cin, line);
		genInfo.push_back(line);

		// Get Includes for file
		std::cout << "Libraries to Include (seperate by space):\n> ";

		getline(std::cin, line);
		genInfo[i+1] += ("\n#include <" + str_replace(line, " ", ">\n#include <")
				+ ">\n\n");

  	}

	std::cout << "\n\nFinal Config: \n" << genInfo[0] 
					<< '\n' << genInfo[1] << "\n####\n";

  	return genInfo;
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

