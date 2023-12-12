<?php


class UnholyFactory
{
    private $_absorbed = array();

    public function absorb($fighter)
    {
        if ($fighter instanceof Fighter) {
            if ($fighter->getType() === 'crippled soldier')
                throw new Exception('This soldier is crippled, he can\'t fight!');
            if (!$this->IsAbsorbed($fighter->getType())) {
                $this->_absorbed[] = array('type' => $fighter->getType(), 'class' => get_class($fighter));
                print ("(Factory absorbed a fighter of type " . $fighter->getType() . ")" . PHP_EOL);
            }
            else
                print ("(Factory already absorbed a fighter of type " . $fighter->getType() . ")" . PHP_EOL);
        }
        else
            print ("(Factory can't absorb this, it's not a fighter)" . PHP_EOL);
    }

    public function fabricate($rf)
    {
        if ($class = $this->IsAbsorbed($rf)) {
            print ("(Factory fabricates a fighter of type " . $rf . ")" . PHP_EOL);
            return new $class;
        }
        else
            print ("(Factory hasn't absorbed any fighter of type " . $rf . ")" . PHP_EOL);
    }

    private function IsAbsorbed($rf)
    {
        foreach ($this->_absorbed as $a) {
            if (in_array($rf, $a))
                return $a['class'];
        }
        return False;
    }
}