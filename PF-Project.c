#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char board[3][3];
int player1Score=0, player2Score=0;
int timerMode=0; 

void initializeBoard()
{
    int count=1;
    int i;
    int j;
     for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            board[i][j]=count + '0';
            count++;
        }
    }
}

void displayBoard(){
    printf("\n");
    int i;
    int j;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            printf(" %c ", board[i][j]);
            if(j<2) printf("|");
        }
        printf("\n");
        if(i<2) printf("---|---|---\n");
    }
}

int checkWinner(){
	int i;
	int j;
    for(i=0; i<3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;
    return 0;
}
int isDraw(){
	int i;
	int j;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(board[i][j]!='X' && board[i][j]!='O') return 0;
        }
    }
    return 1;
}
void playerMove(int player){
    int move, row, col;
    time_t startTime, endTime;

    if(timerMode){
        startTime=time(NULL);
        printf("\nPlayer %d's turn (enter 1-9) within 20 seconds: ", player);
    } else {
        printf("\nPlayer %d's turn (enter 1-9): ", player);
    }

    while(1){
        if(scanf("%d", &move)!=1){
            printf("Invalid input! Please enter a number between 1 and 9.\n");
            while(getchar()!='\n');
            continue;
        }
       if(timerMode){
            endTime=time(NULL);
            if(difftime(endTime, startTime) >= 20){
                printf("\nTime's up! Player %d's turn is skipped.\n", player);
                return;
            }
        }
        if(move < 1 || move > 9) { 
            printf("Invalid move! Enter a number between 1 and 9.\n");
            continue;
        }
        row=(move - 1)/3;
        col=(move - 1)%3;

        if(board[row][col] != 'X' && board[row][col] != 'O'){
            board[row][col]= (player == 1) ? 'X' : 'O';
            break; 
        } else{
            printf("Invalid move! This spot is already taken. Try again.\n");
        }
    }
}


void computerMove(){
    int row, col;
    printf("\nComputer turn:\n");
    srand(time(0));
    while(1){
        int move=rand()%9+1;
        row=(move-1)/3;
        col=(move-1)%3;
        if(board[row][col]!='X' && board[row][col]!='O'){
            board[row][col]='O'; 
            break;
        }
    }
}


void playGame(int mode){
    initializeBoard();
    int player=1;

    while(1){
        displayBoard();
        if(mode==1 && player==2) {
            computerMove();
        } else{
            playerMove(player); 
        }

        if(checkWinner()){
            displayBoard();
            if(mode==1 && player==2){
                printf("\nComputer wins!\n");
            } 
            else{
                printf("\nPlayer %d wins!\n", player);
            }
            if(player==1){
                player1Score++;
            }else{ player2Score++;}
            break;
        }

        if(isDraw()){
            displayBoard();
            printf("\nIt's a draw!\n");
            break;
        }
       if(player==1){
           player=2;
       }else{
           player=1;
       }
    }
}
void displayScores(){
    printf("\nScores:\n");
    printf("Player 1: %d\n", player1Score);
    printf("Player 2/Computer: %d\n", player2Score);
}

int main(){
    int playMode;
    char playAgain;

    printf("Welcome to Tic-Tac-Toe!\n");

    do{
        printf("\nSelect Playing Mode:\n");
        printf("1. Single-player (vs Computer)\n");
        printf("2. Two-player\n");
        do{
            printf("Enter choice: ");
            if(scanf("%d", &playMode)!=1 || (playMode!=1 && playMode!=2)){
                printf("\nInvalid choice! Please enter (1) for Single-player or (2) for Two-player:\n");
                while (getchar()!='\n');
            }
        } while(playMode!=1 && playMode!=2);
        printf("\nSelect Timer Mode:\n");
        printf("1. With Timer (20 seconds per move)\n");
        printf("2. Without Timer\n");

        do{
            printf("Enter choice: ");
            if(scanf("%d", &timerMode)!=1 || (timerMode!=1 && timerMode!=2)){
                printf("\nInvalid choice! Please enter (1) for With Timer (20 seconds per move) or (2) for Without Timer\n");
                while(getchar()!='\n'); 
            }
        } while(timerMode!=1 && timerMode!=2);
        
        if(timerMode==1){
            timerMode=1; 
        } 
        else{
            timerMode=0;
        }

        playGame(playMode);
        
        displayScores();

        do{
            printf("\nDo you want to play again? (y/n): ");
            scanf(" %c", &playAgain);
            if(playAgain!='y' && playAgain!='Y' && playAgain!='n' && playAgain!='N'){
                printf("Invalid input. Please enter 'y' or 'n'.\n");
            }
        } while(playAgain!='y' && playAgain!='Y' && playAgain!='n' && playAgain!='N');

    } while(playAgain=='y' || playAgain=='Y'); 
    printf("\nThank you for playing! Final Scores:\n");
    displayScores();
    return 0;
}
