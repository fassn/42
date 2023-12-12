<?php


class Targaryen
{
    public function getBurned()
    {
        if (static::resistsFire())
            return "emerges naked but unharmed";
        else
            return "burns alive";
    }

    public function resistsFire()
    {}
}