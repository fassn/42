<?php


class Map
{
    private $_map;

    public function __construct()
    {
        for ($j = 0; $j < 100; $j++) {
            for ($i = 0; $i < 150; $i++) {
                $this->_map[$j][$i] = $j . ' - ' . $i; //just a draft to identify the cells of the map
            }
        }
    }

    public function getMap() { return $this->_map; }
}