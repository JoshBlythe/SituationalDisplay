<?php 

      // set variables
      $hostname = "localhost";
      $portnumb = 1234;

      set_time_limit(0);

      //create socket
      $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
      //check if socket failed
      if (!socket) 
      {
        echo "Failed to create the socket!";
      }

      //attempt to connect socket to host (using variables set above)
      $result = socket_connect($socket, $hostname, $portnumb);
      //check if socket connection failed
      if (!result) 
      {
        echo "Failed to connect to host";
      }

      //read in data from socket
      $result = socket_read($socket, 1024);  
      //convert data to Json format
      $JsonObj = json_encode($result);

      // echo $JsonObj;
      //output result to enable display to obtain the data
      echo $result;

      //close the socket
      socket_close($socket);
      //return $result;

 ?>