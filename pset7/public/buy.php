<?php
    
    // configuration 
    require("../includes/config.php");   
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
	$cash =	query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
	render("buy_form.php", ["title" => "Buy", "cash" => $cash]);
    }

    else     if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if symbol or shares empty
        if (empty($_POST["symbol"]) || empty($_POST["shares"]))
        {
            apologize("You must enter a stock symbol and quantity of shares to buy.");
        }
        
        // if symbol is invalid
        if (lookup($_POST["symbol"]) === false)
        {
            apologize("Invalid stock symbol.");
        }
        
        // if shares invalid
        if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            apologize("You must enter a whole, positive integer.");
        }
        
        // set transaction type
        $transaction = 'BUY';
        
        // look up stock price
        $stock = lookup($_POST["symbol"]);
        
        // calculate total cost (stock's price * shares)
        $cost = $stock["price"] * $_POST["shares"];
        
        // query to check how much cash user has
        $cash =	query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);	
        
        // if user's cash < total cost (user can't afford purchase)
        if ($cash < $cost)
        {
            apologize("You can't afford this purchase.");
        }         
        
        // else if user's cash >= total price (user can afford purchase)
        else
        {	
            $_POST["symbol"] = strtoupper($_POST["symbol"]);
                         
            // add stock to their portfolio or update shares
            query("INSERT INTO portfolio (id, symbol, shares, price) VALUES(?, ?, ?, ?) 
                ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $stock["price"]);
            
            // subtract total price from their cash
            query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
            
            // update history
	    $time = date('Y/m/d h:i:s a');
	    
            query("INSERT INTO history (id, transaction, time, symbol, shares, price) VALUES (?, ?, ?, ?, ?, ?)", $_SESSION["id"], $transaction, $time, $_POST["symbol"], $_POST["shares"], $stock["price"]);
            
	    // get user's email, send email receipt
	    $emailSQL = query("SELECT email FROM users WHERE id = ?", $_SESSION["id"]);
	    $email = $emailSQL[0]; // hello, string! goodbye, array!

	    $msg = "You have successfully purchased {$_POST["shares"]} shares of stock symbol {$_POST["symbol"]} at price {$stock["price"]} for a total cost of {$cost}. Thank you for your business!     This is CS50!";

	    $msg = wordwrap($msg, 70);

	    email($email, "C$50 Financial Purchase Receipt", $msg);

	    redirect("index.php");    
        }
    }
