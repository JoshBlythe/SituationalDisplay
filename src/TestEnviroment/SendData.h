#ifndef _SENDDATA_H
#define _SENDDATA_H

//#include "HandleWebSocket.h"
//#include "PlaneManager.h"

#include <jsoncpp/json/json.h>
//#include <jsoncpp/json/writer.h>
#include <string.h>
#include <iostream>

#include "PlaneManager.h"
//#include "TcpSocket.h"

struct WsTcpSocket;

class SendData
{
public:
    SendData();
    ~SendData();

    void SendAircraftInfo(PlaneManager &aircrafts);

private:
    WsTcpSocket *server;
    PlaneManager aircraftData;

    vector(unsigned char) data;

    size_t a;
};

#endif
