#include "PlaneManager.h"
#include "inc/util.h"

#include <sstream>
#include <stdlib.h>

#define SERVER_HOST "localhost"
#define SERVER_PORT 30003
#define RECV_BUFFER 4096


PlaneManager::PlaneManager()
{
    client = WsTcpSocketConnect("localhost", 30003);
    buffer = vector_new(unsigned char);

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
    std::vector<std::string> token;
    //PlaneData plane;
    //output message read in.
    //printf("[%s]\n", packet.c_str());
    SplitStringOnCharacter(packet,',', token, 4);

    //printf("[%s]\n", token.c_str());

    //printf("[%s]\n", token.at(4).c_str());


    if(planes.empty())
    {
        StoreData(token);
    }

    AddNewData(token);

    UpdateData(token);

//            if(planes.at(i).hexID == token.at(4))
//            {
//                planes.at(i).verticalHeading = std::atoi(token.at(11).c_str());
//                planes.at(i).groundSpeed = std::atoi(token.at(12).c_str());
//                planes.at(i).trueHeading = std::atoi(token.at(13).c_str());
//                planes.at(i).latitude = std::atoi(token.at(14).c_str());
//                planes.at(i).longitute = std::atoi(token.at(15).c_str());
//                //UpdateData(plane, token);
//            }

        printf("[%s]\n", packet.c_str());
        for (size_t i = 0; i < planes.size(); i++)
        {
            std::cout << planes.size() << std::endl;
            printf("[%s]\n", planes.at(i).hexID.c_str());
            std::cout << "["<< planes.at(i).latitude << "]" << std::endl;
            std::cout << "["<< planes.at(i).longitute << "]" << std::endl;
            //printf("[%f]\n", planes.at(i).latitude);
            //printf("[%f]\n", planes.at(i).longitute);
            printf("[%i]\n", planes.at(i).groundSpeed);
            printf("[%i]\n", planes.at(i).trueHeading);
            printf("[%i]\n", planes.at(i).verticalHeading);
            printf("[%i]\n", planes.at(i).airborneState);

        }

    //TODO:
    //The first two section read in are the Message type (MSG,AIR, ID)
    //then the Transmittion type (1-8) this is what helps us get the below fields.
    // 1. Add each hex ID to a vector,
    // 2. for each hex ID there will need to be,
        //2a. Position data (latitude and longitude)
                //comes in through MSG 2/3
        //2b. Altitude data
                //comes in through MSG 2/3/5/7
        //2c. Ground speed data
                //comes in through MSG 2/4
        //2d. true heading
                //comes in through MSG (need to find out)
        //2e. Vertical Rate
                //comes in through MSG 4
        //2f. Airborne State (this comes in from is on ground)
                //comes in through MSG 2/3/5/6/7/8


        //if not had data from plane in X amount of messages remove from vector.

}

void PlaneManager::StoreData(std::vector<std::string> &info)
{
    PlaneData plane;

    plane.hexID = info.at(4);
    plane.verticalHeading = std::atoi(info.at(11).c_str());
    plane.groundSpeed = std::atoi(info.at(12).c_str());
    plane.trueHeading = std::atoi(info.at(13).c_str());
    plane.latitude = std::atof(info.at(14).c_str());
    plane.longitute = std::atof(info.at(15).c_str());

    //TODO: Check if this works.
    //could use this
    //std::stof(info.at(14));

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
    plane.verticalHeading = std::atoi(info.at(11).c_str());
    plane.groundSpeed = std::atoi(info.at(12).c_str());
    plane.trueHeading = std::atoi(info.at(13).c_str());
    plane.latitude = std::atof(info.at(14).c_str());
    plane.longitute = std::atof(info.at(15).c_str());

    //TODO:
    // if 21 = "" then continue else update it.
    //plane.airborneState = std::atoi(info.at(21).c_str());


    planes.push_back(plane);

}

void PlaneManager::UpdateData(std::vector<std::string> &info)
{

        for (size_t i = 0; i < planes.size(); i++)
        {
            if(info.at(4) == planes.at(i).hexID)
            {
                if(info.at(1) == "2")
                {
                    planes.at(i).verticalHeading = std::atoi(info.at(11).c_str());
                    planes.at(i).groundSpeed = std::atoi(info.at(12).c_str());
                    planes.at(i).trueHeading = std::atoi(info.at(13).c_str());
                    planes.at(i).latitude = std::atof(info.at(14).c_str());
                    planes.at(i).longitute = std::atof(info.at(15).c_str());
                    planes.at(i).airborneState = std::atoi(info.at(21).c_str());
                }

                if(info.at(1) == "3")
                {
                    planes.at(i).verticalHeading = std::atoi(info.at(11).c_str());
                    planes.at(i).latitude = std::atof(info.at(14).c_str());
                    planes.at(i).longitute = std::atof(info.at(15).c_str());
                    planes.at(i).airborneState = std::atoi(info.at(21).c_str());
                }

                if(info.at(1) == "4")
                {
                    planes.at(i).groundSpeed = std::atoi(info.at(12).c_str());
                    planes.at(i).trueHeading = std::atoi(info.at(13).c_str());
                }

                if(info.at(1) == "5")
                {
                    planes.at(i).verticalHeading = std::atoi(info.at(11).c_str());
                    //planes.at(i).airborneState = std::atoi(info.at(21).c_str());
                }

                if(info.at(1) == "6")
                {
                    //planes.at(i).verticalHeading = std::atoi(info.at(11).c_str());
                    //planes.at(i).airborneState = std::atoi(info.at(21).c_str());
                }

                if(info.at(1) == "7")
                {
                    planes.at(i).verticalHeading = std::atoi(info.at(11).c_str());
                    //planes.at(i).airborneState = std::atoi(info.at(21).c_str());
                }

                if(info.at(1) == "8")
                {
                    //planes.at(i).airborneState = std::atoi(info.at(21).c_str());
                }

            }
        }


//            for (size_t i = 0; i < info.size(); i++)
//            {
//                //std::cout << token.at(i) << std::endl;
//                printf("[%s]\n", info.at(i).c_str());
//            }
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
