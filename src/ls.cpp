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
#include <errno.h>
#include <dirent.h>
#include <vector>


using namespace std;

#define GREEN   "\033[32m" //Green color for executables
#define BLUE    "\033[34m" //Blue color for directories
#define REG   "\033[0m"//regular color
#define HIDDEN  "\033[47m" //hidden files

struct stat stats;
DIR *directory;
struct dirent *dir;
bool alphabetical(string a, string b)
{
	for(unsigned i=0; i<a.size(); i++)
		a[i]=tolower(a[i]);
	for(unsigned i=0; i<b.size(); i++)
		b[i]=tolower(b[i]);
		return a<b;
}
void color(string files, struct stat name)
{
	//Checking Hidden Directories
	if(files.find(".") == 0  &&(name.st_mode&S_IFDIR))
	{
		cout << HIDDEN << BLUE;
		cout << files << "  ";
		cout << REG;
	}
	//Checking Hidden Executables
	else if(files.find(".") == 0 && (name.st_mode&S_IXUSR))
	{
		cout << HIDDEN << GREEN;
		cout << files << "  ";
		cout << REG;
	}
	//Checking Hidden files only
	else if(files.find(".") == 0)
	{
		cout << HIDDEN;
		cout << files << "  ";
		cout << REG;
	}
	//Checking Directories
	else if((name.st_mode & S_IFMT) == S_IFDIR)
	{
		cout << BLUE;
		cout << files << "  ";
		cout << REG;
	}
	//Checking executables
	else if(name.st_mode & S_IXUSR)
	{
		cout << GREEN;
		cout << files << "  ";
		cout << REG;
	}	
	//Checking regular files
	else cout << files << REG << "  " ;
}


void printvector(vector<string> v, string path)
{
	for (unsigned int i = 0; i < v.size(); i++)
	{
		string tmp = path + "/" + v.at(i);
		if (-1 == stat(tmp.c_str(), &stats))
		{
			perror("stat 1");
			exit(1);
		}
		color(v.at(i), stats);
	}
}

bool checkdir(string s)
{
	if (-1 == stat(s.c_str(), &stats))
	{	
		perror("stat");
		exit(1);
	}
	else
	{
		if ((stats.st_mode & S_IFMT) == S_IFREG)
		{
			cout<< s << endl;
			return true;
		}
	}
	return false;
}

bool checkdirnoprint(string s)
{
	if (-1 == stat(s.c_str(), &stats))
	{	
		perror("stat");
		exit(1);
	}
	else
	{
		if ((stats.st_mode & S_IFMT) == S_IFREG)
		{
			return true;
		}
	}
	return false;
}


void printls(string s)
{
	bool isdir = false;
	isdir = checkdir(s);
	if (isdir)
		return;
	vector<string> fag;
	if (NULL == (directory = opendir(s.c_str())))
	{
		perror("opendir :)");
		exit(1);
	}
	errno = 0;
	while (NULL != (dir = readdir(directory)))
	{
		string caa = dir->d_name;
		if (caa.find(".") != 0)
			fag.push_back(caa);

	}
	if(errno==-1)
	{
		perror("while readdir");
		exit(1);
    }
	sort(fag.begin(), fag.end());
	printvector(fag, s);
	cout << endl;

}

void printals(string s)
{
	bool isdir = false;
	isdir = checkdir(s);
	if (isdir)
		return;
	vector<string> fag;
	if (NULL == (directory = opendir(s.c_str())))
	{
		perror("hi :)");
		exit(1);
	}
	errno = 0;
	while (NULL != (dir = readdir(directory)))
	{
		string caa = dir->d_name;
		fag.push_back(caa);

	}
    if(errno==-1)
	{
		perror("while readdir");
		exit(1);
	}
	sort(fag.begin(), fag.end());
	printvector(fag, s);
	cout << endl;
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
		exit(1);
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

void printlls(string s)
{
	bool isdir = false;
	isdir = checkdir(s);
	if (isdir)
		return;
	vector<string> fag;
	if (NULL == (directory = opendir(s.c_str())))
	{
		perror("hi :)");
		exit(1);
	}
	errno = 0;
	int totalblocks=0;
	while (NULL != (dir = readdir(directory)))
	{
		string tmp1 = s + "/" + dir->d_name;
		if (tmp1.find("./") == 0)
			tmp1.erase(0,2);
		if (0  != stat(tmp1.c_str(), &stats))
		{	
			perror("printlls error ");//error is here
			exit(1);
		}
		string tmp = dir->d_name;
		if (tmp.find(".") != 0)
		{
			lprint(stats);
			totalblocks+=stats.st_blocks;
			cout << " ";
			color(tmp,stats);
			cout << endl;
		}
	}
	if(errno==-1)
	{
		perror("while readdir");
		exit(1);
	}
	cout << "Total " << totalblocks/2 << endl;


}

void printlals(string s)
{
	bool isdir = false;
	isdir = checkdir(s);
	if (isdir)
		return;
	vector<string> fag;
	if (NULL == (directory = opendir(s.c_str())))
	{
		perror("hi :)");
		exit(1);
	}
	errno = 0;
	int total=0;
	while (NULL != (dir = readdir(directory)))
	{
		string tmp = s + "/" + dir->d_name;
		if (tmp.find("./") == 0)
			tmp.erase(0,2);
		if (-1 == stat(tmp.c_str(), &stats))
		{	
			perror("stat");
			exit(1);
		}
		lprint(stats);
		cout << " ";
		color(dir->d_name, stats);
		cout << endl;
		total=total+stats.st_blocks;
	}
	if(errno==-1)
	{
		perror("while readdir");
		exit(1);
	}
	cout << "Total " << total/2 << endl;
}






void printrls(string s)
{
	cout << s << ":" << endl;
	printls(s);
	

	bool isdir = false;
	isdir = checkdir(s);
	if (isdir)
		return;
	if (NULL == (directory = opendir(s.c_str())))
	{
		perror("hi" ) ;
		exit(1);
	}
	errno=0;
	while (NULL != (dir = readdir(directory)))
	{
		string caa = dir->d_name;
		if (caa.find(".") != 0)
		{
			if (not checkdirnoprint(s + "/" + caa)) //if not not dir or if it is a dir
			{
				printrls(s + "/" + caa);
			}
		}
	}
	if(errno==-1)
	{
		perror("while readdir");
		exit(1);
	}
			
}


void printrals(string s)
{
	cout << s << ":" << endl;
	printals(s);
	

bool isdir = false;
	isdir = checkdir(s);
	if (isdir)
		return;
	if (NULL == (directory = opendir(s.c_str())))
	{
		perror("hi" ) ;
		exit(1);
	}
	errno=0;
	while (NULL != (dir = readdir(directory)))
	{
		string caa = dir->d_name;
		if (caa != "." && caa != ".." )
		{
			if (not checkdirnoprint(s + "/" + caa)) //if not not dir or if it is a dir
			{
				printrals(s + "/" + caa);
			}
		}
	}
	if(errno==-1)
	{
		perror("while readdir");
		exit(1);
	}
			
}
void printralls(string s)
{
	cout << s << ":" << endl;
	printlals(s);
	

bool isdir = false;
	isdir = checkdir(s);
	if (isdir)
		return;
	if (NULL == (directory = opendir(s.c_str())))
	{
		perror("hi" ) ;
		exit(1);
	}
	int total=0;
	while (NULL != (dir = readdir(directory)))
	{
		string caa = dir->d_name;
		if (caa != "." && caa != ".." )
		{
			if (not checkdirnoprint(s + "/" + caa)) //if not not dir or if it is a dir
			{
				printralls(s + "/" + caa);
			}
		}
		total=total+stats.st_blocks;

	}
}


void printrlls(string s)
{
	cout << s << ":" << endl;
	printlls(s);
	

	/*bool isdir = false;
	*isdir = checkdir(s);
	*if (isdir)
	*	return;
	*vector<string> fag;
	*if (NULL == (directory = opendir(s.c_str())))
	*	perror("hi :)");
	*errno = 0;
	*while (NULL != (dir = readdir(directory)))
	*{
	*	string caa = dir->d_name;
	*	if (caa.find(".") != 0)
	*		fag.push_back(caa);
	*
	*}
    *sort(fag.begin(), fag.end());
	*printvector(fag);
	*cout << endl;
	*
	*printrls();
	*/
	bool isdir = false;
	isdir = checkdir(s);
	if (isdir)
		return;
	if (NULL == (directory = opendir(s.c_str())))
	{
		perror("hi" ) ;
		exit(1);
	}
	errno=0;
	while (NULL != (dir = readdir(directory)))
	{
		string caa = dir->d_name;
		if (caa.find(".") != 0)
		{
			if (not checkdirnoprint(s + "/" + caa)) //if not not dir or if it is a dir
			{
				printrlls(s + "/" + caa);
			}
		}
	}
	if(errno==-1)
	{
		perror("readdir while");
		exit(1);
	}
}




int main(int argc, char* argv[])
{
    bool a=false;//to see if ls contains -a or not
    bool l=false;//to see if ls contains -l or not
    bool R=false;//to see if ls contains -R or not
    vector <string> in;
    //checking for flags
    for(int i=1; i<argc; i++)
	{
            if(argv[i][0]=='-')
                for(int j=1; argv[i][j]!=0; j++)
                {
                    if(argv[i][j]=='R')
                        R=true;
                    else if(argv[i][j]=='l')
                        l=true;
                    else if(argv[i][j]=='a')
                        a=true;
                    else
                    {
                        cerr << "Invalid flag!  " << argv[i][j] << endl;
                        exit(1);
                    }
                }
	    else
	    {
            in.push_back(argv[i]);
		}
    }
    //checking for files now
   /* for(unsigned int i=0; i<in.size(); i++)
    {
        struct stat file;
        if(stat(in.at(i).c_str(),&file)==-1)
        {
            perror("stat");
            exit(1);
        }
        if(!(file.st_mode & S_IFDIR))
        {
        	color(in[0],file);
			cout << endl;
        }
    } */
	sort(in.begin(),in.end());
	if (!a && !R && !l)//ls
	{
	if (in.size() != 0)
		for (unsigned int i = 0; i < in.size(); i++)
		
		{
			printls(in.at(i));
		}
	else	if (in.size() == 0)
	{
			printls(".");
		}
	}
	if (a and !R and !l)//ls -a
	{
		for (unsigned int i = 0; i < in.size(); i++)
		{
			printals(in.at(i));
		}
		if (in.size() == 0)
			printals(".");
	}
	if (!a and !R and l)//ls -l
	{
		sort(in.begin(), in.end());
		for (unsigned int i = 0; i < in.size(); i++)
		{
			
			printlls(in.at(i));
		}
		if (in.size() == 0)
			printlls(".");
	}
	if (a and !R and l)//ls -la
	{
		sort(in.begin(), in.end());
		for (unsigned int i = 0; i < in.size(); i++)
		{
			printlals(in.at(i));
		}
		if (in.size() == 0)
			printlals(".");
	}
	if (not a and R and not l)//ls -R
	{
		for (unsigned int i = 0; i < in.size(); i++)
		{
			
			printrls(in.at(i));
		}
		if (in.size() == 0)
			printrls(".");
	}
	if (a and R and not l)//ls -aR

		{
		for (unsigned int i = 0; i < in.size(); i++)
		{
			
			printrals(in.at(i));
		}
		if (in.size() == 0)
			printrals(".");
	}

	if (a and R and l)//ls -alR

		{
		for (unsigned int i = 0; i < in.size(); i++)
		{
			
			printralls(in.at(i));
		}
		if (in.size() == 0)
			printralls(".");
	}
	if (not a and R and l)//ls -lR

		{
		for (unsigned int i = 0; i < in.size(); i++)
		{
			
			printrlls(in.at(i));
		}
		if (in.size() == 0)
			printrlls(".");
	}


    return 0;
}
