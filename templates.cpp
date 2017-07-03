#include "templates.h"

const int MAXBUFF = 1024;

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
"INCS=$(wildcard $(IDIR)*.h)\n\n"

"# Source Directory\n"
"SDIR:=srcs/\n\n"

"# Source Files\n"
"SRCS=$(wildcard $(SDIR)*.cpp)\n"

"# Docs Directory\n"
"DDIR:=docs/\n\n"

"# Build Directory\n"
"BDIR:=bin/build/\n\n"

"# Pack Directory\n"
"PDIR:=bin/package/\n\n"

"# Directories to Package\n"
"PKGS=$(IDIR) $(OIDIR) $(SDIR) $(DDIR) $(BDIR) $(TDIR)\n\n"


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
".PHONY: all project prjct proj pro clean run docs pack backup recover\n\n"

"all: project prjct proj pro docs"
"\n\t$(info Making $(PRJCT) and Docs...)\n\n\n"

"project: $(BDIR)$(PRJCT)\n"
"prjct: $(BDIR)$(PRJCT)\n"
"proj: $(BDIR)$(PRJCT)\n"
"pro: $(BDIR)$(PRJCT)\n\n\n"

"%$(PRJCT): $(INCS) $(SRCS)"
"\n\t$(warning On Error try running 'make clean' first)"
"\n\t$(info compiling files: $?)"
"\n\t$(CXX) $(SRCS) $(OFLAGS) $(CXXFLAGS) -o $@\n\n\n"

"clean:"
"\n\trm -rf include/*.gch"
"\n\trm -rf bin/build/*\n\n\n"

"run: $(BDIR)$(PRJCT)"
"\n\t./$<\n\n\n"

"docs: $(DDIR)$(PRJCT).tex $(SRCS) $(INCS) "
"\n\tlatex -output-directory $(DDIR) $<"
"\n\tdvipdf $(DDIR)$(PRJCT).dvi $(DDIR)$(PRJCT).pdf\n\n\n"

"pack: $(INCS) $(SRCS) $(DDIR)$(PRJCT).pdf"
"\n\ttar czvf $(PDIR)$(PRJCT)_pkg.tgz $(PKGS)"
"\n\tcp -uvf $(DDIR)$(PRJCT).pdf $(PDIR)\n\n\n"

"backup: pack"
"\n\ttar czvf $(PDIR)/.backup.tgz $(PDIR)*\n\n\n";


const char* docfile = 
"\\documentclass{ffslides}\n"
"\\ffpage{25}{\\numexpr 16/9}\n"
"\\usepackage{fancyvrb}\n"
"\\usepackage[T1]{fontenc}\n"
"\\usepackage{underscore}\n"
"\\begin{document}\n"

"\\normalpage{Specification}\n"
"{Description of what program does from users point of view}\n"

"\\normalpage{Analysis}\n"
"\\{\nqi{Inputs:}\n"
"\\qi{Process:}\n"
"\\qi{Outputs:}\n}\n"

"\\normalpage{Design}\n"
"{\nList each module (compilation unit)"
"with short description\n}\n"

"\\normalpage{Implementation: h File}\n"
"{\nWrite algorithm for expected inputs and outputs"
"...or describe program state (variables)"
"\\VerbatimInput{lab.h}\n"
"}\n"
"%\\putfig{.1}{.7}{.8}{labh}\n"

"\\normalpage{Implementation: cpp File}\n"
"{\nWrite algorithm for expected inputs and outputs\n"
"...or describe program state (variables)"
"\\VerbatimInput{lab.cpp}"
"\n}\n"
"%\\putfig{.1}{.7}{.8}{labcpp}\n"

"\\normalpage{Test}\n"
"{\nSeveral testcases to verify that program meets requirements"
" with expected output manually calculated for each"
"\\qi{Testcase 1:}\n"
"%\\putfig{.1}{.4}{.8}{labcpp}\n"
"\\qi{Testcase 2:}\n"
"%\\putfig{.1}{.7}{.8}{labcpp}\n"
"\n}\n"

"\\end{document}\n";

const char* hfile = 
"/*\n{HEADER}\n*/\n\n"
"// Include Guard\n#ifndef __{HFILE}\n#define __{HFILE}\n\n"
"// Include Dependencies\n{INCLUDES}\n\n"
"// Function Prototypes\n/* Prototypes */\n\n"
"// Global Extern Variables & Other Foward Declarations\n\n"
"// Close Include Guard\n#endif\n";

const char* cppfile = 
"/*\n{HEADER}\n*/\n\n"
"// Include Dependencies\n{INCLUDES}\n\n"
"// Global Declarations/Definitions\n\n"
"// Function Defintions\n/* Source Code */\n\n\n";


const char* mainfunc = 
"\n// Main Function\nint main(int argc, char* argv[])\n{\n\t/* Source Code */\n\tstd::cout << \"Hello World!\\n\";\n\n\treturn 0;\n}\n\n";


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

int file_count_char(std::string file, char c)
{
    int cnt = 1;

    std::ifstream ifs(file.c_str());

    while( !ifs.eof())
    {
        cnt += (ifs.get() == c);
    }

    ifs.close();

    return cnt;
}
