<?php


class Matrix
{
    const IDENTITY = 0;
    const SCALE = 1;
    const RX = 20;
    const RY = 21;
    const RZ = 22;
    const TRANSLATION = 3;
    const PROJECTION = 4;

    static public $verbose = False;

    private $_preset;
    private $_matrix = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
    ];

    public function __construct($array = Null)
    {
        if (isset($array)) {
            if (array_key_exists('preset', $array)) {
                $this->_preset = $array['preset'];
                switch ($this->_preset) {
                    case self::IDENTITY:
                        $this->_matrix[0][0] = 1;
                        $this->_matrix[1][1] = 1;
                        $this->_matrix[2][2] = 1;
                        $this->_matrix[3][3] = 1;
                        break;
                    case self::SCALE:
                        if (array_key_exists('scale', $array)) {
                            $this->_matrix[0][0] = $array['scale'];
                            $this->_matrix[1][1] = $array['scale'];
                            $this->_matrix[2][2] = $array['scale'];
                            $this->_matrix[3][3] = 1;
                        }
                        else
                            throw new Exception("Use 'scale' mandatory key along when 'preset' => IDENTITY to instantiate a Matrix class.");
                        break;
                    case self::RX:
                        if (array_key_exists('angle', $array)) {
                            $this->_matrix[0][0] = 1;
                            $this->_matrix[1][1] = cos($array['angle']);
                            $this->_matrix[1][2] = -sin($array['angle']);
                            $this->_matrix[2][1] = sin($array['angle']);
                            $this->_matrix[2][2] = cos($array['angle']);
                            $this->_matrix[3][3] = 1;
                        }
                        else
                            throw new Exception("Use 'angle' mandatory key along when 'preset' => RX or RY or RZ to instantiate a Matrix class.");
                        break;
                    case self::RY:
                        if (array_key_exists('angle', $array)) {
                            $this->_matrix[0][0] = cos($array['angle']);
                            $this->_matrix[0][2] = sin($array['angle']);
                            $this->_matrix[1][1] = 1;
                            $this->_matrix[2][0] = -sin($array['angle']);
                            $this->_matrix[2][2] = cos($array['angle']);
                            $this->_matrix[3][3] = 1;
                        }
                        else
                            throw new Exception("Use 'angle' mandatory key along when 'preset' => RX or RY or RZ to instantiate a Matrix class.");
                        break;
                    case self::RZ:
                        if (array_key_exists('angle', $array)) {
                            $this->_matrix[0][0] = cos($array['angle']);
                            $this->_matrix[0][1] = -sin($array['angle']);
                            $this->_matrix[1][0] = sin($array['angle']);
                            $this->_matrix[1][1] = cos($array['angle']);
                            $this->_matrix[2][2] = 1;
                            $this->_matrix[3][3] = 1;
                        }
                        else
                            throw new Exception("Use 'angle' mandatory key along when 'preset' => RX or RY or RZ to instantiate a Matrix class.");
                        break;
                    case self::TRANSLATION:
                        if (array_key_exists('vtc', $array)) {
                            if ($array['vtc'] instanceof Vector) {
                                $this->_matrix[0][0] = 1;
                                $this->_matrix[0][3] = $array['vtc']->getX();
                                $this->_matrix[1][1] = 1;
                                $this->_matrix[1][3] = $array['vtc']->getY();
                                $this->_matrix[2][2] = 1;
                                $this->_matrix[2][3] = $array['vtc']->getZ();
                                $this->_matrix[3][3] = 1;
                            }
                            else
                                throw new Exception("'vtc' is not a Vector object. Please pass a Vector object to the 'vtc' key.");
                        }
                        else
                            throw new Exception("Use 'vtc' mandatory key along when 'preset' => TRANSLATION to instantiate a Matrix class.");
                        break;
                    case self::PROJECTION:
                        if (array_key_exists('fov', $array) && array_key_exists('ratio', $array) && array_key_exists('near', $array) && array_key_exists('far', $array)) {
                            $tmp = 1 / tan(0.5 * deg2rad($array['fov']));
                            $this->_matrix[0][0] = $tmp / $array['ratio'];
                            $this->_matrix[1][1] = $tmp;
                            $this->_matrix[2][2] = -1 * (-$array['near'] - $array['far']) / ($array['near'] - $array['far']);
                            $this->_matrix[2][3] = (2 * $array['near'] * $array['far']) / ($array['near'] - $array['far']);
                            $this->_matrix[3][2] = -1;
                        }
                        else
                            throw new Exception("Use 'fov', 'ratio', 'near', 'far mandatory keys along when 'preset' => PROJECTION to instantiate a Matrix class.");
                        break;
                }
            }
            else
                throw new Exception("Use 'preset' mandatory key to instantiate a Matrix class.");

            if (Matrix::$verbose) {
                switch ($this->getPreset()) {
                    case self::IDENTITY:
                        print ("Matrix IDENTITY instance constructed" . PHP_EOL);
                        break;
                    case self::SCALE:
                        print("Matrix SCALE preset instance constructed" . PHP_EOL);
                        break;
                    case self::RX:
                        print("Matrix Ox ROTATION preset instance constructed" . PHP_EOL);
                        break;
                    case self::RY:
                        print("Matrix Oy ROTATION preset instance constructed" . PHP_EOL);
                        break;
                    case self::RZ:
                        print("Matrix Oz ROTATION preset instance constructed" . PHP_EOL);
                        break;
                    case self::TRANSLATION:
                        print("Matrix TRANSLATION preset instance constructed" . PHP_EOL);
                        break;
                    case self::PROJECTION:
                        print("Matrix PROJECTION preset instance constructed" . PHP_EOL);
                }
            }
        }
    }

    public function __destruct()
    {
        if (Matrix::$verbose)
            print("Matrix instance destructed" . PHP_EOL);
    }

    public function __toString()
    {
        return sprintf("M | vtcX | vtcY | vtcZ | vtxO" . PHP_EOL .
            "-----------------------------" . PHP_EOL .
            "x | %.2f | %.2f | %.2f | %.2f" . PHP_EOL .
            "y | %.2f | %.2f | %.2f | %.2f" . PHP_EOL .
            "z | %.2f | %.2f | %.2f | %.2f" . PHP_EOL .
            "w | %.2f | %.2f | %.2f | %.2f",
            $this->_matrix[0][0], $this->_matrix[0][1], $this->_matrix[0][2], $this->_matrix[0][3],
            $this->_matrix[1][0], $this->_matrix[1][1], $this->_matrix[1][2], $this->_matrix[1][3],
            $this->_matrix[2][0], $this->_matrix[2][1], $this->_matrix[2][2], $this->_matrix[2][3],
            $this->_matrix[3][0], $this->_matrix[3][1], $this->_matrix[3][2], $this->_matrix[3][3]);
    }

    public function getPreset() { return $this->_preset; }

    static public function doc()
    {
        return file_get_contents(get_called_class() . '.doc.txt');
    }

    public function getMatrix() { return $this->_matrix; }

    public function mult( Matrix $rhs )
    {
        $mult = [];
        for ($i = 0; $i < count($this->_matrix); $i++)
        {
            $mult[$i] = [];
            for ($j = 0; $j < count($this->_matrix[$i]); $j++)
            {
                $el = 0;
                for ($k = 0; $k < count($rhs->getMatrix()); $k++) {
                    $el += $this->_matrix[$i][$k] * $rhs->getMatrix()[$k][$j];
                }
                $mult[$i][$j] = $el;
            }
        }
        $matrix = new Matrix();
        $matrix->_matrix = $mult;
        return $matrix;
    }

    public function transformVertex( Vertex $vtx )
    {
        $matrix = $this->getMatrix();
        $x = ($vtx->getX() * $matrix[0][0]) + ($vtx->getY() * $matrix[0][1]) + ($vtx->getZ() * $matrix[2][2]) + ($vtx->getW() * $matrix[0][3]);
        $y = ($vtx->getX() * $matrix[1][0]) + ($vtx->getY() * $matrix[1][1]) + ($vtx->getZ() * $matrix[1][2]) + ($vtx->getW() * $matrix[1][3]);
        $z = ($vtx->getX() * $matrix[2][0]) + ($vtx->getY() * $matrix[2][1]) + ($vtx->getZ() * $matrix[2][2]) + ($vtx->getW() * $matrix[2][3]);
        $w = ($vtx->getX() * $matrix[2][3]) + ($vtx->getY() * $matrix[3][0]) + ($vtx->getZ() * $matrix[3][2]) + ($vtx->getW() * $matrix[3][3]);
        $color = $vtx->getColor();
        $vertex = new Vertex(array('x' => $x, 'y' => $y, 'z' => $z, 'w' => $w, 'color' => $color));
        return $vertex;
    }
}