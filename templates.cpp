#include "templates.h"

// Maximum Buffer Size
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
  
const char* makefile =
"# {PROJECT} Makefile\n"
"PRJCT={PROJECT}\n\n"

"# Include Directory\n"
"IDIR:=include/\n\n"

"# Other Include Directories\n"
"OIDIR:={OIDIRS}\n\n"

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
"\n\t$(CXX) $(SRCS) $(OFLAGS) $(OIDIR) $(CXXFLAGS) -o $@\n\n\n"

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
// Import Packages
"\\documentclass{ffslides}\n"
"\\ffpage{25}{\\numexpr 16/9}\n"
"\\usepackage{fancyvrb}\n"
"\\usepackage{enumitem}\n"
"\\usepackage[T1]{fontenc}\n"
"\\usepackage{underscore}\n"
"\\usepackage{color}\n"
"\\usepackage{listings}\n\n"

// Add Implementation Page Command
"\\newcommand{\\implpage}[5]\n{%\n\t"
"\\normalpage{Implementation of #1}\n\t{%\n\t\t"
"#3\n\t\t"
"\\lstinputlisting[language=C++, firstnumber=#4, firstline=#4, "
"lastline=#5]\n\t\t{#2}\n\t}\n}\n\n"

// Add Test Page Command
"\\newcommand{\\testpage}[4]\n{%\n\t"
"\\normalpage{Test: #1}\n\t{%\n\t\t"
"\\ctext{0}{0}{0.24}\n\t\t{%\n\t\t\t"
"#2\\\\\\\\%\n\t\t\tTest:\n\t\t\t"
"\\lstinputlisting[language=C++, firstnumber=#3, firstline=#3, "
"lastline=#4]\n\t\t\t{../bin/test/#1.test}\n\t\t}\n\t\t"
"\\putfig{0.26}{0}{0.68}{#1}\n\t}\n}\n\n"

// Begin the Document
"\\begin{document}\n\n"

// Set Listings Style
"\\lstset{\n\t"
"frame=single,\n\tkeepspaces=true,\n\t"
"columns=flexible,\n\tbreaklines=true,\n\t"
"breakatwhitespace=true,\n\tnumbers=left,\n\t"
"numbersep=5pt,\n\tnumberstyle=\\tiny\\color{gray},\n\t"
"keywordstyle=\\color{blue},\n\tstringstyle=\\color{red},\n\t"
"showstringspaces=false,\n\tcommentstyle=\\color{green}\n}\n\n"

// Specification Page
"\\normalpage{Specification}\n"
"{%Description of the Expected Functionality\n{SPECS}\n}\n\n"

// Analysis Page
"\\normalpage{Analysis}\n{%Input, Outputs, and Processes\n\t"
"\\qi[\\textsc{\\textbf{Inputs:}}]{ \\\\\n{INPUTS}\t}\n\n\t"
"\\qi[\\textsc{\\textbf{Process:}}]{\n\t\\begin{enumerate}[nolistsep]\n"
"{PROCESSES}\t\\end{enumerate}\n\t}\n\n\t"
"\\qi[\\textsc{\\textbf{Outputs:}}]{ \\\\\n{OUTPUTS}\t}\n}\n\n"

// Design Page
"\\normalpage{Design}\n{\n\t"
"\\begin{description}[nolistsep]\n{DESG}\t\\end{description}\n}\n\n"

// Implementation and Test Pages Insert
"{IMPL}\n\n{TESTS}\n\n"

"\\end{document}\n";


// Implementation Page
const char* implmntPage = 
"\\implpage{{FN}}{{FFN}}{{DESC}}{{FL}}{{LL}}\n\n";


const char* testPage = 
"\\testpage{{TN}}{{DESC}}{{FL}}{{LL}}\n\n";


const char* hfile = 
"/*\n{HEADER}\n*/\n\n"
"// Include Guard\n#ifndef __{HFILE}\n#define __{HFILE}\n\n"
"// Include Dependencies{INCLUDES}\n"
"// Function Prototypes\n/* Prototypes */\n\n"
"// Global Extern Variables & Other Foward Declarations\n\n"
"// Close Include Guard\n#endif";


const char* cppfile = 
"/*\n{HEADER}\n*/\n\n"
"// Include Dependencies{INCLUDES}\n"
"// Global Declarations/Definitions\n\n"
"// Function Defintions\n/* Source Code */";


const char* mainfunc = 
"// Main Function\nint main(int argc, char* argv[])\n{\n\t/* Source Code */\n\tstd::cout << \"Hello World!\\n\";\n\n\treturn 0;\n}";


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


// Return a string with original substrings swapped for their
//  replacement
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


// Count the number of charactrs in a file
int file_count_char(std::string file, char c = '\n')
{
    int cnt = 1;

    std::ifstream ifs(file.c_str());
    
    char* buff = new char[MAXBUFF];

    while( !ifs.eof())
    {
        ifs.getline(buff, MAXBUFF);
        cnt++;
    }

    std::cout << "Oh Yeah Got out!\n";

    ifs.close();

    return cnt;
}

