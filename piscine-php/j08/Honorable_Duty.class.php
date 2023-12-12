<?php

require_once "Ship.class.php";

class Honorable_Duty extends Ship
{
    public function __construct()
    {
        $this->_name = "Honorable Duty";
        $this->_size = 2;
        $this->_hp = 5;
        $this->_pp = 10;
        $this->_speed = 15;
        $this->_maneuv = 4;
        $this->_shield = 0;
        $this->_weapons = array("Laser battery");
    }
}