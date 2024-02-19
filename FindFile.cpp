
#include "FindFile.h"
#include"Semaphore.h"


Semaphore semaphore(8);
std::atomic<bool> exit_thread_flag{ false };


void get_files(string& file_to_find, const string& current_path) {
    if (!exit_thread_flag) {
        try {
            for (filesystem::directory_iterator file_it(current_path); file_it != std::filesystem::end(file_it); ++file_it) {
                
                try {
                    if (filesystem::is_directory(*file_it)) {
                        get_files(file_to_find, (*file_it).path().string());
                    }
                    else {
                        filesystem::path p((*file_it).path().string());

                        if (p.filename() == file_to_find) {

                            cout << "\n\n" << (*file_it).path().string() << "\n\n" << std::endl;
                            exit_thread_flag = true;
                        }
                    }
                }
                catch (const std::exception& ex) {
                    //std::cout << "Exception: " << ex.what() << '\n';
                }

            }
        }
        catch (const std::exception& ex) {
            //std::cout << "Exception: " << ex.what() << '\n';
        }

    }
}


void working_thread(string& file_to_find, const string& current_path) {
   
    semaphore.acquire();
    
    get_files(file_to_find, current_path);
    semaphore.release();
}


void search(string& file_to_find, const string& current_path) {

    std::vector<std::thread> threads;
    filesystem::directory_iterator file_it(current_path);

    while (file_it != std::filesystem::end(file_it)) {
        if (!exit_thread_flag) {
            try {
                //std::cout<<(*file_it).path().string()<<std::endl;
                if (filesystem::is_directory(*file_it)) {
                    threads.emplace_back(working_thread, std::ref(file_to_find), (*file_it).path().string());
                }
                else {
                    filesystem::path p((*file_it).path().string());
                    if (p.filename() == file_to_find) {
                        cout << "\n\n" << (*file_it).path().string() << "\n\n" << std::endl;
                        exit_thread_flag = true;
                    }
                }

            }
            catch (const std::exception& ex) {
                //std::cout << "Exception: " << ex.what() << '\n';
            }
            ++file_it;
        }
        else {
            break;
        }

    }

    for (size_t i = 0; i < threads.size(); i++) {
        threads[i].join();
    }
    if (exit_thread_flag == false) {
        std::cout << "\nfile not found" << std::endl;
    }

    exit_thread_flag = false;

}
