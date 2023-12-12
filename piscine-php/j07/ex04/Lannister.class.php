<?php


class Lannister
{
    public function sleepWith($familyMember)
    {
        if ($familyMember instanceof Sansa) {
            return "Let's do this.";
        }
        if ($familyMember instanceof Lannister) {
            return "Not even if I'm drunk !";
        }
    }
}