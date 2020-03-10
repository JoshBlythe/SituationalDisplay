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

    <script src="canvas.js"></script>
    <script src="OpenLayers.light.js"></script>
    <script>
      function init()
        {
            map = new OpenLayers.Map("basicMap");
            var mapnik = new OpenLayers.Layer.OSM();
            var fromProjection = new OpenLayers.Projection("EPSG:4326");   // Transform from WGS 1984
            var toProjection = new OpenLayers.Projection("EPSG:900913"); // to Spherical Mercator Projection
            var position = new OpenLayers.LonLat(13.41,52.52).transform( fromProjection, toProjection);
            //set zoom
            var zoom = 4;

            map.addLayer(mapnik);
            map.setCenter(position, zoom );
        }
    </script>
<!-- php was here -->
</head>


<body onload="init();">

<!-- <img id="plane" width="50" height="50" src="img/plane.jpg"> -->

<!-- <h1 id="head1"> Check PHP </h1> -->

<p id="demo"></p>

<!-- <canvas id="canvasID" width="240" height="297" style="border:1px solid #d3d3d3;">
Your browser does not support the HTML5 canvas tag.
</canvas> -->

<div id="basicMap" class="smallmap"></div>

<div id="basicMap"></div>

</body>

<script type="text/javascript">

    function getData()
    {

      var xmlhttp = new XMLHttpRequest();

      xmlhttp.onreadystatechange = function()
      {
        if (this.readyState == 4 && this.status == 200) {
          var myObj = JSON.parse(this.responseText);
          document.getElementById("demo").innerHTML = myObj;
        }
      };

      xmlhttp.open("GET", "clientPHP.php", true)
      xmlhttp.send();
        //get data from php above and display it using javascript
          // var dataSent = <?php echo json_encode($result)?>;

          // var element = document.getElementById("head1");
          // element.innerHTML = dataSent;

          //   var jsonObj = JSON.parse(dataSent);
          //   //console.log(dataSent);

          //   document.getElementById("demo").innerHTML = jsonObj.Hexideimal;
      //}
    }

    window.setInterval(function()
    {
        getData();
    }, 1000);

</script>

</html>
