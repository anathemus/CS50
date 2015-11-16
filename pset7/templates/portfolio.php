    <ul class="nav nav-pills">
        <li> <form action="index.php"> <input type="submit" value="Portfolio"> </form> </li>
        <li> <form action="quote.php"> <input type="submit" value="Quote"> </form> </li>
        <li> <form action="buy.php"> <input type="submit" value="Buy"> </form> </li>
        <li> <form action="sell.php"> <input type="submit" value="Sell"> </form> </li>
        <li> <form action="history.php"> <input type="submit" value="History"> </form> </li>
        <li> <form action="logout.php"> <input type="submit" value="Log Out"> </form> </li>
    </ul>



    <table class="table table-hover">    
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price Bought</th>
                <th>Price Current</th>
                <th>Total Bought</th>
                <th>Total Current</th>
                <th>Profit / Loss</th>
            </tr>
        </thead>
    <?php foreach ($shares as $share): ?>

        <tbody>
            <tr>
	        <td><?= strtoupper($share["symbol"]) ?></td>
                <td><?= $share["name"] ?></td>
                <td><?= $share["shares"] ?></td>
                <td><?= number_format($share["price_bought"], 2) ?></td>
                <td><?= number_format($share["price_cur"], 2) ?></td>
                <td><?= number_format($share["total_bought"], 2) ?></td>
                <td><?= number_format($share["total_cur"], 2) ?></td>
                <td><?= number_format($share["profit"], 2) ?></td>
            </tr>
        </tbody>
    

    <?php endforeach ?>
    </table>
	<p></p>
	<tr>
        <td colspan="4"><strong>Available Funds</strong></td>
        <td>$<?=number_format($cash[0]["cash"], 2)?></td>
        </tr>
	<p></p>

<a href="logout.php">Log Out</a>
