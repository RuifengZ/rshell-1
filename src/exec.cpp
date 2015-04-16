#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <sys/wait.h>

using namespace std;
//this function splits string into separate words and places into an array
char* splitter(char* input)
{
    char * result;//resulting storage array
    int currcount=0;//counter of current word

    //there are a few cases we need to consider
    //cases include " ", ";", "#" 
    for(int i=0; input[i]!='\0'; i++)
    {
        if(input[i]=='#')
        {
            break;
        }
        else if(input[i] == ';')
        {
        }
        else if(input[i] == ' ')
        {

        }
   
    }
    return result;
}
int main()
{
    bool semicolon=0;
    bool doubleand=0;
    bool doubleor=0;
    string username=getlogin();
    char hostname[999];
    gethostname(hostname, 999);
    string stringinput;
    while(1)
    {
        //if the user name and hostname both exists, then the program displays it before the dollar sign.
        if(getlogin() != '\0' && gethostname(hostname,999) != -1)    
            cout << username << "@" << hostname << "$ ";
        else{
                perror("your hostname or username couldn't be found!");
                cout << "$ ";
        }
        //takes in a string input
        getline(cin, stringinput);
        //this checks for exit and Exit command 
        if(stringinput.find("exit")==0||stringinput.find("Exit")==0)
                exit(1);
       //this checks for comments. Basically, everything after the hash symbol is useless
       if(stringinput.find("#") != string::npos)
       {
           stringinput=stringinput.substr(0,stringinput.find("#"));
       }
        for(int i=0; i<stringinput.size(); i++)
        {        
            int status=0;
            pid_t pid = fork();
            if(pid==-1)
            {        
                perror("this is an error with fork()");
                exit(1);
            }
            else if(pid==0)
            {
                int good=execvp(input[0],input);
                if(good==-1)
                {
                        perror("Command is bad and not good!");
                        exit(1);
                }
                else{
                        cout << "Good!" << execvp(input[0],input) << endl;
                }
            }
            else if(pid>=1)
            {
                if(waitpid(-1,&status,0)==-1)
                {
                        perror("Please take care of your child!");
                        exit(1);
                }
                if(input[i]=="&&")
                {
                        if(status>0)
                                break;
                }
                if(input[i]=="||")
                        if(status<=0)
                                break;

            }
        }
        /*if(words[i]=="exit" || words[i]=="exit")
        {
                exit(1);
        }*/
    }       
    return 0;
}




