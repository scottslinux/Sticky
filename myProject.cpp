#include <iostream>
#include "raylib.h"
#include "Sticky.h"



using namespace std;

int main()
{
    cout<<" Testing again.....\n";

    InitWindow(800,800,"Sticky!!!!");
    InitAudioDevice();
    SetTargetFPS(60);

    Sticky myNote;

    while(!WindowShouldClose())
    {
        BeginDrawing();


        ClearBackground(Color{0,100,50,255});

        myNote.draw();




        EndDrawing();

    }



    CloseAudioDevice();

    return 0;
    
}