/*******************************************************************************************
 *
 *   raylib N64 [Model] example - 3D
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
 *   This example, and all assets and 3D models, are created by @VillagerJJ, and are licensed under CC0
 *
 ********************************************************************************************/


#include <libdragon.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <raylib.h>
#include <rlgl.h>
#include <GL/gl_integration.h>


#define ATTR_NINTENDO64_WIDTH 320
#define ATTR_NINTENDO64_HEIGHT 240




static const GLfloat environment_color[] = { 63.9f/255, 80.0f/255, 85.1f/255, 0.5f/255 }; //color, defined in R,G,B,A



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------w
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    //

    //Define the resolution, this uses the default Libdragon resolution.
    const int screenWidth = ATTR_NINTENDO64_WIDTH;
    const int screenHeight = ATTR_NINTENDO64_HEIGHT;
    

    InitWindow(screenWidth, screenHeight, "raylib N64 [model] example - 3D");
    

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    rlSetClipPlanes(1, 500); //Fixes horrible looking flickering issues with the projection matrix. note, the depth-buffer precision is 16bit, so the closer the values, the higher quailty the depth projection

    //Loads models using Libdragon's Model64 system
    model64_t *Sky = model64_load("rom:/models/Ground/Sky.model64");
    model64_t *Ground = model64_load("rom:/models/Ground/Ground.model64");
    model64_t *Water = model64_load("rom:/models/Ground/WaterPlane.model64");


    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); //needed to enable color materials?
    glEnable(GL_COLOR_MATERIAL); //enable vertex colors (for the sky, and ground shadows)

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close with Start button
    {
        // Update
        //-----------------------------------------------------

        joypad_poll();
        joypad_buttons_t pressed = joypad_get_buttons_pressed(JOYPAD_PORT_1); //this is if you only need when a button is pressed
        joypad_buttons_t held = joypad_get_buttons_held(JOYPAD_PORT_1); //when you need to check if a button is held
        joypad_inputs_t inputs = joypad_get_inputs(JOYPAD_PORT_1); //needed to get the joystick/analog stick data
      

        UpdateCameraPro(&camera, 
          (Vector3){
          (held.c_up)*0.1f -      // Move forward-backward
          (held.c_down)*0.1f,
          (held.c_right)*0.1f -   // Move right-left
          (held.c_left)*0.1f,
          (held.a)*0.1f -   // Move up-down
          (held.b)*0.1f
          },
          (Vector3){
          (inputs.stick_x)*0.05f,                            // Rotation: yaw
          -((inputs.stick_y)*0.05f),                         // Rotation: pitch | this has a negative sign to invert the value of the controller for propper use with Raylib's cameras
          0.0f                                               // Rotation: roll
          },
          0);                              // Move to target (zoom)

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing(); //tell the N64 that we can start drawing some things (this is where the fun begins)

        //ClearBackground(ColorFromHSV(194.4, 24.9, 85.1)); //used for clearing the screen to prevent weird vertex flickering, you can disable this if you use the functions below.

        //this code does the same thing as the ClearBackground function above, but better :)
        //glClearColor(0.3f, 0.5f, 0.9f, 1.0f); // Sets the color of the void to light blue, only needed if you clear the GL_COLOR_BUFFER_BIT
        glClear(GL_DEPTH_BUFFER_BIT); //makes the game run better by not clearing the color buffer, useful if you use a skydome like in this demo, causes solitaire effect when looking into the void.
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Same as ClearBackground in Raylib, but faster

        BeginMode3D(camera); //tells the N64 that its time for cool special drawing functions (3D). you should supply the camera here as well

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, environment_color) //enables lights :)




        glDepthMask (GL_FALSE); //disables the depth check for the following meshes, I recommend you only do this for static, far away objects, like background elements.
        model64_draw_mesh(model64_get_mesh(Sky, 0));

        glDepthMask (GL_TRUE); //enables depth check for more complex meshes, call the closer objects first so you spend less time filling pixels later, unless you need transparent effects.
        model64_draw_mesh(model64_get_mesh(Ground, 0));
        model64_draw_mesh(model64_get_mesh(Water, 0)); //this is closer to the camera most of the time, however, we draw it after the ground because it is transparent.

        EndMode3D(); //turns off 3D :(

        DrawFPS(15,15); //Raylib's built in FPS counter, draws at pixels 15, 15



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

     // De-Initialization
    //--------------------------------------------------------------------------------------
    //


    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}
