#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <graphics.h>
#include <vector>

int Nastup = 0; // режим "Наступления"
int NX = 0, NY = 0; // координаты наступления
class Map{
      private:
             int matrix[11][11];
             int xM, yM; // координаты поля
             int k; // количество кораблей
      public:
             int GetK(){ return k; }
             int MinusK(){ this->k--; }
             void Draw(){
                  char* massC[12] = {"1","2","3","4","5","6","7","8","9","10"," "," "}; // массив цифр
                  for(int i = 0; i <= 275; i+=25){
                          outtextxy(xM+i+25+5,yM+5,massC[i/25]);
                          outtextxy(xM+5,yM+i+25+5,massC[i/25]);
                          moveto(xM,yM+i);
                          lineto(xM+275,yM+i);        
                          moveto(xM+i,yM);
                          lineto(xM+i,yM+275);
                  }     
                  for(int i = 0; i <= 10; i++){
                          for(int j = 0; j <= 10; j++){
                                  if(matrix[i][j]==1){  // 1 - cвой корабль, 2 - утопленник, 4 - неактивная ячейка, 3 - враг, 6 - мимо, 5 - попадание
                                       bar(i*25+xM+25,j*25+yM+25,i*25+xM+50,j*25+yM+50);        
                                  } else if(matrix[i][j]==5){
                                       setfillstyle(1,GREEN);
                                       bar(i*25+xM+25,j*25+yM+25,i*25+xM+50,j*25+yM+50);   
                                       setfillstyle(1,WHITE);     
                                  } else if(matrix[i][j]==6){
                                       circle(i*25+xM+25+25/2,j*25+yM+25+25/2,25/2);                                            
                                       circle(i*25+xM+25+25/2,j*25+yM+25+25/2,25/3);                                            
                                       circle(i*25+xM+25+25/2,j*25+yM+25+25/2,25/4);                                            
                                       circle(i*25+xM+25+25/2,j*25+yM+25+25/2,25/5);                                            
                                       circle(i*25+xM+25+25/2,j*25+yM+25+25/2,25/6);                                            
                                       circle(i*25+xM+25+25/2,j*25+yM+25+25/2,25/7);                                            
                                  }
                          }
                  }
             }
             Map(int xT, int yT){
                   this->xM = xT; this->yM = yT;
                   for(int i = 0; i < 10; i++){
                           for(int j = 0; j < 10; j++){
                                   matrix[i][j] = 0;        
                           }        
                   }
                   this->k = 10;
                   Draw();
             }
             int SetYa(int x, int y, int P, int status, int Z){ 
                  if(P == 1){ // Z - чем заполнить ячейку 
                       if(matrix[x-1][y-1] != 1 && matrix[x-1][y-1] != 4){ 
                       for(int i = x-2; i <= x; i++){
                               if(i == -1 || i == 10) continue;
                               for(int j = y-2; j <= y; j++){
                                       if(j == 10 || j == -1) continue;
                                       matrix[i][j] = 4;        
                               }        
                       }
                       matrix[x-1][y-1] = Z;
                       } else { return 1; } 
                  } else if(P == 2){
                       switch(status){
                            case 0:{ 
                               if((y-1<1) ||matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x-1][y-2] == 1 || matrix[x-1][y-2] == 4) return 1;
                               for(int i = x-2; i <= x; i++){
                                       if(i == -1 || i == 10) continue;
                                       for(int j = y-3; j <= y; j++){
                                         if(j == 10 || j == -1) continue;
                                         matrix[i][j] = 4;        
                                       }        
                               }
                               matrix[x-1][y-1] = Z; matrix[x-1][y-2] = Z; 
                            } break;
                            case 1:{ 
                                 if((x-1 > 8) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x][y-1] == 1 || matrix[x][y-1] == 4) return 1;
                                 for(int i = x-2; i <= x+1; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-2; j <= y; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 }
                                 matrix[x-1][y-1] = Z; matrix[x][y-1] = Z; 
                            } break;
                            case 2:{ 
                                 if((y-1 > 8) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x][y-1] == 1 || matrix[x][y-1] == 4) return 1;
                                 for(int i = x-2; i <= x; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-2; j <= y+1; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 }
                                 matrix[x-1][y-1] = Z; matrix[x-1][y] = Z; 
                            } break;
                            case 3:{ 
                                 if((x-1 < 1) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x-2][y-1] == 1 || matrix[x-2][y-1] == 4) return 1;
                                 for(int i = x-3; i <= x; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-2; j <= y; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 }
                                 matrix[x-1][y-1] = Z; matrix[x-2][y-1] = Z; 
                            } break;
                       }  
                  } else if(P == 3){
                       switch(status){
                            case 0:{ 
                                 if((y-1 < 2) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x-1][y-2] == 1 || matrix[x-1][y-2] == 4 || matrix[x-1][y-3] == 1 || matrix[x-1][y-3] == 4) return 1;
                                 for(int i = x-2; i <= x; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-4; j <= y; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 }
                                 matrix[x-1][y-1] = Z; matrix[x-1][y-2] = Z; matrix[x-1][y-3] = Z; } break;
                            case 1:{ 
                                 if((x-1 > 7) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x][y-1] == 1 || matrix[x][y-1] == 4 || matrix[x+1][y-1] == 1 || matrix[x+1][y-1] == 4) return 1;
                                 for(int i = x-2; i <= x+2; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-2; j <= y; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 }
                                 matrix[x-1][y-1] = Z; matrix[x][y-1] = Z; matrix[x+1][y-1] = Z; } break;
                            case 2:{ 
                                 if((y - 1 > 7) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x-1][y] == 1 || matrix[x-1][y] == 4 || matrix[x-1][y+1] == 1 || matrix[x-1][y+1] == 4) return 1;
                                 for(int i = x-2; i <= x; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-2; j <= y+2; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 }
                                 matrix[x-1][y-1] = Z; matrix[x-1][y] = Z; matrix[x-1][y+1] = Z; } break;
                            case 3:{ 
                                 if((x - 1 < 2) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x-2][y-1] == 1 || matrix[x-2][y-1] == 4 || matrix[x-3][y-1] == 1 || matrix[x-3][y-1] == 4) return 1;
                                 for(int i = x-4; i <= x; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-2; j <= y; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 }
                                 matrix[x-1][y-1] = Z; matrix[x-2][y-1] = Z; matrix[x-3][y-1] = Z; } break;
                       }       
                  } else if(P == 4){
                       switch(status){
                            case 0:{ 
                                 if((y-1 < 3) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x-1][y-2] == 1 || matrix[x-1][y-2] == 4 || matrix[x-1][y-3] == 1 || matrix[x-1][y-3] == 4 || matrix[x-1][y-4] == 1 || matrix[x-1][y-4] == 4) return 1;
                                 for(int i = x-2; i <= x; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-5; j <= y; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 }
                                 matrix[x-1][y-1] = Z; matrix[x-1][y-2] = Z; matrix[x-1][y-3] = Z; matrix[x-1][y-4] = Z; } break;
                            case 1:{
                                 if((x - 1 > 6) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x][y-1] == 1 || matrix[x][y-1] == 4 || matrix[x+1][y-1] == 1 || matrix[x+1][y-1] == 4 || matrix[x+2][y-1] == 1 || matrix[x+2][y-1] == 4) return 1;
                                 for(int i = x-2; i <= x+3; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-2; j <= y; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 } 
                                 matrix[x-1][y-1] = Z; matrix[x][y-1] = Z; matrix[x+1][y-1] = Z; matrix[x+2][y-1] = Z; } break;
                            case 2:{
                                 if((y - 1 > 6) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x-1][y] == 1 || matrix[x-1][y] == 4 || matrix[x-1][y+1] == 1 || matrix[x-1][y+1] == 4 || matrix[x-1][y+2] == 1 || matrix[x-1][y+2] == 4) return 1;
                                 for(int i = x-2; i <= x; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-2; j <= y+3; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 }  
                                 matrix[x-1][y-1] = Z; matrix[x-1][y] = Z; matrix[x-1][y+1] = Z; matrix[x-1][y+2] = Z; } break;
                            case 3:{ 
                                 if((x - 1 < 3) || matrix[x-1][y-1] == 1 || matrix[x-1][y-1] == 4 || matrix[x-2][y-1] == 1 || matrix[x-2][y-1] == 4 || matrix[x-3][y-1] == 1 || matrix[x-3][y-1] == 4 || matrix[x-4][y-1] == 1 || matrix[x-4][y-1] == 4) return 1;
                                 for(int i = x-5; i <= x; i++){
                                         if(i == -1 || i == 10) continue;
                                         for(int j = y-2; j <= y; j++){
                                                 if(j == 10 || j == -1) continue;
                                                 matrix[i][j] = 4;        
                                         }        
                                 } 
                                 matrix[x-1][y-1] = Z; matrix[x-2][y-1] = Z; matrix[x-3][y-1] = Z; matrix[x-4][y-1] = Z; } break;
                       }              
                  } else { return 1; }
                  return 0;
             }
             int Izm(int x, int y){
                  if(matrix[x-1][y-1] == 5 || matrix[x-1][y-1] == 6){
                       return 0;
                  } else if(matrix[x-1][y-1] == 3 || matrix[x-1][y-1] == 1){
                       matrix[x-1][y-1] = 5;
                       int status = 1;
                       if((matrix[x-1][y-2] == 1 || matrix[x-2][y-1] == 1 || matrix[x][y-1] == 1 || matrix[x-1][y] == 1) || (matrix[x-1][y-2] == 3 || matrix[x-2][y-1] == 3 || matrix[x][y-1] == 3 || matrix[x-1][y] == 3)){
                             status = 0;                    
                       }
                       if(status == 1){
                             return 3;
                       }
                       return 1;
                  } else if(matrix[x-1][y-1] == 4 || matrix[x-1][y-1] == 0){
                       matrix[x-1][y-1] = 6;
                       return 2;
                  }
             }
};

class Ship{
      protected:
             int pr; // принадлежность к определенному полю
             int x,y; // координаты коробля
             int status; // 0 - мертв, 1 - живой
      public:
             void Init(int xT, int yT, int prT){
                    this->x = xT; 
                    this->y = yT;
                    this->pr = prT;
                    this->status = 1;
             }      
             void Kill(){
                  status = 0;     
             }
};
class Ship_1:public Ship{ // однопалубные корабли
      public:
             void Init(int xT, int yT, int prT){
                  Ship::Init(xT,yT,prT);
             }
};
int Ship1Init = 0;
std::vector<Ship_1> vShip_1(8);

class Ship_2:public Ship{
      protected:
             int napr; // направление корабля
      public:
             void Init(int xT, int yT, int n, int prT){
                  Ship::Init(xT,yT,prT);
                  this->napr = n;
             }      
};
int Ship2Init = 0;
std::vector<Ship_2> vShip_2(6);

class Ship_3:public Ship{
      protected:
             int napr; // направление корабля
      public:
             void Init(int xT, int yT, int n, int prT){
                  Ship::Init(xT,yT,prT);
                  napr = n;
             }            
};
int Ship3Init = 0;
std::vector<Ship_3> vShip_3(4);

class Ship_4:public Ship{
      protected:
             int napr; // направление корабля
      public:
             void Init(int xT, int yT, int n, int prT){
                  Ship::Init(xT,yT,prT);
                  napr = n;
             }            
};
int Ship4Init = 0;
std::vector<Ship_4> vShip_4(2);

void War(Map MyMap, Map WarMap){
     printf("Да начнется битва!");
     printf("Введите координаты: ");
     while(1){   
          if(WarMap.GetK() == 0 || MyMap.GetK() == 0) break;
          int x = 0, y = 0; 
          metka:
          scanf("%d %d",&x,&y);
          int P = WarMap.Izm(x,y);
          if(P == 0){
             printf("\nВы уже стреляли в эту ячейку! Повторите:\n");
             goto metka;
          } else if(P == 1){
             printf("Вы попали!\n");
          } else if(P == 2){
             printf("Мимо!\n"); 
          } else if(P == 3){
             printf("Корабль врага уничтожен! :))\n");  
             WarMap.MinusK();     
             printf("У врага осталось кораблей: %d\n",WarMap.GetK());
          }
          WarMap.Draw();
          metka8:
          if(Nastup == 0){
              x = rand()%10+1;
              y = rand()%10+1;
          } else if(Nastup <= 4){
              int r = rand()%4;
              switch(r){
                   case 0: if(NX < 10){ x = NX+1; y = NY; } break;
                   case 1: if(NX > 0){ x = NX-1; y = NY; } break;
                   case 2: if(NY > 0){ x = NX; y = NY-1; } break;
                   case 3: if(NY < 10){ x = NX; y = NY+1; } break;
              }       
          }
          P = MyMap.Izm(x,y);
          int Fl = 0; // сколько раз в невозможное место
          if(P == 0){
             Fl++;
             if(Fl == 4){
                  Nastup = NX = NY = Fl = 0;
                  printf("Наступление окончено!");
                  }
             goto metka8;
          } else if(P == 1){
             printf("Увы, но в ваш корабль попали!\n");
             Nastup++;
             NX = x;
             NY = y;
          } else if(P == 2){
             printf("Уху, враг промахнулся!\n");       
          } else if(P == 3){
             printf("Ваш корабль потоплен :((\n");    
             Nastup = 0;
             MyMap.MinusK();
             printf("У вас осталось кораблей: %d\n",MyMap.GetK());
          }
          MyMap.Draw();
     }
     if(MyMap.GetK() == 0){
          printf("Вы проиграли! :((");                
     }
     if(WarMap.GetK() == 0){
          printf("Вы выиграли! :)");                 
     }
     system("PAUSE");
}

void Start(){
    Map map1(25,25);  // первое игровое поле
    Map map2(350,25); // игровое поле врага
    /*for(int i = 0; i < 4; i++){
           printf("Разместите 1-нопалубные корабли введя координаты[X Y]:\n");
           metka:
           int k = 0;
           int b = 0;
           scanf("%d %d",&b,&k);
           if(map1.SetYa(b,k,1,1,1) == 0){
                     vShip_1[Ship1Init].Init(b,k,1);
                     Ship1Init++;
                     map1.Draw();
           } else {
             printf("Невозможно установить! Повторите: ");       
             goto metka;
           }
    }
    printf("\n0 - вверх, 1 - вправо, 2 - вниз, 3 - влево\n");
    for(int i = 0; i < 3; i++){
           printf("Разместите 2-хпалубные корабли введя координаты [X Y направление]:\n");
           metka1:
           int k = 0;
           int b = 0;
           int n = 0;
           scanf("%d %d %d",&b,&k,&n);
           if(map1.SetYa(b,k,2,n,1) == 0){
                      vShip_2[Ship2Init].Init(b,k,n,1);
                      Ship2Init++;
                      map1.Draw();
           } else {
             printf("Невозможно установить! Повторите: ");       
             goto metka1;       
           }
    }
    for(int i = 0; i < 2; i++){
           printf("Разместите 3-хпалубные корабли введя координаты [X Y направление]:\n");
           metka2:
           int k = 0;
           int b = 0;
           int n = 0;
           scanf("%d %d %d",&b,&k,&n);
           if(map1.SetYa(b,k,3,n,1) == 0){
                      vShip_3[Ship3Init].Init(b,k,n,1);
                      Ship3Init++;
                      map1.Draw();        
           } else {
             printf("Невозможно установить! Повторите: ");       
             goto metka2;       
           } 
    }
    for(int i = 0; i < 1; i++){
           printf("Разместите 4-хпалубный корабль введя координаты [X Y направление]:\n");
           metka3:
           int k = 0;
           int b = 0;
           int n = 0;
           scanf("%d %d %d",&b,&k,&n);
           if(map1.SetYa(b,k,4,n,1) == 0){
                      vShip_4[Ship4Init].Init(b,k,n,1);
                      Ship3Init++;
                      map1.Draw();        
           } else {
             printf("Невозможно установить! Повторите:\n");       
             goto metka3;       
           } 
    } */
    srand(time(NULL));   
    for(int i = 0; i < 4; i++){
           metka4:
           int k = rand()%10+1;
           int b = rand()%10+1;
           if(map2.SetYa(b,k,1,1,3) == 0){
                     vShip_1[Ship1Init].Init(b,k,2);
                     Ship1Init++;
           } else {
             goto metka4;
           }
    }
    for(int i = 0; i < 3; i++){
           metka5:
           int k = rand()%10+1;
           int b = rand()%10+1;
           int n = rand()%4;
           if(map2.SetYa(b,k,2,n,3) == 0){
                      vShip_2[Ship2Init].Init(b,k,n,2);
                      Ship2Init++;
           } else {
             goto metka5;       
           }
    }
    for(int i = 0; i < 2; i++){
           metka6:
           int k = rand()%10+1;
           int b = rand()%10+1;
           int n = rand()%4;
           if(map2.SetYa(b,k,3,n,3) == 0){
                      vShip_3[Ship3Init].Init(b,k,n,2);
                      Ship3Init++;
           } else {
             goto metka6;       
           } 
    }
    for(int i = 0; i < 1; i++){
           metka7:
           int k = rand()%10+1;
           int b = rand()%10+1;
           int n = rand()%4;
           if(map2.SetYa(b,k,4,n,3) == 0){
                      vShip_4[Ship4Init].Init(b,k,n,2);
                      Ship4Init++;    
           } else {
             goto metka7;      
           } 
    }
    //Снять комментарий, если лень расставлять самому 
    srand(time(NULL));   
    for(int i = 0; i < 4; i++){
           metka8:
           int k = rand()%10+1;
           int b = rand()%10+1;
           if(map1.SetYa(b,k,1,1,1) == 0){
                     vShip_1[Ship1Init].Init(b,k,2);
                     Ship1Init++;
           } else {
             goto metka8;
           }
    }
    for(int i = 0; i < 3; i++){
           metka9:
           int k = rand()%10+1;
           int b = rand()%10+1;
           int n = rand()%4;
           if(map1.SetYa(b,k,2,n,1) == 0){
                      vShip_2[Ship2Init].Init(b,k,n,2);
                      Ship2Init++;
           } else {
             goto metka9;       
           }
    }
    for(int i = 0; i < 2; i++){
           metka10:
           int k = rand()%10+1;
           int b = rand()%10+1;
           int n = rand()%4;
           if(map1.SetYa(b,k,3,n,1) == 0){
                      vShip_3[Ship3Init].Init(b,k,n,2);
                      Ship3Init++;
           } else {
             goto metka10;       
           } 
    }
    for(int i = 0; i < 1; i++){
           metka11:
           int k = rand()%10+1;
           int b = rand()%10+1;
           int n = rand()%4;
           if(map1.SetYa(b,k,4,n,1) == 0){
                      vShip_4[Ship4Init].Init(b,k,n,2);
                      Ship4Init++;    
           } else {
             goto metka11;      
           } 
    }
    cleardevice();
    map2.Draw();  
    map1.Draw();
    War(map1,map2);           
}

int main(){
    setlocale(LC_ALL, "Russian");     
    initwindow(700,400);  
    Start();
    closegraph();
    return 0;
}
