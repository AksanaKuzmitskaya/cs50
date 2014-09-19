<?php

    // configuration
    require("../includes/config.php"); 
    
    // retrieve user's symbols and numbers of shares
    $rows = query("SELECT symbol, shares FROM portfolios WHERE id = ?", $_SESSION["id"]);
    
    // array to store the values 
    $positions = [];
    
    // go through each stock user owns
    foreach($rows as $row)
    {
        // store at Yahoo Finance name and price of the stock
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    
    // query database for user to find how much cash he owns
    $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash0 = $cash[0];
    
    // render portfolio
   render("portfolio.php", ["cash0" => $cash0, "positions" => $positions, "title" => "Portfolio"]);

?>
