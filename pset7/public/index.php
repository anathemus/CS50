<?php
    // configuration
    require("../includes/config.php");
    
    // check user's shares
    $rows = query("SELECT symbol, shares, price FROM portfolio WHERE id = ?", $_SESSION["id"]);

    // check user's cash
    $cash =	query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    
    // bundle it all into shares array.
    $shares = [];
    
    foreach($rows as $row)
    {
        // Yahoooooooooooooo-oo!
        $stock = lookup($row["symbol"]);
        
        if ($stock !== false)
        {
            $shares[] = [
                "symbol"    => $row["symbol"]
                ,"name"     => $stock["name"]
                ,"shares"   => $row["shares"]
                ,"price_bought" => $row["price"]
                ,"price_cur"    => $stock["price"]
                ,"total_bought" => $row["shares"] * $row["price"]
                ,"total_cur"    => $row["shares"] * $stock["price"]
                ,"profit"   => $row["shares"] * $stock["price"] - $row["shares"] * $row["price"]       
            ];
        }
    }


    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "shares" => $shares, "cash" => $cash]);
?>
