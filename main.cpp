


#include "FindFile.h"
#include "Semaphore.h"
#include <string>
#include <iostream>




int main(){
    std::cout << "Enter the name of file:";
    

    std::string file_to_find;
    std::getline(std::cin, file_to_find);

    std::string current_path = "C:\\";


    search(file_to_find, current_path);


    return 0;
}