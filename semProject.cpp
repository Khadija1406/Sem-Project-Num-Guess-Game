#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//ANSI colour codes
#define CYAN        "\033[1;36m"
#define RED         "\033[1;31m"
#define YELLOW      "\033[1;33m"
#define BLUE        "\033[1;34m"
#define GREEN       "\033[1;32m"
#define MAGENTA     "\033[1;35m"
#define GRAY        "\033[1;30m"
#define ORANGE      "\033[38;5;208m"
#define LIGHT_PINK  "\033[38;5;218m"
#define RESET       "\033[0m"

typedef struct
{
    int upperLimit;
    int maxAttempts;
} gameLevel;

//just prints a line
void printLine()
{
    printf("\t\t\t\t=================================================================\n");
}
/// prints a long line with magenta colour
void printLongLine()
{
    printf(MAGENTA "\t================================================================================================================\n" RESET);
}
//prints title with a beautiful cyan colour and magenta title title border lines too
void printTitle()
{   
    printLongLine();   
    printf(CYAN "\t\t\t\t\t   ??? WELCOME TO THE NUMBER GUESSING GAME ???\n" RESET);
   
    printLongLine(); 
    printf(ORANGE "\n\n\tWelcome to the Number Guessing Game! Choose from Easy, Medium, or Hard levels. The computer will try to guess \n\tyour number based on your feedback. Your cheat can easily be detected so be careful. Let's begin!\n" RESET);

}
//takes input untill a next line
void clearInput()
{
    while (getchar() != '\n');
}

void waitEnterInput()
{
    printf(GRAY "\t\t\t\t\t\tPress ENTER when you're ready......" RESET);
    getchar();
}

void showInstructions()
{
    printLine();
    printf(CYAN "\t\t\t\tThink of a number based on selected difficulty and DON'T TELL ME!\n");
    printf("\t\t\t\t   I will try to guess it in the minimum number of attempts!\n" RESET);
    printLine();
}
//asking for user respone
char getUserResponse(int guess)
{
    char response;
    printf("\n\tIs your number %d?\n", guess);
    printf(MAGENTA "\tEnter:\n" RESET);
    printf("\t  'h' if your number is higher than %d\n", guess);
    printf("\t  'l' if your number is lower than %d\n", guess);
    printf("\t  'c' if I guessed correctly\n");
    printf("\tYour response : ");
    scanf(" %c", &response);
    clearInput();
    return response;
}
//printing celebration messages
void printCelebration(int guess, int count)
{
    printf(GREEN "\n\t\t\tGreat! I guessed your number %d correctly!\n", guess);
    printf("\t\t\tIt took me %d attempt%s to get it right!\n" RESET, count, count == 1 ? "" : "s");

    if (count <= 5)
    {
        printf(GREEN "\t\t\tAwesomeee! That was fast!\n" RESET);
    }
    else if (count <= 7)
    {
        printf(BLUE "\t\t\tNot baddd! I am getting there.\n" RESET);
    }
    else
    {
        printf(YELLOW "\t\t\tWhewww! That took a while......\n" RESET);
    }
    printLongLine();
    printf("\a"); //beep when answer is judged correctly
}

void cheatDetected()
{
    printf("\a");
    printf(RED "\n\tWait a minute..... There is some problem!\n");
    printf("\tYour answers are inconsistent. Are you changing your number?\n" RESET);
}
//code to handle the whole game
void handleGame(int low, int high, int maxAttempts)
{
    int guess = 0;
    int attempts = 0;
    char response;

    showInstructions();
    waitEnterInput();
    while (low <= high)
    {
        if (attempts >= maxAttempts)
        {
            printf(RED "\n\tYou have exceeded the maximum number of attempts (%d)! Better luck next time.\n" RESET, maxAttempts);
            return;
        }

        guess = (low + high) / 2;
        attempts = attempts + 1;
        response = getUserResponse(guess);

        if (response == 'h' || response == 'H')
        {
            low = guess + 1;
        }
        else if (response == 'l' || response == 'L')
        {
            high = guess - 1;
        }
        else if (response == 'c' || response == 'C')
        {
            printCelebration(guess, attempts);
            return;
        }
        else
        {
            printf("\a");//beep for invalid input and next line shows error message in red
            printf(RED "\n\tInvalid input! Please enter only h, l, or c. Try again.\n" RESET);
            attempts = attempts - 1;
        }

        if (low > high)
        {
            cheatDetected();
            return;
        }
        printf(LIGHT_PINK "\tRemaining Attempts: %d\n" RESET, maxAttempts - attempts);
       
    }
}
//part to ask user if he wants to play again or not using do while
char askPlayAgain()
{
    char choice;
    printf(YELLOW "\n\tWould you like to play again? (y/n) : " RESET);
    scanf(" %c", &choice);
    clearInput();
    return choice;
}
//printing farewell bye bye message
void farewellMessage()
{
    printLine();
    printf(BLUE "\t\t\t\t\t     Thank you for playing ! BYEEE BYEEE!\n");
    printf("\t\t\t\t\t\tProject by: KHADIJA NAEEM KHAN\n");
    printf("\t\t\t\t\t\t  Roll No. : BSEF24MO43\n" RESET);
    printLine();
}
//using struct here to define our upper limit and max attempts to operate program with their help
gameLevel selectLevel()
{
    gameLevel levelData;
    char input[100];
    int level;
    int valid = 0;
    int attempts = 0;

    while (!valid && attempts < 3)
    {
        printf(YELLOW "\n\tSelect Difficulty Level:\n\n");
        printf("\t  1. Easy   (1 - 50)   --> Max 6 attempts for this level\n");
        printf("\t  2. Medium (1 - 100)  --> Max 7 attempts for this level\n");
        printf("\t  3. Hard   (1 - 500)  --> Max 9 attempts for this level\n\n");
        printf("\tEnter your choice (1-3): " RESET);

        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%d", &level) != 1)
        {
            printf("\a");
            printf(RED "\n\tInvalid input! Please enter a number (1, 2, or 3).\n" RESET);
            attempts = attempts + 1;
            continue;
        }

        if (level < 1 || level > 3)
        {
            printf("\a");
            printf(RED "\n\tInvalid level! Please choose between 1 and 3.\n" RESET);
            attempts = attempts + 1;
            continue;
        }

        valid = 1; // Valid input received
    }

    // go to default if too many failed attempts
    if (!valid)
    {
        printf(RED "\n\tToo many invalid attempts. Defaulting to Medium level.\n" RESET);
        printf("\a");
        level = 2;
    }

    // give values based on selected level
    if (level == 1)
    {
        levelData.upperLimit = 50;
        levelData.maxAttempts = 6;
        printf(BLUE "\n\tYou selected Easy. Number range is 1 to 50, and you have 6 attempts.\n" RESET);
    }
    else if (level == 2)
    {
        levelData.upperLimit = 100;
        levelData.maxAttempts = 7;
        printf(BLUE "\n\tYou selected Medium. Number range is 1 to 100, and you have 7 attempts.\n" RESET);
    }
    else // level  3
    {
        levelData.upperLimit = 500;
        levelData.maxAttempts = 9;
        printf(BLUE "\n\tYou selected Hard. Number range is 1 to 500, and you have 9 attempts.\n" RESET);
    }

    return levelData;
}

int main()
{
    char playAgain;
    int isFirstGame = 1;
    gameLevel levelData;
    do
    {
        if (isFirstGame)
        {
            printTitle();
            isFirstGame = 0;
        }
        levelData = selectLevel();
        handleGame(1, levelData.upperLimit, levelData.maxAttempts);
        playAgain = askPlayAgain();

    } while (playAgain == 'y' || playAgain == 'Y');

    farewellMessage();
    return 0;
}
