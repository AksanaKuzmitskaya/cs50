<?php

    // configuration
    require("../includes/config.php");
    
    // if file form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            // inform registrants of their error
            apologize("You must select a stock to sell.");
        }
        else
        {   
            // look for the current price of the stock        
            $stock = lookup($_POST["symbol"]);
            
            // look for number of shares of this stock
            $shares = query("SELECT shares FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], strtoupper($_POST["symbol"]));
            
            // add selling stock to the history
            query("INSERT INTO history (id, transaction, time, symbol, shares, price) VALUES (?, ?, CURRENT_TIMESTAMP, ?, ?, ?)", $_SESSION["id"], "SELL", strtoupper($_POST["symbol"]),  $shares[0]["shares"], $stock["price"]);
                
            // update the cash 
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $stock["price"] * $shares[0]["shares"], $_SESSION["id"]);
            
            // remove that stock from the portfolio  
            query("DELETE FROM portfolios WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
          
            redirect("/");
        }
    }
    else
    {   
        // stores all the symbols user owes   
        $rows = query("SELECT symbol FROM portfolios WHERE id = ?", $_SESSION["id"]);

        // render to sell_form passing symbols user owes
        render("sell_form.php", ["rows" => $rows, "title" => "Sell"]);
            
    }
    
?>
