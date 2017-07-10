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
		else if (std::string(argv[1]) == "--doc")
		{
			arg_doc();
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

    genFile << prj << "\n#~\n" << gf_str[0] << "#~\n" << gf_str[1];

	for(int i = 1 ; i < cnt; i++)
	{
        genFile << "#~\n" << gf_str[3*i-1] << '\n' << gf_str[3*i] << '\n'
            << gf_str[3*i+1] << '\n';
	}

    genFile << "#~";

	//Close file
	genFile.close();
	
	// Create Initial header and source files
	std::cout << "Creating Project Header and Source Files...\n";

	std::fstream fw;

    // Cycle through and create all files
    for(int i = 2; i < gf_str.size(); i+=3)
    {
        std::string content;

        std::cout << "Creating " << gf_str[i] << "...\n";
        // Create a Header File
        if(gf_str[i].find(".h") != std::string::npos)
        {
	        fw.open((prj + "/include/" + gf_str[i]).c_str(), 
                    std::fstream::out | std::fstream::trunc);

            content = std::string(hfile);

            // Swap in values from file templates
            content = str_replace(content, "{HEADER}",
                    std::string(gf_str[0]) + std::string(gf_str[i+1]));

            content = str_replace(content, "{INCLUDES}", gf_str[i+2]);
            
            content = str_replace(content, "{HFILE}", 
                    str_replace(std::string(gf_str[i]), ".", "_"));

            fw << content;
            fw.close();
            
        }
        // Create a Source File
        else if(gf_str[i].find(".cpp") != std::string::npos)
        {
	        fw.open( (prj + "/srcs/" + gf_str[i] ).c_str(), 
                    std::fstream::out | std::fstream::trunc);

            content = std::string(cppfile);

            // Swap in values from file templates
            content = str_replace(content, "{HEADER}",
                    std::string(gf_str[0]) + std::string(gf_str[i+1]));
            
            content = str_replace(content, "{INCLUDES}", gf_str[i+2]);


            if(gf_str[i].find(prj) != std::string::npos)
            {
                // Add the main function if name matches project name
                content = str_replace(content, "/* Source Code */", 
                        mainfunc);
            }

            fw << content;
            fw.close();

        }

        std::cout << "\tSuccessfully Created " << gf_str[i] << "\n\n";
    }



    _init_makefile(prj);

    std::cout << "[/] Sucessfully Initialized Project Directory\n\n";

    return;
  
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
    char ch;
    std::string line, section, content;
    std::fstream fw;
    std::vector<std::string> genInfo;

    content = std::string(docfile);

    std::cout << "Run Documentation Wizard? (y/n): ";

    getline(std::cin, line);

    if(std::string("YESYesyes").find(line) != std::string::npos)
    {
        std::string designSlide = "";

        genInfo = _parse_genFile();
        
        fw.open( ("docs/" + genInfo[0] + ".tex").c_str(), 
                std::fstream::out | std::fstream::trunc);

        // Set the Specifications Slide
        content = str_replace(content, "{SPECS}", genInfo[4]);

        // Set Inputs, Processes, and Outputs;
        section = "";
        std::cout << "Analysis\n\n";

        // Get the Inputs
        std::cout << "Inputs (leave line empty to save entry): \n";
        do
        {
            getline(std::cin, line);
            section += (line.empty() ? "\n": 
                    ("\t\t\\qii{" + str_replace(line,"\t","i")+"}\n"));
        
        }while(!line.empty());

        // Set the Inputs
        content = str_replace(content, "{INPUTS}", section);
        
        
        // Get the Processes
        section = "";
        std::cout << "Processes (leave line empty to save entry): \n";
        do
        {
            getline(std::cin, line);
            section += 
                (line.empty() ? "\n" : ("\t\t\\item " + line + "\n")); 
        
        }while(!line.empty());

        // Set the Processes
        content = str_replace(content, "{PROCESSES}", section);

        
        // Get the Outputs
        section = "";
        std::cout << "Outputs (leave line empty to save entry): \n";
        do
        {
            getline(std::cin, line);
            section += (line.empty() ? "\n":
                    ("\t\t\\qii{" + str_replace(line,"\t","i")+"}\n"));

        }while(!line.empty());

        // Set the Outputs
        content = str_replace(content, "{OUTPUTS}", section);


        // Go Cycle Through Files for Implementation Slides
        for(int i = 5; i < genInfo.size(); i+=3)
        {
            designSlide += "\t\t\\item["+ genInfo[i] 
                            + "]\\hfill \\\\ " + genInfo[i+1] + "\n"; 
            std::string impSlide = std::string(implmntPage);
            std::string testSlide = std::string(testPage);
            section = "";

            std::cout << "Implementation for " << genInfo[i] 
                << ":\n(leave line empty to save entry)\n";

            getline(std::cin, line);
           
            // Get File Implementation Description
            while(!line.empty())
            {
                section += line + "\n";
                getline(std::cin, line);
            }

            // Generate the Directory name
            std::string dir = "";
            int len = genInfo[i].size();
            
            if( genInfo[i].substr(len - 2, 2) == ".h")
            {
                dir += "include/";
            }
            else if( genInfo[i].substr(len - 4, 4) == ".cpp")
            {
                dir += "srcs/"; 
            }

            int numOfLines = file_count_char(dir + genInfo[i], '\n');

            std::cout << "\nDone Counting Lines\nCount: " 
                << numOfLines << "\n";

            impSlide = str_replace(impSlide,"{DESC}", section);

            for(int j = 1; j <= numOfLines; j+= 15)
            {
                // Add First Line parameter
                impSlide = str_replace(impSlide, "{FL}", 
                        std::string(itoa(j)));
                // Add Last Line parameter
                impSlide = str_replace(impSlide,"{LL}", 
                        std::string(itoa(std::min(j+14,numOfLines))));
               
                std::cout << "J: " << j << "vs num "
                    << numOfLines << "\n";

                impSlide += "\n" + 
                    ((numOfLines - j) < 16 ? "" : 
                     str_replace(implmntPage, "{DESC}", ""));
            }

            
            // Replace all the Filename & Full Filename Placeholders
            impSlide = str_replace(impSlide, "{FN}", genInfo[i]);
            impSlide = str_replace(impSlide, "{FFN}", 
                    "../"+dir+genInfo[i]); 


            // Append New Implementation Slide
            content = str_replace(content, "{IMPL}", 
                    impSlide + "\n{IMPL}");
        }

        // Add In Content For Design Slide 
        content = str_replace(content, "{DESG}", designSlide);
        // Remove Any Trailing Implementation Slides
        content = str_replace(content, "{IMPL}", "");

    }

    fw << content;
    fw.close();

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

		// File Content should be Cleared
		if (choice == "clear" || choice == "Clear")
		{
			if(testFile.is_open())
			{
				testFile.close();
			}	

			std::cout << ((std::remove("bin/test/.tests")) ? 
					"Tests Successfully Cleared.\n" : 
					"Failed to clear tests.\n");
	

		}
		// File Content should be listed
		else if (choice == "list" || choice == "List")
		{
			if(testFile.is_open())
			{
				testFile.close();
			}
            
            // Open the file for reading
			testFile.open("bin/test/.tests", std::fstream::in);
		
            std::cout << "Current Tests:\n\n";

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
				
			testFile <<"#~" << choice << "\n";

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


    std::vector<std::vector<std::string> > testInfo = _parse_testFile();

    
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

    
	genInfo.push_back("");

	// Get Project Description
  	std::cout <<"\nProject Description/Specificatioin (Leave blank line to save entry):\n";
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
	genInfo.push_back(
            line.empty() ? "\n" : // Add newline if 'line' is empty
                ("\n#include <" + str_replace(line, " ", ">\n#include <")
				+ ">\n\n")); // Otherwise add Include Directives 

    // Add Project Source File
	genInfo.push_back(std::string(vals[2]) + ".cpp");
	
    // Get Descriptions for Project Source file
   	std::cout << "\nBrief Description For " << genInfo.back() << ":\n> ";
  	getline(std::cin, line);
    genInfo.push_back(line);
	// Get Included Libraries
	std::cout << "Libraries to Include (seperate by space):\n> ";
	getline(std::cin, line);
	
    genInfo.push_back( 
        line.empty() ? "\n" : // Add newline if 'line' is empty
                ("\n#include <" + str_replace(line, " ", ">\n#include <")
				+ ">\n\n")); // Otherwise add Include Directives 

	// Cycle through and add rest of files
  	for(int i = 3; i < cnt; i++)
  	{ 
     	genInfo.push_back( std::string(vals[i]) ); // Adds Files to Vector

	 	std::cout << "\nBrief Description For " << genInfo[3*i-1] << ":\n> ";
  		getline(std::cin, line);
		genInfo.push_back(line);

		// Get Includes for file
		std::cout << "Libraries to Include (seperate by space):\n> ";

		getline(std::cin, line);
		genInfo.push_back(
            line.empty() ? "\n" : // Add newline if 'line' is empty
                ("\n#include <" + str_replace(line, " ", ">\n#include <")
				+ ">\n\n")); // Otherwise add Include Directives 

  	}


    std::cout << "\n[/]Project Initialization Wizard Completed.\n\n";


  	return genInfo;
}


// Create the Makefile
bool _init_makefile(std::string prj)
{
    // Open File Stream for writing the make file;
    std::fstream fw;
    
    std::string line, content = std::string(makefile);

    content = str_replace(content, "{PROJECT}", prj);

    std::cout << "Makefile Wizard\n\n" <<
        "Any other include directories? (seperate with single space):\n> ";

    getline(std::cin, line);

    content = str_replace(content, "{OIDIRS}",
            (line.empty()) ? line : ("-I " + str_replace(line, " ", " -I ")));

    std::cout << "Any other compiler flags?: \n";

    getline(std::cin, line);

    content = str_replace(content, "{OFLAGS}", line);

    fw.open( (prj + "/Makefile").c_str(), std::fstream::out | std::fstream::trunc);

    fw << content;

    fw.close();

    return true;

}

// Check if Project has been Initialized
bool _check_init()
{
	return std::ifstream(".genFile"); 
}

std::vector<std::string> _parse_genFile()
{
    std::vector<std::string> genFile;
    std::fstream fr(".genFile", std::fstream::in);
    std::string line, lines; 
    
    if(!_check_init())
    {
        return genFile;
    }

    // Get the name of the project
    getline(fr, line);
    genFile.push_back(line);

    // Get Author Line
    getline(fr, line);	//Throw Out '#~'
    getline(fr, line);
    genFile.push_back(line);

    // Get Email Line
    getline(fr, line);
    genFile.push_back(line);
    
    // Get Tag line
    getline(fr, line);
    genFile.push_back(line);

    // Get Description
    lines = "";
    getline(fr, line);	// Throw Out Next '#~'
    
    while(!line.empty())
    {
        getline(fr, line);
        lines += ((line.empty()) ? line : (line + "\n"));
    }

    genFile.push_back(lines);


    lines = "";
    getline(fr, line);	// Throw Out Next '#~'
    
    // Cycle Through the rest of the content
    while(fr.peek() != EOF && fr.good())
    {
        // Get File Name
        do
        {
            getline(fr, line);
        }while(line.empty());
        
        genFile.push_back(line);

        // Get File Description
        getline(fr, line);
        genFile.push_back(line);
        
        //Get Init Content
        while(fr.peek() != EOF)
        {
            getline(fr, line);
            if(line.find("#~") != std::string::npos)
            {
		        //**DB std::cout << "Pushing back:\n" << lines << "\n";
                genFile.push_back(lines);
                lines = "";
                break;
            }
	        else
	        {
		        //std::cout << line << "\n";
		        lines += line + '\n';
	        }
        }
    }


    for(int i = 0; i < genFile.size(); i++)
    {
	    std::cout << i << ".\n" << genFile[i] << "\n\n";
    }

    return genFile;
    
}


std::vector<std::vector<std::string> > _parse_testFile()
{
    std::vector< std::vector<std::string> > tests;
    std::string lines, line;

    std::fstream fr("bin/test/.tests", std::fstream::in);
    

    getline(fr, line);

   	std::vector<std::string> test;

    while(fr.good() && !fr.eof())
    {
		test.clear();   
        if(line.substr(0,2) == "#~")
        {
            // Get Test Name
            test.push_back(str_replace(line, "#~", ""));

            // Push Empty String for holding rest of test
            test.push_back("");
	    	test.push_back("");

            // Cycle through rest of lines for the test
            while( !fr.eof() )
            {
                getline(fr, line);

                if(line.find("#~") == std::string::npos)
                {
                    test[1] += line + "\n";
		    		if(line[0] == '$')
					{
						// Track Any lines that are meant to be
						// 	sent to STDIN
						test[2] += line.substr(1, line.size() - 1) + "\n";
					}
                }
                else
                {
                    tests.push_back(test);
                    break;
                }   
            }
        }
    }

    // Make Sure to add Last Test
    tests.push_back(test);

    for(int i = 0; i < tests.size(); i++)
    {
        std::cout << "\nTest #" << i << "\n";
        for(int j = 0; j < 3; j++)
        {
            std::cout << "" << tests[i][j] << "\n";
        }

        //std::cout << "\n";
    }
    
    return tests;
}

std::string itoa(unsigned int a)
{
    std::string num = "";

    while(a)
    {
        num = (char)(48 + a%10) + num;

        a /= 10;
    }

    return num;
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

