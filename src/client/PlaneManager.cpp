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

    value = 0;

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
        //if is store the first plane
        StoreData(token);
    }
    //could optimse this more, check the hex id here instead of going into the function to do it.
    AddNewData(token);
    //call update function
    UpdateData(token);

    //testing
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

    PlaneData plane;

    plane.hexID = info.at(4);
    plane.verticalHeading = info.at(11).c_str();
    plane.groundSpeed = info.at(12).c_str();
    plane.trueHeading = info.at(13).c_str();
    plane.latitude = info.at(14).c_str();
    plane.longitute = info.at(15).c_str();
    plane.isAircraft = true;

    //TODO:
    // if 21 = "" then continue else update it.
    //std::atoi(info.at(13).c_str());
    //plane.airborneState = std::atoi(info.at(21).c_str());


    planes.push_back(plane);

}

void PlaneManager::UpdateData(std::vector<std::string> &info)
{
    for (size_t i = 0; i < planes.size(); i++)
    {
        if(info.at(4) == planes.at(i).hexID)
        {
            value = 0;
            planes.at(i).checkAircraft = value;
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
            }

            if(info.at(1) == "3")
            {
                planes.at(i).verticalHeading = info.at(11).c_str();
                planes.at(i).latitude = info.at(14).c_str();
                planes.at(i).longitute = info.at(15).c_str();
                planes.at(i).airborneState = info.at(21).c_str();
            }

            if(info.at(1) == "4")
            {
                planes.at(i).groundSpeed = info.at(12).c_str();
                planes.at(i).trueHeading = info.at(13).c_str();
            }

            if(info.at(1) == "5")
            {
                planes.at(i).verticalHeading = info.at(11).c_str();
                //planes.at(i).airborneState = std::atoi(info.at(21).c_str());
            }

            if(info.at(1) == "6")
            {
                //planes.at(i).verticalHeading = std::atoi(info.at(11).c_str());
                //planes.at(i).airborneState = std::atoi(info.at(21).c_str());
            }

            if(info.at(1) == "7")
            {
                planes.at(i).verticalHeading = info.at(11).c_str();
                //planes.at(i).airborneState = std::atoi(info.at(21).c_str());
            }

            if(info.at(1) == "8")
            {
                //planes.at(i).airborneState = std::atoi(info.at(21).c_str());
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

    RemoveData();

}

void PlaneManager::RemoveData()
{
    for (size_t i = 0; i < planes.size(); i++)
    {
        if(planes.at(i).checkAircraft == 10)
        {
            planes.at(i).isAircraft = false;
            return;
        }
        else if (planes.at(i).checkAircraft >= 15)
        {
            planes.erase(planes.begin() + i);
            return;
        }

        if(planes.at(i).latitude == planes.at(i).latitude &&
                planes.at(i).longitute == planes.at(i).longitute)
        {

            value++;
            planes.at(i).checkAircraft = value;
            return;
        }
        if(planes.at(i).verticalHeading == planes.at(i).verticalHeading ||
                planes.at(i).groundSpeed == planes.at(i).groundSpeed ||
                planes.at(i).trueHeading == planes.at(i).trueHeading)
        {
            value++;
            planes.at(i).checkAircraft = value;
            return;
        }
    }

//    if(planes.at(idx).latitude == planes.at(idx).latitude &&
//            planes.at(idx).longitute == planes.at(idx).longitute &&
//            planes.at(idx).verticalHeading == planes.at(idx).verticalHeading &&
//            planes.at(idx).groundSpeed == planes.at(idx).groundSpeed &&
//            planes.at(idx).trueHeading == planes.at(idx).trueHeading)
//    {

//        value++;
//        planes.at(idx).checkAircraft = value;
//    }

//    if(planes.at(idx).checkAircraft == 5)
//    {
//        planes.at(idx).isAircraft = false;
//    }
//    else if (planes.at(idx).checkAircraft >= 8)
//    {
//        planes.erase(planes.begin() + idx);
//    }


}

std::string PlaneManager::convertData(size_t c)
{
    //TODO: if the message are no longer being received then remove them from list, similar to reading in the data in link above

    std::string prepToSend;
    Json::Value root;
    Json::Value data;

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
        //vector_push_back(stream, vector_at(buffer, ci));
        stream.push_back(vector_at(buffer, ci));

    }

    if(stream.size() < 1)
    {
        return;
    }

    //message.push_back();
//    size_t length = 0;
//    length = strlen(&ch);

//    for (ci = 0; ci < length; ci++)
//    {
//        message.append("");
//    }


    //sstream_str_cstr(packet, "");

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
            //message.append("");
            //sstream_str_cstr(packet, "");
        }
        else
        {
            packet += ch;
            //message.append(&ch);
            //sstream_append_char(packet, ch);
        }
    }

    if(lnl)
    {
        //vector_erase(stream, 0, lnl);
        stream.erase(stream.begin(), stream.begin() + lnl);
    }
}
