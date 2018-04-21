#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(StudentWorld * world, int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0, bool isAlive = true);
    StudentWorld * getWorld() const;
    virtual void doSomething() = 0;
    virtual bool isAlien() const;
    void setState(bool state);
    bool getState() const;
    
private:
    bool isActorAlive;
    StudentWorld * world;
protected:
    static const int HIT_BY_PROJECTILE = 2552, HIT_BY_CHARACTER = 1235;
};

class Star: public Actor
{
public:
    Star(StudentWorld * world, double startX, double startY);
    virtual void doSomething();
};

class Explosion: public Actor
{
public:
    Explosion(StudentWorld * world, double startX, double startY);
    virtual void doSomething();
private:
    int numOfTicks;
};

class FloatingObject: public Actor
{
public:
    FloatingObject(StudentWorld * world, int imageID, double startX, double startY, int dir = 0);
    virtual void doSomething();
    
private:
    virtual void doSpecialSomething()  = 0;
    virtual bool checkForCollision() = 0;
    virtual bool checkOffScreen() const;
};

class Projectile: public FloatingObject
{
public:
    Projectile(StudentWorld * world, int imageID, double startX, double startY, int damage, bool shotByVillain, int movement, int dir = 0);
protected:
    int getDamage() const;
    void setMovement(int movement);
    
private:
    int damage, movement;
    bool shotByVillain;
    virtual void doSpecialSomething();
    virtual bool checkForCollision();
    virtual bool checkOffScreen() const;
};

class Cabbage: public Projectile
{
public:
    Cabbage(StudentWorld * world, double startX, double startY);
};

class Turnip: public Projectile
{
public:
    Turnip(StudentWorld * world, double startX, double startY);
};

class FlatulenceTorpedo: public Projectile
{
public:
    FlatulenceTorpedo(StudentWorld * world, double startX, double startY, bool shotByVillain);
};

class Character
{
public:
    Character(int ammoCount, int torpedoCount, int hp);
    void incTorpedoCount(int num);
    int getTorpedoCount() const;
    void setAmmoCount(int count);
    int getAmmoCount() const;
    void setHP(int hP);
    int getHP() const;
    void fire(Projectile * projectile, int type) const;
    virtual void damageCharacter(int damage);
    
protected:
    static const int CABBAGE = 1, TURNIP = 2, TORPEDO = 3;

private:
    int hp, ammoCount, torpedoCount;
};

class NachenBlaster: public Actor, public Character
{
public:
    NachenBlaster(StudentWorld * world);
    virtual void doSomething();
    int getAmmoPercentage();
    int getHPPercentage();
    virtual void damageCharacter(int damage, int cause);
    
private:
    static const int POS_MOVEMENT = 6, NEG_MOVEMENT = -6;

    void moveX(int movement);
    void moveY(int movement);
};

class Alien: public Character, public FloatingObject
{
public:
    Alien(StudentWorld * world, int imageID, int startX, int startY, int hp, double flightSpeed, int hpReduce, int pointIncrease);
    
    virtual bool isAlien() const;
    virtual void damageCharacter(int damage, int cause);
    
private:
    double flightSpeed;
    int flightPlan, flightDirection;
    int hpReduce, pointIncrease;
    virtual bool isNewPlanNeeded() const;
    virtual void doSpecialSomething();
    virtual bool checkForCollision();
    virtual void dropGoodie();
    virtual void move();
    void die();
    
protected:
    static const int DOWNLEFT = 1, UPLEFT = 2, LEFT = 3;
    virtual void selectNewPlan();
    void setFlightSpeed(double speed);
    void setFlightDirection(int direction);
    void setFlightPlanLength(int length);
    virtual bool attack();
};

class Smallgon: public Alien
{
public:
    Smallgon(StudentWorld * world, int startX, int startY);
};

class Smoregon: public Alien
{
public:
    Smoregon(StudentWorld * world, int startX, int startY);
    
private:
    virtual bool attack();
    virtual void dropGoodie();
};

class Snagglegon: public Alien
{
public:
    Snagglegon(StudentWorld * world, int startX, int startY);

private:
    virtual bool attack();
    virtual void dropGoodie();
    virtual void selectNewPlan();
};

class Goodie: public FloatingObject
{
public:
    Goodie(StudentWorld * world, int imageID, double startX, double startY);
    
private:
    virtual void doSpecialSomething();
    virtual bool checkForCollision();
    virtual void doGoodieAction(NachenBlaster * blaster) = 0;
};

class ExtraLifeGoodie: public Goodie
{
public:
    ExtraLifeGoodie(StudentWorld * world, double startX, double startY);
    
private:
    virtual void doGoodieAction(NachenBlaster * blaster);
};

class RepairGoodie: public Goodie
{
public:
    RepairGoodie(StudentWorld * world, double startX, double startY);
    
private:
    virtual void doGoodieAction(NachenBlaster * blaster);
};

class FlatulenceTorpedoGoodie: public Goodie
{
public:
    FlatulenceTorpedoGoodie(StudentWorld * world, double startX, double startY);
    
private:
    virtual void doGoodieAction(NachenBlaster * blaster);
};

#endif // ACTOR_H_
