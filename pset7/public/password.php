<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username_email"]))
        {
            apologize("You must provide your username or email address.");
        }

        // query database for user
        $rows = query("SELECT email, username FROM users WHERE username = ? OR email = ?", $_POST["username_email"], $_POST["username_email"]);

        // if we found user, update password
        if (count($rows) == 1)
        {
            // random 32 characters password 
            $rand_password = md5(uniqid(rand()));
            
            // new user's password 8 characters 
            $new_password = substr($rand_password, 0, 8);
            
            // update user's password 
            query("UPDATE users SET hash = ? WHERE username = ? OR email = ?", crypt($new_password), $_POST["username_email"], $_POST["username_email"]);
            
            require_once("PHPMailer/class.phpmailer.php");
            
            // instantiate mailer
            $mail = new PHPMailer();
            $mail->IsSMTP();
            
            //required for gmail
            $mail->SMTPAuth   = true;
            $mail->Host = "smtp.gmail.com";
            
            // login to gmail
            $mail->Username   = "help.cs50finance@gmail.com";
            
            // password to gmail
            $mail->Password   = "passwordhelp";
            
            //required for gmail
            $mail->SMTPSecure = "tls"; 
            $mail->Port = 587;
            
            // set From:
            $mail->SetFrom("kkssiiuu@gmail.com");
            
            // set To:
            $mail->AddAddress($rows[0]["email"]);

            // set Subject:
            $mail->Subject = "Reset your password";

            // set body
            $mail->Body = "<html> 
                               <body>
                                   <h2>Hello!</h2>
                                   <p>Your new password is: {$new_password}</p>
                                   <p>Your username is: {$rows[0]["username"]}.</p>
                                   <p>If you didn't request a password reset, feel free to delete this email!</p>
                                   <p>All the best,</p>
                                   <p>The C$50 Finance Team</p>
                               </body>                            
                           </html>";

            // set alternative body, in case user's mail client doesn't support HTML
            $mail->AltBody = "    Hello!\n\nYour new password is: {$new_password}\n\nYour username is: {$rows[0]["username"]}.
                             \nIf you didn't request a password reset, feel free to delete this email!\n\nAll the best,\n\nThe C$50 Finance Team";

            // send mail
            if ($mail->Send() === false)
            die($mail->ErrorInfo . "\n");
            
            // render form
            render("passwordSent_form.php", ["title" => "Password sent"]);  
        }
        else
        {
            // else apologize
            apologize("Invalid username or email address");
        }
    }
    else
    {
        // else render form
        render("password_form.php", ["title" => "Password Reset"]);
    }

?>
