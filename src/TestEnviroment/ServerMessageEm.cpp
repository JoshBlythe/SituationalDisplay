#include "ServerMessageEm.h"

#define TEST_SERVER "localhost"
#define TEST_PORT 30003

ServerMessageEm::ServerMessageEm()
{
    //initalise the test server
    serverem = WsTcpListen(TEST_PORT);

    //check if initalised, if not abort (because a error occured)
    if(!serverem)
    {
        _WsPanic("Failed to Initalised the Test Server!");
        abort();
    }

    aircraft.hexID = "9999";
    aircraft.checkAircraft = 0;
    aircraft.isAircraft = true;
    aircraft.verticalHeading = "8000";
    aircraft.groundSpeed = "150";
    aircraft.trueHeading = "5";
    aircraft.latitude = "-9.44314";
    aircraft.longitute = "147.17972";

    aircraft2.hexID = "2999";
    aircraft2.checkAircraft = 0;
    aircraft2.isAircraft = true;
    aircraft2.verticalHeading = "14500";
    aircraft2.groundSpeed = "400";
    aircraft2.trueHeading = "41";
    aircraft2.latitude = "-9.46351";
    aircraft2.longitute = "147.17921";

    aircraft3.hexID = "3999";
    aircraft3.checkAircraft = 0;
    aircraft3.isAircraft = true;
    aircraft3.verticalHeading = "12000";
    aircraft3.groundSpeed = "500";
    aircraft3.trueHeading = "61";
    aircraft3.latitude = "-9.45414";
    aircraft3.longitute = "147.17872";

    divider = ",";

    data = vector_new(unsigned char);
    testSystemLoop = 0;

}

ServerMessageEm::~ServerMessageEm()
{
    //clean up test server
    WsTcpSocketClose(serverem);
}

void ServerMessageEm::SendMessage()
{
    char sc = 0;

    struct WsTcpSocket *socket = NULL;
    struct WsTcpSocket *clientConnection = NULL;

    //check if client connection isnt null
    if(clientConnection)
    {
        //set the socket to the clientconnection value
        socket = clientConnection;

        //check if there is not a connection
        if(!WsTcpSocketConnected(socket))
        {
            //if so print to console
            printf("Client has Disconnected!\n");
            //close the socket and
            WsTcpSocketClose(socket);
            //null the pointer to ensure there is no hanging pointer.
            clientConnection = NULL;
        }

        //check if the current socket is not ready
        if(!WsTcpSocketReady(socket))
        {
            //if not then early return.
            return;
        }

        //send/recieve data stored within data vector to client connected
        WsTcpSocketSend(clientConnection, data);
    }
    else
    {
        //set the socket to serverem value
        socket = serverem;

        //check to see if the socket is ready if not then early return
        if(!WsTcpSocketReady(socket))
        {
            return;
        }

        printf("Client Connected!\n");
        //set the cleint connection to the accepted socket
        clientConnection = WsTcpSocketAccept(socket);


        //convert the data in planeData into a char and send it via the TCP Socket
        std::string currPlane;

        currPlane = divider + divider + planeData.at(testSystemLoop).hexID + divider
                + divider + divider + divider + divider + divider + divider + divider + divider
                + planeData.at(testSystemLoop).verticalHeading + divider
                + planeData.at(testSystemLoop).groundSpeed + divider + planeData.at(testSystemLoop).trueHeading
                + divider + planeData.at(testSystemLoop).latitude + divider
                + planeData.at(testSystemLoop).longitute + divider + divider + divider + divider + divider
                + divider + divider + divider;

        std::cout << "Server Output string : " << std::endl;
        std::cout << currPlane << std::endl;

        //loop through the current plane string variable
        for (size_t i = 0; i < currPlane.size(); i++)
        {
            //pull the value you at i
            sc = currPlane.at(i);
            // and push it into data.
            vector_push_back(data, sc);
        }

        //send data vector to the client
        WsTcpSocketSend(clientConnection, data);
    }

    //close the connected client after data is sent.
    WsTcpSocketClose(clientConnection);

}

void ServerMessageEm::SetAircraftPos()
{
    if(testSystemLoop < 5)
    {
        if(testSystemLoop == 4)
        {
            testSystemLoop = 0;
        }

        if(testSystemLoop == 0)
        {
            planeData.push_back(aircraft);
            planeData.push_back(aircraft2);
            planeData.push_back(aircraft3);
        }

        if(testSystemLoop == 1)
        {
            aircraft.hexID = "9999";
            aircraft.checkAircraft = 0;
            aircraft.verticalHeading = "7725";
            aircraft.groundSpeed = "14500";
            aircraft.trueHeading = "5";
            aircraft.latitude = "-9.44327";
            aircraft.longitute = "147.17991";

            aircraft2.hexID = "2999";
            aircraft2.checkAircraft = 0;
            aircraft2.verticalHeading = "14500";
            aircraft2.groundSpeed = "400";
            aircraft2.trueHeading = "41";
            aircraft2.latitude = "-9.46378";
            aircraft2.longitute = "147.18001";

            aircraft3.hexID = "3999";
            aircraft3.checkAircraft = 0;
            aircraft3.verticalHeading = "12000";
            aircraft3.groundSpeed = "500";
            aircraft3.trueHeading = "61";
            aircraft3.latitude = "-9.45350";
            aircraft3.longitute = "147.17921";
        }

        if(testSystemLoop == 2)
        {
            aircraft.hexID = "9999";
            aircraft.checkAircraft = 0;
            aircraft.verticalHeading = "8000";
            aircraft.groundSpeed = "150";
            aircraft.trueHeading = "5";
            aircraft.latitude = "-9.44384";
            aircraft.longitute = "147.18023";

            aircraft2.hexID = "2999";
            aircraft2.checkAircraft = 0;
            aircraft2.verticalHeading = "14500";
            aircraft2.groundSpeed = "400";
            aircraft2.trueHeading = "41";
            aircraft2.latitude = "-9.46390";
            aircraft2.longitute = "147.18072";

            aircraft3.hexID = "3999";
            aircraft3.checkAircraft = 0;
            aircraft3.verticalHeading = "12000";
            aircraft3.groundSpeed = "500";
            aircraft3.trueHeading = "61";
            aircraft3.latitude = "-9.45314";
            aircraft3.longitute = "147.17952";
        }

        if(testSystemLoop == 3)
        {
            aircraft.hexID = "9999";
            aircraft.checkAircraft = 0;
            aircraft.verticalHeading = "8000";
            aircraft.groundSpeed = "150";
            aircraft.trueHeading = "5";
            aircraft.latitude = "-9.44414";
            aircraft.longitute = "147.17852";

            aircraft2.hexID = "2999";
            aircraft2.checkAircraft = 0;
            aircraft2.verticalHeading = "14500";
            aircraft2.groundSpeed = "400";
            aircraft2.trueHeading = "41";
            aircraft2.latitude = "-9.46421";
            aircraft2.longitute = "147.17951";

            aircraft3.hexID = "3999";
            aircraft3.checkAircraft = 0;
            aircraft3.verticalHeading = "12000";
            aircraft3.groundSpeed = "500";
            aircraft3.trueHeading = "61";
            aircraft3.latitude = "-9.45304";
            aircraft3.longitute = "147.17972";

        }

//        if(testSystemLoop == 6)
//        {
//            testSystemLoop = 0;
//        }

    }

    testSystemLoop++;
}

