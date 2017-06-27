#include "templates.h"
#include <iostream>
#include <string>

const char* help =
  "GENLAB - Lab Template Generator\n\n"
  "USAGE:\n"
  "\tgenlab [argument] [file ..]\n\n"
  "ARGUMENTS:\n"
  "\t--init\t\tInitialize the project directory,\n"
  "\t\t\tautomatically generate a *.h and\n"
  "\t\t\t*.cpp file for the project along\n"
  "\t\t\twith any other files specified\n"
  "\t\t\tfollowing the argument.\n\n"
  "\t--build\t\tCompiles the project and produces\n"
  "\t\t\tan executable.\n\n"
  "\t--run\t\tRuns the project executable made\n"
  "\t\t\tafter building the project.\n\n"
  "\t--doc\t\tRuns a documentation wizard and\n"
  "\t\t\tgenerates *.tex file.\n\n"
  "\t--test\t\tRuns test cases on the project.\n\n"
  "\t--pack\t\tProduces a *.tgz and *.pdf for\n"
  "\t\t\tproject submission.\n\n"
  "\t--help\t\tPrints Help.\n\n";


const char* header =
  "/**\n@author: {AUTHOR}\n@email:\t{EMAIL}\n{DATE}\n{TAG}\nDesc:\t{DESC}\n\n\n*/";
  
  
const char* genfile =
"#hfiles\n{hfiles}\n"
"#cfiles\n{cfilles}\n"
"#head\n{head}\n"
"#make\n{make}\n"
"#doc\n{doc}\n"
"#test\n{test}\n";

const char* makefile =
"IDIR=include\n"
"SDIR=srcs\n"
"CXX=g++\n"
"CXXFLAGS=-pedantic -Wall -I$(IDIR)\n"
"TEX=latex\n\n"
"";


const char* docfile = 
"";

const char* hfile = 
"";

const char* cppfile = 
"";

const char* testfile = 
"";

const char* buildCMD[] =
  {
	  "{project}",
	  "{project}/include",
	  "{project}/src",
	  "{project}/docs",
	  "{project}/bin",
	  "{project}/bin/build",
	  "{project}/bin/package",
	  "{project}/bin/test"
  };

std::string str_replace(std::string str, std::string ori, std::string rep)
{
  int p = str.find(ori, 0);
  std::string res = "";
  
  while(p != std::string::npos)
  {
    res += str.substr(0, p) + rep;
    str = str.substr(p + ori.size(), str.size() - p - ori.size());
    p = str.find(ori);
  }

  return res + str;
  
}
