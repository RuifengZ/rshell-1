// RM.CPP
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <iostream>
#include <vector>
#include <string>


#include "rm.h"


bool RM_DIRS = false;



int main(int argc, char** argv) {

    std::vector<const char*> cmdfiles;
    
    for(int i = 1; i < argc; i++)
        if(argv[i][0] == '-') {
            if(argv[i][1] == 'r')
                RM_DIRS = true;
            else {
                std::cout << "Invalid flag: " << argv[i] << std::endl;
                return 1;
            }
        } else
            cmdfiles.push_back(argv[i]);

    if(cmdfiles.empty()) {
        std::cout << "Missing operands; supported flags: -r" << std::endl;
        return 1;
    }

    for(auto f : cmdfiles)
        removedir(f);
}



int removedir(const char* path) {

    // check if is file; if so, remove immediately
    std::vector<std::string> dirfiles;
    int scan_status = scandir(path, dirfiles);
    if(scan_status == -1) { 
        std::cout << "Error reading directory " << path << std::endl; 
        return 1;
    } else if(scan_status == 1) {
        if(unlink(path) != 0) { perror("unlink 1"); return 1; }
        return 0;
    }

    // iterate over all found files
    for(auto f : dirfiles) {

        struct stat filestat;
        std::string fullpath = std::string(path) + "/" + f;
        const char* fullpath_cstr = fullpath.c_str();
        if(stat(fullpath_cstr, &filestat) == -1) { perror("stat"); return 1; }

        // extract filename from full path
        std::string filename(fullpath);
        filename = filename.substr(filename.find_last_of("/\\") + 1);

        if(RM_DIRS && S_ISDIR(filestat.st_mode)) {
            if(filename != "." && filename != "..")
                return removedir(fullpath_cstr);
            else continue;
        }

        if(unlink(fullpath.c_str()) != 0) { perror("unlink 2"); return 1; }
    }

    // tail recursion; delete current dir
    if(rmdir(path) != 0) { perror("rmdir"); return 1; }

    return 0;
}



// yanked from previous project
// scan a directory for all contained files
// return values: -1 - syscall error; 1 - is a file
int scandir(const char* path, std::vector<std::string> &files) {
   
    struct stat stat_buf;
    if(stat(path, &stat_buf) == -1) { perror("stat"); return 1; }

    if(!S_ISDIR(stat_buf.st_mode))
        return 1;

	DIR* dirp;
    if( (dirp = opendir(path)) == NULL) {
        perror("opendir");
        return -1; 
    }


    struct dirent* entry;
    errno = 0;
    while( (entry = readdir(dirp)) != NULL)
        files.push_back(entry->d_name);
    
    if(errno != 0) {
        perror("readdir");
        return -1;
    }

   if(closedir(dirp) != 0) {
        perror("closedir");
        return -1;
    }

    return 0;
}
