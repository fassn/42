<?php


class Color
{
    public static $verbose = False;

    public $red;
    public $green;
    public $blue;

    public function __construct(array $array)
    {
        if (array_key_exists('rgb', $array) && (array_key_exists('red', $array) || array_key_exists('green', $array) || array_key_exists('blue', $array)))
            throw new Exception("Use 'rgb' or 'red', 'green' and 'blue'. Not both!");
        if (array_key_exists('rgb', $array)) {
            $int = filter_var($array['rgb'], FILTER_VALIDATE_INT, FILTER_FLAG_ALLOW_HEX);
            $this->red = $int >> 16 & 255;
            $this->green = ($int >> 8) & 255;
            $this->blue = $int & 255;
        }
        elseif (array_key_exists('red', $array) && array_key_exists('green', $array) && array_key_exists('blue', $array)) {
            $this->red = intval($array['red']);
            $this->green = intval($array['green']);
            $this->blue = intval($array['blue']);
        }
        else
            throw new Exception("Use 'rgb' or 'red', 'green' and 'blue' keys to instantiate a Color class.");

        if (Color::$verbose === True) {
            printf("Color( red: %3d, green: %3d, blue: %3d ) constructed." . PHP_EOL, $this->red, $this->green, $this->blue);
        }
    }

    public function __destruct()
    {
        if (Color::$verbose === True) {
            printf("Color( red: %3d, green: %3d, blue: %3d ) destructed." . PHP_EOL, $this->red, $this->green, $this->blue);
        }
    }

    public function __toString()
    {
        return sprintf("Color( red: %3d, green: %3d, blue: %3d )", $this->red, $this->green, $this->blue);
    }

    static function doc()
    {
        return file_get_contents(get_called_class() . '.doc.txt');
    }

    public function add( Color $rhs )
    {
        return (new Color(array(
            'red' => $this->red + $rhs->red,
            'green' => $this->green + $rhs->green,
            'blue' => $this->blue + $rhs->blue)
        )
        );
    }

    public function sub( Color $rhs )
    {
        return (new Color(array(
                'red' => $this->red - $rhs->red,
                'green' => $this->green - $rhs->green,
                'blue' => $this->blue - $rhs->blue)
        )
        );
    }

    public function mult( $f )
    {
        return (new Color(array(
                'red' => $this->red * $f,
                'green' => $this->green * $f,
                'blue' => $this->blue * $f)
        )
        );
    }
}