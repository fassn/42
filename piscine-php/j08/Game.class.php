<?php

require_once "Map.class.php";
require_once "Dice.class.php";

class Game
{
    public $dice;
    public $map;

    public function __construct()
    {
        $this->dice = new Dice();
        $this->map = new Map();
    }
}