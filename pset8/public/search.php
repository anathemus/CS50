<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // search database for places matching $_GET["geo"]
    $geo = array_map('trim', explode(",", $_GET["geo"]));
    
    // Begin SQL query to be concatenated!
    $sqlcat = "SELECT * FROM places WHERE ";

    
    for($i = 0, $count = count($geo); $i < $count; $i++)
    {
	// check for state abbreviation
        if(strlen($geo[$i]) === 2 || (strlen($geo[$i])) === 3 && preg_match('/,/', $geo[$i]) === 1)
	{
	     $sqlcat .= 'admin_code1 LIKE "' . htmlspecialchars($geo[$i], ENT_QUOTES) . '%"';
	}
	
	// check for zip code
	else if (is_numeric($geo[$i])) 
	{
             $sqlcat .= 'postal_code LIKE "' . htmlspecialchars($geo[$i], ENT_QUOTES) . '%"';
        } 

	// check for everything else
	else 
	{
            $sqlcat .= '(place_name  LIKE "' . htmlspecialchars($geo[$i], ENT_QUOTES) . '%" OR ' . 'admin_name1 LIKE "' . htmlspecialchars($geo[$i], ENT_QUOTES) . '%")';
        }
        
        if ($i < ($count - 1)) 
	{
            $sqlcat .= " AND ";
        }
    }
    
    // send concatenated query to be stored in places array
    $places = query($sqlcat);

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
