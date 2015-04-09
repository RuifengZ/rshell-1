#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <cstdlib>

using namespace std;
//this function splits string into separate words and places into a vector
vector<char> splitter(char input[999])
{
    vector <char> words;
    int currcount=0;//counter of current word
    string store;//storage for words that come from inputted string

    //there are a few cases we need to consider
    //Cases include " ", ";", "#" 
    for(int i=0; input[i]!='\0'; i++)
    {
        if(input[i]=='#')
        {
            words.push_back(input[i]);
            words.push_back(';');
            store="";
            break;
        }
        else if(input[i] == ';')
        {
            words.push_back(' ');
            words.push_back(input[i]);
            words.push_back(' ');
        }
        else if(input[i] == ' ')
        {

        }
   
    }
    return words;
}
int main()
{
    string username=getlogin();
    char hostname[999];
    gethostname(hostname, 999);
    string stringinput;
    char resultstring[999];
    char input[999];
    while(1)
    {
        cout << username << "@" << hostname << "$ ";
        getline(cin, stringinput);
        strcpy(input, stringinput.c_str());
        strcpy(resultstring, stringinput.c_str());
        vector<char> words=splitter(input);
        for(int i=0; input!='\0'; i++)
        {        
            cout << words[i];
        }
        /*if(words[i]=="exit" || words[i]=="Exit")
        {
                exit(1);
        }*/
    }       
    return 0;
}




