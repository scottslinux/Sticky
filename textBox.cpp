#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "raylib.h"
#include "textBox.h"

using namespace std;



//*******************************************
TextBox::TextBox(Vector2 chrdim,Vector2 screenpos,int fntsz)
{
    MonoFont=LoadFontEx("./resources/marker.ttf",100,NULL,0);
    SetTextureFilter(MonoFont.texture,TEXTURE_FILTER_BILINEAR);


    fontsize=fntsz;
    cursorpixxy={0,0};     
    
    boxposition=screenpos;
    boxdimen=chrdim;    //set the dimensions in chars (vector2)

    string test="W";
    boxpixels=MeasureTextEx(MonoFont,test.c_str(),fntsz,0);
    fontwidth=boxpixels.x;
    fontheight=boxpixels.y*.85; //correct for the monospace too tall oddity
    margin=20;

    boxpixels.x*=boxdimen.x; //total pixels= single char pix * #chars across
    boxpixels.y*=boxdimen.y; //same for the vertical

 

}
//*******************************************
TextBox::~TextBox()
{

}
//*******************************************
void TextBox::update()
{
    
        TextBox::getSomeKeyStrokes();
      //  cout<<"lines: "<<countlinesbreaks()<<endl;

    
    
    


}
//*******************************************
void TextBox::draw()
{
   // DrawRectangleLinesEx({boxposition.x,(float)boxposition.y-fontheight*.5,
    //        (float)boxpixels.x*.6,boxpixels.y+fontwidth*2},1,BLUE);

    
        int row=0,col=0;
        int charindex=0;  
        
        
        tempstring=text;    //transfer the contents to keep the original info intact
        tempstring=wrapper(tempstring,boxdimen.x);


        float fontposx=0;   //start off on the left margin
        string prevchar="";

        for(char c:tempstring)        //iterate thru the string 
        {

            
            {
                //  add the character input to a string for display
                if(c==10 )
                {
                    //cout<<"I see the carriage return!!!!";
                    col=-1;
                    row++;
                    prevchar="";    //ON A NEW LINE...don't need leading spaces

                    fontposx=0; //reset character position to left margin
                    


                }


                string a;
                
                a+=c;   //convert the character into a string

                fontposx+=MeasureTextEx(MonoFont,prevchar.c_str(),fontsize,0).x;   //tally up the spacing in realtime


                DrawTextEx(MonoFont,a.c_str(),{boxposition.x+(fontposx)+25,boxposition.y+(row*fontheight)+25},fontsize,0,BLACK);
                col++;

                cursorpixxy={boxposition.x+(fontposx),boxposition.y+(row*fontheight)};

                prevchar=a; //save the previous character for spacing

                
            }

            

        }
        


        
        //drawCursor(0,0);

        //cout<<tempstring<<endl;

   
}



//*******************************************

void TextBox::getSomeKeyStrokes()
{   
    //thanks Copilot--add the keystrokes to the string text



    int key = GetCharPressed();

    while (key > 0) {
        text.push_back(static_cast<char>(key));
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !text.empty()) {
        text.pop_back();
    }

    if(IsKeyPressed(KEY_ENTER))
    {
        text+=char(10);

    }


}
//*******************************************

void TextBox::drawCursor(float x,float y)   //pass the pixel x,y
{

    if (cursorpauseflag) return;    //blank it for the snapshot

    cursortimer+=GetFrameTime();    //increment the counter

    if (cursortimer>0.50)   //if it has been x seconds..change the state of the cursor from one to the other
    {
        if(cursorblink)
        {
            cursorblink=false;
            cursortimer=0;     //reset the timer
        }
        else
        {
            cursortimer=0;
            cursorblink=true;
        }


    }
    Color curscolor;        //set the color of the cursor based on the state flag
    switch (cursorblink)
    {
    case true:
        curscolor=Color{0,0,0,220};

        break;
    case false:
        curscolor=Color{0,0,0,10};
        break;
    
    default:
        break;
    }

    DrawRectangle(cursorpixxy.x+fontwidth/1.5,cursorpixxy.y,fontwidth/3,fontheight,curscolor);  //and there you go....

}

//*******************************************

//***************************************************************/
//  Here is the pure word wrap function....let's see
string TextBox::wrapper(string workingstr,int width)
{



    int charcount=0;
    int changes=0;
    
    for (int i=0;i<workingstr.length();i++)
    {
        if(charcount==width)    //you are at the end (width*lines keeps the party going!)
        {
            if(workingstr[i]==10)   //if parser encounters a native RETURN
            {
                charcount=-1;   //start the counter at 0 -i will iterate to next character
                changes++;



            }



            else if (workingstr[i]==32)  //if there is a space convert to \n
            {
                workingstr[i]=10;
                charcount=-1;    //reset the width counter. it will inc to 0 after loop
                changes++;

                
                

            }

            else    //there is a character at the border. Go back to the last space

                for (int j=i;j>0;j--)
                {   
                    if(workingstr[j]==32)
                    {
                        workingstr[j]=10;
                        charcount=-1;  //reset the width counter. it will inc to 0 after loop
                        changes++;
                        i=j+1; //go back on character in the count to start fresh on new line
                        



                        break;  //stop the process so not all spaces get replaced

                    }



                }



        }
        


    
        charcount++;    //increment to the next character in the string
    }
   

    


    return workingstr;
}
//********************************************************** */

string TextBox::getTextString()
{
    return text;
}
//********************************************************** */
void TextBox::cleartextbox()
{
    text="";
}
//***************************************************************/
void TextBox::pauseCursor()
{

    cursorpauseflag=(cursorpauseflag==false) ? true : false ;


}
//***************************************************************/

void TextBox::resetLines()
{
    lines=0;
}
//***************************************************************/

int TextBox::countlinesbreaks()
{
    int linebrk=0;

    for(char c:tempstring)
        {
            if(c==10)
            linebrk++;
        }


    return linebrk;


}
//***************************************************************/
//  Let's me set the contents of the text box without manually entering

void TextBox::settextString(string newmsg) //used in repopulating the notes from saved vector
{
    text=newmsg;


}

