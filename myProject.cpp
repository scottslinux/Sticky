#include <iostream>
#include <unistd.h>
#include "raylib.h"
#include "Sticky.h"

//--------------------------------------------------------------
//      ​‌‌‍⁡⁣⁢⁣𝕊𝕥𝕚𝕔𝕜 ℕ𝕠𝕥𝕖𝕤 𝕍𝕖𝕣𝕤𝕚𝕠𝕟 𝟚.𝟘 𝟜/𝟙𝟚/𝟚𝟘𝟚𝟞​⁡
//      ​‌‌⁡⁣⁢⁣‍𝕊𝕔𝕠𝕥𝕥 𝕊𝕙𝕖𝕣  𝕔𝕣𝕖𝕒𝕥𝕖𝕕 𝕚𝕟 𝕊𝕔𝕠𝕥𝕥𝕤𝕕𝕒𝕝𝕖, ℕ𝕖𝕨𝕐𝕠𝕣𝕜 𝕒𝕟𝕕 ℙ𝕙𝕚𝕝𝕒⁡​
//--------------------------------------------------------------

using namespace std;

int main()
{  

    chdir("/home/scott/GitHub_Projects/Sticky");


    cout<<" Testing again.....\n";

    SetConfigFlags(FLAG_MSAA_4X_HINT);  //prevents aliasing
    InitWindow(800,800,"Sticky!!!!");
    InitAudioDevice();
    SetTargetFPS(60);

    Sticky myNote;

    while(!WindowShouldClose())
    {
        BeginDrawing();


        ClearBackground(Color{0,100,50,255});

        myNote.switchBoard();   //state machine control
        //myNote.draw();




        EndDrawing();

    }



    CloseAudioDevice();

    return 0;
}