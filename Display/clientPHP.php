<?php 
    // function clientstate()
    // {
      $hostname = "localhost";
      $portnumb = 1234;

      set_time_limit(0);

      $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
      if (!socket) 
      {
        echo "Failed to create the socket!";
      }

      $result = socket_connect($socket, $hostname, $portnumb);
      if (!result) 
      {
        echo "Failed to connect to host";
      }

      $result = socket_read($socket, 1024);  

      $JsonObj = json_encode($result);


      socket_close($socket);

      echo $JsonObj;
      //echo $result;
      //return $result;

    //}    

    // for ($i=0; $i < 5 ; $i++) 
    // { 
    //   clientstate();
    // }
 ?>