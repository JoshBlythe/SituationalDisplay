#ifndef _SENDDATA_H
#define _SENDDATA_H

//#include "WebSocket.h"

#include "inc/stent.h"

struct WsServer;

class SendData
{
public:
    SendData();
    ~SendData();

    void convertData();
    void sendData();

private:
   // WsServer* server;
    vector(unsigned char) data;


};

#endif
