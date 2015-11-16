<h1>
	<?=// Displays Price
	"$".number_format($stock["price"],2)?>
</h1>
<h4>
	<?=// Displays Stock Name
	$stock["name"]?>
</h4>
<h4>
	<?=// Displays Stock Symbol
	$sy = strtoupper($stock["symbol"])?>
</h4>

<img style="-webkit-user-select: none" src="http://chart.finance.yahoo.com/z?s=<?=$sy?>"
