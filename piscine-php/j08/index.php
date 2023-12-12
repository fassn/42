<?php

require_once "Game.class.php";

$game = new Game;

?>

<html>
<head>
    <link type="text/css" rel="stylesheet" href="css/index.css">
</head>
<body>
    <div id="board">
        <?php
            for ($j = 0; $j < 100; $j++) {
                for ($i = 0; $i < 150; $i++) {?>
                    <div class="cell"><?php echo $game->map->getMap()[$j][$i] ?></div>
                <?php }
            }
        ?>
    </div>
</body>
</html>