#include "stringswitcher.h"
#include <iostream>



void stringSwithcer::stringSwitch(std::string &mainInput, std::string replace, std::string replacewhat)
{

   int pos = mainInput.find(replacewhat);

   std::string temp = mainInput.substr(0, pos);
   std::string temp2 = mainInput.substr(pos + replacewhat.size());

   temp.append(replace);

   mainInput = temp;
   mainInput += temp2;

}

void stringSwithcer::swtichAll(std::string &mainInput, std::pair<std::string, std::string> passPair)
{
    int loops = 0;
    int pos = mainInput.find(passPair.first, 0);
    while(pos != std::string::npos)
    {
        pos = mainInput.find(passPair.first, pos+1);
        loops++;
    }

    for(int i = 0; i < loops; i++)
    {
        stringSwitch(mainInput, passPair.second, passPair.first);
    }

}

void stringSwithcer::emailBodyReplace(std::string &mainInput, std::initializer_list<std::pair<std::string, std::string>> L)
{
    for(auto a : L)
        swtichAll(mainInput, a);

}

