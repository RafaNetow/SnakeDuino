#include "VGA.h"








//Object To Help
int scores[] = {0,0,0,0,0,0,0,0,0,0};
char*buffers="";  
char*bufferScore="";

void orderscore()
{
	for(int i =0; i<9; i++)
	{		for(int p=i; i<9; i++)
		{
			if(scores[i]<scores[p])
			{
				int temp = scores[i];
				scores[i] = scores[p];
				scores[p] = temp;
			}
		}
	}
}


void insertscore(int nscore)
{
	for(int i =0; i<9; i++)
	{
		if(nscore > scores[i])
		{
			scores[i] = nscore;
		}
	}
}
boolean GameOver =false;





void printscores()
{
	VGA.setColor(GREEN);
       VGA.printtext(50,2,"HighScore");
      for(int i =0; i<10; i++){
        
        VGA.setColor(PURPLE);
        itoa(scores[i],buffers,10);
 	   VGA.printtext(100,38,buffers,true );  
      }
}
struct Sprite{

  int posX;

  int posY;

  int nextx;

  int nexty;

  int width;
  

  int height;
  
  int direction;

  unsigned char *image;

  

};

struct Text{
   int posX;
   
   int posY;
   
   int Num;
   
   char* Text;
  

};
unsigned char snakeMenuPicture[]={
WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
WHITE,WHITE,WHITE,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,
WHITE,WHITE,WHITE,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,WHITE,WHITE,WHITE,WHITE,
WHITE,WHITE,BLACK,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,GREEN,BLACK,WHITE,WHITE,WHITE,WHITE,
WHITE,WHITE,BLACK,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,GREEN,GREEN,BLACK,WHITE,WHITE,WHITE,
WHITE,WHITE,BLACK,RED,GREEN,GREEN,GREEN,GREEN,GREEN,RED,GREEN,BLACK,WHITE,WHITE,WHITE,
WHITE,WHITE,WHITE,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,WHITE,WHITE,WHITE,WHITE,
WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,
WHITE,WHITE,BLACK,BLACK,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,BLACK,WHITE,WHITE,WHITE,
WHITE,BLACK,GREEN,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,GREEN,BLACK,GREEN,BLACK,WHITE,WHITE,
BLACK,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,GREEN,GREEN,GREEN,BLACK,WHITE,
BLACK,GREEN,GREEN,GREEN,BLACK,BLACK,BLACK,BLACK,BLACK,GREEN,GREEN,GREEN,BLACK,GREEN,BLACK,
BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,GREEN,BLACK,
WHITE,BLACK,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,BLACK,BLACK,GREEN,BLACK,
WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,BLACK,WHITE,    
};
 struct Sprite menu;
void initsnakeMenu(){

    menu.posX=100;
   
    menu.posY=38;
     
     menu.image = snakeMenuPicture;
   
    menu.width = 1;
    
     menu.height = 1;
   
     menu.direction = -1;
    
     VGA.writeArea( 30, 38, 15, 15, snakeMenuPicture );
     VGA.setColor(GREEN);
      VGA.printtext(30,10," SNAKEDUINO ");
      //VGA.writeArea(40,20 ,80,21, Intro);
      VGA.setBackgroundColor(BLACK);
      VGA.setColor(WHITE);
      VGA.printtext(60,45,"Start"); 


}

//Object of the Game
  unsigned char colorRed[] = {
 RED 
};
 unsigned char colorPurple[]={
  PURPLE
 };
 
 unsigned char colorBlue []={
   BLUE
 };
 
 unsigned char colorWhite[]={
   WHITE
 };
 unsigned char colorGreen[]={
   GREEN
 };

unsigned char Snake[]={
YELLOW
 
};

  
  struct Sprite snake[50];
  
  struct Sprite powerups[8];

  struct Sprite powerupcolor[4]; 

  struct Sprite food;
  
  struct Text score;

  int timer;
   
  bool activetimer;

//Size Margins



int width = VGA.getHSize();

int height = VGA.getVSize();

const int mapwidth = width;

const int mapheight = height;



//Collider
struct Rectangle {
		unsigned int x1, y1, x2, y2;
};

#define PointInRectangle(x, y, x1, y1, x2, y2)		((( (x) >= (x1)) && ((y) >= (y1))) && (((x) <= (x2)) && ((y) <= (y2))))
int Collide(struct Rectangle *r1, struct Rectangle *r2)
{
	return (PointInRectangle(r1->x1, r1->y1, r2->x1, r2->y1, r2->x2, r2->y2) ||
		PointInRectangle(r1->x2, r1->y2, r2->x1, r2->y1, r2->x2, r2->y2) ||
		PointInRectangle(r1->x1, r1->y2, r2->x1, r2->y1, r2->x2, r2->y2) ||
		PointInRectangle(r1->x2, r1->y1, r2->x1, r2->y1, r2->x2, r2->y2));
}


//Drawing Sprites


 void drawFood(){
      
   VGA.writeArea(food.posX,food.posY,1,1,colorRed);
 
 }


void drawMargins(){

    VGA.setColor( GREEN );
    
    VGA.drawRect( 1, 0, 1, mapheight );

    VGA.drawRect( mapwidth-2, 0, 1, mapheight );

    VGA.drawRect( 0, 1, mapwidth, 1 );

    VGA.drawRect( 0, mapheight-5, mapwidth, 1 );

}

 
 
void initpowerups()
{
	
	powerupcolor[0].image = colorPurple;
	powerupcolor[1].image = colorBlue;
	powerupcolor[2].image = colorRed;
	powerupcolor[3].image = colorWhite;
	powerupcolor[4].image = colorRed;

	for(int i =0; i<3; i++)
	{
		int p = rand() % 4 + 0;
		powerups[i].image = powerupcolor[p].image;
		powerups[i].posX = rand() % 156 + 2;
		powerups[i].posY = rand() % 116 + 2;


	}
	for(int i =4; i<8; i++)
	{
			
		powerups[i].image = BLACK;
		powerups[i].posX = rand() % 156 + 2;
		powerups[i].posY = rand() % 116 + 2;
	}
}

void newpowerup(int x, int y)
{
	for(int i =0; i<3; i++)
	{
		if(powerups[i].posX == x && powerups[i].posY == y)
		{
			int p = rand() % 4 + 0;
			powerups[i].image = powerupcolor[p].image;
			powerups[i].posX = rand() % 156 + 2;
			powerups[i].posY = rand() % 116 + 2;
		}

	}
}
boolean powerActivate = false;
void timerPowerUp()
{
	if(timer < 100 && powerActivate)
	{
		timer ++;
	}else if(timer >= 100){
			timer = 0;
                powerActivate = false;
	}
}

void verifypowerup(int color)
{
	switch(color){
		
		case PURPLE :
                growSnake();
                score.Num = score.Num+1;;
    	        itoa(score.Num,buffers,10);
                powerActivate=true;
			timer = 0;
		for(int i =3; i<8; i++)
		{
			powerups[i].image = colorRed;
			powerups[i].posX = rand() % 156 + 2;
			powerups[i].posY = rand() % 116 + 2;
		}
		break;
		
		case BLUE:
                        growSnake();
			score.Num = score.Num+2;;
    			itoa(score.Num,buffers,10);
       		       score.Text = bufferScore;
			break;
		
		case RED:
                        growSnake();
			score.Num = score.Num+1;;
    			itoa(score.Num,buffers,10);
    			
		break;
		
		case WHITE:
                        growSnake();
                        score.Num = score.Num+1;;
    			itoa(score.Num,buffers,10);
                          if(powerActivate)
			{
				for(int i =0; i<8; i++)
				{
					powerups[i].image = colorBlue;
					powerups[i].posX = rand() % 156 + 2;
					powerups[i].posY = rand() % 116 + 2;
				}

			}else
			{
				for(int i =0; i<3; i++)
				{
					powerups[i].image = colorBlue;
					powerups[i].posX = rand() % 156 + 2;
					powerups[i].posY = rand() % 116 + 2;
				}
                                

			}
		break;}	
	
}

   

 


// Funct To Inializer Objects
 
 void InitialScore(){
    score.posX = 2;
   
     score.posY = 2;
   
     score.Num =0;
   
     score.Text = "0";
 
 
 }
 
 
 
 void InitSnakePosition()

 {

   snake[0].posX=65;

   snake[0].posY=65;

   snake[0].width =1;

   snake[0].height=1;

   snake[0].direction = 2;
   
   snake[0].image = Snake;
 
   for(int i =1; i<50; i++)
   {
       snake[i].image = BLACK;
       snake[i].posX=65-i;
       snake[i].posY=65;
       snake[i].width =1;
       snake[i].height=1;
       snake[i].direction = 2;       
   }

 }
 

 
//Funct to Help
/*
boolean touchBound(struct Sprite someSprite){
  if(someSprite.posX ==0 || someSprite.posY == 0 || someSprite.posX == mapwidth-4 || someSprite.posY == mapheight-4)
      true;
} 
 */
 
boolean beginGame = false;
int currenSnakeSize = 0;

void ifGameOverTrue(){
  VGA.clear();
  
  InitSnakePosition();
  
  
  InitialScore();
  
  initpowerups();
  VGA.printtext(50,50,"Game Over" );
   delay(50000);
  insertscore(score.Num);
  void printscores();
  
   VGA.clear();
  
    delay(5000000);

}

void setup(){
 

  VGA.begin(VGAWISHBONESLOT(9),CHARMAPWISHBONESLOT(10));
 GameOver= false;
  Serial.begin(9600);
  
  InitSnakePosition();
  

  
  InitialScore();
  
  initpowerups();
  VGA.setBackgroundColor(WHITE);

    

 

  

}

int cont = 1;
int currentPixel;;

boolean ate = false;
void loop(){
     
  
  
  
   if(digitalRead(FPGA_BTN_0)){
      beginGame=true;
     VGA.clear();
   }
  if(beginGame==false)  
  initsnakeMenu();
  
  
  if(beginGame){
    
   itoa(score.Num,bufferScore,10);
   score.Text = bufferScore;
    
  VGA.printtext(score.posX,score.posY,score.Text);
 
  
     drawPowerUp();
     timerPowerUp();
    
  
     

   drawMargins(); 
   drawFood();  

  if(digitalRead(FPGA_BTN_0) && snake[0].direction !=2)
         snake[0].direction = 0;
   if(snake[0].direction==0)
        drawWithDirection(cont,&snake[0]);

  if(digitalRead(FPGA_BTN_1) && snake[0].direction !=3)
          snake[0].direction= 1;
   if(snake[0].direction==1)
       drawWithDirection(cont,&snake[0]);

  if(digitalRead(FPGA_BTN_2)&&snake[0].direction !=0)
          snake[0].direction = 2;
   if(snake[0].direction==2) 
       drawWithDirection(cont,&snake[0]);

  if(digitalRead(FPGA_BTN_3)&& snake[0].direction !=1)
          snake[0].direction = 3;
    if(snake[0].direction==3)
         drawWithDirection(cont,&snake[0]);


//////// 
   ///////////// cambiar verify de bool a void
	/////////////// 
  verifyIfNextPixelIsDiferenntColor(&snake[0]);          
               

       delay(50);        //VGA.printtext(0,20,"MSLC");    

    //   VGA.clearArea(100-cont,65,10,9);

  }      

}


//push
int currentSnakeSize = 1;
void saveSnakepos(){
   for(int i = 0; i<50-1; i++){
     snake[i+1].nextx = snake[i].posX;
     snake[i+1].nexty = snake[i].posY;
	
   }
   
//   VGA.writeArea(snake[currentSnakeSize].posX,snake[currentSnakeSize].posY,1,1,BLACK);
   
}

void moveSnake(){
   for(int i = 1; i<50; i++){
     snake[i].posX = snake[i].nextx;
     snake[i].posY = snake[i].nexty;
	
   }
   
//   VGA.writeArea(snake[currentSnakeSize].posX,snake[currentSnakeSize].posY,1,1,BLACK);
   
}
  //asdasd
  void drawSnake()
{
    for(int i = 0; i<=currentSnakeSize; i++){
      if(i<currentSnakeSize)
      VGA.writeArea(snake[i].posX,snake[i].posY,snake[i].width,snake[i].height,snake[i].image); 
    else if(i==currentSnakeSize)
      VGA.putPixel(snake[i].posX,snake[i].posY,BLACK);
  }
}

  void drawPowerUp(){
    
    if(powerActivate == true)
     for(int i = 0; i<8; i++){
       VGA.writeArea(powerups[i].posX,powerups[i].posY,1,1,powerups[i].image); 
       
    }  else{
    
    
    for(int i = 0; i<3; i++){
       VGA.writeArea(powerups[i].posX,powerups[i].posY,1,1,powerups[i].image); 
       
    }  for(int i = 3;i <8; i++){
         VGA.putPixel(powerups[i].posX,powerups[i].posY,BLACK);
       
    }  
    

    }  
} 
 
 
  void growSnake(){
    currentSnakeSize++;
    snake[currentSnakeSize-1].image = colorGreen;
  
  }
void drawWithDirection(int cont,struct Sprite*someSprite){

    //0 derecha  

    //1 arriba

    //2 izquierda

    //3 abajo


  

   if(someSprite->direction==0){
     saveSnakepos();
     someSprite->posX = someSprite->posX-cont;
     //Mira aca necesitamos llamar la funcion que dibuje toda la snake
     moveSnake();
     drawSnake();
   }
   if(someSprite->direction==1){
     saveSnakepos();
     someSprite->posY = someSprite->posY-cont;
     moveSnake();
     drawSnake();
   }
   if(someSprite->direction==2){
     saveSnakepos(); 
     someSprite->posX = someSprite->posX+cont;
      moveSnake();
      drawSnake();
     
   }
   if(someSprite->direction==3){
     saveSnakepos();
     someSprite->posY = someSprite->posY+cont;
     moveSnake();
     drawSnake(); 
   }
     

}


bool verifyIfNextPixelIsDiferenntColor(struct Sprite*head){
    int pixel_t;
    
     //Toma los colors de la izquiera, derecha, arriba y abajo
      pixel_t = VGA.getPixel(head->posX+1,head->posY);
      if(head->direction==0){
           pixel_t = VGA.getPixel(head->posX-1,head->posY);
            newpowerup(head->posX-1,head->posY);
            if(pixel_t == GREEN){
          ifGameOverTrue();
            }
            verifypowerup(pixel_t);
	}		
      if(head->direction==1){
           pixel_t = VGA.getPixel(head->posX,head->posY-1);
             newpowerup(head->posX,head->posY-1);
            if(pixel_t == GREEN){
              ifGameOverTrue(); 
          }
		verifypowerup(pixel_t);
      	 }
       if(head->direction==2){
           pixel_t = VGA.getPixel(head->posX+1,head->posY);
               newpowerup(head->posX+1,head->posY);
            if(pixel_t == GREEN){
                 ifGameOverTrue();
          } 
		verifypowerup(pixel_t); 	 
    }
      
      if(head->direction==3){
           pixel_t = VGA.getPixel(head->posX,head->posY+1);
              newpowerup(head->posX,head->posY+1);
            if(pixel_t == GREEN) {
      	         ifGameOverTrue();
            } 
			verifypowerup(pixel_t); 
  }
    
	
	



}

