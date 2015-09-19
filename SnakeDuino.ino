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

  
  struct Sprite snake;
  
  struct Sprite food;
  
  struct Text score;
   

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

   snake.posX=10;

   snake.posY=65;

   snake.width =1;

   snake.height=1;

   snake.direction = 2;
   
   snake.image = Snake;

 }
 

 
//Funct to Help
/*
boolean touchBound(struct Sprite someSprite){
  if(someSprite.posX ==0 || someSprite.posY == 0 || someSprite.posX == mapwidth-4 || someSprite.posY == mapheight-4)
      true;
} 
 */
 
 

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
     Rectangle r4 ={snake.posX,snake.posY,(snake.posX+snake.width),(snake.posY+snake.height) };
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
         snake.direction = 0;
   if(snake.direction==0)
        drawWithDirection(cont,&snake);

  if(digitalRead(FPGA_BTN_1))
          snake.direction= 1;
   if(snake.direction==1)
       drawWithDirection(cont,&snake);

  if(digitalRead(FPGA_BTN_2))
          snake.direction = 2;
   if(snake.direction==2) 
       drawWithDirection(cont,&snake);

  if(digitalRead(FPGA_BTN_3))
          snake.direction = 3;
    if(snake.direction==3)
         drawWithDirection(cont,&snake);

    
  if(verifyIfNextPixelIsDiferenntColor(&snake))          
       VGA.printtext(200,200,"Fin del juego" );             

       delay(50);        //VGA.printtext(0,20,"MSLC");    

    //   VGA.clearArea(100-cont,65,10,9);

       

}


//push
void saveSnakepos(){
   for(int i = 0; i<currentSnakeSize-1; i++){
     snake[i+1].nextx = snake[i].posX;
     snake[i+1].nexty = snake[i].posY;
	
   }
   
//   VGA.writeArea(snake[currentSnakeSize].posX,snake[currentSnakeSize].posY,1,1,BLACK);
   
}

void moveSnake(){
   for(int i = 1; i<currentSnakeSize-1; i++){
     snake[i].posX = snake[i].nextx;
     snake[i].posY = snake[i].nexty;
	
   }
   
//   VGA.writeArea(snake[currentSnakeSize].posX,snake[currentSnakeSize].posY,1,1,BLACK);
   
}

  

void drawWithDirection(int cont,struct Sprite*someSprite){

    //0 derecha  

    //1 arriba

    //2 izquierda

    //3 abajo


  

   if(someSprite->direction==0){
     someSprite->posX = someSprite->posX-cont;
     VGA.writeArea(someSprite->posX,someSprite->posY,someSprite->width,someSprite->height,someSprite->image);
   }
   if(someSprite->direction==1){
     someSprite->posY = someSprite->posY-cont;
     VGA.writeArea(someSprite->posX,someSprite->posY,someSprite->width,someSprite->height,someSprite->image);
   }
   if(someSprite->direction==2){
      someSprite->posX = someSprite->posX+cont;
     VGA.writeArea(someSprite->posX,someSprite->posY,someSprite->width,someSprite->height,someSprite->image);
   }
   if(someSprite->direction==3){
     someSprite->posY = someSprite->posY+cont;
     VGA.writeArea(someSprite->posX,someSprite->posY,someSprite->width,someSprite->height  ,someSprite->image);  
   }
     

}


bool verifyIfNextPixelIsDiferenntColor(struct Sprite*head){
    int pixel_t;
    
     //Toma los colors de la izquiera, derecha, arriba y abajo
      pixel_t = VGA.getPixel(head->posX+1,head->posY);
      if(head->direction==0){
           pixel_t = VGA.getPixel(head->posX+1,head->posY);
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
           pixel_t = VGA.getPixel(head->posX-1,head->posY);
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

