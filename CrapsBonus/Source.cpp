#include <iostream>
#include <time.h>  // For time, to set our random seed as close to true random as possible

void clearcin();
int RollDice();
int WinCheck(int Check, int Point);

int NumSnakeEyes{};
int NumRolls{};

int main() {

    int DiceResult{};
    int Point{};
    int WinCon{};
    bool RepeatGame{};
    char RepeatAns{};
    char RepeatQuestion{};
    int NumSims{};
    int NumWins{};
    int NumLoss{};


    srand(time(NULL)); // Set the random seed to current system time, so we don't get the exact same pattern of dice every time

    do {
        system("cls"); // Clear the screen of any potential previous game
        NumWins = 0; // Re-initialize the win/loss/snake eyes variables, in case this is a repeat of the program
        NumLoss = 0;
        NumSnakeEyes = 0;
        std::cout << "Hello, and welcome to Craps simulator! The rules of Craps is as follows:\n"
            << "You will throw two dice, and your score will be the sum of these dice.\n"
            << "If you score 7 or 11, you win! But if you score 2, 3 or 12, you lose.\n"
            << "If you score anything other than that, your score will become your \"point\" and you will throw the dice again.\n"
            << "If you then get a 7, you lose! But if you roll the same score as your point, you will win!\n"
            << "You will then keep throwing the dice until you either win or lose.\n"
            << "This program will simulate as many games of Craps as you'd like, and count the amount of wins, losses, and snake eyes (1 on both dice).\n"
            << "So, how many simulations would you like to run ? \n";
        std::cin >> NumSims;
        clearcin();
        for (int i{}; i < NumSims; i++) {
            DiceResult = RollDice();
            Point = 0; // Set the point to 0, so WinCheck works for the first roll
            if (WinCheck(DiceResult, Point) == 2) {
                Point = DiceResult;
                do {
                    DiceResult = RollDice();
                } while (WinCheck(DiceResult, Point) == 2);
            }
            switch (WinCheck(DiceResult, Point)) {
            case 0:
                NumLoss++;
                break;
            case 1:
                NumWins++;
                break;
            default:
                std::cout << "Something went wrong, please tell me how you broke my program!";
                EXIT_FAILURE;
            }
        }
        std::cout << "You simulated " << NumSims << " games of Craps, and in those you got the following stats:\n"
            << "Number of wins: " << NumWins << "\n"
            << "Number of losses: " << NumLoss << "\n"
            << "Number of times you rolled a die: " << NumRolls << " (2 dice " << NumRolls / 2 << " times)\n"
            << "Number of times you rolled snake eyes:" << NumSnakeEyes << "\n";
        do {
            // Ask if you want to simulate the game again, and set RepeatGame accordingly
            std::cout << "Would you like to simulate again?\n"; /* No need to tell them to use Y / N format, since
                                                            we store the answer in a char variable, it will only
                                                            take the first letter anyway*/
            std::cin >> RepeatAns;
            clearcin();
            RepeatAns = toupper(RepeatAns); /* We set the character to its uppercase equivalent, so we only get
                                            2 condition checks instead of 4*/
            switch (RepeatAns) {
            case 'Y':
                RepeatQuestion = false;
                RepeatGame = true;
                break;
            case 'N':
                RepeatQuestion = false;
                RepeatGame = false;
                std::cout << "Very well, goodbye for now!";
                break;
            default:
                std::cout << "That's not a valid answer! Please answer yes or no.\n";
                RepeatQuestion = true;
                break;
            }
        } while (RepeatQuestion);


    } while (RepeatGame);
}

int RollDice() {

    int Result{};
    int FirstDie{};
    int SecondDie{};

    FirstDie = rand() % 6 + 1; // Roll a random number between 1 and 6
    SecondDie = rand() % 6 + 1;
    Result = FirstDie + SecondDie;
    if (FirstDie == 1 && SecondDie == 1) {
        NumSnakeEyes++;
    }
    NumRolls = NumRolls + 2;

    return Result;
}

int WinCheck(int Check, int Point) {

    if (Point == 0) {
        if (Check == 7 || Check == 11) {
            return 1;
        }
        else if (Check == 2 || Check == 3 || Check == 12) {
            return 0;
        }
        else {
            return 2;
        }
    }
    else {
        if (Check == Point) {
            return 1;
        }
        else if (Check == 7) {
            return 0;
        }
        else {
            return 2;
        }
    }
}

/* Function to clear out the buffer of cin, ensuring we don't take in more than one word and get weird inputs
(or worse, infinite loops)*/
void clearcin() {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
}