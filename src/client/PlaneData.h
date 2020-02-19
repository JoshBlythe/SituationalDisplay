#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <bits/stdc++.h>

struct PlaneData
{
    std::string hexID;
    double latitude;
    double longitute;
    int groundSpeed;
    int trueHeading;
    int verticalHeading;
    int airborneState;
};

PlaneData StoreData(std::vector<std::string> &info);
PlaneData UpdateData(std::vector<std::string> &info);
PlaneData AddNewData(std::vector<std::string> &info);
//class PlaneData
//{
//public:
//    std::list<PlaneInfo> planeData;
//};
