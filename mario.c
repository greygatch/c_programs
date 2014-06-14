/*

mario.c

I built a half pyramid, like on one in the old Mario games. 

*/

int main(void)
{   
    int* height;
    do
    {   
        // prompt for input
        
        printf("This program constructs a half-pyramid. Please choose an integer from 1-23 to select the height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    for (int row = 1; row <= height; row++)
    {
        // formula for hashes and spaces
        
        int spaces = height - row;
        int hashes = row + 1;
        
        // incremental gains, then next line.   
        
        for (int x = 1; x <= spaces; x++)
            {
                printf(" ");
            }
        for (int y = 1; y <= hashes; y++)
            {
                printf("#");
            }    
                printf("\n");
    }                
}
