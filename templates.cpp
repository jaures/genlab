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
"# {PROJECT} Makefile\n"
"PRJCT={PROJECT}\n\n"

"# Include Directory\n"
"IDIR:=include/\n\n"

"# Other Include Directories"
"OIDIR:={OIDIRS}"

"# Header Files\n"
"INCS=(wildcard $(IDIR)*.h)\n\n"

"# Source Directory\n"
"SDIR:=srcs/\n\n"

"# Source Files\n"
"SRCS=(wildcard $(SDIR)*.cpp)\n"

"# Docs Directory\n"
"DDIR:=docs/\n\n"

"# Build Directory\n"
"BDIR:=bin/build/\n\n"

"# Pack Directory\n"
"PDIR:=bin/build/\n\n"

"# Test Directory\n"
"TDIR:=bin/test/\n"

"# C++ Compiler\n"
"CXX=g++\n"

"# C++ Flags to Pass to Compiler\n"
"CXXFLAGS=-pedantic -Wall -I $(IDIR) $(O_IDIRS)\n"

"# Other C++ Flags\n"
"OFLAGS={OFLAGS}\n\n"

"# Output Flag\n"
"OUT:= -o $(BDIR)\n\n"

"# TEX Compiler\n"
"TEX=latex\n\n"

"# DVI to PDF Program\n"
"DTP=dvipdf\n\n"

"# Make sure make does not operate files\n"
"# with reserved targets\n"
".PHONY: clean run back\n\n"

"$(PRJCT): $(INCS) $(SRCS)"
"\n\t$(warning On Error try running 'make clean' first)"
"\n\t$(info compiling files: $?)"
"\n\t$(CXX) $(SRCS) $(OFLAGS) $(CXXFLAGS) $(OUT)\n\n\n"

"clean:"
"\n\trm -rf include/*.gch"
"\n\trm -rf bin/build/*\n\n"

"run: $(BDIR)$(PRJCT)"
"\n\t./$<\n\n"

""
""
"\n\t"
"";


const char* docfile = 
"";

const char* hfile = 
"{HEADER}\n\n"
"{DESC}\n*/\n\n"
"// Include Guard\n#ifndef __{HFILE}\ndefine __{HFILE}"
"// Include Dependencies\n{INCLUDES}\n\n"
"// Function Prototypes\n\n"
"// Global Extern Variables & Other Foward Declarations\n\n"
"// Close Include Guard\n#endif\n";

const char* cppfile = 
"/*\n{HEADER}\n\n\n"
"{DESC}\n*/\n\n"
"// Include Dependencies\n{INCLUDES}\n\n"
"// Global Declarations/Definitions\n\n"
"// Function Defintions\n/* Source Code */\n"
"";


const char* mainfunc = 
"// Main Function\nint main(int argc, char* argv[])\n{\n\t/* Source Code */\n\treturn 0;\n}\n\n";


const char* buildCMD[] =
  {
	  "{project}",
	  "{project}/include",
	  "{project}/srcs",
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
