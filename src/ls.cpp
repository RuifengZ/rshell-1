#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    bool checkflag=true;//checks for flags and files
    bool a=false;
    bool l=false;
    bool R=false;
    vector <string> in;
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
        struct stat file;
        if(stat(in.c_str(),&file)==-1)
        {
            perror("stat");
            exit(1);
        }
    }
    return 0;
}
