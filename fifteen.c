/**
 * fifteen.c
 *
 * Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
 
void init(void)
{
    int dimension = d * d;
    // column
    for (int i = 0; i < d; i++)
    {
        // row
        for (int j = 0; j < d; j++)      
        {   
            // last blank is d sqrd - 1 
            board[i][j] = dimension - 1;
                   
            // if even, switch 2 to 1   
            if (d % 2 == 0 && board[i][j] == 2)
            {
                board[i][j] = 1;
                dimension--;
            }
            // if even switch 1 to 2
            else if (d % 2 == 0 && board[i][j] == 1)
            {
                board[i][j] = 2;
                dimension--;
            }
            // if block equal to 0, fill space
            else if (board[i][j] <= 0)
            {
                board[i][j] = 100;
            }
            
            else
            {
                dimension--;              
            }                          
        }
    }
}

/**
 * Prints the board in its current state.
 */
 
void draw(void)
{
    // columns
    for (int i = 0; i < d; i++)
    {
        // rows
        for (int j = 0; j < d; j++)
        {
            //if blank
            if (board[i][j] == 100)
            {
                printf(" _");
            }
            // print value    
            else
            {
                printf("%2d", board[i][j]);
            }           
        }
        
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{   
    while (tile < d * d)
    {   
        // column
        for (int i = 0; i < d; i++)
        {
            // row
            for (int j = 0; j < d; j++)    
            {
                if (board[i][j] == tile)
                {
                    // check                
                    if (board[i + 1][j] == 100)
                    {
                        // swap below
                        board[i + 1][j] = tile;
                        board[i][j] = 100;
                        
                        return true;
                                           
                    }
                    
                    else if (board[i][j + 1] == 100)
                    {
                        // swap right
                        board[i][j + 1] = tile;
                        board[i][j] = 100;
                        
                        return true;              
                    }
                    
                    else if (board[i - 1][j] == 100)
                    {
                        // swap above
                        board[i - 1][j] = tile;
                        board[i][j] = 100;
                        
                        return true;                 
                    }
                    
                    else if (board[i][j - 1] == 100)
                    {
                        // swap left 
                        board[i][j - 1] = tile;
                        board[i][j] = 100;
                        
                        return true;
                    }
                    
                    // if blank not adj
                    else
                    {
                        return false;
                    }            
                }
                                     
            }
        }
        
        return true;
    }./fifteen 3 < ~cs50/pset3/3x3.txt
        
    return false;    
}

/*
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
 
bool won(void)
{   
    int check = 1;
    
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {            
            if(board[i][j] == check || board[i][j] == 100)
            {
                check++;
            }
            else
            {
                return false;
            }
        }  
    }

    return true;
}

/*
 * Saves the current state of the board to disk (for testing).
 */
 
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}

