#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "raylib.h"
#include "textBox.h"

using namespace std;


//*******************************************
TextBox::TextBox() : TextBox({10,4},{120,120},30) {}
//*******************************************
TextBox::TextBox(Vector2 chrdim,Vector2 screenpos,int fntsz)
{
    MonoFont=LoadFontEx("./resources/comicmono.otf",50,NULL,0);
    fontsize=fntsz;
    
    boxposition=screenpos;
    boxdimen=chrdim;    //set the dimensions in chars (vector2)

    string test="A";
    boxpixels=MeasureTextEx(MonoFont,test.c_str(),fntsz,0);
    fontwidth=boxpixels.x;
    fontheight=boxpixels.y*.85; //correct for the monospace too tall oddity
    margin=20;

    boxpixels.x*=boxdimen.x; //total pixels= single char pix * #chars across
    boxpixels.y*=boxdimen.y; //same for the vertical

 /*
    cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
    cout<<"char x: "<<boxdimen.x<<endl;
    cout<<"char y: "<<boxdimen.y<<endl;
    cout<<"Letter A pixels: "<<MeasureTextEx(MonoFont,test.c_str(),fntsz,0).x<<", "<<
        MeasureTextEx(MonoFont,test.c_str(),fntsz,0).y<<endl;
    cout<<"pixels x,y: "<<boxpixels.x<<", "<<boxpixels.y<<endl;
    cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";

    text="This is a test string that will never in itself change. Reach deep inside of yourself and try not to sink into the void...";

    tempstring=text;  //for testing create a copy of the text string
*/


}
//*******************************************
TextBox::~TextBox()
{

}
//*******************************************
void TextBox::update()
{
        TextBox::getSomeKeyStrokes();

    
        
    


}
//*******************************************
void TextBox::draw()
{
    DrawRectangleLinesEx({boxposition.x-fontwidth,(float)boxposition.y-fontheight*.5,
            (float)boxpixels.x+fontwidth*2.5,boxpixels.y+fontwidth*2},2,YELLOW);

    
        int row=0,col=0;
        int charindex=0;       
        
        tempstring=text;    //transfer the contents to keep the original info intact
        tempstring=wrapper(tempstring,boxdimen.x);




        for(char c:tempstring)        //iterate thru the string 
        {
            
            {
                //  add the character input to a string for display
                if(c==10 )
                {
                    //cout<<"I see the carriage return!!!!";
                    col=-1;
                    row++;
                    //break;


                }


                string a;
                a+=c;   //convert the character into a string
                DrawTextEx(MonoFont,a.c_str(),{boxposition.x+(col*fontwidth),boxposition.y+(row*fontheight)},fontsize,0,BLACK);
                col++;

                
            }

            

        }
        


        Vector2 rec=rc_xy({col,row});
        drawCursor(rec.x,rec.y);

        cout<<tempstring<<endl;

   
}



//*******************************************
//row,column to pixel xy  ---return the pixel location for a row,col character spot
Vector2 TextBox::rc_xy(Vector2 rc)
{
    Vector2 pixelxy={boxposition.x+rc.x*fontwidth, boxposition.y+rc.y*fontheight};

    
    //cout<<pixelxy.x<<" , "<<pixelxy.y<<endl;




    return pixelxy;
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
        curscolor=Color{255,255,255,220};

        break;
    case false:
        curscolor=Color{255,255,255,100};
        break;
    
    default:
        break;
    }

    DrawRectangle(x,y,fontwidth,fontheight,curscolor);  //and there you go....

}

//*******************************************

//***************************************************************/
//  Here is the pure word wrap function....let's see
string TextBox::wrapper(string workingstr,int width)
{
    int charcount=0;
    int changes=0;
    int lines=1;

    for (int i=0;i<workingstr.length();i++)
    {
        if(charcount==width)    //you are at the end (width*lines keeps the party going!)
        {
            if(workingstr[i]==10)   //if parser encounters a native RETURN
            {
                charcount=-1;   //start the counter at 0 -i will iterate to next character
                lines++;
                changes++;



            }



            else if (workingstr[i]==32)  //if there is a space convert to \n
            {
                workingstr[i]=10;
                charcount=-1;    //reset the width counter. it will inc to 0 after loop
                lines++;
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
                        lines++;
                        



                        break;  //stop the process so not all spaces get replaced

                    }



                }



        }
        charcount++;    //increment to the next character in the string
    }
    
    cout<<"             SUCCESS!!!!!!\n";
    cout<<"\nIn the function wrapper..."<<changes<<" changes were made.\n";
    cout<<"The text was wrapped to a width of "<<width<<" characters.";
    cout<<"the string was "<<workingstr.length()<<" characters long.\n\n";

    return workingstr;
}
