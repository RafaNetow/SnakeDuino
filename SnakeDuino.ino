#include "VGA.h"








//Object To Help

  
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

//Object of the Game
  unsigned char Food[] = {
 RED 
};
unsigned char Snake[]={
YELLOW
 
};

  
  struct Sprite snake[50];
  
  struct Sprite powerups[8];

  struct sprite powerupcolor[4]; 

  struct Sprite food;
  
  struct Text score;

  int timer:
   

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
      
   VGA.writeArea(food.posX,food.posY,1,1,Food);
 
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
	powerupcolor[0].image = PURPLE;
	powerupcolor[1].image = BLUE;
	powerupcolor[2].image = RED;
	powerupcolor[3].image = WHITE;
	powerupcolor[4].image = ORANGE;

	for(int i =0; i<3; i++)
	{
		int p rand() % 4 + 1;
		powerup[i].image = powerupcolor[p].image;
		powerup[i].posX = rand() % 156 + 2;
		powerup[i].posY = rand() % 116 + 2;

	}
}

void newpowerup()
{
	int p rand() % 4 + 1;
	powerup[i].image = powerupcolor[p].image;
	powerup[i].posX = rand() % 156 + 2;
	powerup[i].posY = rand() % 116 + 2;
}

void timer()
{
	if(timer < 60)
	{
		time++;
	}else if(timer >= 60)
		timer = 0l;
}

void verifypowerup(color)
{
	switch(color)
		
		case: PURPLE:
		for(int i =5; i<8; i++)
		{
			powerup[i].image = BLUE;
			powerup[i].posX = rand() % 156 + 2;
			powerup[i].posY = rand() % 116 + 2;
		}
		break;
		
		case:BLUE:
		score.Num = score.Num+2;
    		itoa(score.Num,buffers,10);
       	score.Text = buffers;
		break;
		
		case:RED:
		score.Num = score.Num+1;
    		itoa(score.Num,buffers,10);
       	score.Text = buffers;
		break;
		
		case:WHITE:
		for(int i =5; i<8; i++)
		{
			powerup[i].image = BLUE;
			powerup[i].posX = rand() % 156 + 2;
			powerup[i].posY = rand() % 116 + 2;
		}
		break;
		
		case:ORANGE:
		break;
}

void putRandomFood()
 {

   VGA.clear();


        

    food.posX = rand() % 156 + 2;

    food.posY = rand() % 116 + 2;

    

 }    

 


// Funct To Inializer Objects
 
 void InitialScore(){
    score.posX = 0;
   
     score.posY = 0;
   
     score.Num =0;
   
     score.Text = "0";
 
 
 }
 
 
 void InitialFoodPosition(){
     
   food.posX=100;
     
     food.posY=38;
     
     food.image = Food;
    
     food.width = 1;
    
     food.height = 1;
    
     food.direction = -1;
     
     VGA.writeArea( food.posX, food.posY, 1, 1, Food );     
 
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
 
 
int currenSnakeSize = 0;
void setup(){
 

  VGA.begin(VGAWISHBONESLOT(9),CHARMAPWISHBONESLOT(10));

  Serial.begin(9600);
  
  InitSnakePosition();
  
  InitialFoodPosition();
  
  InitialScore();
  
  VGA.setBackgroundColor(WHITE);

    

 

  

}

int cont = 1;
int currentPixel;;
char*buffers="";
boolean ate = false;
void loop(){
          
     VGA.printtext(score.posX,score.posY,score.Text);
 // itoa(RED,buffers,10);
  //VGA.printtext(100,38,buffers,true );  
  
     Rectangle r3 ={food.posX,food.posY,(food.posX+food.width),(food.posY+food.height) };
     Rectangle r4 ={snake[0].posX,snake[0].posY,(snake[0].posX+snake[0].width),(snake[0].posY+snake[0].height) };
     delay(10);
     int collide= Collide(&r3,&r4);
     if(collide ==1)
     {
       score.Num = score.Num+1;
       itoa(score.Num,buffers,10);
       score.Text = buffers;
       putRandomFood();
     }
  
     

   drawMargins(); 
   drawFood();  

  if(digitalRead(FPGA_BTN_0))
         snake[0].direction = 0;
   if(snake[0].direction==0)
        drawWithDirection(cont,&snake[0]);

  if(digitalRead(FPGA_BTN_1))
          snake[0].direction= 1;
   if(snake[0].direction==1)
       drawWithDirection(cont,&snake[0]);

  if(digitalRead(FPGA_BTN_2))
          snake[0].direction = 2;
   if(snake[0].direction==2) 
       drawWithDirection(cont,&snake[0]);

  if(digitalRead(FPGA_BTN_3))
          snake[0].direction = 3;
    if(snake[0].direction==3)
         drawWithDirection(cont,&snake[0]);

    
  if(verifyIfNextPixelIsDiferenntColor(&snake[0]))          
       VGA.printtext(200,200,"Fin del juego" );             

       delay(50);        //VGA.printtext(0,20,"MSLC");    

    //   VGA.clearArea(100-cont,65,10,9);

       

}


//push
int currentSnakeSize = 0;
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

  void drawSnake()
{
    for(int i = 0; i<=currentSnakeSize; i++){
         VGA.writeArea(snake[i].posX,snake[i].posY,snake[i].width,snake[i].height,snake[i].image);   }
  

  
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
    moveSnake()
     drawSnake();
   }
   if(someSprite->direction==1){
     saveSnakepos();
     someSprite->posY = someSprite->posY-cont;
     moveSnake()
     drawSnake();
   }
   if(someSprite->direction==2){
     saveSnakepos(); 
     someSprite->posX = someSprite->posX+cont;
      moveSnake()
      drawSnake();
   }
   if(someSprite->direction==3){
     saveSnakepos();
     someSprite->posY = someSprite->posY+cont;
     moveSnake()
     drawSnake(); 
   }
     

}


bool verifyIfNextPixelIsDiferenntColor(struct Sprite*head){
    int pixel_t;
    
     //Toma los colors de la izquiera, derecha, arriba y abajo
      pixel_t = VGA.getPixel(head->posX+1,head->posY);
      if(head->direction==0){
           pixel_t = VGA.getPixel(head->posX-1,head->posY);
            if(pixel_t == GREEN){
             VGA.printtext(50,100,"Entre" );
             return true;
            }
      if(head->direction==1){
           pixel_t = VGA.getPixel(head->posX,head->posY-1);
            if(pixel_t == GREEN){
             VGA.printtext(50,100,"Entre" );
              return true;  
          }
      	 }
       if(head->direction==2){
           pixel_t = VGA.getPixel(head->posX+1,head->posY);
            if(pixel_t == GREEN){
             VGA.printtext(50,100,"Entre" );
              return true;  
          }  	 
    }
      
      if(head->direction==3){
           pixel_t = VGA.getPixel(head->posX,head->posY+1);
            if(pixel_t == GREEN) {
             VGA.printtext(50,100,"Entre" );
      	       return true;
            }  
  }
    
	
	

}

}

