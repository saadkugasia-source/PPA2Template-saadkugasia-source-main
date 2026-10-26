#include <stdio.h>
#include <stdlib.h> // to use many functions like calloc or malloc or randome number generation
#include <time.h>   // to seed the rand by time in srand
#include "MacUILib.h"

// hi my name is saad kugasia

// WARNING:  This solution version is VERY OOD-tified.  Students do not have to go this far. :)

// PREPROCESSOR DIRECTIVE CONSTANTS
// ================================
// For program-wide constants, define them here using #define.  Add as seen needed.
#define DIMY 15                // Default Gameboard Size
#define DIMX 30                // Default Gameboard Size
#define GAME_MASTER_SPEED 2000 // Default Game Delay Constant in Microseconds

// GLOBAL VARIABLES
// ================================
int exitFlag; // Program Exiting Flag, used to determine whether to leave the program loop and shutdown the program
int gameover;
char inputChar; // Input Character, used to store the most recent input character for the main program logic to use

// Add more variables here as needed
char **gameBoard; // Game Board, used to store the current state of the game board for display
int score;

// Object: Player
typedef struct // the use of typedef is so we don't have to write struct eveytime!
{
    int x;          // x-coordinate of the starship body ('H')
    int y;          // y-coordinate of the starship body ('H')
    char symbol[4]; // Default symbol for the player
} Player;           // <H>

Player *player;

// Object: Bullet
typedef struct
{
    int x;
    int y;
    char symbol;
} Bullet; // |

Bullet *bullets[3] = {NULL, NULL, NULL};

// Object: Enemy
typedef struct
{
    int x;          // x-coordinate of the starship body ('V')
    int y;          // y-coordinate of the starship body ('V')
    char symbol[4]; // Default symbol for the enemy
} Enemy;            // wVw

Enemy *enemies[3];

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
    while (!exitFlag)
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

// HELPER FUNCTIONS
// ===============================

// Init_Player is just to initialize player and its position!
void Init_Player(Player *player, int xp, int yp)
{

    player->symbol[0] = '<';
    player->symbol[1] = 'H';
    player->symbol[2] = '>';
    player->symbol[3] = '\0'; // every string has this in the back or end of it, afterall string is a array of characters!!

    player->x = xp;
    player->y = yp;
}

void Move_Player(Player *player, int dx)
{
    if (dx == -1)
    {
        if (player->x == 1)
            return;  // when void is there and u need to get out of the function
        player->x--; // to move to leftward
    }
    else if (dx == 1)
    {
        if (player->x == 28)
            return; // when void is there and u need to get out of the function
        player->x++;
    }
}

void Draw_Player(Player *player)
{
    gameBoard[player->y][player->x] = player->symbol[1];
    gameBoard[player->y][(player->x) - 1] = player->symbol[0];
    gameBoard[player->y][(player->x) + 1] = player->symbol[2];
}

void Undraw_Player(Player *player)
{
    gameBoard[player->y][player->x] = ' ';
    gameBoard[player->y][(player->x) - 1] = ' ';
    gameBoard[player->y][(player->x) + 1] = ' ';
}

// Init_Enemy , to initialize the enemy object

void Init_Enemy(Enemy *enemy, int xp, int yp)
{
    enemy->symbol[0] = 'w';
    enemy->symbol[1] = 'V';
    enemy->symbol[2] = 'w';
    enemy->symbol[3] = '\0';

    enemy->x = xp;
    enemy->y = yp;
}

void Move_Enemy(Enemy *enemy)
{
    if (enemy->y >= 14)
    {

        Init_Enemy(enemy, (rand() % (DIMX - 2)) + 1, rand() % 5);
        return;
    }
    enemy->y++;
}

void Draw_Enemy(Enemy *enemy)
{
    gameBoard[enemy->y][enemy->x] = enemy->symbol[1];
    gameBoard[enemy->y][(enemy->x) - 1] = enemy->symbol[0];
    gameBoard[enemy->y][(enemy->x) + 1] = enemy->symbol[2];
}

void Undraw_Enemy(Enemy *enemy)
{
    gameBoard[enemy->y][enemy->x] = ' ';
    gameBoard[enemy->y][(enemy->x) - 1] = ' ';
    gameBoard[enemy->y][(enemy->x) + 1] = ' ';
}

// Bullet functions

void Init_Bullet(Bullet *bullet, int xp, int yp)
{
    bullet->symbol = '|';
    bullet->x = xp;
    bullet->y = yp;
}

void Undraw_Bullet(Bullet *bullet) // the reason i had to put Undraw_Bullet here is because i am using it in Move_Bullet() function.
{
    gameBoard[bullet->y][bullet->x] = ' ';
}

void Move_Bullet(Bullet *bullet)
{
    if (bullet->y == 0)
    {
        Undraw_Bullet(bullet);
        return;
    }
    bullet->y--;
}

void Draw_Bullet(Bullet *bullet)
{
    gameBoard[bullet->y][bullet->x] = '|';
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
    srand(time(NULL)); // Seed the random number generator

    MacUILib_printf("System Initialized...\n");

    // [TODO]: Initialize variables
    exitFlag = 0; // 0 - do not exit, non-zero - exit the program
    gameover = 0;
    score = 0; // Initialize score

    // [TODO]: Add more variables initializations here as seen needed.

    // In PPA2, you must create Player, Enemy, and Bullet instances on the Heap.
    // Stack instances for the three mentioned game objects will result in 5 mark deduction.
    MacUILib_clearScreen(); // Clear the screen before starting the program loop

    // Init_Player();
    player = (Player *)malloc(sizeof(Player));
    Init_Player(player, 14, 13);

    // Init_Enemy();
    // enemy = (Enemy *)malloc(sizeof(Enemy));
    // Init_Enemy(enemy, (rand() % (DIMX - 2)) + 1, rand() % 5);
    for (i = 0; i < 3; i++)
    {
        enemies[i] = (Enemy *)malloc(sizeof(Enemy));
        Init_Enemy(enemies[i], (rand() % (DIMX - 2)) + 1, rand() % 5);
    }

    // Init_Bullet(); its the only one to be intialized in the get_input() routine

    // GAMEBOARD
    gameBoard = malloc(DIMY * sizeof(char *)); // to put gameBoard on heap and its sizeof(char *) because gameBoard is a array of pointers pointing a char, i.e char*, so we need the size of pointers.
    for (i = 0; i < DIMY; i++)
    {
        gameBoard[i] = malloc(DIMX * sizeof(char)); // now we have a rows of chars, so we just need the size of char and not char*
        for (j = 0; j < DIMX; j++)
        {
            gameBoard[i][j] = ' '; // this is same as *(*(gameBoard + i ) + j)
        }
    }
    MacUILib_printf("Game Ready to Start!\n");
}

// INPUT COLLECTION ROUTINE - "Observe"
// ===============================
// In our program loop setup, we always try to first determine whether there is any incoming input.
// This routine should be "non-blocking" (asynchronous input) by default.

void GetInput(void)
{
    int i;
    // [TODO]: The most basic asynchronous input collection algorithm is:
    //   1. Check whether there is any unprocessed input character - read the lab manual and see which MacUILib function you need to use.
    //   2. If there is an input character waiting to be processed, get the character and store it as the "command"
    //      - again, read the lab manual to find out which MacUILib function you need to use.
    //   3. If there is no input character to be processed, just don't do anything and move on.
    if (MacUILib_hasChar())
    {
        inputChar = MacUILib_getChar();
    }
    else
    {
        inputChar = '\0';
    }

    switch (inputChar)
    {
    case 'X':
    case 'x':
        exitFlag = 1;
        break;
    case 'A':
    case 'a':
        Undraw_Player(player);
        Move_Player(player, -1);
        break;
    case 'D':
    case 'd':
        Undraw_Player(player);
        Move_Player(player, 1);
        break;
    case ' ': // to check if the user pressed spacebar
        for (i = 0; i < 3; i++)
        {
            if (bullets[i] == NULL)
            {
                // bullet = (Bullet *)malloc(sizeof(Bullet));
                // Init_Bullet(bullet, player->x, (player->y) - 1);
                bullets[i] = (Bullet *)malloc(sizeof(Bullet));
                Init_Bullet(bullets[i], player->x, (player->y) - 1);
                break; // Stop searching once we've spawned our one bullet!
            }
        }
        break;
    default:
        break;
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
    // THE BELOW SECTION OF CODE MAKES THE ENEMY MOVE EVERY 10 FRAMS.
    int i, j;
    static int enemyMoveCounter = 0; // basically is a gloabal variable, i.e it is stored in the static part of the memory.

    // Only move the enemy every 10 game ticks (adjust this number to speed up or slow down)
    enemyMoveCounter++;
    if (enemyMoveCounter >= 10)
    {
        // Undraw_Enemy(enemy);
        // Move_Enemy(enemy);
        for (i = 0; i < 3; i++)
        {
            Undraw_Enemy(enemies[i]);
            Move_Enemy(enemies[i]);
        }
        enemyMoveCounter = 0;
    }

    for (i = 0; i < 3; i++)
    {
        if (bullets[i] != NULL)
        {
            Undraw_Bullet(bullets[i]);
            Move_Bullet(bullets[i]);

            if (bullets[i]->y == 0) // Check out of bounds
            {
                free(bullets[i]);
                bullets[i] = NULL;
            }
            else
            {
                for (j = 0; j < 3; j++) // Check collision against all 3 enemies
                {
                    if (bullets[i]->y == enemies[j]->y)
                    {
                        if (bullets[i]->x == enemies[j]->x ||
                            bullets[i]->x == (enemies[j]->x) - 1 ||
                            bullets[i]->x == (enemies[j]->x) + 1)
                        {
                            Undraw_Enemy(enemies[j]);
                            Init_Enemy(enemies[j], (rand() % (DIMX - 2)) + 1, rand() % 5);

                            free(bullets[i]);
                            bullets[i] = NULL;

                            score += 10;
                            break; // Bullet is freed, stop checking other enemies for this bullet
                        }
                    }
                }
            }
            // else if (bullet->y == enemy->y)
            // {
            //     if (bullet->x == enemy->x || bullet->x == (enemy->x) - 1 || bullet->x == (enemy->x) + 1)
            //     {
            //         Undraw_Enemy(enemy);
            //         free(bullet);
            //         bullet = NULL;
            //         Init_Enemy(enemy, (rand() % (DIMX - 2)) + 1, rand() % 5);
            //         score += 10;
            //     }
            // }
        }
    }

    for (i = 0; i < 3; i++)
    {
        if (enemies[i]->y == player->y)
        {
            if (abs(enemies[i]->x - player->x) <= 2) // to cover all cases of the player and enemies colliding
            {
                gameBoard[player->y][player->x] = ' ';
                gameover = 1;
            }
        }
    }

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
    int i, j;
    // Pesudocode
    // 1. Clear the screen
    // 2. Draw the contents of the Game Board (refer to Manual)
    MacUILib_clearScreen(); // Clear the screen before starting the program loop

    if (gameover != 1)
        Draw_Player(player);
    else
        Undraw_Player(player);

    // Draw_Enemy(enemy);
    for (i = 0; i < 3; i++)
    {
        Draw_Enemy(enemies[i]);
    }

    for (i = 0; i < 3; i++)
    {
        // if (bullet != NULL)
        // {
        //     Draw_Bullet(bullet);
        // }
        if (bullets[i] != NULL)
        {
            Draw_Bullet(bullets[i]);
        }
    }

    // GAMEBOARD
    for (i = 0; i < DIMY; i++)
    {
        for (j = 0; j < DIMX; j++)
        {
            MacUILib_printf("%c", gameBoard[i][j]);
        }
        MacUILib_printf("\n");
    }

    if (gameover == 0)
    {
        MacUILib_printf("=============================\n");
        MacUILib_printf("Your Current Score is:%d", score);
    }
    if (gameover == 1)
    {
        MacUILib_printf("Your Score is:%d\n", score);
        MacUILib_printf("=============================\n");
        MacUILib_printf("GAME OVER \t WASTED\n");
        MacUILib_printf("=============================");
        exitFlag = 1;
    }
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
    MacUILib_Delay(GAME_MASTER_SPEED); // Delay for 2000 microseconds (2 milliseconds)
}

// TEAR-DOWN ROUTINE
// ===============================
// This routine is run only once at the end of the program right before shutdown, intended to clean up all the resources used by the program.
// This routine is VERY IMPORTANT to prevent memory leak.  We will cover this after the midterm.

void CleanUp(void)
{
    int i;
    // For now, you only need to call MacUILib_uninit() routine to shut down the MacUILib module.
    MacUILib_uninit();
    // line 237 and 238 are both required and equally important
    if (gameBoard != NULL)
    {
        for (int i = 0; i < DIMY; i++) // this loop is to clean all the rows first
        {
            free(gameBoard[i]); // here we are cleaning the rows i.e the pointer
            gameBoard[i] = NULL;
        }
        free(gameBoard); // then finally we clean the main double pointer which is gameBoard
        gameBoard = NULL;
    }
    free(player);
    player = NULL;

    // free(enemy);
    // enemy = NULL;
    for (i = 0; i < 3; i++)
    {
        free(enemies[i]);
        enemies[i] = NULL;
    }
    for (i = 0; i < 3; i++)
    {
        if (bullets[i] != NULL)
        {
            free(bullets[i]);
            bullets[i] = NULL;
        }
    }
    // In PPA2, you will have to create Player, Enemies, and Bullets on Heap.
    //  This means you will have to deallocate them here before game shutdown to prevent memory leakage.
}
