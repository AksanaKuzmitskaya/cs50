<?php

    // configuration
    require("../includes/config.php"); 
    
    // store all user's history 
    $rows = query("SELECT transaction, time, symbol, shares, price FROM history WHERE id = ? order by time DESC", $_SESSION["id"]);
    
    $positions = [];
    
    // goes through each transaction user made
    foreach($rows as $row)
    {    
        $positions[] = [
            "transaction" => $row["transaction"],
            "time" => $row["time"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $row["price"]
        ];
    }
    
    // render portfolio
    render("history_form.php", ["positions" => $positions, "title" => "History"]);

?>
