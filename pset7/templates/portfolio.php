<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>
<table class="table table-striped">
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>

    <tbody>

        <?php foreach ($positions as $position): ?>
        
        <tr>    
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["name"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td><?= "$" . $position["price"] ?></td>
            <td><?= "$" . number_format($position["price"] * $position["shares"], 2)?></td>
        </tr>

        <?php endforeach ?>
    
        <tr>
            <td colspan="4"><strong>CASH</strong></td>
            <?php print("<td>$" . number_format($cash0["cash"], 2) . "</td>")?>
        </tr>
    </tbody>
</table>
