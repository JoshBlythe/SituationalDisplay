#ifndef _PLANEMANAGER_H
#define _PLANEMANAGER_H

#include <vector>
#include <sstream>
#include <string>
#include <iostream>


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

private:
      friend class SendData;

      WsTcpSocket *client;

      vector(unsigned char) buffer;
      //vector(unsigned char) stream;
      //ref(sstream) packet;
      //vector(ref(sstream)) tokens;
      std::string packet;
      //std::vector<unsigned char> _buffer;
      std::vector<unsigned char> stream;
      //std::vector<std::string> _tokens;
      std::string message;

      std::vector<PlaneData> planes;

};

#endif
