#include "util.h"

#include "iostream"
#include "sstream"

void SplitStringOnCharacter(std::string s, char splitter, std::vector<std::string> &out, int data)
{
//    int i = 0;
//    size_t curr;
//    char ch = 0;
    std::string token;

    //TODO:
    //check if there is anything in string already if clear it and create a new string.
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

   // out = "";

//    for (curr = 0; curr < s.length(); curr++)
//    {
//        ch = s.at(curr);

//        //std::cout<<ch << std::endl;

//        if(ch == splitter)
//        {
//            if(i != data)
//            {
//                i++;
//                //std::cout << i << std::endl;
//            }


//        }

//        if(i == 4)
//        {
//            if (ch != splitter)
//            {
//                //push character into string.
//                token += ch;
//            }

//            out.push_back(token);
//        }

//     }


}
