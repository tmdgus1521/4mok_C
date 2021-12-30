#include <stdio.h>
#include <stdlib.h>
#define R 9
#define C 9
int crush_test(int r, int c,int cmp[][3], char board[][9], int marker){
      if ( marker == 'O'){
         for (int i = 0; i < 3; i++){
           for (int j = 0; j < 3; j++){
            if ( cmp[i][j] == 1 && board[r+i][c+j] != 0){ return 0;}
         }
      }
      }  
      else if ( marker == '@'){
         for (int i = 0; i < 3; i++){
           for (int j = 0; j < 3; j++){
            if ( cmp[i][j] == 1 && board[r+i][c+j] != 0){ return 0;}
         }
      }
      }
return 1;
}
void place(int r, int c, int cmp[][3], char board[][9], int marker){
   for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (cmp[i][j] == 1) {board[r+i][c+j] = marker;}
        }
   }
  
}

void getRandomBlock(int ary[][3]){ //return n_marker
   static const int block_candidate[][3][3] = {
      {
         {1, 1, 1},
         {0, 0, 0},
         {0, 0, 0}
      },
      {
         {1, 1, 1},
         {1, 0, 0},
         {0, 0, 0}
      },
      {
         {1, 1, 1},
         {0, 0, 1},
         {0, 0, 0}
      },
      {
         {1, 1, 1},
         {0 ,1, 0},
         {0, 0, 0}
      },
      {
         {0, 1, 1},
         {1, 1, 0},
         {0, 0, 0}
      },
      {
         {1, 1, 0},
         {0, 1, 1},
         {0, 0, 0}
      },
      {
         {1, 1, 0},
         {1, 1, 0},
         {0, 0, 0}
      },
      {
         {1, 0, 0},
         {1, 1, 0},
         {1, 1, 0}
      },
      {
         {0, 1, 1},
         {1, 1, 0},
         {1, 0, 0}
      },
      {
         {1, 1, 0},
         {0, 1, 1},
         {0, 1, 0}
      },
      {
         {0, 1, 1},
         {1, 1, 0},
         {0, 1, 0}
      },
      {
         {0, 0, 1},
         {1, 1, 1},
         {1, 0, 0}
      },
      {
         {1, 0, 0},
         {1, 1, 1},
         {0, 0, 1}
      },
      {
         {0, 1, 0},
         {1, 1, 1},
         {0, 1, 0}
      }
   };

   srand((unsigned int) time (NULL));
   int r = rand() % 14;

   for (int i = 0 ; i < 3; ++i){
      for(int j = 0 ; j < 3; ++j){
         ary[i][j] = block_candidate[r][i][j];
      }
   }


   
}

const char* markerToStr(char c){
   if (c == 'O') return "P1";
   else if (c == '@') return "P2";
   else {
      printf("impossible marker : %c", c);
      exit(17);
   }
}

int block(char ary[][9], int marker){
   int num1 = 0;
   int num2 = 0;
   int cmp[3][3] = {0}; //랜덤 블록 3X3 저장
   

   getRandomBlock(cmp);
   

            while(1){
               //player check하기
               printf("\n%s's block : \n", markerToStr(marker));
               printf(" _ _ _\n");//랜덤 블록 보여주기
               for (int i = 0; i < 3; i++){
                     for (int j = 0; j < 3; j++){
                        if (cmp[i][j] == 1) printf("|%c", marker);
                        else printf("|_");
                     }
                     printf("|\n");     
               }

               int isGameOver = win_lose(ary,cmp);
               //게임이 끝나지 않으면 위치 입력 받기
               if (isGameOver != 1){
                  printf("\nPut your block (r c) or Rotate (0): ");
                  scanf("%d",&num1);
                  if (num1 != 0) {
                     scanf(" %d",&num2);
                     int a = crush_test(num1-1,num2-1,cmp,ary,marker);//충돌 테스트 check
                     if (a == 0){//충돌이 일어나면 충돌 메시지 출력
                        if (marker == 'O') printf("P1 is not able to put the block into (%d,%d).\n",num1,num2);
                        else if (marker == '@') printf("P2 is not able to put the block into (%d,%d).\n",num1,num2);
                     }
                     else if (a == 1){//충돌이 일어나지 않으면 배치
                        place(num1-1,num2-1,cmp,ary,marker);
                        break;
                     }
                  }
               }
               //입력값이 0이면 회전
               if (isGameOver != 1 && num1 == 0){rotate(cmp);}

               if (isGameOver == 1 ){
                  if (marker == 'O') {printf("\nP1 fails to put the block. P2 wins!"); return 1;}
                  else if (marker == '@'){printf("\nP2 fails to put the block. P1 wins!");return 1;}
               }

            }
return 0;
}       
                  
                  

int win_lose(char ary[][9], int temp[][3]){

   int copy_temp[3][3]={0};

   for (int i = 0; i < 3; i++){
      for (int j = 0; j < 3; j++){
          copy_temp[i][j] = temp[i][j];
      }
   }
   for (int a = 0; a < 4; a++){
      rotate(copy_temp);
      for ( int row_start = 0; row_start <= 6; ++row_start ){
         for ( int col_start = 0; col_start <= 6; ++col_start ){

            int block_feasible = 1;
            for (int r = row_start; r < row_start + 3; ++r){
               for (int c = col_start; c < col_start + 3; ++c){
                  if (copy_temp[r-row_start][c-col_start] != 0){
                     if (ary[r][c] != 0){
                        block_feasible = 0;
                     }
                  }
               }
            }
         if (block_feasible == 1) return 0;//적어도 1경우 가능
         }
      }
   
   }
   return 1;    //가능한 경우 없음


}
void rotate(int arr[3][3]){ //랜덤 블록을 인자로 받아서 회전시키기
    int bin[3][3] = {0};// 회전한 블록 여기에 저장하기
    for (int i = 0; i < 3; i++){// 블록들을 회전해서 bin array에 저장
      for (int j = 0; j < 3; j++){
         bin[j][2-i] = arr[i][j];
        }
    }
    for (int i = 0; i < 3; i++){// 회전한 블록들은 다시 인자에 붙혀넣기
      for (int j = 0; j < 3; j++){
         arr[i][j] = bin[i][j];
        }
    }
}

void draw_board(char board[R][C]){ //게임판 출력 함수
    for (int i = 0; i < R; ++i)
            if (i == 0) printf("\n   %d", i+1);
            else printf(" %d",i+1); // 1  2  3  4  5  6  7  8  9 표시
    printf("\n");
    printf("   _ _ _ _ _ _ _ _ _\n");
    for (int i = 0; i < C; ++i){// 게임판에 마커 표시하기
            printf("%d ",i+1);
            for (int j =0; j < R; ++j){
                if (board[i][j] == 0)
				      printf("|_");
			       else if (board[i][j] == 'O')
				      printf("|O");
			       else if (board[i][j] == '@')
				      printf("|@");
            }
        printf("|\n");
    }
}

int main(){
    char board[R][C] = {0}; //9X9 게임판 초기화
    draw_board(board); //게임판 출력
    while(1){//return 1이면 break
    int isGameDone = block(board,'O');
    if (isGameDone==1){break;} 
    draw_board(board);
    isGameDone = block(board,'@'); 
    if (isGameDone==1){break;}
    draw_board(board);
    }
}