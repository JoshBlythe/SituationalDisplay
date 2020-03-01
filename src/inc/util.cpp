#include "util.h"

#include <iostream>
#include <sstream>


void SplitStringOnCharacter(std::string s, char splitter, std::vector<std::string> &out, int data)
{
    std::string token;

    if(!out.empty())
    {
        out.clear();
    }

    std::istringstream ss(s);

    while (std::getline(ss, token, splitter))
    {
        out.push_back(token);

        //printf("[%s]\n", token.c_str());
    }

}
