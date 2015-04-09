#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <cstdlib>

using namespace std;
//this function splits string into separate words and places into an array
char* splitter(char* input)
{
    char * result;//resulting storage array
    int currcount=0;//counter of current word

    //there are a few cases we need to consider
    //Cases include " ", ";", "#" 
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
    string username=getlogin();
    char hostname[999];
    gethostname(hostname, 999);
    string stringinput;
    char resultstring[999];
    char input[999];
    int counter=0;
    while(1)
    {
        cout << username << "@" << hostname << "$ ";
        getline(cin, stringinput);
        strcpy(input, stringinput.c_str());
        strcpy(resultstring, stringinput.c_str());
        char *storage=strtok(input," ");
        if(strcmp(storage,"exit")==0)
                exit(1);
        for(int i=0; input!='\0'; i++)
        {        
            cout << storage[i];
            int pid =fork();
            if(pid==-1)
            {        
                perror("This is an error with fork()");
                exit(1);
            }
            else if(pid==0)
            {
            
            }
            else if(pid==1)
            {
    
            }
            counter++;
        }
        /*if(words[i]=="exit" || words[i]=="Exit")
        {
                exit(1);
        }*/
    }       
    return 0;
}




