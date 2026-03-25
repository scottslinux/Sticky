#include "Sticky.h"
#include "Button.h"
#include <ctime>



using namespace std;


Texture2D Sticky::notepic{};    //initialize the static


//###########################################
//           ⁡⁣⁢⁣​‌‌‍𝗖𝗼𝗻𝘀𝘁𝗿𝘂𝗰𝘁𝗼𝗿​⁡

Sticky::Sticky():mybutton({550,700},.07),inputbox({10,4},{30,10},130)
{
    notepic=LoadTexture("./resources/stickypic.png");
    
    
    noteimage=LoadRenderTexture(notepic.width,notepic.height);
    corkboard=LoadTexture("./resources/corkboard.png");
    closingX=LoadTexture("./resources/closingX.png");

    state=States::display;  //starting state for the moment

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

    case States::initialize:
        break;
    //---------------------------
    case States::create:
        
        create_update();
            if (state==States::display) break;
        create_draw();
        savetoRender();
        break;
    //---------------------------

    case States::deleting:

        deleting_update();
        deleting_draw();
        break;
    //---------------------------
      
    case States::display:
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
    if(mybutton.update()==true && state==States::display && notelist.size()<9) //button pressed to start creating
        {
            state=States::create;
            int i=rand()%4;;
            notecolor=stickycolor[i];    //choose a random color from the 4 for the new note
            noterotation=rand()%30 + -15;

            SetMousePosition(300,800);
 
        }
        
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&(IsKeyDown(KEY_LEFT_SHIFT)))
    {
            cout<<"#######################################\n"; 

            state=States::deleting;
               

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
                Rectangle recsource={0,0,(float)note.width,(float)note.height};
                Rectangle recdest={(float)50+(note.width*c*.35),(float)50+note.height*r*.45,200,200};

                notelist[i].targetrect=recdest; //register the position in the list for collision

                DrawRectangleLinesEx(recdest,4,RED);
                DrawText(to_string(i).c_str(),recdest.x,recdest.y,30,WHITE);


                
                DrawTexturePro(note,recsource,recdest,{0,0},notelist[i].rotation,WHITE);

                c++;    //increment the col
                if(c>2) //only 0,1,2 per row
                {
                    c=0;    //beginning of the next col
                    r++;    //down to the next row
                }
                i++;    //increment the iterator
            }


        }

            if(state==States::display && notelist.size()<9) mybutton.draw(); //only draw the button when in display state




}

//-------------------------------------------
void Sticky::create_draw()
{
    if(CheckCollisionPointCircle(GetMousePosition(),{500,200},50)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        state=States::display;
        SetMousePosition(100,300);

        return;
    
    }
    
    display_draw(); //draw the background and any existing notes

    DrawCircle(300,700,15,RED);
    DrawRing({300,700},13,17,0,360,999,WHITE);
    //don't draw the button 
    DrawTextureEx(closingX,{500,200},0,.08,WHITE);



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
        DrawTextureEx(notepic,{0,0},0,1,notecolor); //create full sized noteimage with large font
        inputbox.update();
        
        inputbox.draw();

    EndTextureMode();


    if(CheckCollisionPointCircle(GetMousePosition(),{300,700},20)&&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&state==States::create)    //button has been pressed again-->post it!
    {
        cout<<"Time to post!!!\n";
        state=States::display;

        

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
        state=States::display;
        mybutton.value=false;

        

    }


    //DrawTextureRec(noteimage.texture,{0,0,(float)noteimage.texture.width/2,-(float)noteimage.texture.height/2},{50,600},WHITE);
        Rectangle recsource={0,0,(float)noteimage.texture.width,-1*(float)noteimage.texture.height};
        Rectangle recdest={(float)50+(noteimage.texture.width*.35),(float)50+noteimage.texture.height*.35,300,300};
        DrawTexturePro(noteimage.texture,recsource,recdest,{0,0},0,notecolor);




}
//--------------------------------------------------------------
void Sticky::deleting_update()
{
    for(int i=0;i<notelist.size();i++)
    {
        if(CheckCollisionPointRec(GetMousePosition(),notelist[i].targetrect)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            cout<<"******DELETING****    "<<i<<endl;
            notelist.erase(notelist.begin()+i);
            ImageList.erase(ImageList.begin()+i);

                state=States::display;

        }
    }

    
}

//--------------------------------------------------------------
void Sticky::deleting_draw()
{
    display_draw();

    
}