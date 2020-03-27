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
    PlaneManager();
    ~PlaneManager();

    void displayADSBData();

    void StateProcessNetwork();
    void StateProcessPacket();
    void StoreData(std::vector<std::string> &info);
    void AddNewData(std::vector<std::string> &info);
    void UpdateData(std::vector<std::string> &info);
    void RemoveData();

    std::string convertData(size_t c);

private:
      friend class SendData;

      WsTcpSocket *client;
      WsTcpSocket *SendData;

      vector(unsigned char) buffer;
      //vector(unsigned char) stream;
      //ref(sstream) packet;
      //vector(ref(sstream)) tokens;
      std::string packet;
      //std::vector<unsigned char> _buffer;
      std::vector<unsigned char> stream;
      int value;

      std::vector<PlaneData> planes;
      std::vector<std::string> jsonConverted;

};

#endif
