#pragma once

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <sstream>

#include "raylib.h"

using namespace std;

class TextBox{

private: 

    Font MonoFont;              //load comicmono.otf in constructor
    int fontsize;
    int fontwidth,fontheight;
    int margin;                 //margin around the text to the rectangle
    int lines=0;

    Vector2 boxdimen;           //horizontal x vertical character counts
    Vector2 boxpixels;          //corresponding pixel dimensions
    Vector2 boxposition;        //position on the screen x,y
    Vector2 cursorpixxy;

    float cursortimer=0;
    bool cursorpauseflag=false;

    int charcount;
    int changesmade=0;
    Vector2 chardimen;
    string text,tempstring;

    bool spaceflag, newlineflag;
    bool cursorblink=false;
    bool changemade=true;   //start off true to visit word wrap

    enum class State_{idle,txtentry,reset};
    State_ state;

    



public:

    TextBox();                                             //default constructor
    TextBox(Vector2 chardim,Vector2 screenpos,int fntsz);  //constructor
    ~TextBox(); //destructor

    void update();
    void draw();
    void textinput();

    Vector2 rc_xy(Vector2 rc);
    void getSomeKeyStrokes();
    void drawCursor(float col,float row);
    string wrapper(string workingstr,int width);
    string getTextString();
    void cleartextbox();
    void pauseCursor();
    void resetLines();
    int countlinesbreaks();
    void settextString(string);

};
