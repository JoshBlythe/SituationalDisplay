#ifndef _PLANEMANAGER_H
#define _PLANEMANAGER_H

#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/writer.h>


#include "PlaneData.h"
#include "TcpSocket.h"


struct WsTcpSocket;
struct PlaneData;

class PlaneManager
{
public:
    //class constructor
    PlaneManager();
    //and destructor
    ~PlaneManager();

    //used to obtain the raw packets from the dump1090 server.
    void StateProcessNetwork();

    //used to extract the aircraft data from the stored raw packets in stream. Then either stores or updates
    //the planes vector of aircraft
    void StateProcessPacket();
    //stores a aircraft
    void StoreData(std::vector<std::string> &info);
    //adds a new aircraft
    void AddNewData(std::vector<std::string> &info);
    //updates a stored aircraft data
    void UpdateData(std::vector<std::string> &info);

    //removes a aircraft from the vector
    void RemoveData();


    //converts the stored aircraft data to json format.
    std::string convertData(size_t c);

private:
      //friend class to sendData allows private vaiables to be accessed.
      friend class SendData;

      // reference to WsTcpSocket, used to connect to dump1090 server.
      WsTcpSocket *client;

      vector(unsigned char) buffer;
      //vector(unsigned char) stream;
      //ref(sstream) packet;
      //vector(ref(sstream)) tokens;
      std::string packet;
      //std::vector<unsigned char> _buffer;
      //vector of unsiged char to store the raw packets read from dump1090
      std::vector<unsigned char> stream;

      //vector of planes, stores type planeData (this is a struct which holds the read in aircraft data).
      std::vector<PlaneData> planes;

};

#endif
