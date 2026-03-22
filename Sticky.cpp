#include "Sticky.h"
#include "Button.h"
#include <ctime>



using namespace std;


Texture2D Sticky::notepic{};    //initialize the static


//###########################################
//           ⁡⁣⁢⁣​‌‌‍𝗖𝗼𝗻𝘀𝘁𝗿𝘂𝗰𝘁𝗼𝗿​⁡

Sticky::Sticky():mybutton({550,700},.07),inputbox({13,4},{30,10},35)
{
    notepic=LoadTexture("./resources/stickypic.png");
    
    noteimage=LoadRenderTexture(500,500);
    corkboard=LoadTexture("./resources/corkboard.png");

    state=state_::display;  //starting state for the moment

    stickycolor={Color{141,232,23,255},Color{118,236,232,255},Color{229,232,23,255},Color{255,201,252,255}};
    noterotation=0;

    
   srand(time(nullptr));    //improve randomness
    

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
   

    switch (state)
    {

    case state_::initialize:
        break;
    //---------------------------
    case state_::create:
        
        create_update();
        create_draw();
        savetoRender();
        break;
    //---------------------------

    case state_::deleting:
        break;
    //---------------------------
      
    case state_::display:
        display_update();
        display_draw();    


        break;

    //---------------------------


    default:
        break;
    }

    vector<string> verbosestate={"initialize","display","create","deleting",};
    cout<<"state: "<<verbosestate[static_cast<int>(state)]<<endl;

}

//-------------------------------------------

void Sticky::display_update()
{
    if(mybutton.update()==true && state==state_::display) //button pressed to start creating
        {
            state=state_::create;
            int i=rand()%4;;
            notecolor=stickycolor[i];    //choose a random color from the 4 for the new note
            noterotation=rand()%30 + -15;
 
        }
        
    
    

}


//-------------------------------------------
void Sticky::display_draw()
{
    //always draw the corkboard
    DrawTexturePro(corkboard,{0,0,(float)corkboard.width,(float)corkboard.height},{0,0,800,800},{0,0},0,Fade(WHITE,0.85));


    if(!ImageList.empty())  //if the list is not empty draw it.
                            //otherwise just draw the background
        {
            int r=0,c=0;    //row col indexes
            int i=0;        //useful index 
            for(Texture2D note:ImageList)//iterate the list
            {
                DrawTexturePro(note,{0,0,(float)note.width,(float)note.height},
                        {(float)50+(note.width*c*.45),(float)50+note.height*r*.45,
                            500,500},{0,0},notelist[i++].rotation,WHITE);

                c++;    //increment the col
                if(c>2) //only 0,1,2 per row
                {
                    c=0;    //beginning of the next col
                    r++;    //down to the next row
                }
            }


        }

            if(state==state_::display) mybutton.draw(); //only draw the button when in display state




}

//-------------------------------------------
void Sticky::create_draw()
{
    display_draw(); //draw the background and any existing notes

    DrawCircle(300,700,15,RED);
    DrawRing({300,700},13,17,0,360,999,WHITE);
    //don't draw the button 



}
//-------------------------------------------
void Sticky::create_update()
{
    
    savetoRender();



}


//-------------------------------------------


void Sticky::draw()
{

  



        


}


//###########################################

void Sticky::savetoRender()
{
    //first draw to render texture and then display it to the screen
    BeginTextureMode(noteimage);
    
        ClearBackground(BLANK);
        DrawTextureEx(notepic,{0,0},0,.35,notecolor);
        inputbox.update();
        
        inputbox.draw();

    EndTextureMode();


    if(CheckCollisionPointCircle(GetMousePosition(),{300,700},20)&&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&state==state_::create)    //button has been pressed again-->post it!
    {
        cout<<"Time to post!!!\n";
        state=state_::display;

        

        notestruct tempnote;
        tempnote.notecol=WHITE;
        tempnote.notemsg="hello";
        tempnote.posxy={100,100};
        tempnote.rotation=noterotation;


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
        state=state_::display;
        mybutton.value=false;is

        

    }


    DrawTextureRec(noteimage.texture,{0,0,(float)noteimage.texture.width,-(float)noteimage.texture.height},{50,600},WHITE);



}