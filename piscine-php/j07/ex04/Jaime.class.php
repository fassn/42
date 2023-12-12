<?php


class Jaime extends Lannister
{
    public function sleepWith($familyMember)
    {
        $sleepWith = parent::sleepWith($familyMember);
        if ($familyMember instanceof Cersei) {
            $sleepWith = "With pleasure, but only in a tower in Winterfell, then.";
        }
        print ($sleepWith . PHP_EOL);
    }
}