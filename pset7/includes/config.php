<?php

    /**
     * config.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Configures pages.
     */

    // display errors, warnings, and notices
    ini_set("display_errors", true);
    error_reporting(E_ALL);

    // requirements
    require("constants.php");
    require("functions.php");
    
    // PHPMailer!
    require_once("libphp-phpmailer/class.phpmailer.php");

    // enable sessions
    session_start();

    // require authentication for all pages except /login.php, /logout.php, and /register.php
    if (!in_array($_SERVER["PHP_SELF"], ["/login.php", "/logout.php", "/register.php"]))
    {
        if (empty($_SESSION["id"]))
        {
            redirect("login.php");
        }
    }

    // needed to call mail fuction
    ini_set('sendmail_from', 'cs50bburgess@gmail.com');

?>
