/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Global JavaScript.
 */

// Google Map
var map;

// markers for map
var markers = [];

// info window
var info = new google.maps.InfoWindow({maxWidth: 350});

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }

    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 42.3770, lng: -71.1256}, // Cambridge, Massachusetts
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

       
});

function FBButton(controlDiv, map) {

  // Set CSS for the control border.
  var controlUI = document.createElement('div');
  controlUI.style.backgroundColor = 'rgb(59,89,152)';
  controlUI.style.border = '2px solid #fff';
  controlUI.style.borderRadius = '3px';
  controlUI.style.boxShadow = '0 2px 6px rgba(0,0,0,.3)';
  controlUI.style.cursor = 'pointer';
  controlUI.style.marginBottom = '22px';
  controlUI.style.textAlign = 'center';
  controlUI.title = 'Click to open a window to Facebook';
  controlDiv.appendChild(controlUI);

  // Set CSS for the control interior.
  var controlText = document.createElement('div');
  controlText.style.color = '#fff';
  controlText.style.fontFamily = 'Roboto,Arial,sans-serif';
  controlText.style.fontSize = '16px';
  controlText.style.lineHeight = '38px';
  controlText.style.paddingLeft = '5px';
  controlText.style.paddingRight = '5px';
  controlText.innerHTML = 'Take me to Facebook!';
  controlUI.appendChild(controlText);

  // Setup the click event listeners: simply set the map to Chicago.
  controlUI.addEventListener('click', function() {
   facebookOpen();
  });

}



  // Create the DIV to hold the control and call the FBHometownButton() constructor
  // passing in this DIV.
  // var FBHometownButtonDiv = document.createElement('div');
  // var FBHometownButtonInit = new FBHometownButton(FBHometownButtonDiv, map);

  // FBHometownButtonDiv.index = 1;
  // map.controls[google.maps.ControlPosition.TOP_RIGHT].push(FBHometownButtonDiv);
  // }

/**
 * Adds marker for place to map.
 */
function addMarker(place)
{
    // store Lat and Lng in variable
    var myLatLng = {lat: parseFloat(place.latitude), lng: parseFloat(place.longitude)};
    
    
    
    // image for the marker
    var image = { 
    url: "http://maps.google.com/mapfiles/kml/pal4/icon8.png",
    anchor: new google.maps.Point(0, 32)
    };
        
    // information for the marker
    var marker = new MarkerWithLabel({
    position: myLatLng,
    map: map,
    icon: image,
    labelClass: "label",
    labelContent: place.place_name,
    labelAnchor: new google.maps.Point(20,0),
    });
    
    
    // grab the articles for the info window
    $.getJSON("articles.php?geo="+place.place_name)
    .done(function(data, textStatus, jqXHR) 
    {
        // message if JSON doesn't find anything for that zip code
        if (data.length === 0)
        {
            var articles = "<div>Not much happening here!</div>";
            
            // "listens" for click on the marker, opens info window with articles!
            marker.addListener('click', function() {showInfo(marker, articles);});
        }

        // else concatenate the articles, or ahticles if you're from Massachusetts.
        else
        {
            var articles = "<ul>";
            var len = data.length;

            for (var i = 0; i < len; i++) 
            {
                articles += "<div><li> <a href=\"" + data[i].link + "\" target=\"_blank\">" + data[i].title + "</li></div>";
            }
            articles += "</ul>";
        
            // "listens" for click on the marker, opens info window with articles!
            marker.addListener('click', function() {showInfo(marker, articles);});
        }
        
        
    });
    
    // "push" the marker into the markers array
    markers.push(marker);
}

/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {
        update();
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // remove markers whilst dragging
    google.maps.event.addListener(map, "dragstart", function() {
        removeMarkers();
    });

    // configure typeahead
    // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
    $("#q").typeahead({
        autoselect: true,
        highlight: true,
        minLength: 1
    },
    {
        source: search,
        templates: {
            empty: "no places found yet",
            suggestion: _.template("<p><%- place_name %>, <%- admin_code1 %>, <%- admin_name1 %>, <%- postal_code %></p>")
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // ensure coordinates are numbers
        var latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        var longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);

        // set map's center
        map.setCenter({lat: latitude, lng: longitude});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        hideInfo();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true; 
        event.stopPropagation && event.stopPropagation(); 
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();

    // Create Facebook Hometown Button!
    // Create the DIV to hold the control and call the FBHometownButton() constructor
    // passing in this DIV.
    var FBButtonDiv = document.createElement('div');
    var FBButtonInit = new FBButton(FBButtonDiv, map);

    FBButtonDiv.index = 1;
    map.controls[google.maps.ControlPosition.TOP_RIGHT].push(FBButtonDiv);
     

      
    
}
/**
 * Hides info window.
 */
function hideInfo()
{
    info.close();
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    // iterate over each marker, remove it from the map
    for (var i = 0; i < markers.length; i++)
        {
            var marker = markers[i];
            marker.setMap(null);  
        }
    
    // per https://developers.google.com/maps/documentation/javascript/markers#remove
    // markers.length = 0;

    
    markers = [];
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb)
{
    // get places matching query (asynchronously)
    var parameters = {
        geo: query
    };
    $.getJSON("search.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        cb(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // start div
    var div = "<div id='info'>";
    if (typeof(content) === "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='img/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update() 
{
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // remove old markers from map
        removeMarkers();

        // add new markers to map
        for (var i = 0; i < data.length; i++)
        {
            addMarker(data[i]);
        }
        
     })
     .fail(function(jqXHR, textStatus, errorThrown) {

         // log error to browser's console
         console.log(errorThrown.toString());
     });
};

/*function displayNHLCities(){
/**
 * Adds NHL markers on cities with NHL teams on the map.
 *

    // store Lat and Lng in variable
    var NHLLatLng = {lat: parseFloat(42.215651), lng: parseFloat(-71.34218)};
    
    // image for the marker
    var image = { 
    url: "https://mapicons.mapsmarker.com/wp-content/uploads/mapicons/shape-default/color-ff8a22/shapecolor-color/shadow-1/border-dark/symbolstyle-white/symbolshadowstyle-dark/gradient-no/icehockey.png",
    anchor: new google.maps.Point(0, 32)
    };
 
    
    // information for the marker
    var NHLmarker = new google.maps.Marker({
    position: NHLLatLng,
    map: map,
    icon: image,
    labelClass: "label",
    labelContent: "TD Garden",
    labelAnchor: new google.maps.Point(20,0),
  });
    
    // grab the articles for the info window
    $.getJSON("NHL.php")
    .done(function(game, textStatus, jqXHR) 
    {
        // message if JSON doesn't find anything for that zip code
        if (game.length === 0)
        {
            var games = "<div>Not much happening here!</div>";
            
            // "listens" for click on the marker, opens info window with articles!
            marker.addListener('click', function() {showInfo(marker, articles);});
        }

        // else concatenate the articles, or ahticles if you're from Massachusetts.
        else
        {
            var len = game.length;

            for (var i = 0; i < len; i++) 
            {
                console.log(game[i]);
            }
            
        }
        
        
    });
    
    // "push" the marker into the markers array
    NHLmarker.setMap(map);
}
*/

/**
 * Can't get data I need to localhost because AJAXing between domains is a no-no. #lessonlearned. 
 *
 *
 * So I made due, and added a button to location.assign Facebook.
 */
function facebookOpen()
{
    location.assign("https://www.facebook.com");
    // var myLatLng = {lat: 42.2195, lng: -71.5195};
    // map.setCenter(myLatLng);
    // facebook(facebookPin, fbName, fbPic);
};



