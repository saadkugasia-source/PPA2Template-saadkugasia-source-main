#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MacUILib.h"

// WARNING:  This solution version is VERY OOD-tified.  Students do not have to go this far. :)


// PREPROCESSOR DIRECTIVE CONSTANTS
// ================================
// For program-wide constants, define them here using #define.  Add as seen needed.
#define DIMY 15  // Default Gameboard Size
#define DIMX 30  // Default Gameboard Size
#define GAME_MASTER_SPEED 2000  // Default Game Delay Constant in Microseconds

// GLOBAL VARIABLES
// ================================
int exitFlag;   // Program Exiting Flag, used to determine whether to leave the program loop and shutdown the program
char inputChar;  // Input Character, used to store the most recent input character for the main program logic to use


// Add more variables here as needed
char** gameBoard;  // Game Board, used to store the current state of the game board for display
int score;


// Object: Player
typedef struct
{
    int x;
    int y;
    char symbol[4];  // Default symbol for the player
} Player;  // <H>

// Object: Bullet
typedef struct 
{
    int x;
    int y;
    char symbol;
} Bullet;  // |


// Object: Enemy
typedef struct
{
    int x;
    int y;
    char symbol[4];  // Default symbol for the enemy    
} Enemy;  // wVw


// FUNCTION PROTOTYPES
// ================================
// Declare function prototypes here, so that we can organize the function implementation after the main function for code readability.

// These are the six required program loop function to build our "McMaster Terminal Program Engine"
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


// Add more function prototypes here as needed



// MAIN PROGRAM
// ===============================
int main(void)
{

    // Start-Up
    Initialize();

    // Program Loop
    while(!exitFlag)  
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();
    }

    // Tear-Down
    CleanUp();

    return 0;

}





// INITIALIZATION ROUTINE
// ===============================
// This routine is run only once before the start of the program loop - aka Start-Up Routine.
// You would typically do the following in this function:
//  1. Initialize global variables
//  2. Allocated memories for dynamic variables (we will talk about this after midterm)
//  3. Call the relevant initialization functions to enable certain library supports.

void Initialize(void)
{
    int i, j;

    // Call the MacUI Library Initialization Function 
    MacUILib_init();
    srand(time(NULL));  // Seed the random number generator

    MacUILib_printf("System Initialized...\n");

    // [TODO]: Initialize variables
    exitFlag = 0;  // 0 - do not exit, non-zero - exit the program
    score = 0;  // Initialize score
    
    // [TODO]: Add more variables initializations here as seen needed.

    // In PPA2, you must create Player, Enemy, and Bullet instances on the Heap.  
    // Stack instances for the three mentioned game objects will result in 5 mark deduction.

    MacUILib_printf("Game Ready to Start!\n");
    
    MacUILib_clearScreen();  // Clear the screen before starting the program loop
}






// INPUT COLLECTION ROUTINE - "Observe"
// ===============================
// In our program loop setup, we always try to first determine whether there is any incoming input.
// This routine should be "non-blocking" (asynchronous input) by default.

void GetInput(void)
{

    // [TODO]: The most basic asynchronous input collection algorithm is:
    //   1. Check whether there is any unprocessed input character - read the lab manual and see which MacUILib function you need to use.
    //   2. If there is an input character waiting to be processed, get the character and store it as the "command"
    //      - again, read the lab manual to find out which MacUILib function you need to use.
    //   3. If there is no input character to be processed, just don't do anything and move on.
    if(MacUILib_hasChar())
    {
        inputChar = MacUILib_getChar();        
    }

    // In PPA2, you will need to process additional inputs to ensure full control over our 
    // playable starship. Read Manual!

}




// MAIN LOGIC ROUTINE - "Think"
// ===============================
// Execute the main program logic.  
// In this routine, we should determine the outcome of the logic using 
//    a) current status / state / behaviour of the program, and 
//    b) the most recent input
// The outcome of the logic then will be drawn on the screen.
//
// In PPA2, this will mainly involve:
//    a) Updating the state of the player starship
//    b) Updating the enemy ships
//    c) Create bullets when player shoots
//    d) Check if bullet collides with enemy ships -> destroy enemy ship if collided.

void RunLogic(void)
{    
    // [TODO]: Implement the features in the lab manual
    
    // DO NOT print anything out.  This routine is the "thinking" part, not the "acting" part.
    // You should only update all the key program parameters here.
     
}







// DRAW ROUTINE - "Act"
// ===============================
// This routine creates the output of the program for a given iteration, using the resultant parameters from the RunLogic() routine.
// In the completed program, this should be the only routine calling the MACUILib_printf().
// If we apply the animation technique discussed in the lab document, we can then create a smooth marquee display animation on the terminal.

void DrawScreen(void)
{
    // Pesudocode
    // 1. Clear the screen
    // 2. Draw the contents of the Game Board (refer to Manual)

    // [TODO]: Complete the implementation of the above pseudocode
    
    
}





// DELAY ROUTINE - "Wait"
// ===============================
// Sometimes referred to as the "stupidifier", this routine is only intended to slow down the program loop so that
// 1. The animation is not too fast to be appreciated
// 2. The main logic is not executed too often, such that the game won't act too ahead of the player's reaction.  Otherwise, the game will be impossible to be beaten.

void LoopDelay(void)
{
    // [TODO]: For now, just call the MacUILib_Delay routine here, and introduce sufficient delay constant
    MacUILib_Delay(GAME_MASTER_SPEED);  // Delay for 2000 microseconds (2 milliseconds)
}





// TEAR-DOWN ROUTINE
// ===============================
// This routine is run only once at the end of the program right before shutdown, intended to clean up all the resources used by the program.
// This routine is VERY IMPORTANT to prevent memory leak.  We will cover this after the midterm.

void CleanUp(void)
{    
    
    // For now, you only need to call MacUILib_uninit() routine to shut down the MacUILib module.
    MacUILib_uninit();

    // In PPA2, you will have to create Player, Enemies, and Bullets on Heap.
    //  This means you will have to deallocate them here before game shutdown to prevent memory leakage.
}

