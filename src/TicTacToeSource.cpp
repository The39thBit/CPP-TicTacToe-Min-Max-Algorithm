//Abdurrahman Aliyu Gambo || The39thBit ||March 2023
#include "TicTacToeVector.h"
#include<ctype.h>
#include <iostream>
class PvP {
public:
    int location;
    char userlocation = ' ';
    Board PvPBoard;
    void PVP() {
        while (true) {
            //DisplayBoard
            PvPBoard.DisplayBoard();
            //Player 1 Input
            while (true) {
                std::cout << "Player 1 enter a desired location (1-9)" << std::endl;

                std::cin >> userlocation;
                if (isdigit(userlocation)) {
                    //converting location to a form usable by backend
                    location = int(userlocation) - 49;
                    std::cout << "userlocation val = " << userlocation << std::endl;
                    std::cout << "userlocation val int = " << int(userlocation) << std::endl;
                    std::cout << "location val = "<<location << std::endl;
                    if (PvPBoard.CheckValid(location)) {
                        PvPBoard.setX(location);
                        break;
                    }
                    else("This Location is Already Filled Try again");
                }
                else {
                    std::cout << "Invalid Input --- Try again" << std::endl;
                }
            }
            PvPBoard.DisplayBoard();
            if (PvPBoard.GameOverCheck()) {
                if (PvPBoard.gamewin != 0) {
                    std::cout << "Congrats, Player " << PvPBoard.gamewin << " wins" << std::endl;
                }
                else {
                    std::cout << "The game is a draw" << std::endl;
                }
                break;
            }
            //Player 2 Input
            while (true) {
                std::cout << "Player 2 enter a desired location (1-9)" << std::endl;

                std::cin >> userlocation;
                if (isdigit(userlocation)) {
                    //converting location to a form usable by backend
                    location = int(userlocation) - 49;
                    if (PvPBoard.CheckValid(location)) {
                        PvPBoard.setO(location);
                        break;
                    }
                    else("This Location is Already Filled Try again");
                }
                else {
                    std::cout << "Invalid Input --- Try again" << std::endl;
                }
            }
            if (PvPBoard.GameOverCheck()) {
                if (PvPBoard.gamewin != 0) {
                    std::cout << "Congrats, Player " << PvPBoard.gamewin << " wins" << std::endl;
                }
                else {
                    std::cout << "The game is a draw" << std::endl;
                }
                break;
            }
        }
    }
};
class PvC {
public:
    Board PVCBoard; 
    bool PlayerP1;
    bool GameOver = false;
    int playerinput;
    ComputerPlayer Comp;
    bool TurnP1 = true;
    int iter = 0;
    PvC(){
        while (true) {
          
            char input;
            int Choice;
            std::cout << "Select 1 to be Player 1. Select 2 to be Player 2" << std::endl;
            std::cin >> input;
            if (isdigit(input)) {

                //ASCII Conversion
                int Choice = int(input) - 48;
                
                if (Choice == 1) {
                    PlayerP1 = true;
                    PVCBoard.DisplayBoard();
                    PVCBoard.DisplayBoardR();
                    playerinput = PlayerChoose();
                    UpdatePVCBoard(playerinput);
                    PVCBoard.DisplayBoard();
                    PVCBoard.DisplayBoardR();
              
                    //Comp 
                    Comp.SetUp(PVCBoard);
                    Comp.MakeNextMove();
                    UpdatePVCBoard(Comp.CompChoice);
                    PVCBoard.DisplayBoard();
                    PVCBoard.DisplayBoardR();
                   
                 
                }
                else if (Choice == 2) {
                    PlayerP1 = false;
                    PVCBoard.DisplayBoard();
                    PVCBoard.DisplayBoardR();
                    Comp.SetUp(PVCBoard);
                    Comp.MakeNextMove();
                    UpdatePVCBoard(Comp.CompChoice);
                    PVCBoard.DisplayBoard();
                    PVCBoard.DisplayBoardR();
                    PlayerTurn();
               
                
                }
                else {

                    std::cout << "Invalid Choice. Please enter 1 or 2" << std::endl;
                    continue;

                }

                while (!GameOver) {
                    /*std::cout << "Entered RUN GAME " << "Iteration: "<<iter+1<<std::endl;*/
                    iter++;
                    RUNGAME();
                    
                }
                if (GameOver) { break; }
               
               
            }
            continue;
        
        
        }

    }
    int PlayerChoose() {
        while (true)  {
            char squarechoose;
            int choosensquare;
            std::cout << "Select which Square to fill (1-9)" << std::endl;
            std::cin >> squarechoose;
            if (isdigit(squarechoose)) {
               choosensquare = int(squarechoose) - 49;
               if ((choosensquare >= 0) && (choosensquare <9 )) {
                   if (PVCBoard.BoardArray[choosensquare] == 0) {
                       std::cout << "Chosen Square: " << choosensquare+1 << std::endl;
                       return choosensquare;
                   
                   
                   }
                   else {
                       std::cout << "That Square is Already Filled, Try Again" << std::endl;
                       continue;
                   }
                
               
               
               }
               else { 
                   std::cout << "Invalid Input, Try Again" << std::endl;
                   continue; 
               }
            
            }
        
        
        
        }
    
    
    }
    void UpdatePVCBoard(int choice) {
        if (PVCBoard.BoardArray[choice] == 0) {
            if (TurnP1) {
                PVCBoard.BoardArray[choice] = 1;

            }
            else {
                PVCBoard.BoardArray[choice] = 2;
            }
            TurnP1 = !TurnP1;
        }
        else {
        
            std::cout << "ERROR||Invalid Input -> This Square is Already Filled" << std::endl;
        }
    
    }
    void PlayerTurn() {
        playerinput = PlayerChoose();
        UpdatePVCBoard(playerinput);
        PVCBoard.DisplayBoard();
        PVCBoard.DisplayBoardR();
        Comp.UpdateBoard(playerinput);
    
    }
    void CompTurn() {
        Comp.MakeNextMove();
        UpdatePVCBoard(Comp.CompChoice);
        PVCBoard.DisplayBoard();
        PVCBoard.DisplayBoardR();
    }
    void RUNGAME() {
        if (!GameOver) {
            if (PlayerP1) {
                //Player Input
                PlayerTurn();

                //Check
                if (PVCBoard.GameOverCheck()) {
                    GameOver = true;
                    return;

                }

                //Comp Input
                CompTurn();
            }
            else {

                //Comp Input
                CompTurn();

                //Check
                if (PVCBoard.GameOverCheck()) {
                    GameOver = true;
                    return;
                
                }

                //Player Input
                PlayerTurn();
                if (PVCBoard.GameOverCheck()) {
                    GameOver = true;
                    return;

                }

            }

            if (PVCBoard.GameOverCheck()) {
                GameOver = true;

            }

        }
    }
};

int main() {
    
   PvC pvc;
    
    return 0;
}