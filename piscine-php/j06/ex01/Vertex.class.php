<?php

require_once ('../ex00/Color.class.php');

class Vertex
{
    public static $verbose = False;

    private $_x;
    private $_y;
    private $_z;
    private $_w = 1.0;
    private $_color;

    public function __construct(array $array)
    {
        if (array_key_exists('x', $array) && array_key_exists('y', $array) && array_key_exists('z', $array)) {
            if (array_key_exists('color', $array))
                $this->setColor($array['color']);
            else
                $this->setColor(new Color(array('red' => 255, 'green' => 255, 'blue' => 255)));
            if (array_key_exists('w', $array))
                $this->setW($array['w']);
            $this->setX($array['x']);
            $this->setY($array['y']);
            $this->setZ($array['z']);
        }
        else
            throw new Exception("Use 'x', 'y' and 'z' mandatory keys to instantiate a Vertex class.");

        if (Vertex::$verbose === True) {
            printf ("Vertex( x: %.2f, y: %.2f, z:%.2f, w:%.2f, %s ) constructed" . PHP_EOL, $this->_x, $this->_y, $this->_z, $this->_w, $this->_color);
        }
    }

    public function __destruct()
    {
        if (Vertex::$verbose === True) {
            printf ("Vertex( x: %.2f, y: %.2f, z:%.2f, w:%.2f, %s ) destructed" . PHP_EOL, $this->_x, $this->_y, $this->_z, $this->_w, $this->_color);
        }
    }

    public function __toString()
    {
        $toString = sprintf ("Vertex( x: %.2f, y: %.2f, z:%.2f, w:%.2f", $this->_x, $this->_y, $this->_z, $this->_w);

        if (Vertex::$verbose === True)
            $toString = $toString . ", " . $this->_color . " )";
        else
            $toString = $toString . " )";
        return $toString;
    }

    public function getX() { return $this->_x; }
    public function getY() { return $this->_y; }
    public function getZ() { return $this->_z; }
    public function getW() { return $this->_w; }
    public function getColor() { return $this->_color; }

    public function setX($value) { $this->_x = $value; }
    public function setY($value) { $this->_y = $value; }
    public function setZ($value) { $this->_z = $value; }
    public function setW($value) { $this->_w = $value; }
    public function setColor(Color $value) { $this->_color = $value; }

    static public function doc()
    {
        return file_get_contents(get_called_class() . '.doc.txt');
    }
}