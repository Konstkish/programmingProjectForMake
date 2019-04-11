#ifndef STRINGSWITCHER_H
#define STRINGSWITCHER_H
#include<string>
#include<utility>
#include<initializer_list>

namespace stringSwithcer
{

void stringSwitch(std::string &mainInput, std::string replace, std::string replacewhat);


void swtichAll(std::string &mainInput, std::pair<std::string, std::string> passPair);


void emailBodyReplace(std::string &mainInput,std::initializer_list<std::pair<std::string, std::string>> L);

template<typename S, typename T, typename...L>
void variadicReplacer(S &mainInput, T t, L...args);

template<typename S>
void variadicReplacer(S &mainInput);

template<typename S, typename T>
void variadicReplacer(S &mainInput, T t)
{
    swtichAll(mainInput, t);
}

template<typename S, typename T, typename...L>
void variadicReplacer(S &mainInput, T t, L...args)
{
    swtichAll(mainInput, t);
    variadicReplacer(mainInput, args ...);

}
}



#endif // STRINGSWITCHER_H
