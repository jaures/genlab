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
"\\documentclass{ffslides}\n"
"\\ffpage{25}{\\numexpr 16/9}\n"
"\\usepackage{fancyvrb}\n"
"\\usepackage[T1]{fontenc}\n"
"\\usepackage{underscore}\n"
"\\usepackage{color}"
"\\usepackage{listings}\n"
"\n\\lstset{\n"
"frame=single,\nkeepspaces=true,\n"
"columns=flexible,\nbreaklines=true,\n"
"breakatwhitespace=true,\nnumbers=left,\n"
"numbersep=5pt,\nnumberstyle=\\tiny\\color{gray},\n"
"keywordstyle=\\color{blue},stringstyle=\\color{red},\n"
"showstringspaces=false,\ncommentstyle=\\color{green}\n}\n\n"
"\\begin{document}\n\n"

"\\normalpage{Specification}\n"
"{\n\t{SPECS}\n\\end{lstlisting}\n}\n\n"

"\\normalpage{Analysis}\n"
"{\\qi{Inputs:\n{INPUTS}\n}\n"
"\\qi{Process:\n\\begin{enumerate}\n{PROCESSES}\n\\end{enumerate}\n}\n"
"\\qi{Outputs:\n{OUTPUTS}\n}\n}\n\n"

"\\normalpage{Design}\n"
"{\\begin{lstlisting}\n{DESG}\n\\end{lstlisting}\n}\n\n"

"\n{IMPLMNT/TESTS}\n"
"\\end{document}\n";


const char* implmntPage = 
"\\normalpage{Implementation: {FILE}}\n"
"{\\begin{lstlisting}\n{DESC}\n\\end{lstlisting}\n}\n\n"
"\\lstinputlisting[language=C++, "
    "firstline={FL}, lastline={LL}]{{FILE}}\n"
"}%%\\putfig{0.1}{0.7}{0.8}{{IMG}}\n\n";


const char* testPage = 
"\\normalpage{Test: {TEST}}\n"
"{\\begin{lstlisting}\n{DESC}\n\\end{lstlisting}\n}\n\n"
"\\fvset{firstline={FL}, lastline={LL}}\n"
"\\lstinputlisting{{TEST}}\n"
"}%%\\putfig{0.1}{0.7}{0.8}{{IMG}}\n\n";


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

    std::cout << "Couting lines for:\n" << file << "|\n";

    std::ifstream ifs(file.c_str());
    
    std::string temp;
    
    char* tmp = new char[256]; 

    getline(std::cin,temp);

    std::cout << "Made It this Far\n\n";

    getline(std::cin,temp);
    while( !ifs.eof())
    {
        ifs.getline(tmp, 256);
        cnt++;
        std::cout << tmp << "\n";
        getline(std::cin, temp);
    }

    getline(std::cin,temp);
    std::cout << "Oh Yeah Got out!\n";

    ifs.close();

    return cnt;
}

