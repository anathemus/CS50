<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // checks to make sure username and password are filled.
	if ($_POST["username"] == NULL || $_POST["password"] == NULL)
	{
	    render("apology.php", ["message" => "Username or Password missing."]);	
	}
	
	// make sure passwords match.
	else if ($_POST["password"] != $_POST["confirmation"])
	{
	    render("apology.php", ["message" => "Password does not match Second Entry."]);
	}
	
	else
	{
	    // insert into SQL
	    query("INSERT INTO users (username, hash, email, cash) VALUES(?, ?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]), $_POST["email"]);
	    
	}
    

    	// Checks to ensure query returned true. If it didn't, user already exists.
    	if ($handle === false)
    	{
	    render("apology.php", ["message" => "Username already exists!"]);
    	}

    	else
    	{
	    $rows = query("SELECT LAST_INSERT_ID() AS id");
	    $id = $rows[0]["id"];
	    $_SESSION["id"] = $id;
	    redirect("index.php");
    	}
}
?>
