#include "PlaneManager.h"
#include "inc/util.h"

//#include <sstream>
#include <stdlib.h>

#define SERVER_HOST "localhost"
#define SERVER_PORT 30003
#define RECV_BUFFER 4096

#define SEND_DATA 8080


PlaneManager::PlaneManager()
{
    client = WsTcpSocketConnect("localhost", 30003);
    buffer = vector_new(unsigned char);

//    value = 0;

    if(!client)
    {
        _WsPanic("Failed to connect to Port 30003, Is Dump1090 running?");
    }

}

PlaneManager::~PlaneManager()
{
    //clean up
    WsTcpSocketClose(client);
    vector_delete(buffer);

}

void PlaneManager::StateProcessPacket()
{
    //create a vector which will be used to store the data stream values
    std::vector<std::string> token;

    //output message read in.
    //printf("[%s]\n", packet.c_str());
    //call function to split the data stream via a identified character
    SplitStringOnCharacter(packet,',', token, 4);

    //check if vector is empty
    if(planes.empty())
    {
//        if is store the first plane
        StoreData(token);


//    used for testing of removed aircraft as aircraft wasnt able to be obtained
//    PlaneData aircraft;
//    aircraft.hexID = "9999";
//    aircraft.checkAircraft = 0;
//    aircraft.isAircraft = true;
//    aircraft.verticalHeading = "9999";
//    aircraft.groundSpeed = "9999";
//    aircraft.trueHeading = "9999";
//    aircraft.latitude = "50.7192";
//    aircraft.longitute = "-1.8808";

//    planes.push_back(aircraft);

    }

    //could optimse this more, check the hex id here instead of going into the function to do it.
    //takes in a reference to the vector which has the extracted aircraft data stored within.
    AddNewData(token);
    //call update function
    UpdateData(token);
    RemoveData();

//    testing the aircraft data was being stored
//    for (size_t i = 0; i < planes.size(); i++)
//    {
//        std::cout << planes.at(i).hexID << std::endl;
//        std::cout << planes.at(i).checkAircraft << std::endl;
//        std::cout << planes.at(i).isAircraft << std::endl;
//    }

    //if not had data from plane in X amount of messages remove from vector.

}

void PlaneManager::StoreData(std::vector<std::string> &info)
{
    //create a instance of the plane object
    PlaneData plane;

    //set the plane object values, from the obtained data stream
    plane.hexID = info.at(4);
    plane.verticalHeading = info.at(11).c_str();
    plane.groundSpeed = info.at(12).c_str();
    plane.trueHeading = info.at(13).c_str();
    plane.latitude = info.at(14).c_str();
    plane.longitute = info.at(15).c_str();

    //push back plane object into vector
    planes.push_back(plane);
}

void PlaneManager::AddNewData(std::vector<std::string> &info)
{
    for (size_t i = 0; i < planes.size(); i++)
    {
        if(planes.at(i).hexID == info.at(4))
        {
            //Continue
            return;
        }
    }

    //create object
    PlaneData plane;

    //store the data
    plane.hexID = info.at(4);
    plane.verticalHeading = info.at(11).c_str();
    plane.groundSpeed = info.at(12).c_str();
    plane.trueHeading = info.at(13).c_str();
    plane.latitude = info.at(14).c_str();
    plane.longitute = info.at(15).c_str();
    plane.isAircraft = true;

    //push back the data into vector
    planes.push_back(plane);
    //TODO:
    // if 21 = "" then continue else update it.
    //std::atoi(info.at(13).c_str());
    //plane.airborneState = std::atoi(info.at(21).c_str());


}

void PlaneManager::UpdateData(std::vector<std::string> &info)
{
    //loop through the stored planes
    for (size_t i = 0; i < planes.size(); i++)
    {
        //check if current aircraft hexID matches a stored aircraft.
        if(info.at(4) == planes.at(i).hexID)
        {
            planes.at(i).checkAircraft = 0;
            planes.at(i).isAircraft = true;

            if(info.at(1) == "2")
            {
                //planes.at(i).verticalHeading = std::atoi(info.at(11).c_str());
                planes.at(i).verticalHeading = info.at(11).c_str();
                planes.at(i).groundSpeed = info.at(12).c_str();
                planes.at(i).trueHeading = info.at(13).c_str();
                planes.at(i).latitude = info.at(14).c_str();
                planes.at(i).longitute = info.at(15).c_str();
                planes.at(i).airborneState = info.at(21).c_str();
                //test if putting a early return in each increase speed?
//                return;
            }

            if(info.at(1) == "3")
            {
                planes.at(i).verticalHeading = info.at(11).c_str();
                planes.at(i).latitude = info.at(14).c_str();
                planes.at(i).longitute = info.at(15).c_str();
                planes.at(i).airborneState = info.at(21).c_str();
//                return;
            }

            if(info.at(1) == "4")
            {
                planes.at(i).groundSpeed = info.at(12).c_str();
                planes.at(i).trueHeading = info.at(13).c_str();
//                return;
            }

            if(info.at(1) == "5")
            {
                planes.at(i).verticalHeading = info.at(11).c_str();
//                planes.at(i).airborneState = info.at(20).c_str();
//                return;
            }

            if(info.at(1) == "6")
            {
//                planes.at(i).verticalHeading = info.at(11).c_str();
//                planes.at(i).airborneState = info.at(20).c_str();
//                return;
            }

            if(info.at(1) == "7")
            {
                planes.at(i).verticalHeading = info.at(11).c_str();
//                planes.at(i).airborneState = info.at(20).c_str();
//                return;
            }

            if(info.at(1) == "8")
            {
//                planes.at(i).airborneState = info.at(20).c_str();
//                return;
            }

            //testing early return to check if aircraft still there?
            return;
        }
    }


    //            for (size_t i = 0; i < info.size(); i++)
    //            {
    //                //std::cout << token.at(i) << std::endl;
    //                printf("[%s]\n", info.at(i).c_str());
    //            }


}

void PlaneManager::RemoveData()
{
//    size_t cur = 0;
    if(!planes.empty())
    {
        for (size_t cur = 0; cur < planes.size(); cur++)
        {
            if(planes.at(cur).checkAircraft == 30 &&
                    planes.at(cur).checkAircraft < 60)
            {
                planes.at(cur).isAircraft = false;
            }
            else if (planes.at(cur).checkAircraft >= 60)
            {
                planes.erase(planes.begin() + cur);
                return;
            }


            if(planes.at(cur).latitude == planes.at(cur).latitude &&
                    planes.at(cur).longitute == planes.at(cur).longitute)
            {
                planes.at(cur).checkAircraft++;
                return;
            }
            else if (planes.at(cur).airborneState == planes.at(cur).airborneState ||
                    planes.at(cur).airborneState == "")
            {
                planes.at(cur).checkAircraft++;
                return;
            }
            else if (planes.at(cur).trueHeading == planes.at(cur).trueHeading ||
                     planes.at(cur).trueHeading == "")
            {
                planes.at(cur).checkAircraft++;
                return;
            }
            else if (planes.at(cur).groundSpeed == planes.at(cur).groundSpeed ||
                     planes.at(cur).groundSpeed == "")
            {
                planes.at(cur).checkAircraft++;
                return;
            }

            std::cout << planes.at(cur).checkAircraft << std::endl;

        }

    }
}

std::string PlaneManager::convertData(size_t c)
{
    //TODO: if the message are no longer being received then remove them from list, similar to reading in the data in link above

    std::string prepToSend;
    Json::Value root;
//    Json::Value data;

    //removed passing the aircraft vector into function.
    root["Hexideimal"] = planes.at(c).hexID;
    root["lat"] = planes.at(c).latitude;
    root["long"] = planes.at(c).longitute;
    root["altitude"] = planes.at(c).verticalHeading;
    root["speed"] = planes.at(c).groundSpeed;
    root["heading"] = planes.at(c).trueHeading;
    root["aircraftFound"] = planes.at(c).isAircraft;
    root["recAircraft"] = planes.at(c).checkAircraft;


    //root["data"] = data;

    prepToSend = root.toStyledString();

    std::cout << prepToSend << std::endl;

    return prepToSend;
}


void PlaneManager::StateProcessNetwork()
{
    WsTcpSocket *socket = NULL;

    size_t ci = 0;
    char ch = 0;
    size_t lnl = 0;

    socket = client;
    //message = sstream_cstr(packet);

    if(!WsTcpSocketConnected(socket))
    {
        panic("Connection broken");
        printf("Client disconnected\n");
        WsTcpSocketClose(socket);
        client = NULL;
        stream.clear();
        return;
    }

    if(!WsTcpSocketReady(socket))
    {
        return;
    }

    vector_resize(buffer, RECV_BUFFER);
    WsTcpSocketRecv(socket, buffer);


    for (ci = 0; ci < vector_size(buffer); ci++)
    {
        stream.push_back(vector_at(buffer, ci));

    }

    if(stream.size() < 1)
    {
        return;
    }

    packet = "";

    for (ci = 0; ci < stream.size(); ci++)
    {
        ch = stream.at(ci);

        if(ch == '\r')
        {
            //Ignore
        }
        else if (ch == '\n')
        {
            lnl = ci + 1;
            StateProcessPacket();
            packet = "";
        }
        else
        {
            packet += ch;

        }
    }

    if(lnl)
    {
        stream.erase(stream.begin(), stream.begin() + lnl);
    }
}
