#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <bits/stdc++.h>

struct PlaneData
{
    std::string hexID;
    std::string latitude;
//    double latitude;
    std::string longitute;
//    double longitute;
    std::string groundSpeed;
//    int groundSpeed;
    std::string trueHeading;
//    int trueHeading;
    std::string verticalHeading;
//    int verticalHeading;
    std::string airborneState;
//    int airborneState;
    bool isAircraft;
    int checkAircraft;
};

PlaneData StoreData(std::vector<std::string> &info);
PlaneData UpdateData(std::vector<std::string> &info);
PlaneData AddNewData(std::vector<std::string> &info);
//class PlaneData
//{
//public:
//    std::list<PlaneInfo> planeData;
//};
