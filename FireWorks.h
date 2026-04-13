#include <iostream>
#include <cstdlib>
#include <vector>
#include "raylib.h"

using namespace std;

class FireWorks
{
private:
    bool fireflag=false;
    int numfrags=0;
    float blstTimer=0;
    Color shotColor;

    Sound bling;
    Sound confetti; //2 alternative sounds for the destruction animation
    

    Vector2 blstcntr={0,0};

    struct particle
    {
        Vector2 xy;
        Vector2 Vel;

        float lifespan;
        float opacity;
        Color color;

    };

    vector<particle> frags;

//=========================================================


public:
    FireWorks();
    ~FireWorks();
    void CreateRound();
    void FireAnimate();
    void reloadRound(int num,Vector2 pos, Color shotcol); //reload the round different pos
    bool fire();
    bool shotintheair();

};

//=========================================================





