#include "Sticky.h"
#include "Button.h"
#include <ctime>
#include <iomanip>



using namespace std;


Texture2D Sticky::notepic{};    //initialize the static


//###########################################
//           ⁡⁣⁢⁣​‌‌‍𝗖𝗼𝗻𝘀𝘁𝗿𝘂𝗰𝘁𝗼𝗿​⁡

Sticky::Sticky():mybutton({550,700},.07),inputbox({10,4},{30,10},130)
{
    notepic=LoadTexture("resources/stickypic.png");
    
    
    noteimage=LoadRenderTexture(notepic.width,notepic.height);
    corkboard=LoadTexture("resources/corkboard.png");
    closingX=LoadTexture("resources/closingX.png");

    utility=LoadFontEx("resources/pencil.ttf",80,0,NULL);

    state=States::initialize;  //starting state for the moment

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
        if(!notelist.size())
        {
            readfromFile(); //let's see if there is already a list of notes
            state=States::display;
            cout<<"vector lenght: "<<notelist.size()<<endl;
        }
        savereadflag=true;
        operationString="LOADING...";

        
        break;
    //---------------------------
    case States::create:
        
        create_update();
        create_draw();
        //savetoRender();
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
        if(savereadflag)
                save_readGraphic(operationString);  //play the graphic load bar


        break;

    //---------------------------

    case States::aborting:

        mybutton.value=false;   //turn off the create button
        abortingFlag=true;
    
        cout<<"Fell Through....aborting!!!!!!!\n";

        state=States::display;
        break;
    
    //---------------------------------------
    default:

        break;
    }

    
}

//-------------------------------------------

void Sticky::display_update()
{
    //check for create button to be pressed. Change state display-->create
    if(mybutton.update()==true && state==States::display && notelist.size()<9) //button pressed to start creating
        {
            state=States::create;
            int i=rand()%4;;
            notecolor=stickycolor[i];    //choose a random color from the 4 for the new note
            noterotation=rand()%30 + -15;

            SetMousePosition(300,780);

            cout<<"dispay update....create button seems pressed...fix value\n";
 
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

                if(changesmade)
                {
                    changesmade=false;
                    save2File();    //write the vector out to a file

                }

                //DrawRectangleLinesEx(recdest,4,RED);
                //DrawText(to_string(i).c_str(),recdest.x,recdest.y,30,WHITE);


                
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

    vector<string> verbosestate={"initialize","display","create","deleting","aborting"};
    //cout<<"state: "<<verbosestate[static_cast<int>(state)]<<endl;
    string currstate="mode: "+verbosestate[static_cast<int>(state)];
    DrawTextEx(utility,currstate.c_str(),{400,770},40,0,WHITE);



}

//-------------------------------------------
void Sticky::create_draw()
{
    
    
    display_draw(); //draw the background and any existing notes

    
    DrawCircle(308,780,20,BLACK);
    DrawCircle(300,780,15,GREEN);
    DrawRing({300,780},13,20,0,360,100,LIGHTGRAY);
    DrawRing({300,780},10,13,0,360,100,DARKGREEN);
    DrawCircle(305,775,4,Color{255,255,255,150});
    //don't draw the button 
    DrawTextureEx(closingX,{500,200},0,.08,WHITE);

    

    savetoRender();




}
//-------------------------------------------
void Sticky::create_update()
{
    //Abort the creation of a note and delete it
    //DrawCircle(540,245,30,WHITE);
    if(CheckCollisionPointCircle(GetMousePosition(),{540,245},25)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        state=States::aborting;
        SetMousePosition(100,300);
        cout<<"confirm press.....\n";

        return;
    
    }
       

}


//-------------------------------------------


void Sticky::draw()
{

  //replaced by switchboard and specific drawing routines based on state



        


}


//###########################################

void Sticky::savetoRender()
{
    if (abortingFlag)   //we bailed out of the last note...so clear the text
    {
        //clear the textbox
        inputbox.cleartextbox();
        abortingFlag=false; //reset the flag





    }
    //first draw to render texture and then display it to the screen
    BeginTextureMode(noteimage);
    
        ClearBackground(BLANK);
        DrawTextureEx(notepic,{0,0},0,1,notecolor); //create full sized noteimage with large font
        inputbox.update();
        
        inputbox.draw();

    EndTextureMode();

    //this is the button sensing routine for the save note procedure
    if(CheckCollisionPointCircle(GetMousePosition(),{308,780},20)&&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&state==States::create)    //button has been pressed again-->post it!
    {
        changesmade=true;   //will signal a write to file operation

        cout<<"Time to post!!!\n";
        state=States::display;

        

        notestruct tempnote;
        tempnote.notecol=notecolor;
        tempnote.notemsg=inputbox.getTextString();
        tempnote.posxy={100,100};
        tempnote.rotation=noterotation;
        //don't need the rectangle since it is dynamically positioned
        



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



    cout<<notelist.size()<<endl;

    save2File();
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
            savereadflag=true;
            operationString="DELETING...";

        }
        else
            if(CheckCollisionPointRec(GetMousePosition(),notelist[i].targetrect)&&GetMouseWheelMove())
            {
                notelist[i].rotation+=(GetMouseWheelMove());
                
                if(!IsKeyDown(KEY_LEFT_SHIFT))  //end the rotation and return to 
                    state=States::display;
            }
    }

    
}

//--------------------------------------------------------------
void Sticky::deleting_draw()
{
    display_draw();

    
}
//---------------------------------------------------------------

//      ⁡⁣⁣⁢​‌‌‍𝗪𝗿𝗶𝘁𝗲 𝘁𝗵𝗲 𝗘𝘅𝗶𝘀𝘁𝗶𝗻𝗴 𝗡𝗼𝘁𝗲𝘀 𝘁𝗼 𝗮 𝗙𝗶𝗹𝗲​⁡

void Sticky::save2File()    //write it out to a file
{
    savereadflag=true;
    operationString="SAVING....";

    string path="./resources/data.txt";
    ofstream outfile(path);
    if(outfile.is_open())
            cout<<"file opened successfully for write operation.\n";
            else
                cout<<"FAILED TO OPEN FILE FOR WRITE!!!\n";

    for(const auto& c:notelist)
    {
        //convert the colors to integers so they can be read back
        outfile
        <<(int)c.notecol.r<<' '<<(int)c.notecol.g<<' '<<(int)c.notecol.b<<' '<<(int)c.notecol.a
        <<' '<<std::quoted(c.notemsg)
        <<' '<<c.posxy.x<<' '<<c.posxy.y
        <<' '<<c.rotation<<' '
        <<'\n';


    }

    outfile.close();
            
}
//---------------------------------------------------------------
void Sticky::readfromFile()
{
    //  ⁡⁣⁣⁢​‌‌‍𝗥𝗲𝘀𝘁𝗼𝗿𝗲 𝘁𝗵𝗲 𝗩𝗲𝗰𝘁𝗼𝗿 𝗳𝗿𝗼𝗺 𝘁𝗵𝗲 𝗦𝗮𝘃𝗲𝗱 𝗡𝗼𝘁𝗲 𝗙𝗶𝗹𝗲​⁡
    
    
    string path="./resources/data.txt";
    ifstream infile(path);  //if not valid file...get out
        if (!infile) { std::cerr << "FAILED TO OPEN FILE FOR READ!!!\n"; return; }
            else
                cout<<"there is a valid file and it is being opened....\n";

    notestruct tempnote;

    notelist.clear();   //clear the existing list

  int r,g,b,a;

  while(infile
            >>r>>g>>b>>a
            >>std::quoted(tempnote.notemsg)
            >>tempnote.posxy.x
            >>tempnote.posxy.y
            >>tempnote.rotation)
    {
        
        tempnote.notecol={ (unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a };
        notelist.push_back(tempnote);
    }
//vector has been populated. Now time to create the images

for(auto c:notelist)
{
    BeginTextureMode(noteimage);
    
        ClearBackground(BLANK);
        DrawTextureEx(notepic,{0,0},0,1,c.notecol); //create full sized noteimage with large font
        inputbox.settextString(c.notemsg);
        inputbox.update();
        
        inputbox.draw();

    EndTextureMode();


    Image snapshot=LoadImageFromTexture(noteimage.texture);
        ImageFlipVertical(&snapshot);
        Texture2D savedNote=LoadTextureFromImage(snapshot);
        UnloadImage(snapshot);

        ImageList.push_back(savedNote); //push the image onto the ImageList vector

    



}
inputbox.cleartextbox();    //clear the note text out so we start clean


    

}
//---------------------------------------------------------------
void Sticky::save_readGraphic(string title)
{
    animTimer+=GetFrameTime();
    if(animTimer<2)
    {
        DrawTextEx(utility,title.c_str(),{150,700},50,0,WHITE);
        DrawRectangleRounded({100,750,300,10},1,100,WHITE);
        DrawRectangleRounded({100,750,(300*animTimer/2),10},1,100,GREEN);

    }
    else
        {
            animTimer=0;
            savereadflag=false;
        }


}