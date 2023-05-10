#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include "ExtraFunctions.h"
#include <memory>

//TODO TempPath saved to nodes using VectorToInt(), doesn't work for move 1 = 0, therefore a switch to VectorToString() may be necessary

my_ostream fout;
my_rstream rout;
class Board {
public:
    int gamewin = 4;
    std::vector<int>BoardArray = { 0,0,0,0,0,0,0,0,0 };
    void setX(int location) {
        BoardArray[location] = 1;


    }
    void setO(int location) {
        BoardArray[location] = 2;

    }
    bool CheckValid(int location) {
        if (BoardArray[location] != 0) {
            std::cout << "Invalid Move" << std::endl;
            return false;
        }
        return true;
    }
    char ReturnVal(int location) {
        if (BoardArray[location] == 0) {
            return ' ';
        }
        if (BoardArray[location] == 1) {
            return 'X';
        }
        if (BoardArray[location] == 2) {
            return 'O';
        }
        else { return 'E'; }


    }
    void DisplayBoard() {

        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0) {
                std::cout << std::endl;
               
                std::cout << "---------------" << std::endl;
              
            }
           std::cout << ReturnVal(i) << " || ";
           
        }
        std::cout << std::endl;
       
    }
    void DisplayBoardF() {

        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0) {
               
                fout << std::endl;

                fout << "---------------" << std::endl;
            }
           
            fout << ReturnVal(i) << " || ";
        }

        fout << std::endl;
    }
    void DisplayBoardR() {
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0) {
                rout << std::endl;

                rout << "---------------" << std::endl;

            }
            rout << ReturnVal(i) << " || ";

        }
        rout << std::endl;

    }
    bool GameOverCheck() {

        //Check if Player has won
            //Verticals
        for (int i = 0; i < 3; i++) {

            if ((BoardArray[0 + i] == BoardArray[3 + i]) && (BoardArray[0 + i] == BoardArray[6 + i]) && (BoardArray[0 + i] != 0)) {
                gamewin = BoardArray[0 + i];
                std::cout << i << std::endl;
                std::cout << "Win in Column " << i + 1 << std::endl;
                return true;
            }
        }
        //Horizontals
        for (int i = 0; i < 3; i++) {
            if ((BoardArray[3 * i] == BoardArray[3 * i + 1]) && (BoardArray[3 * i] == BoardArray[3 * i + 2]) && (BoardArray[3 * i] != 0)) {
                gamewin = BoardArray[3 * i];
                std::cout << "Win in Row " << i + 1 << std::endl;
                return true;

            }
        }
        //Diagonals
        if ((BoardArray[0] == BoardArray[4]) && (BoardArray[0] == BoardArray[8]) && (BoardArray[0] != 0)) {
            gamewin = BoardArray[0];
            std::cout << "Win in Diagonal Left To Right " << std::endl;
            return true;
        }
        if ((BoardArray[2] == BoardArray[4]) && (BoardArray[2] == BoardArray[6]) && (BoardArray[2] != 0)) {
            gamewin = BoardArray[2];
            std::cout << "Win in Diagonal Right to Left" << std::endl;
            return true;
        }
        //If all squares are filled
        for (int i = 0; i < BoardArray.size(); i++)
        {
            if (BoardArray[i] == 0) {

                break;

            }
            if (i == 8) {
                gamewin = 0;
                std::cout << "The Game is a Draw" << std::endl;
                return true;

            }
            else {
                continue;
            }

        }
        return false;

    }
    bool GameOverCheckSilent() {

        //Check if Player has won
            //Verticals
        for (int i = 0; i < 3; i++) {

            if ((BoardArray[0 + i] == BoardArray[3 + i]) && (BoardArray[0 + i] == BoardArray[6 + i]) && (BoardArray[0 + i] != 0)) {
                gamewin = BoardArray[0 + i];
                return true;
            }
        }
        //Horizontals
        for (int i = 0; i < 3; i++) {
            if ((BoardArray[3 * i] == BoardArray[3 * i + 1]) && (BoardArray[3 * i] == BoardArray[3 * i + 2]) && (BoardArray[3 * i] != 0)) {
                gamewin = BoardArray[3 * i];

                return true;

            }
        }
        //Diagonals
        if ((BoardArray[0] == BoardArray[4]) && (BoardArray[0] == BoardArray[8]) && (BoardArray[0] != 0)) {
            gamewin = BoardArray[0];

            return true;
        }
        if ((BoardArray[2] == BoardArray[4]) && (BoardArray[2] == BoardArray[6]) && (BoardArray[2] != 0)) {
            gamewin = BoardArray[2];

            return true;
        }
        //If all squares are filled
        for (int i = 0; i < BoardArray.size(); i++)
        {
            if (BoardArray[i] == 0) {

                break;

            }
            if (i == 8) {
                gamewin = 0;
                return true;

            }
            else {
                continue;
            }

        }
        return false;

    }
};
struct IndexDetails {
    int index;
    //if eval 1->winning for parent node, 2->draw for parent 3-> loss for parent, default of 0 means it has not been evaluated.
    int eval = 0;


};
struct BoardNodeArr {
    //Level of root by default
    int TreeLevel = 0;
    //not a leaf by default
    bool isLeaf = false;
    //Board of this Node
    Board BoardOfNode;
    //Evaluation of Node (as will be determined from the leaf nodes to the top of the tree)---> Is this node going to lead to a win or a draw or a loss (ValidChildNodes Hold All the non-losing choices))
    int NodeEvaluation = 4;
    //This value determines if node is to play Xs or Os if X -> true, if 0 -> false
    bool isNodePlayer1;
    int path;
    std::string Path;
    //By default Index is 0 (root node). It is assigned during BoardNodeArr creation by Parent Node
    int Index = 0;
    int ParentIndex;
    std::vector<IndexDetails>ChildIndexes;
 
    ~BoardNodeArr() {
      //  std::cout << "Object at location: "<< this << " deconstructed"<<std::endl;
    }
    void CheckLeaf() {
        BoardOfNode.GameOverCheck();
        if (BoardOfNode.gamewin != 4) {
            //Game is Completed therefore this is a leaf node
            isLeaf = true;

        }
        else {
            isLeaf = false;

        }



    }
    void CheckLeafSilent() {
        BoardOfNode.GameOverCheckSilent();
        if (BoardOfNode.gamewin != 4) {
            //Game is Completed therefore this is a leaf node
            isLeaf = true;
        }
        else {
            isLeaf = false;

        }



    }
    void LeafResult() {
        CheckLeafSilent();
        if (isLeaf) {
            if (BoardOfNode.gamewin == 0) {
                std::cout << " Draw " << std::endl;
            }
            if (BoardOfNode.gamewin == 1)
            {
                std::cout << " Win for Xs " << std::endl;
            }
            if (BoardOfNode.gamewin == 2)
            {
                std::cout << " Win for Os" << std::endl;
            }
        }


    }
    void LeafEvaluation() {
        CheckLeafSilent();
        if (isLeaf) {

            if (BoardOfNode.gamewin == 0) {
                NodeEvaluation = 0;
                //std::cout << "Node with Index: " << Index << "Set to Evaluation 0" << std::endl;
            }
            if (BoardOfNode.gamewin == 1)
            {
                NodeEvaluation = 1;
                //std::cout << "Node with Index: " << Index << "Set to Evaluation 1" << std::endl;
            }
            if (BoardOfNode.gamewin == 2)
            {
                NodeEvaluation = -1;
                //std::cout << "Node with Index: " << Index << "Set to Evaluation -1" << std::endl;
            }
            //std::cout << "Node with Index: " << Index << "Set to Evaluation " << NodeEvaluation << std::endl;
        }

    }
    void setNodePlayer() {
        if (TreeLevel % 2 == 0) {
            isNodePlayer1 = true;
        }
        else {
            isNodePlayer1 = false;
        }

    }
    void SetTreeLevel() {
        int rootct = 0;
        for (int i = 0; i < BoardOfNode.BoardArray.size(); i++) {
            if (BoardOfNode.BoardArray[i] != 0) {
                rootct++;
            }
        }
        TreeLevel = rootct;
    
    
    }
    void PrintNodeDetails() {
        std::cout << "Tree Level: " << TreeLevel << " ";
        BoardOfNode.DisplayBoard();


    }
    void AddNodeToTreeArray(Board newBoard, int TreeLevel, std::vector<std::shared_ptr<BoardNodeArr>>* treevector) {
        std::shared_ptr<BoardNodeArr> newnode (new BoardNodeArr());
       
        newnode->BoardOfNode = newBoard;
        //std::cout << "TreeLevel: " << TreeLevel << std::endl;
        newnode->LeafEvaluation();
        newnode->TreeLevel = TreeLevel;
       // std::cout << "Parent Index: " << Index << std::endl;
        newnode->ParentIndex = Index;
        newnode->Index = treevector->size();
        //std::cout << "Node Index: " << treevector->size() << std::endl;
        IndexDetails childindex;
        childindex.index = newnode->Index;
        ChildIndexes.push_back(childindex);
        //std::cout << "ChildIndexes size: " << ChildIndexes.size()<< " for node: " <<Index<< std::endl; 
        treevector->push_back(newnode);
        //std::cout << "Tree Vector Size: " << treevector->size() << std::endl;


    }
    void AddNodeToTreeArray2(Board newBoard, std::vector<BoardNodeArr>* treevector) {
        BoardNodeArr newnode;

        newnode.BoardOfNode = newBoard;
        //std::cout << "TreeLevel: " << TreeLevel << std::endl;
        newnode.LeafEvaluation();
        newnode.SetTreeLevel();
        // std::cout << "Parent Index: " << Index << std::endl;
        newnode.ParentIndex = Index;
        newnode.Index = treevector->size();
        //std::cout << "Node Index: " << treevector->size() << std::endl;
        IndexDetails childindex;
        childindex.index = newnode.Index;
        ChildIndexes.push_back(childindex);
        //std::cout << "ChildIndexes size: " << ChildIndexes.size()<< " for node: " <<Index<< std::endl; 
        treevector->push_back(newnode);
        //std::cout << "Tree Vector Size: " << treevector->size() << std::endl;


    }
};
struct MinMaxTree {
    
    int LeafNodeCt = 0;
    int NodeCt = 0;
    BoardNodeArr VecROOT;

    //For representing the tree using a vector/array
    std::vector<BoardNodeArr>MinMaxTreeNodes;
    std::vector<BoardNodeArr>* MinMaxTreePtr = &MinMaxTreeNodes;
    //This keeps track of the paths to get to a leaf node
    std::vector<int>TempPath;

    void FullTreeCreationVector(Board StartBoard, bool CompFirst) {
        VecROOT.BoardOfNode = StartBoard; 
        VecROOT.SetTreeLevel();
        //Adding Root Node to MinMaxTreeNodes
        MinMaxTreeNodes.push_back(VecROOT);
        //Creating MinMax Tree 
        ChildNodeSetterVector(0, CompFirst);
       
    }
    void ChildNodeSetterVector(int node, bool CompFirst) {
        //This sets the new boardnode with a new board (makes a move)
        std::vector<int>TempArray;
        //Recursive Creation of Min-Max Tree
        for (int i = 0; i < 9; i++) {
            TempArray = MinMaxTreeNodes[node].BoardOfNode.BoardArray;

            //Resetting TempPath once the board has returned to its original state
            if (TempArray == VecROOT.BoardOfNode.BoardArray) {
               
                TempPath = {};
            }
            //Base Case Checking (has a LeafNode been found)
            if (MinMaxTreeNodes[node].BoardOfNode.GameOverCheckSilent() == true) {
                LeafNodeCt++;
                //Setting Leaf Node's Evaluation
                MinMaxTreeNodes[node].LeafEvaluation();
                // Resetting (Backtracking) TempPath
                TempPath.pop_back();
                return;
            }

            //for unfilled squares in the board
            if (MinMaxTreeNodes[node].BoardOfNode.BoardArray[i] == 0) {
                //creating all the child nodes with the different possible boards
                TempPath.push_back(i);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // Case where Computer is X or Player 1
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                
                    if ((MinMaxTreeNodes[node].TreeLevel) % 2 == 0) {
                        TempArray[i] = 1;
                    }
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                // Case where Computer is O or Player 2
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                    else {
                        TempArray[i] = 2;
                    }
                
                
                
                
                //Creating NewBoard
                Board NewBoard;
                NewBoard.BoardArray = TempArray;
                //Adding Node to MinMaxNodeTree
                MinMaxTreeNodes[node].AddNodeToTreeArray2(NewBoard, MinMaxTreePtr);

                
               
                NodeCt++;
                //Determines if this a min or max node
                MinMaxTreeNodes.back().setNodePlayer();
                MinMaxTreeNodes.back().path = VectorToInt(TempPath);
                MinMaxTreeNodes.back().Path = VectorToString(TempPath);

                ChildNodeSetterVector(MinMaxTreeNodes.back().Index, CompFirst);
            }
        }
        if (TempPath.size() > 0) {
            TempPath.pop_back();
        }
        CheckEvalArr(MinMaxTreeNodes[node]);

    }
    void CheckEvalArr(BoardNodeArr board) {

        int WinIndex = 0;
        int DrawIndex = 0;
        if (board.isNodePlayer1) {
            for (int i = 0; i < board.ChildIndexes.size(); i++) {

                if (MinMaxTreeNodes[board.ChildIndexes[i].index].NodeEvaluation == 1) {
                    MinMaxTreeNodes[board.Index].NodeEvaluation = 1;
                    MinMaxTreeNodes[board.Index].ChildIndexes[i].eval = 1; //win for nodeplayer1
                    WinIndex++;
                    

                }
                else if (MinMaxTreeNodes[board.ChildIndexes[i].index].NodeEvaluation == 0) {
                    MinMaxTreeNodes[board.Index].ChildIndexes[i].eval = 2; //draw for nodeplayer1
                    DrawIndex++;
                }
                else if (MinMaxTreeNodes[board.ChildIndexes[i].index].NodeEvaluation == -1) {
                    MinMaxTreeNodes[board.Index].ChildIndexes[i].eval = 3; //loss for nodeplayer1
                }
                else {

                }

            }

            if ((WinIndex == 0) && (DrawIndex != 0)) {

                MinMaxTreeNodes[board.Index].NodeEvaluation = 0;
            }
            if ((WinIndex == 0) && (DrawIndex == 0)) {
                MinMaxTreeNodes[board.Index].NodeEvaluation = -1;



            }

        }
        if (!board.isNodePlayer1) {
            for (int i = 0; i < board.ChildIndexes.size(); i++) {
                // std::cout << "Entered for P2" << std::endl;
                if (MinMaxTreeNodes[board.ChildIndexes[i].index].NodeEvaluation == -1) {
                    MinMaxTreeNodes[board.Index].NodeEvaluation = -1;
                    MinMaxTreeNodes[board.Index].ChildIndexes[i].eval = 1; //win for nodeplayer2
                    WinIndex++;

                }
                else if (MinMaxTreeNodes[board.ChildIndexes[i].index].NodeEvaluation == 0) {
                    MinMaxTreeNodes[board.Index].ChildIndexes[i].eval = 2; //draw for nodeplayer2
                    DrawIndex++;
                }
                else if (MinMaxTreeNodes[board.ChildIndexes[i].index].NodeEvaluation == 1) {
                    MinMaxTreeNodes[board.Index].ChildIndexes[i].eval = 3; //loss for nodeplayer2
                }
                else {

                }

            }
            if ((WinIndex == 0) && (DrawIndex != 0)) {

                MinMaxTreeNodes[board.Index].NodeEvaluation = 0;
            }
            if ((WinIndex == 0) && (DrawIndex == 0)) {
                MinMaxTreeNodes[board.Index].NodeEvaluation = 1;



            }

        }

    }

    
};
class ComputerPlayer {
public:
    
    bool GameEnd = false;
    bool CompFirst;
    int CompChoice;
    Board CurrentBoard;
    int CurrentMove;
    BoardNodeArr* CurrentCheckNode = nullptr;
    MinMaxTree CompTree;

    
    void SetUp(Board StartBoard) {

        //ComputerPlayer, and Current Move/CurrentBoard Setup
        CurrentBoard = StartBoard;
        CompFirst = true;
        for (int i = 0; i < StartBoard.BoardArray.size(); i++) {
            //If Board has any move played (Comp is Player 2)
            if (StartBoard.BoardArray[i] != 0) {
                CompFirst = false;
            }
        }
        if (CompFirst) {
            CurrentMove = 1;

        }
        else {
            CurrentMove = 2;
        }
        //TreeSetup
        TreeMaker(StartBoard);
        CurrentCheckNode = &(CompTree.MinMaxTreeNodes[0]);
    }
    void UpdateBoard(int location) {
        if (GameEnd) {
            return;
        }
        //Check if Location is Valid
        if (CurrentBoard.BoardArray[location] == 0) {
            if (CurrentMove % 2 == 1) {

                CurrentBoard.BoardArray[location] = 1;
            }
            else {
                CurrentBoard.BoardArray[location] = 2;

            }
            //Increment Move
            CurrentMove++;
        }
       
        else {
            std::cout << "||ERROR, Location is Already Filled||" << std::endl;
            return;
        }
        for (int i = 0; CurrentCheckNode->ChildIndexes.size(); i++) {
            //std::cout << "ChildIndexes size()" << CurrentCheckNode->ChildIndexes.size() << std::endl;
           int test = GetLastDigit(CompTree.MinMaxTreeNodes[CurrentCheckNode->ChildIndexes[i].index].path);
           if (test == location) {
               CurrentCheckNode = &CompTree.MinMaxTreeNodes[CurrentCheckNode->ChildIndexes[i].index];
               CurrentBoard = CurrentCheckNode->BoardOfNode;
               if (CurrentBoard.GameOverCheckSilent()) {
                   GameEnd = true;
               }
               break;
           }

        }


    }
    void TreeMaker(Board StartBoard) {

        CompTree.FullTreeCreationVector(StartBoard, CompFirst);


    }
    bool IsTurn() {
        //Determining if it's the computer players turn or not
        if (CompFirst && (CurrentMove%2 == 1)) {
            return true;
        }
        else if ((!CompFirst) && (CurrentMove % 2 == 0)) {
            return true;
        }
        return false;
    
    
    }
    //Computer Player's next move choice
    int MakeNextMove() {

        if (GameEnd == true) {
            return 404;
        
        }
        if (IsTurn()) {
            
                std::vector<IndexDetails>TempChoose;
               
                switch (CurrentCheckNode->NodeEvaluation)
                {
                 
                case 1:
                   /* std::cout << "Entered Case 1:" << std::endl;*/
                    if (CompFirst) {
                        for (int i = 0; i < CurrentCheckNode->ChildIndexes.size(); i++) {
                            //std::cout << "ChildIndex[" << i << "].eval == " << CurrentCheckNode->ChildIndexes[i].eval << std::endl;
                            if (CurrentCheckNode->ChildIndexes[i].eval == 1) {


                                TempChoose.push_back(CurrentCheckNode->ChildIndexes[i]);

                            }

                        }
                    }
                    else {
                        //std::cout << "Entered Case 1:" << std::endl;
                        
                            for (int i = 0; i < CurrentCheckNode->ChildIndexes.size(); i++) {
                                //std::cout << "ChildIndex[" << i << "].eval == " << CurrentCheckNode->ChildIndexes[i].eval << std::endl;
                                if (CurrentCheckNode->ChildIndexes[i].eval == 3) {


                                    TempChoose.push_back(CurrentCheckNode->ChildIndexes[i]);

                                }

                            }
                        
                    
                    
                    
                    
                    
                    }

                    break;
                case -1:
                    if (CompFirst) {
                        //std::cout << "Entered Case -1:" << std::endl;
                        for (int i = 0; i < CurrentCheckNode->ChildIndexes.size(); i++) {
                            //std::cout << "ChildIndex[" << i << "].eval == " << CurrentCheckNode->ChildIndexes[i].eval << std::endl;
                            if (CurrentCheckNode->ChildIndexes[i].eval == 3) {

                                TempChoose.push_back(CurrentCheckNode->ChildIndexes[i]);

                            }

                        }
                    }
                    else {
                        //std::cout << "Entered Case -1:" << std::endl;
                        for (int i = 0; i < CurrentCheckNode->ChildIndexes.size(); i++) {
                            //std::cout << "ChildIndex[" << i << "].eval == " << CurrentCheckNode->ChildIndexes[i].eval << std::endl;
                            if (CurrentCheckNode->ChildIndexes[i].eval == 1) {

                                TempChoose.push_back(CurrentCheckNode->ChildIndexes[i]);

                            }

                        }
                    
                    
                    }

                    break;
                case 0:
                    //std::cout << "Entered Case 0:" << std::endl;
                    for (int i = 0; i < CurrentCheckNode->ChildIndexes.size(); i++) {
                        //std::cout << "ChildIndex[" << i << "].eval == " << CurrentCheckNode->ChildIndexes[i].eval << std::endl;
                        if (CurrentCheckNode->ChildIndexes[i].eval == 2) {

                            TempChoose.push_back(CurrentCheckNode->ChildIndexes[i]);

                        }

                    }
                    break;
                default:
                    std::cout << "Error No NODE Evaluation" << std::endl;
                }
                   
                
                
            //Choosing next current node;
              
                IndexDetails Choice = VectorRandomChooseIndex(TempChoose);
                CurrentCheckNode = &CompTree.MinMaxTreeNodes[Choice.index];
                CompChoice = GetLastDigit(CurrentCheckNode->path);
                CurrentBoard = CurrentCheckNode->BoardOfNode;
                CurrentMove++;
               
                
        }
        else {
            std::cout << "||ERROR, Waiting for Opponents Move||" << std::endl;
            return 443;
        }

    };
    
    
IndexDetails VectorRandomChooseIndex(std::vector<IndexDetails> v) {
        srand((unsigned)time(NULL));
        int random = rand();
        return v[random % v.size()];


    }






};

