<?php

    require(__DIR__ . "/../includes/config.php");

    //get today's date to grab the day's matchups
    $today = date("Y/m/d");

    // numerically indexed array of matches
    $matches = [];
    
    // array for the scores
    $score = [];


    // headers for proxy servers
    /*$headers = [
        "Accept" => "**",
        "Connection" => "Keep-Alive",
        "User-Agent" => sprintf("curl/%s", curl_version()["version"])
    ];

    // download RSS from Google News
    $context = stream_context_create([
        "http" => [
            "header" => implode(array_map(function($value, $key) { return sprintf("%s: %s\r\n", $key, $value); }, $headers, array_keys($headers))),
            "method" => "GET"
        ]
    ]);*/

    // get the schedule of games for the day
    $contents = @file_get_contents("http://api.sportradar.us/nhl-t3/games/{$today}/schedule.json?api_key=gy4r972tsvfvptqgfbpgkpne");
    if ($contents === false)
    {
        http_response_code(503);
        exit;
    }

    // parse JSON
    $json = json_decode($contents, true);
    $games = $json['games'];
    
   

    // var_dump($games);
    // echo $games[0]['home']['name'];
    // echo $games[8][0];
    // print(json_encode($contents, JSON_PRETTY_PRINT));
    // iterate over games in json response
    foreach ($games as $game)
    {
        /*
        */
        
        // add games' data to array
        $matches[] = [
            "gameid" => (string) $game['id'],
            "home_name" => (string) $game['home']['name'],
            "home_alias" => (string) $game['home']['alias'],
            "away_name" => (string) $game['away']['name'],
            "away_alias" => (string) $game['away']['alias']
        ];
    }
    // print(json_encode($matches, JSON_PRETTY_PRINT));
    // iterate over game ID's, grab scores from each game
   
   foreach($matches as $match)
    {
        $gameID = $match['gameid'];
        // var_dump($gameID);

        // delay, can only call api once per second, delay 2 just to be safe.
        sleep(2);
        $gameContents = @file_get_contents("http://api.sportradar.us/nhl-t3/games/{$gameID}/boxscore.json?api_key=gy4r972tsvfvptqgfbpgkpne");
        if ($gameContents === false)
        {
            http_response_code(503);
            exit;
        }

        //parse game JSON
        $gameJson = json_decode($gameContents, true);
        // var_dump($gameJson);
        // iterate over each game's json code, grab the score values for home and away, add them to a score array
        for($i =1; $i <= count($gameContents); $i++)
        {
            // until the game starts, the score will be 0-0
            if (!isset($gameContents['home']['points']) && !isset($gameContents['away']['points']))
            {
                $score[] = [
                    "home_score" => "0",
                    "away_score" => "0"
                ];
            }
            else
            {
                $score[] = [
                    "home_score" => (string) $gameContents['home']['points'],
                    "away_score" => (string) $gameContents['away']['points']
                ];
            }
        }
    }
    
    // output articles as JSON (pretty-printed for debugging convenience)
    // header("Content-type: application/json");
    print(json_encode($matches, JSON_PRETTY_PRINT));
    print(json_encode($score, JSON_PRETTY_PRINT)); 

?>
