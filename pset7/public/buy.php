<?php

    // configuration
    require("../includes/config.php");
    
    // if file form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must specify a number of shares.");
        }
        
        // make sure that user buys whole shares, not fractions
        else if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            apologize("Invalid number of shares.");
        }
        else
        {   
            // find current price of the stock        
            $stock = lookup($_POST["symbol"]);
            
            // ensure the stock is valid
            if ($stock === false)
            {
                apologize("Symbol not found.");
            }
            else
            {
                // find how much cash user has
                $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            
                // check if the user can afford to buy this stock
                if ($_POST["shares"] * $stock["price"] > $cash[0]["cash"])
                {
                    apologize("You can't afford that.");
                }
                else
                {
                    // add stock to the portfolio
                    query("INSERT INTO portfolios (id, symbol, shares) VALUES (?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + ?", $_SESSION["id"], strtoupper($_POST["symbol"]),  $_POST["shares"],  $_POST["shares"]);
                
                    // add buying stock to the history
                    query("INSERT INTO history (id, transaction, time, symbol, shares, price) VALUES (?, ?, CURRENT_TIMESTAMP, ?, ?, ?)", $_SESSION["id"], "BUY", strtoupper($_POST["symbol"]),  $_POST["shares"], $stock["price"]);
                
                    // update cash 
                    query("UPDATE users SET cash = cash - ? WHERE id = ?", $_POST["shares"] * $stock["price"], $_SESSION["id"]); 
                    
                    // redirects to the user's portfolio 
                    redirect("/");
                }
            }   
        }
    }
    else
    {      
        render("buy_form.php", ["title" => "Buy"]);            
    }
    
?>
