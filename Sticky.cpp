#include "Sticky.h"
#include "Button.h"


using namespace std;


Texture2D Sticky::notepic{};    //initialize the static


//###########################################
//           ⁡⁣⁢⁣​‌‌‍𝗖𝗼𝗻𝘀𝘁𝗿𝘂𝗰𝘁𝗼𝗿​⁡

Sticky::Sticky():mybutton({550,700},.08)
{
    notepic=LoadTexture("./resources/stickypic.png");
    
    noteimage=LoadRenderTexture(500,500);
    corkboard=LoadTexture("./resources/corkboard.png");

    
   




    

}
//###########################################










//###########################################
Sticky::~Sticky()
{
  //  UnloadTexture(notepic);
   // UnloadRenderTexture(noteimage);
   if(corkboard.id!=0)
   {
    UnloadTexture(corkboard);
    cout<<"unloading corkboard...\n";
   }

}
//###########################################
void Sticky::draw()
{

    //DrawTexture(corkboard,0,0,WHITE);
    DrawTexturePro(corkboard,{0,0,corkboard.width,corkboard.height},{0,0,800,800},{0,0},0,Fade(WHITE,0.85));
   
    DrawTextureEx(notepic,{100,100},0,.35,GREEN);   //Draw the note image and get the input over top

    savetoRender();

    inputbox.update();
    inputbox.draw();
    mybutton.update();
    mybutton.draw();

    DrawTextureRec(noteimage.texture,{0,0,(float)noteimage.texture.width,-(float)noteimage.texture.height},{200,200},WHITE);

    



        


}


//###########################################

void Sticky::savetoRender()
{
    BeginTextureMode(noteimage);
        DrawTextureEx(notepic,{100,100},15,.35,WHITE);
  

    EndTextureMode();



}