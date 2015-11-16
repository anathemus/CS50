<?php
 
    // configuration
    require("../includes/config.php");
     
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //render form
        render("quote_form.php", ["title" => "Quote"]);
    }
 
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
 
        if ($stock === false)
        {
        	apologize(["message" => "Invalid stock symbol."]);
        }
 
        render("quote_result.php", ["stock" => $stock]);
 
    }
 
?>
