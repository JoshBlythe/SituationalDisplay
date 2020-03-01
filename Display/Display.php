<!DOCTYPE HTML>
<html>



  <head>
    <title>ADS-B Display</title>
    <style type="text/css">
      html, body, #basicMap {
          width: 100%;
          height: 100%;
          margin: 0;
      }
    </style>
	
    <script src="OpenLayers.light.js"></script>
    <script>
      function init() {
        map = new OpenLayers.Map("basicMap");
        var mapnik         = new OpenLayers.Layer.OSM();
        var fromProjection = new OpenLayers.Projection("EPSG:4326");   // Transform from WGS 1984
        var toProjection   = new OpenLayers.Projection("EPSG:900913"); // to Spherical Mercator Projection
        var position       = new OpenLayers.LonLat(13.41,52.52).transform( fromProjection, toProjection);
        var zoom           = 15; 

        map.addLayer(mapnik);
        map.setCenter(position, zoom );
      }
    </script>
  </head>


<body>
<h1> Check PHP </h1>

<?php
    //session_start();

    //define socket
    $host = "localhost";
    $port = 1234;

    set_time_limit(0);

    //create socket.
    $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP) or die("Couldnt create socket!\n");
    //connect socket to the server.
    $result = socket_connect($socket, $host, $port) or die("Unable to connect to Server!\n");


    $buf = 'Ready to Read in Data';

    //socket_write($socket, $message, strlen($buf)) or die("Couldn't send the data to the server\n");

    //$bytes = socket_recv($socket, $buf, 2048, MSG_WAITALL);
    //echo "socket_recv failed: Reason" . socketstrerror(socket_last_error($socket)) . "\n";

    //echo $buf . "\n";

    //while(true)
    //{
        $result = socket_read($socket, 1024) or die("Couldnt read server data!\n");
        //$_SESSION["result"] = $result;
    //}

    echo "Message from server: ".$result;

    //close
    socket_close($socket);

?>
</body>

 <body onload="init();">
    <div id="basicMap"></div>
  </body>

</html>
