<!DOCTYPE html>

<html>
  <head>
    <meta name="viewport" content="initial-scale=1.0, user-scalable=no" />
    <style type="text/css">
      html { height: 100% }
      body { height: 100%; margin: 0; padding: 0 }
      #map_canvas { height: 100% }
      #info {
        position: absolute;
        width:20%;
        height:100%;
        bottom:0px;
        right:0px;
        top:0px;
        background-color: white;
        border-left:1px #666 solid;
        font-family:Helvetica;
      }
      #info div {
        padding:0px;
        padding-left:10px;
        margin:0px;
      }
      #info div h1 {
        margin-top:10px;
        font-size:16px;
      }
      #info div p {
        font-size:14px;
        color:#333;
      }
    </style>
    <script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.3/jquery.min.js">
    </script>
    <script type="text/javascript"
      src="https://maps.googleapis.com/maps/api/js?sensor=true">
    </script>
    <script type="text/javascript">
    Map=null;
    CenterLat=45.0;
    CenterLon=9.0;
    Planes={};
    NumPlanes = 0;
    Selected=null

    function getIconForPlane(plane) {
        var r = 255, g = 255, b = 0;
        var maxalt = 40000; /* Max altitude in the average case */
        var invalt = maxalt-plane.altitude;
        var selected = (Selected == plane.hex);

        if (invalt < 0) invalt = 0;
        b = parseInt(255/maxalt*invalt);
        return {
            strokeWeight: (selected ? 2 : 1),
            path: google.maps.SymbolPath.FORWARD_CLOSED_ARROW,
            scale: 5,
            fillColor: 'rgb('+r+','+g+','+b+')',
            fillOpacity: 0.9,
            rotation: plane.track
        };
    }

    function selectPlane() {
        if (!Planes[this.planehex]) return;
        var old = Selected;
        Selected = this.planehex;
        if (Planes[old]) {
            /* Remove the highlight in the previously selected plane. */
            Planes[old].marker.setIcon(getIconForPlane(Planes[old]));
        }
        Planes[Selected].marker.setIcon(getIconForPlane(Planes[Selected]));
        refreshSelectedInfo();
    }
    
    function refreshGeneralInfo() {
        var i = document.getElementById('geninfo');

        i.innerHTML = NumPlanes+' planes on screen.';
    }

    function refreshSelectedInfo() {
        var i = document.getElementById('selinfo');
        var p = Planes[Selected];

        if (!p) return;
        var html = 'ICAO: '+p.hex+'<br>';
        if (p.flight.length) {
            html += '<b>'+p.flight+'</b><br>';
        }
        html += 'Altitude: '+p.altitude+' feet<br>';
        html += 'Speed: '+p.speed+' knots<br>';
        html += 'Coordinates: '+p.lat+', '+p.lon+'<br>';
        i.innerHTML = html;
    }

    function fetchData() {
        $.getJSON('/data.json', function(data) {
            var stillhere = {}
            for (var j=0; j < data.length; j++) {
                var plane = data[j];
                var marker = null;
                stillhere[plane.hex] = true;
                plane.flight = $.trim(plane.flight);

                if (Planes[plane.hex]) {
                    var myplane = Planes[plane.hex];
                    marker = myplane.marker;
                    var icon = marker.getIcon();
                    var newpos = new google.maps.LatLng(plane.lat, plane.lon);
                    marker.setPosition(newpos);
                    marker.setIcon(getIconForPlane(plane));
                    myplane.altitude = plane.altitude;
                    myplane.speed = plane.speed;
                    myplane.lat = plane.lat;
                    myplane.lon = plane.lon;
                    myplane.track = plane.track;
                    myplane.flight = plane.flight;
                    if (myplane.hex == Selected)
                        refreshSelectedInfo();
                } else {
                    marker = new google.maps.Marker({
                        position: new google.maps.LatLng(plane.lat, plane.lon),
                        map: Map,
                        icon: getIconForPlane(plane)
                    });
                    plane.marker = marker;
                    marker.planehex = plane.hex;
                    Planes[plane.hex] = plane;

                    /* Trap clicks for this marker. */
                    google.maps.event.addListener(marker, 'click', selectPlane);
                }
                if (plane.flight.length == 0)
                    marker.setTitle(plane.hex)
                else
                    marker.setTitle(plane.flight+' ('+plane.hex+')')
            }
            NumPlanes = data.length;

            /* Remove idle planes. */
            for (var p in Planes) {
                if (!stillhere[p]) {
                    Planes[p].marker.setMap(null);
                    delete Planes[p];
                }
            }
        });
    }

    function initialize() {
        var mapOptions = {
            center: new google.maps.LatLng(CenterLat, CenterLon),
            zoom: 5,
            mapTypeId: google.maps.MapTypeId.ROADMAP
        };
        Map = new google.maps.Map(document.getElementById("map_canvas"), mapOptions);

        /* Setup our timer to poll from the server. */
        window.setInterval(function() {
            fetchData();
            refreshGeneralInfo();
        }, 1000);
    }

    </script>
  </head>
  <body onload="initialize()">
    <div id="map_canvas" style="width:80%; height:100%"></div>
    <div id="info">
      <div>
        <h1>Dump1090</h1>
        <p id="geninfo"></p>
        <p id="selinfo">Click on a plane for info.</p>
      </div>
    </div>
  </body>
</html>
