#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "raylib.h"
#include <vector>
#include "textBox.h"
#include "Button.h"
#include <fstream>

using namespace std;


class Sticky
{
private:
    static Texture2D notepic;

    Texture2D corkboard;
    Texture2D buttonup;
    Texture2D buttondown;
    Texture2D closingX;

    Font utility;

    RenderTexture2D noteimage;

    Button mybutton;
    Color notecolor;
    float noterotation;
    vector<Color> stickycolor;
    float notescale=0.25;

    float animTimer=0;
    bool abortingFlag=false;
    bool changesmade=false;
    bool savereadflag=false;
    string operationString;
    
    

    //------------------------------------------------
    //     ⁡⁣⁣⁢𝗘𝗡𝗨𝗠 𝗖𝗟𝗔𝗦𝗦 𝗦𝗧𝗔𝗧𝗘𝗦⁡
    enum class States{initialize,display,create,deleting,aborting};

    States state=States::initialize;
    
    //------------------------------------------------
    
    TextBox inputbox;


public:
    
    struct notestruct
    {   //data for each note
        Vector2 posxy{0,0};
        Color notecol{100,100,100,255};
        float rotation=0;
        string notemsg;
        Rectangle targetrect;

    };
    
    vector<notestruct> notelist;
    vector<Texture2D> ImageList;

    Sticky(/* args */);
    ~Sticky();

    void draw();

    void savetoRender();
    void switchBoard();
    void display_draw();
    void display_update();
    void create_draw();
    void create_update();
    void deleting_update();
    void deleting_draw();
    void save2File();
    void readfromFile();

    void save_readGraphic(string);
    

};

