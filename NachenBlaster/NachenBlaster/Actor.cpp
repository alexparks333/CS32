#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(StudentWorld * world, int imageID, double startX, double startY, int dir, double size, int depth, bool isAlive):
    GraphObject(imageID, startX, startY, dir, size, depth), isActorAlive(isAlive), world(world)
{
}

bool Actor::isAlien() const
{
    return false;
}

bool Actor::getState() const
{
    return isActorAlive;
}

void Actor::setState(bool state)
{
    isActorAlive = state;
}

StudentWorld * Actor::getWorld() const
{
    return world;
}

Star::Star(StudentWorld * world, double startX, double startY):
    Actor(world, IID_STAR, startX, startY, 0, .06, 3)
{
    setSize(((randInt(500, 5000))/10000.0));
}

void Star::doSomething()
{
    moveTo(getX()-1, getY());
    if(getX() <= -1)
        setState(false);
}

Explosion::Explosion(StudentWorld * world, double startX, double startY):
Actor(world, IID_EXPLOSION, startX, startY, 0, 1), numOfTicks(0)
{
}

void Explosion::doSomething()
{
    if(numOfTicks == 4)
    {
        setState(false);
        return;
    }
    
    setSize(1.5*getSize());
    numOfTicks++;
}

Character::Character(int ammoCount, int torpedoCount, int hp):
hp(hp), ammoCount(ammoCount), torpedoCount(torpedoCount)
{
}

void Character::incTorpedoCount(int num)
{
    torpedoCount += num;
}

int Character::getTorpedoCount() const
{
    return torpedoCount;
}

void Character::setAmmoCount(int num)
{
    ammoCount = num;
}

int Character::getAmmoCount() const
{
    return ammoCount;
}

int Character::getHP() const
{
    return hp;
}

void Character::setHP(int hP)
{
    hp = hP;
}

void Character::fire(Projectile  * projectile, int type) const
{
    StudentWorld * world = projectile->getWorld();
    world->addActor(projectile);
    
    switch (type)
    {
        case CABBAGE:
            world->playSound(SOUND_PLAYER_SHOOT);
            break;
        case TURNIP:
            world->playSound(SOUND_ALIEN_SHOOT);
            break;
        case TORPEDO:
            world->playSound(SOUND_TORPEDO);
            break;
    }
}

void Character::damageCharacter(int damage)
{
    setHP(getHP() - damage);
}

NachenBlaster::NachenBlaster(StudentWorld * world):
Actor(world, IID_NACHENBLASTER, 0, 128), Character(30, 0, 50)
{
}

void NachenBlaster::doSomething()
{
    if(!getState())
        return;
    
    int key = 0;
    if(getWorld()->getKey(key))
    {
        switch (key)
        {
            case KEY_PRESS_SPACE:
                if(getAmmoCount() >= 5)
                {
                    fire(new Cabbage(getWorld(), getX() + 12, getY()), CABBAGE);
                    setAmmoCount(getAmmoCount() - 5);
                }
                break;
                
            case KEY_PRESS_TAB:
                if(getTorpedoCount() >= 1)
                {
                    fire(new FlatulenceTorpedo(getWorld(), getX() + 12, getY(), false), TORPEDO);
                    incTorpedoCount(-1);
                }
                break;
                
            case KEY_PRESS_LEFT:
                moveX(NEG_MOVEMENT);
                break;
                
            case KEY_PRESS_RIGHT:
                moveX(POS_MOVEMENT);
                break;
                
            case KEY_PRESS_UP:
                moveY(POS_MOVEMENT);
                break;
                
            case KEY_PRESS_DOWN:
                moveY(NEG_MOVEMENT);
                break;
        }
    }
    if(getAmmoCount() < 30) setAmmoCount(getAmmoCount() + 1);
}

void NachenBlaster::moveX(int movement)
{
    if(getX() + movement < VIEW_WIDTH && getX() + movement >= 0)
        moveTo(getX() + movement, getY());
}

void NachenBlaster::moveY(int movement)
{
    if(getY() + movement < VIEW_HEIGHT && getY() + movement >= 0)
        moveTo(getX(), getY() + movement);
}

int NachenBlaster::getAmmoPercentage()
{
    return 100*(getAmmoCount()/30.0);
}

int NachenBlaster::getHPPercentage()
{
    return 100*(getHP()/50.0);
}

void NachenBlaster::damageCharacter(int damage, int cause)
{
    Character::damageCharacter(damage);
    if(getHP() <= 0)
        setState(false);
    
    switch (cause)
    {
        case HIT_BY_PROJECTILE:
            if(getState())
                getWorld()->playSound(SOUND_BLAST);
            break;
            
        case HIT_BY_CHARACTER:
            getWorld()->playSound(SOUND_DEATH);
            break;
    }
}

Alien::Alien(StudentWorld * world, int imageID, int startX, int startY, int hp, double flightSpeed, int hpReduce, int pointIncrease):
    FloatingObject(world, imageID, startX, startY), Character(0, 0, hp), flightSpeed(flightSpeed), hpReduce(hpReduce), pointIncrease(pointIncrease), flightPlan(0)
{
    setSize(1.5);
}

void Alien::doSpecialSomething()
{
    if(isNewPlanNeeded())
        selectNewPlan();
    
    if(getWorld()->isNachenInLineOfFire(this))
    {
        if(attack())
            return;
    }
    
    move();
}

bool Alien::checkForCollision()
{
    NachenBlaster * player = getWorld()->getCollidingPlayer(this);
    
    if(player != nullptr)
    {
        player->damageCharacter(hpReduce, HIT_BY_CHARACTER);
        die();
        return true;
    }

    return false;
}

void Alien::move()
{
    switch(flightDirection)
    {
        case DOWNLEFT:
            if(getY() - flightSpeed <= 0)
            {
                moveTo(getX() - flightSpeed, 0);
                break;
            }
            moveTo(getX() - flightSpeed, getY() - flightSpeed); break;
        case UPLEFT:
            if(getY() + flightSpeed >= VIEW_HEIGHT - 1)
            {
                moveTo(getX() - flightSpeed, VIEW_HEIGHT-1);
                break;
            }
            moveTo(getX() - flightSpeed, getY() + flightSpeed); break;
        case LEFT:
            moveTo(getX() - flightSpeed, getY()); break;
    }
    flightPlan--;
}

bool Alien::isAlien() const
{
    return true;
}

bool Alien::attack()
{
    int rand = randInt(1, (20/getWorld()->getLevel()) + 5);
    if(rand == 1)
    {
        fire(new Turnip(getWorld(), getX() - 14, getY()), TURNIP);
        return true;
    }
    return false;
}

bool Alien::isNewPlanNeeded() const
{
    if(flightPlan == 0 || getY() >= VIEW_HEIGHT - 1 || getY() <= 0)
        return true;
    return false;
}

void Alien::selectNewPlan()
{
    if(getY() >= VIEW_HEIGHT - 1)
        flightDirection = DOWNLEFT;
    if(getY() <= 0)
        flightDirection = UPLEFT;
    else if(flightPlan == 0)
    {
        int rand = randInt(1, 3);
        if(rand == 1)
            flightDirection = DOWNLEFT;
        else if(rand == 2)
            flightDirection = UPLEFT;
        else
            flightDirection = LEFT;
        flightPlan = randInt(1, 32);
    }
}

void Alien::setFlightSpeed(double speed)
{
    flightSpeed = speed;
}

void Alien::setFlightDirection(int direction)
{
    flightDirection = direction;
}

void Alien::setFlightPlanLength(int length)
{
    flightPlan = length;
}

void Alien::die()
{
    setState(false);
    getWorld()->playSound(SOUND_DEATH);
    getWorld()->increaseScore(pointIncrease);
    getWorld()->addActor(new Explosion(getWorld(), getX(), getY()));
    getWorld()->recordAlienDying();
    dropGoodie();
}

void Alien::damageCharacter(int damage, int cause)
{
    Character::damageCharacter(damage);
    
    switch (cause)
    {
        case HIT_BY_PROJECTILE:
            if(getHP() <= 0)
                die();
            else
                getWorld()->playSound(SOUND_BLAST);
            break;
            
        case HIT_BY_CHARACTER:
            die();
            break;
    }
}

void Alien::dropGoodie()
{
    
}

Smallgon::Smallgon(StudentWorld * world, int startX, int startY):
    Alien(world, IID_SMALLGON, startX, startY, 0, 2.0, 5, 250)
{
    setHP(5 * ( 1 + 0.1 * (getWorld()->getLevel() - 1 )));
}

Smoregon::Smoregon(StudentWorld * world, int startX, int startY):
    Alien(world, IID_SMOREGON, startX, startY, 0, 2.0, 5, 250)
{
    setHP(5 * ( 1 + 0.1 * (getWorld()->getLevel() - 1 )));
}

bool Smoregon::attack()
{
    if(Alien::attack())
        return true;

    int rand = randInt(1, 20/getWorld()->getLevel() + 5);
    if(rand == 2)
    {
        setFlightDirection(LEFT);
        setFlightPlanLength(VIEW_WIDTH);
        setFlightSpeed(5);
    }

    return false;
}

void Smoregon::dropGoodie()
{
    int rand = randInt(1,3);
    
    if(rand == 2)
    {
        rand = randInt(3, 4);
        if(rand == 3)
            getWorld()->addActor(new RepairGoodie(getWorld(), getX(), getY()));
        
        else if(rand == 4)
            getWorld()->addActor(new FlatulenceTorpedoGoodie(getWorld(), getX(), getY()));
    }
}

Snagglegon::Snagglegon(StudentWorld * world, int startX, int startY):
Alien(world, IID_SNAGGLEGON, startX, startY, 0, 1.75, 15, 1000)
{
    setHP(10*(1 + (getWorld()->getLevel() - 1)*0.1));
    setFlightDirection(DOWNLEFT);
}

void Snagglegon::selectNewPlan()
{
    if(getY() >= VIEW_HEIGHT - 1)
        setFlightDirection(DOWNLEFT);
    if(getY() <= 0)
        setFlightDirection(UPLEFT);
}

bool Snagglegon::attack()
{
    int rand = randInt(1,(15/getWorld()->getLevel() + 10));
    if(rand == 2)
    {
        fire(new FlatulenceTorpedo(getWorld(), getX() - 14, getY(), true), TORPEDO);
        return true;
    }
    return false;
}

void Snagglegon::dropGoodie()
{
    int rand = randInt(1, 6);
    
    if(rand == 2)
        getWorld()->addActor(new ExtraLifeGoodie(getWorld(), getX(), getY()));
}

FloatingObject::FloatingObject(StudentWorld * world, int imageID, double startX, double startY, int dir):
    Actor(world, imageID, startX, startY, dir, 0.5, 1)
{
    
}

void FloatingObject::doSomething()
{
    if(!getState())
        return;
    
    if(checkOffScreen())
    {
        setState(false);
        return;
    }
    
    if(checkForCollision())
        return;
    
    doSpecialSomething();
    checkForCollision();
}

bool FloatingObject::checkOffScreen() const
{
    if(getX() < 0 || getY() < 0)
        return true;
    return false;
}

Projectile::Projectile(StudentWorld * world, int imageID, double startX, double startY, int damage, bool shotByVillain, int movement, int dir):
    FloatingObject(world, imageID, startX, startY, dir), damage(damage), shotByVillain(shotByVillain), movement(movement)
{
    
}

void Projectile::doSpecialSomething()
{
    moveTo(getX() + movement, getY());
    setDirection(20 + getDirection());
}

bool Projectile::checkOffScreen() const
{
    if(shotByVillain)
    {
        if(getX() < 0)
            return true;
    }
    
    else
    {
        if(getX() >= VIEW_WIDTH)
            return true;
    }
    
    return false;
}

void Projectile::setMovement(int movement)
{
    this->movement = movement;
}

int Projectile::getDamage() const
{
    return damage;
}

bool Projectile::checkForCollision()
{
    if(shotByVillain)
    {
        NachenBlaster * player = getWorld()->getCollidingPlayer(this);
    
        if(player != nullptr)
        {
            player->damageCharacter(getDamage(), HIT_BY_PROJECTILE);
            setState(false);
            return true;
        }
    }
    
    if(!shotByVillain)
    {
        Alien * alien = getWorld()->getOneCollidingAlien(this);
        
        if(alien != nullptr)
        {
            alien->damageCharacter(getDamage(), HIT_BY_PROJECTILE);
            setState(false);
            return true;
        }
    }
    
    return false;
}


Cabbage::Cabbage(StudentWorld * world, double startX, double startY):
    Projectile(world, IID_CABBAGE, startX, startY, 2, false, 8)
{
    
}

Turnip::Turnip(StudentWorld * world, double startX, double startY):
Projectile(world, IID_TURNIP, startX, startY, 2, true, -6)
{
    
}

FlatulenceTorpedo::FlatulenceTorpedo(StudentWorld * world, double startX, double startY, bool shotByVillain):
Projectile(world, IID_TORPEDO, startX, startY, 8, shotByVillain, 8)
{
    if(shotByVillain)
        setMovement(-8);
}

Goodie::Goodie(StudentWorld * world, int imageID, double startX, double startY):
    FloatingObject(world, imageID, startX, startY)
{
    
}

void Goodie::doSpecialSomething()
{
    moveTo(getX() - 0.75, getY() - 0.75);
}

bool Goodie::checkForCollision()
{
    NachenBlaster * blaster = getWorld()->getCollidingPlayer(this);
    if(blaster != nullptr)
    {
        getWorld()->increaseScore(100);
        setState(false);
        getWorld()->playSound(SOUND_GOODIE);
        doGoodieAction(blaster);
        return true;
    }
    return false;
}

ExtraLifeGoodie::ExtraLifeGoodie(StudentWorld * world, double startX, double startY):
    Goodie(world, IID_LIFE_GOODIE, startX, startY)
{
}

void ExtraLifeGoodie::doGoodieAction(NachenBlaster * blaster)
{
    getWorld()->incLives();
}

RepairGoodie::RepairGoodie(StudentWorld * world, double startX, double startY):
Goodie(world, IID_REPAIR_GOODIE, startX, startY)
{
}

void RepairGoodie::doGoodieAction(NachenBlaster * blaster)
{
    if(blaster->getHP() + 10 >= 50)
        blaster->setHP(50);
    else
        blaster->setHP(blaster->getHP() + 10);
}

FlatulenceTorpedoGoodie::FlatulenceTorpedoGoodie(StudentWorld * world, double startX, double startY):
Goodie(world, IID_TORPEDO_GOODIE, startX, startY)
{
}

void FlatulenceTorpedoGoodie::doGoodieAction(NachenBlaster * blaster)
{
    blaster->incTorpedoCount(5);
}
