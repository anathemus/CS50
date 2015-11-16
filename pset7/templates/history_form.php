    <ul class="nav nav-pills">
        <li> <form action="index.php"> <input type="submit" value="Portfolio"> </form> </li>
        <li> <form action="quote.php"> <input type="submit" value="Quote"> </form> </li>
        <li> <form action="buy.php"> <input type="submit" value="Buy"> </form> </li>
        <li> <form action="sell.php"> <input type="submit" value="Sell"> </form> </li>
        <li> <form action="history.php"> <input type="submit" value="History"> </form> </li>
        <li> <form action="logout.php"> <input type="submit" value="Log Out"> </form> </li>
    </ul>


<table class="table table-striped">

    <thead>
        <tr>
            <th>Transaction Type</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>


    <tbody>
    <?php
	    foreach ($table as $row)	
        {   
            echo("<tr>");
            echo("<td>" . $row["transaction"] . "</td>");
            echo("<td>" . date('d/m/y, g:i A',strtotime($row["time"])) . "</td>");
            echo("<td>" . $row["symbol"] . "</td>");
            echo("<td>" . $row["shares"] . "</td>");
            echo("<td>$" . number_format($row["price"], 2) . "</td>");
            echo("</tr>");
        }
    ?>

    <tr>
        <td colspan="4">Available Funds</td>
        <td>$<?=number_format($cash[0]["cash"], 2)?></td>
    </tr>

    </tbody>
    
</table>