#include "VGA.h"





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

void drawMargins(){

    VGA.setColor( GREEN );
    
    VGA.drawRect( 1, 0, 1, mapheight );

    VGA.drawRect( mapwidth-2, 0, 1, mapheight );

    VGA.drawRect( 0, 1, mapwidth, 1 );

    VGA.drawRect( 0, mapheight-5, mapwidth, 1 );

}

    

unsigned char Food[] = {
 RED 
};
unsigned char Snake[]={
GREEN

};



struct Sprite{

  int posX;

  int posY;

  int width;

  int height;
  
  int direction;

  unsigned char *image;

  

};


//Sprites
  struct Sprite snake;
  
  struct Sprite food;

 void putRandomFood()
 {

   VGA.clearArea( food.posX, food.posY, 1, 1 );

    food.posX = rand() % 156 + 2;

    food.posY = rand() % 116 + 2;

    VGA.writeArea( 100, 38, 1, 1, Food ); 

    

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
 
 void drawFood(){
      
   VGA.writeArea(food.posX,food.posY,1,1,Food);
 
 }

 
 
 void InitSnakePosition()

 {

   snake.posX=100;

   snake.posY=65;

   snake.width =1;

   snake.height=1;

   snake.direction = 2;
   
   snake.image = Snake;

 }
 
 void DrawCurrentPosFood(){
 
 
 }

void setup(){
 

  VGA.begin(VGAWISHBONESLOT(9),CHARMAPWISHBONESLOT(10));

  Serial.begin(9600);
  
  InitSnakePosition();
  
  InitialFoodPosition();
  
  VGA.setBackgroundColor(WHITE);

    

 

  

}

int cont = 1;
int currentPixel;;
char*buffers="";
boolean marioSeLacome = false;
void loop(){
          
 
 // itoa(RED,buffers,10);
  //VGA.printtext(100,38,buffers,true );  
  
     Rectangle r3 ={food.posX,food.posY,(food.posX+food.width),(food.posY+food.height) };
     Rectangle r4 ={snake.posX,snake.posY,(snake.posX+snake.width),(snake.posY+snake.height) };
     delay(10);
     int collide= Collide(&r3,&r4);
     if(collide ==1)
     {
         marioSeLacome = true;
     }
     if(marioSeLacome)
          VGA.printtext(0,20,"MSLC");  
     

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
    
   
 
  
    
   if(snake.posX==0)
          VGA.printtext(200,200,"Fin del juego" );             
       delay(100);        //VGA.printtext(0,20,"MSLC");    

    //   VGA.clearArea(100-cont,65,10,9);

       

}

  

void drawWithDirection(int cont,struct Sprite*someSprite){

    //0 derecha  

    //1 arriba

    //2 izquierda

    //3 abajo


  VGA.clear();

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

/*
bool verifyIfNextPixelIsDifrentColor(struct Sprite*head){
    typedef unsigned char pixel_t; 
    pixel_t typeOfColor[4];
    
     //Toma los colors de la izquiera, derecha, arriba y abajo
      typeOfColor[0] = VGA.getPixel(head->posX-1,head->posY);
    typeOfColor[1] = VGA.getPixel(head->posX,head->posY+1);
    typeOfColor[2] = VGA.getPixel(head->posX+1,head->posY);
    typeOfColor[3] = VGA.getPixel(head->posX,head->posY-1);
	
	return  verifyIfColissionWithObstacule(*head,typeOfColor);

}

bool verifyIfColissionWithObstacule(struct Sprite spriteToVerify, unsigned char*nextsPixels ){
	for(int pos=0; pos<4; pos++){
		if(nextsPixels[pos] == 224 && spriteToVerify.direction== pos){
			return true;
		}
	}
  return false;
}
*/
