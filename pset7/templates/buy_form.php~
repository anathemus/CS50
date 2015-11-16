    <ul class="nav nav-pills">
        <li> <form action="index.php"> <input type="submit" value="Portfolio"> </form> </li>
        <li> <form action="quote.php"> <input type="submit" value="Quote"> </form> </li>
        <li> <form action="buy.php"> <input type="submit" value="Buy"> </form> </li>
        <li> <form action="sell.php"> <input type="submit" value="Sell"> </form> </li>
        <li> <form action="history.php"> <input type="submit" value="History"> </form> </li>
        <li> <form action="logout.php"> <input type="submit" value="Log Out"> </form> </li>
    </ul>


<form action="buy.php" method="post">
    <fieldset>
        <div class="control-group">
            <input class="input-medium" name="symbol" placeholder="Symbol" type="text"/>
        </div>
        <div class="control-group">
            <input class="input-small" name="shares" placeholder="Shares" type="text"/>
        </div>
        <div class="control-group">
            <button type="submit" class="btn">Buy</button>
        </div>
	<p></p>
	<tr>
        <td colspan="4"><strong>Available Funds</strong></td>
        <td>$<?=number_format($cash[0]["cash"], 2)?></td>
        </tr>
    </fieldset>
</form>
