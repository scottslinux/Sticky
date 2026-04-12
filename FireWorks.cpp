#include "FireWorks.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

FireWorks::FireWorks()
{
    numfrags=50;
    blstcntr={400,400};
    shotColor=Color{YELLOW};

    bling=LoadSound("resources/bling.wav");



}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FireWorks::~FireWorks()
{


}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void FireWorks::CreateRound()
{
    if(frags.size())
        frags.clear();  //if for some reason the vector is populated clear it




    for(int i=0;i<numfrags;i++)
    {
        int basevelx=1500;
        int basevely=2000;
        particle part;

        part.xy.x=blstcntr.x;  //random position clustered
        part.xy.y=blstcntr.y;   //around the center

        part.Vel.x=(-basevelx+rand()%(2*basevelx));  //range of velocities
        part.Vel.y=-rand()%(basevely)+500;  //range of velocities

        part.lifespan= rand()%2 +1;    //the amount of time that the particle will live
        part.opacity=rand()%100+155;   // all of the frags start at different brightness
        part.color.r = 150;
        part.color.g = static_cast<unsigned char>(rand()%255);
        part.color.b = 0;
        part.color.a = static_cast<unsigned char>(part.opacity);

        frags.push_back(part);  //pack that frag into the round and make the next

    }
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void FireWorks::FireAnimate()
{
   if (!fireflag) // if there is no shot in the air, nothing to animate
     {  
        cout<<"No Shot in the air....\n";
        return;
     }

    float acc=2000; //set the gravity

    //-----------------------------------
    //      timing

    float dt=GetFrameTime();
    blstTimer+=dt;  //total elapsed time
    cout<<"blast time: "<<blstTimer<<endl;
    //----------------------------------- 
    if(blstTimer>2)
    {
        blstTimer=0;
        fireflag=false;
        return;
    }

    for(auto& c:frags)
    {   


        // X=vel * time
        float xpos=c.Vel.x*dt+c.xy.x;


        // Y=1/2 at2 + Vely*time + Y0
        float ypos= (0.5*acc*dt*dt)+(c.Vel.y*dt)+(c.xy.y);

        if(c.opacity>0)
            c.opacity-=1;

        c.color.a = static_cast<unsigned char>(c.opacity < 0 ? 0 : c.opacity);

        if(c.lifespan>0)
            //DrawCircle(xpos,ypos,8,shotColor);
            DrawRectangle(xpos,ypos,15,15,shotColor);


        c.xy.x=xpos;
        c.xy.y=ypos;

        c.Vel.y=acc*dt + c.Vel.y;

    }


}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//   choose new position and number for the next shot
void FireWorks::reloadRound(int num,Vector2 pos, Color shotcol)
{
    numfrags=num;
    blstcntr=pos;
    shotColor=shotcol;

    CreateRound();  // Load the vector with fragements



}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool FireWorks::fire()
{
    while(!IsSoundPlaying(bling))
        PlaySound(bling);
    fireflag=true;  //intiate the shot
    blstTimer=0;    //reset the timer

    return fireflag;

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>but       




