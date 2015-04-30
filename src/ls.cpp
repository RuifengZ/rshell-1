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
#include <pwd.h>
#include <grp.h>
#include <iomanip>

using namespace std;

#define GREEN   "\033[32m" //Green color for executables
#define BLUE    "\033[34m" //Blue color for directories
#define GRAY  "\033[47m" //Gray color for hidden files
#define REG   "\033[0m"//regular color
#define HIDDEN  "\033[47m" //hidden files

void color(string files, struct stat name)
{
	//Checking Hidden Directories
	if(files[0]=='.' &&(name.st_mode&S_IFDIR))
	{
		cout << HIDDEN << BLUE;
		cout << files;
		cout << REG;
	}
	//Checking Hidden Executables
	if(files[0]=='.' && (name.st_mode&S_IXUSR))
	{
		cout << HIDDEN << GREEN;
		cout << files;
		cout << REG;
	}
	//Checking Hidden files only
	if(files[0]=='.')
	{
		cout << HIDDEN;
		cout << files;
		cout << REG;
	}
	//Checking Directories
	if(name.st_mode & S_IFDIR)
	{
		cout << BLUE;
		cout << files;
		cout << REG;
	}
	//Checking executables
	{
		if(name.st_mode & S_IXUSR)
		{
			cout << GREEN;
			cout << files;
			cout << REG;
		}	
	}
	//Checking regular files
	cout << files << REG;
}

void total(vector <string> &file, string path)
{
	int total=0;
	for(int i=0; i<file.size(); i++)
	{
		struct stat size;
		string temp=path+'/'+file[i];
		if(stat(temp.c_str(),&size)==-1)
		{
			perror("stat error");
			exit(1);
		}
		total += size.st_blocks/2;
		cout << "total" << total << endl;
	}
}

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
    if(!pw)
    {
        perror("Failed to get pwuid");
        exit(1);
    }
    struct group* gp=getgrgid(name.st_gid);
    if(!gp)
    {
        perror("Failed to get grgid");
    }
    cout << pw->pw_name << ' ';
    cout << gp->gr_name << ' ';
	cout << setw(5) << right;
	cout << name.st_size << ' ';
	//time last modified
	char buff[80];
	struct tm* time=localtime(&name.st_mtime);	
	if(!strftime(buff,80,"%b %d %H: %M",time))
	{
		perror("strftime function error");	
		exit(1);
	}
	cout << buff << ' ';
	
	
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
