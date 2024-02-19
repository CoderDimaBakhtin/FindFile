

#ifndef FINDFILE_H
#define FINDFILE_H



#include <string>
#include <iostream>
#include <filesystem>
#include <thread>
#include <atomic>
#include<vector>



using namespace std;
using namespace std::literals;





void get_files(string& file_to_find, const string& current_path);

void working_thread(string& file_to_find, const string& current_path);

void search(string& file_to_find, const string& current_path);


#endif


