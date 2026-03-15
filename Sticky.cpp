#include "Sticky.h"

using namespace std;


Texture2D Sticky::notepic{};    //initialize the static


//###########################################
Sticky::Sticky()
{
    notepic=LoadTexture("./resources/stickypic.png");

    

}
//###########################################
Sticky::~Sticky()
{
    UnloadTexture(notepic);

}
//###########################################
void Sticky::draw()
{
    DrawTextureEx(notepic,{100,100},0,.30,GREEN);

    inputbox.update();
    inputbox.draw();


}


//###########################################

