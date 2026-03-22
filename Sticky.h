#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "raylib.h"
#include <vector>
#include "textBox.h"
#include "Button.h"

using namespace std;


class Sticky
{
private:
    static Texture2D notepic;
    Texture2D corkboard;
    Texture2D buttonup;
    Texture2D buttondown;

    RenderTexture2D noteimage;

    Button mybutton;
    
    
    struct notestruct
    {   //data for each note
        Vector2 posxy{0,0};
        Color notecol{100,100,100,255};
        float rotation=0;
        string notemsg;

    };
    
    vector<notestruct> notelist;
    vector<Texture2D> ImageList;

    //------------------------------------------------
    //     ⁡⁣⁣⁢𝗘𝗡𝗨𝗠 𝗖𝗟𝗔𝗦𝗦 𝗦𝗧𝗔𝗧𝗘𝗦⁡
    enum class state_{initialize,idle,create,deleting};

    state_ state=state_::initialize;
    
    //------------------------------------------------
    
    TextBox inputbox;


public:
    
    Sticky(/* args */);
    ~Sticky();

    void draw();

    void savetoRender();
    void switchBoard();

};

