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
	std::ofstream genFile;
	genFile.open( (prj + "/.genFile").c_str() | std::ios::noreplace);

    if(genFile.bad())
    {
        // Exit on error
        std::cout << "Error: Failed to create genFile."
            << "Project may already exist or insufficient permissions.\n\n";
        return;
    }

	genFile << _init_genFile(cnt, vals);

	//Close file
	genFile.close();


	// Create Initial header and source files
	std::cout << "Creating Project Header and Source Files...\n";



	
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
    // Open Test File
    std::fstream tests;
    tests.open("/bin/test/.tests", std::fstream::in | std::fstream::out | std::fstream::app);

    if(tests.fail())
    {
        // Exit on Error
        std::cout << "Error: Unable to access tests\n\n";
        return;
    }


    std::string choice;
    char ch;

    std::cout << "Run Test Wizard? (y/n): ";
    getline(std::cin, choice);

    // Run Through Test Wizard if yes
    for(int i = 0; string("YESYesyes").find(choice) != std::string::npos)
    {
        std::string test = "#";
    }
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
  	std::string genFile;
  	std::string line;

  	// Append Project Files to genFile
  	genFile += "#FILES#\n";
  	for(int i = 2; i < cnt; i++)
  	{ 
    	genFile += std::string(vals[i]) + '\n';
  	}

  	// Append Header information to genFile
  	genFile += "#HEADER#\n";
  
  	std::cout << "Author: ";
  	std::cin >> line; genFile += line + "\n";

  	std::cout << "Email: ";
  	std::cin >> line; genFile += line + "\n";

  	std::cout << "Tag: ";
  	std::cin >> line; genFile += line +"\n";

  	// Append File Descriptions to genFile
  	genFile += "#DESC#\n";
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

  	// Append libraries for each file
  	genFile += "#INCLUDES\n";
  	std::cout << "Enter Libraries for each file, seperated by spaces\n\n";
  	std::cout << "\t" << vals[2] << ".h: ";
  	getline(std::cin, line);
  
  	genFile += line + "\n";
  
  	std::cout << "\t" << vals[2] << ".cpp: ";
  	getline(std::cin, line);
  
  	genFile += line + "\n";
  
  	for (int i = 3; i < cnt; i++)
  	{
		std::cout << "\t" << vals[i] << ": ";
		getline(std::cin, line);
 		genFile += line + "\n";
  	}
 
    // Mark end of the genFile
  	genFile += "####\n";
  
 	std::cout << genFile;

  	return genFile;
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

