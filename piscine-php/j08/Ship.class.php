<?php


abstract class Ship
{
    use Movement;

    protected $_name;
    protected $_size = array();
    protected $_img;              // image path for the board
    protected $_hp;               // hull points
    protected $_pp;               // power points
    protected $_speed;
    protected $_extraSpeed;       // extra speed received by spending pp on speed
    protected $_maneuv;
    protected $_shield;
    protected $_weapons = array();
    protected $_isStatic = True;

    public function rightTurn()
    {
    }

    public function leftTurn()
    {
    }

    public function movementMax()
    {
        return $this->_speed + $this->_extraSpeed;
    }




}