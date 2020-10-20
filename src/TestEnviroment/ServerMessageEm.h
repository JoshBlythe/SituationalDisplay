#ifndef _ServerMessageEm_
#define _ServerMessageEm_

#include <string.h>
#include <iostream>

#include "PlaneData.h"
#include "TcpSocket.h"

struct WsTcpSocket;
struct PlaneData;

class ServerMessageEm
{
public:
    ServerMessageEm();
    ~ServerMessageEm();

    void SendMessage();
    void SetAircraftPos();

private:


    WsTcpSocket *serverem;

    vector(unsigned char) data;

    std::vector <PlaneData> planeData;

    PlaneData aircraft;
    PlaneData aircraft2;
    PlaneData aircraft3;

    size_t testSystemLoop;
    std::string divider;

};


#endif
