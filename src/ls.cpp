#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cassert>
using namespace std;

#define GREEN   "\033[32m" //Green color for executables
#define BLUE    "\033[34m" //Blue color for directories
#define GRAY  "\033[47m" //Gray color for hidden files

void lprint(struct stat name)
{
    if(S_ISDIR(name.st_mode))
        cout << 'd';
    else
    {
        if(S_ISLNK(name.st_mode))
            cout << 'l';
        else
            cout << '-';
    }
    if(name.st_mode & S_IRUSR)
        cout << 'r';
    else
        cout << '-';
    if(name.st_mode & S_IWUSR)
        cout << 'w';
    else
        cout << '-';
    if(name.st_mode & S_IXUSR)
        cout << 'x';
    else
        cout << '-';
    if(name.st_mode & S_IRGRP)
        cout << 'r';
    else
        cout << '-';
    if(name.st_mode & S_IWGRP)
        cout << 'w';
    else
        cout << '-';
    if(name.st_mode & S_IXGRP)
        cout << 'x';
    else
        cout << '-';
    if(name.st_mode & S_IROTH)
        cout << 'r';
    else 
        cout << '-';
    if(name.st_mode & S_IWOTH)
        cout << 'w';
    else
        cout << '-';
    if(name.st_mode & S_IXOTH)
        cout << 'x';
    else
        cout << '-';
    cout << ' ' << name.st_nlink << ' ';
    struct passwd* pw=getpwuid(name.st_uid);
    struct group* gp=getgrgid(name.st_gid);
    if(!pw)
    {
        perror("Failed to get pwuid");
        exit(1);
    }
    if(!gp)
    {
        perror("Failed to get grgid");
    }
    cout << pw->pw_name << ' ';
    cout << gp->gr_name << ' ';
}

int main(int argc, char* argv[])
{
    bool checkflag=true;//checks for flags and files
    bool a=false;//to see if ls contains -a or not
    bool l=false;//to see if ls contains -l or not
    bool R=false;//to see if ls contains -R or not
    vector <string> in;
    vector <string> dir;
    //checking for flags
    for(int i=1; i<argc; i++)
    {
        if(checkflag)
        {
            if(argv[i][0]=='-')
            {    
                for(int j=1; argv[i][j]!=0; j++)
                {
                    if(argv[i][j]=='R')
                        R=true;
                    else if(argv[i][j]=='l')
                        l=true;
                    else if(argv[i][j]='a')
                        a=true;
                    else
                    {
                        cerr << "Invalid flag!" << argv[i][j] << endl;
                        exit(1);
                    }
                }
            }
        }
        else
        {
            in.push_back(argv[i]);
        }
    }
    //checking for files now
    for(int i=0; i<in.size(); i++)
    {
        struct stat file;
        if(stat(in.at(i).c_str(),&file)==-1)
        {
            perror("stat");
            exit(1);
        }
        if(!(file.st_mode & S_IFDIR))
        {
        
        }
    }
    return 0;
}
