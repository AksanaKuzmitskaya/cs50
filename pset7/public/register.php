<?php

    // configuration
    require("../includes/config.php");
    
    // if file form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
        {
            // inform registrants of their error
            apologize("Username required.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("Password required.");
        }
        else if (empty($_POST["email"]))
        {
            apologize("Email required.");
        }
        else if (filter_var($_POST["email"], FILTER_VALIDATE_EMAIL) === false)
        {
            apologize("This email address is invalid.");
        }
        else if ($_POST["email"] != $_POST["confirm_email"])
        {
            apologize("Emails do not match.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match.");
        }
        else
        {
            // check if the username exists already in database
            $result = query("INSERT INTO users (username, email, hash, cash) VALUES(?, ?, ?, 10000.00)", $_POST["username"], $_POST["email"], crypt($_POST["password"]));
            if ($result === false)
            {
                apologize("That username appears to be taken.");
            }
            else
            {
                // insert user's information to database
                query("INSERT INTO users (username, email, hash, cash) VALUES(?, ?, ?, 10000.00)", $_POST["username"], $_POST["email"], crypt($_POST["password"]));
                
                // retrieve user's id
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                
                // remember that user's now logged in by storing user's ID in session
                $id = $rows[0]["id"];
                $_SESSION["id"] = $id;

                // redirect to portfolio
                redirect("index.php");
            }
        }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
?>
