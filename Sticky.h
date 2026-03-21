#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "raylib.h"
#include <vector>
#include "textBox.h"

using namespace std;


class Sticky
{
private:
    static Texture2D notepic;
    Texture2D corkboard;

    RenderTexture2D noteimage;
    
    
    struct notestruct
    {   //data for each note
        Vector2 posxy{0,0};
        Color notecol{100,100,100,255};
        float rotation=0;
        string notemsg;

    };
    
    vector<notestruct> notelist;

    enum class state_{idle,creating,deleting};
    state_ state=state_::creating;
    TextBox inputbox;


public:
    
    Sticky(/* args */);
    ~Sticky();

    void draw();

    void savetoRender();

};

