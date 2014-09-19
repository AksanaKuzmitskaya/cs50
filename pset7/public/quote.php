<?php

    // configuration
    require("../includes/config.php");
    
    // if file form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            // inform registrants of their error
            apologize("You must provide a symbol.");
        }
        else
        {   
            // check if the stock exists 
            $stock = lookup($_POST["symbol"]);
            
            // ensure the stock is valid
            if ($stock === false)
            {
                apologize("Symbol not found.");
            }
            else
            {
                render("quote.php", ["stock" => $stock, "title" => "Quote"]);
            }
        }
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }
?>
