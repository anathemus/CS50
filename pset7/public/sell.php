<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // query user's portfolio
        $rows =	query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);	
        // create new array to store stock symbols
        $stocks = [];
        
        foreach ($rows as $row)	
        {   
            // save stock symbol
            $stock = $row["symbol"];
            
            // add stock symbol to the new array
            $stocks[] = $stock;       
        }    
        // render sell form
        render("sell_form.php", ["title" => "Sell Form", "stocks" => $stocks]);
    }

    else if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        // set transaction type
        $transaction = 'SELL';
        // lookup stock
        $stock = lookup($_POST["symbol"]);
        
        // lookup user's shares of stock being sold
        $shares = query("SELECT shares FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // calculate total sale value (stock's price * shares)
        $value = $stock["price"] * $shares[0]["shares"];
        
        // add the sale value to cash
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $value, $_SESSION["id"]);
        // delete the stock from their portfolio 
        query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);        
        
        // update history
        $time = date('Y/m/d h:i:s a');
	    
        query("INSERT INTO history (id, transaction, time, symbol, shares, price) VALUES (?, ?, ?, ?, ?, ?)", $_SESSION["id"], $transaction, $time, $_POST["symbol"], $_POST["shares"], $stock["price"]);
            
	// get user's email, send email receipt
	$emailSQL = query("SELECT email FROM users WHERE id = ?", $_SESSION["id"]);
	$email = $emailSQL[0]; // hello, string! goodbye, array!

	$msg = "You have successfully sold {$_POST["shares"]} shares of stock symbol {$_POST["symbol"]} at price {$stock["price"]} for a total sales of {$value}. Thank you for your business!     This is CS50!";

	$msg = wordwrap($msg, 70);

	email($email, "C$50 Financial Sales Receipt", $msg);
         
        redirect("index.php");
    }
?>
