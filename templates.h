#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

extern const int MAXBUFF;

extern const char* help;

extern const char* header;

extern const char* genfile;

extern const char* makefile;

extern const char* docfile;

extern const char* implmntPage;

extern const char* testPage;

extern const char* hfile;

extern const char* cppfile;

extern const char* mainfunc;

extern const char* buildCMD[];

extern const char* testfile;

std::string str_replace(std::string, std::string, std::string);

int file_count_char(std::string, char);
