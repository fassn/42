<?php


class Vector
{
    public static $verbose = False;

    private $_x;
    private $_y;
    private $_z;
    private $_w = 0;

    public function __construct(array $array)
    {
        if (array_key_exists('dest', $array)) {
            if (array_key_exists('orig', $array))
                $orig = new Vertex(array('x' => $array['orig']->getX(), 'y' => $array['orig']->getY(), 'z' => $array['orig']->getZ()));
            else
                $orig = new Vertex(array('x' => 0, 'y' => 0, 'z' => 0));
            $this->_x = $array['dest']->getX() - $orig->getX();
            $this->_y = $array['dest']->getY() - $orig->getY();
            $this->_z = $array['dest']->getZ() - $orig->getZ();
        }
        else
            throw new Exception("Use 'dest' mandatory key to instantiate a Vector class.");
        if (Vector::$verbose === True) {
            printf ("Vector( x:%.2f, y:%.2f, z:%.2f, w:%.2f ) constructed" . PHP_EOL, $this->_x, $this->_y, $this->_z, $this->_w);
        }
    }

    public function __destruct()
    {
        if (Vector::$verbose === True) {
            printf ("Vector( x:%.2f, y:%.2f, z:%.2f, w:%.2f ) destructed" . PHP_EOL, $this->_x, $this->_y, $this->_z, $this->_w);
        }
    }

    public function getX() { return $this->_x ; }
    public function getY() { return $this->_y ; }
    public function getZ() { return $this->_z ; }
    public function getW() { return $this->_w ; }

    public function __toString()
    {
        return sprintf ("Vector( x:%.2f, y:%.2f, z:%.2f, w:%.2f )", $this->_x, $this->_y, $this->_z, $this->_w);
    }

    static public function doc()
    {
        return file_get_contents(get_called_class() . '.doc.txt');
    }

    public function magnitude()
    {
        return sqrt(pow($this->getX(), 2) + pow($this->getY(), 2) + pow($this->getZ(), 2));
    }

    public function normalize()
    {
        $magn = $this->magnitude();
        return new Vector(array('dest' => new Vertex(array(
            'x' => $this->getX() / $magn,
            'y' => $this->getY() / $magn,
            'z' => $this->getZ() / $magn)
        )));
    }

    public function add ( Vector $rhs )
    {
        return new Vector(array('dest' => new Vertex(array(
            'x' => $this->getX() + $rhs->getX(),
            'y' => $this->getY() + $rhs->getY(),
            'z' => $this->getZ() + $rhs->getZ()
        ))));
    }

    public function sub ( Vector $rhs )
    {
        return new Vector(array('dest' => new Vertex(array(
            'x' => $this->getX() - $rhs->getX(),
            'y' => $this->getY() - $rhs->getY(),
            'z' => $this->getZ() - $rhs->getZ()
        ))));
    }

    public function opposite()
    {
        return new Vector(array('dest' => new Vertex(array(
            'x' => -$this->getX(),
            'y' => -$this->getY(),
            'z' => -$this->getZ()
        ))));
    }

    public function scalarProduct ( $k )
    {
        return new Vector(array('dest' => new Vertex(array(
            'x' => $this->getX() * $k,
            'y' => $this->getY() * $k,
            'z' => $this->getZ() * $k
        ))));
    }

    public function dotProduct ( Vector $rhs )
    {
        return $this->getX() * $rhs->getX() + $this->getY() * $rhs->getY() + $this->getZ() * $rhs->getZ();
    }

    public function cos( Vector $rhs )
    {
        return $this->dotProduct($rhs) / ($this->magnitude() * $rhs->magnitude());
    }

    public function crossProduct( Vector $rhs )
    {
        return new Vector(array('dest' => new Vertex(array(
            'x' => $this->getY() * $rhs->getZ() - $this->getZ() * $rhs->getY(),
            'y' => $this->getZ() * $rhs->getX() - $this->getX() * $rhs->getZ(),
            'z' => $this->getX() * $rhs->getY() - $this->getY() * $rhs->getX()
    ))));
    }
}