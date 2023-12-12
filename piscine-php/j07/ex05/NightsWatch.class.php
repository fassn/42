<?php


class NightsWatch
{
    private $_fighters = array();

    public function recruit($character)
    {
        if (method_exists($character, 'fight')) {
            array_push($this->_fighters, $character);
        }
    }

    public function fight()
    {
        foreach ($this->_fighters as $fighter) {
            $fighter->fight();
        }
    }
}