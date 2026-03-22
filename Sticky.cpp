#include "Sticky.h"
#include "Button.h"


using namespace std;


Texture2D Sticky::notepic{};    //initialize the static


//###########################################
//           ⁡⁣⁢⁣​‌‌‍𝗖𝗼𝗻𝘀𝘁𝗿𝘂𝗰𝘁𝗼𝗿​⁡

Sticky::Sticky():mybutton({550,700},.07),inputbox({13,4},{30,10},35)
{
    notepic=LoadTexture("./resources/stickypic.png");
    
    noteimage=LoadRenderTexture(500,500);
    corkboard=LoadTexture("./resources/corkboard.png");

    
   
    

}
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
//##########################################
//          ⁡⁣⁢⁣​‌‌‍𝕊𝕎𝕀𝕋ℂℍ𝔹𝕆𝔸ℝ𝔻​⁡

void Sticky::switchBoard()
{
    if(mybutton.update())
        state=state_::create;




    switch (state)
    {
    case state_::initialize:
        break;

    case state_::create:
        
        savetoRender();
        break;

    case state_::deleting:
        break;
        
    case state_::idle:
        break;



    default:
        break;
    }

}
//-------------------------------------------


void Sticky::draw()
{

    DrawTexturePro(corkboard,{0,0,(float)corkboard.width,(float)corkboard.height},{0,0,800,800},{0,0},0,Fade(WHITE,0.85));
   
    if(!ImageList.empty())
        DrawTexturePro(ImageList[0],{0,0,ImageList[0].width,ImageList[0].height},
        {50,50,500,500},{0,0},0,WHITE);
   
    mybutton.draw();

    switchBoard();



        


}


//###########################################

void Sticky::savetoRender()
{
    //first draw to render texture and then display it to the screen
    BeginTextureMode(noteimage);
    
        ClearBackground(BLANK);
        DrawTextureEx(notepic,{0,0},0,.35,WHITE);
        inputbox.update();
        
        inputbox.draw();

    EndTextureMode();


    if(mybutton.update()==false)    //button has been pressed again-->post it!
    {
        cout<<"Time to post!!!\n";
        state=state_::idle;

        

        notestruct tempnote;
        tempnote.notecol=WHITE;
        tempnote.notemsg="hello";
        tempnote.posxy={100,100};
        tempnote.rotation=0;


        notelist.emplace_back(tempnote);
        
        Image snapshot=LoadImageFromTexture(noteimage.texture);
        ImageFlipVertical(&snapshot);
        Texture2D savedNote=LoadTextureFromImage(snapshot);
        UnloadImage(snapshot);

        ImageList.push_back(savedNote);




        cout<<"members in notelist: "<<notelist.size()<<endl;
        cout<<"members in ImageList: "<<ImageList.size()<<endl;

        inputbox.cleartextbox();

        mybutton.value=true;    //try resetting the button

        

    }


    DrawTextureRec(noteimage.texture,{0,0,(float)noteimage.texture.width,-(float)noteimage.texture.height},{50,600},WHITE);



}