/* =============================================================================
   Test Memory MSX SDCC Library
   Version: 1.1
   Date: 28/06/2018
   Author: mvac7/303bcn
   Architecture: MSX
   Format: ROM 8K
   Programming language: C
   WEB: 
   mail: mvac7303b@gmail.com

   Description:
     Test functions from memory.rel
     
   History of versions:
     - v1.1 (28/06/2018)<
     - v1.0 (11/02/2016)
     
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxSystemVars.h"
#include "../include/msxBIOS.h"

#include "../include/textmode.h"
#include "../include/memory_MSX.h"



#define  HALT __asm halt __endasm   //wait for the next interrupt



// Definitions of Labels -------------------------------------------------------


#define VALUE8B  123
#define VALUE16B 12345

#define PAUSETIME  50



//  definition of functions  ---------------------------------------------------

void test();

char INKEY();
void WAIT(uint cicles);
void PressKey();



// constants  ------------------------------------------------------------------

const char text01[] = "Test Memory MSX SDCC Lib";
const char text02[] = "v1.1 (28/06/2018)";

const char stringOK[] = " Ok";
const char stringErr[] = " Error";

const char stringYES[] = "YES";
const char stringNO[] = "NO";

const char msg01[] = "Press any key to continue";


const char testBloq[]={
 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
96,97,98,99};

// Functions -------------------------------------------------------------------


//
void main(void)
{
    
  test();
  
  WAIT(PAUSETIME);


//EXIT MSXDOS
/*  screen(0);
    
__asm
 	ld b,4(ix)
	ld c,#0x62
	call 5 
__endasm;*/
//end EXIT

  return;
}



/* =============================================================================
One character input (waiting)
============================================================================= */
char INKEY() __naked
{
__asm
   push IX
      
   call CHGET
   ld   L,A
   
   pop  IX
   ret
__endasm;
}



// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
  return;
}




// TEST SCREEN 0 ###############################################################
void test()
{
  uint addr;
  char value;
  char i;
  char slot;
  char defslot;
  char defSslot;
  char page=2;
  uint valueW;
  
  COLOR(LIGHT_GREEN,BLACK,BLACK);      
  SCREEN0();
  WIDTH(40);
  
  
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);

//TEST read & write memory <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  
  //void POKE(uint address, byte value)
  //byte PEEK(uint address)
  LOCATE(0,4);
  PRINT(">Test POKE() & PEEK() --->");  
  POKE(0xE000,VALUE8B);
  value = PEEK(0xE000);
  if(value==VALUE8B) PRINT(stringOK);
  else PRINT(stringErr);
  WAIT(PAUSETIME);
  
  //test PEEKW and POKEW
  //void POKEW(uint address, uint value)
  //uint PEEKW(uint address)
  LOCATE(0,6);
  PRINT(">Test POKEW() & PEEKW() ->");  
  POKEW(0xE000,VALUE16B);
  valueW = PEEKW(0xE000);
  if(valueW==VALUE16B) PRINT(stringOK);
  else PRINT(stringErr);
  WAIT(PAUSETIME);
  
  //test CopyRAM
  //void CopyRAM(unsigned int source, unsigned int destination, unsigned int length);
  LOCATE(0,8);
  PRINT(">Test CopyRAM() --->");
  addr=0xE000;
  valueW=0;
  CopyRAM((uint) testBloq,addr,100);
  for(i=0;i<100;i++){
    HALT;
    valueW=valueW+PEEK(addr++);
    LOCATE(21,8);
    PrintFNumber(valueW,' ',5);
  } 
  if(valueW==4950) PRINT(stringOK);
  else PRINT(stringErr);  
  WAIT(PAUSETIME);
     
  //test fill
  //void FillRAM(uint address, uint length, byte value)
  LOCATE(0,10);
  PRINT(">Test FillRAM() --->");
  addr=0xE000;
  valueW=0;
  FillRAM(addr,100,1);
  //for(i=0;i<100;i++) valueW=valueW+PEEK(addr++);
  for(i=0;i<100;i++){
    HALT;
    valueW=valueW+PEEK(addr++);
    LOCATE(21,10);
    PrintFNumber(valueW,' ',5);
  } 
  if(valueW==100) PRINT(stringOK);
  else PRINT(stringErr);
  WAIT(PAUSETIME);
  
  PRINT("\n");
  PressKey();
//TEST END read & write memory <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  

  
//TEST GetPageSlot <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  CLS();
  PRINT(">Test GetPageSlot(page)\n\n");
  for(i=0;i<4;i++)
  {
    PRINT("- GetPageSlot(");
    PrintNumber(i);
    PRINT(") ->");
    value = GetPageSlot(i);
    PrintFNumber(value,' ',3);
    //if(value==128) PRINT(" ERROR page>3"); 
    PRINT("\n");
    WAIT(PAUSETIME);
  }
  
  PressKey();
//END TEST GetPageSlot <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  

//TEST SetPageSlot <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  
  CLS();
  PRINT(">Test SetPageSlot(page,slot)\n\n");
  defslot=GetPageSlot(page);
  for(i=0;i<4;i++)
  {
    PRINT("- SetPageSlot(");
    PrintNumber(page);
    PRINT(",");
    PrintNumber(i);
    PRINT(") ->");
    
    SetPageSlot(page,i);
    
    //read slot and compare
    value = GetPageSlot(page);
    
    SetPageSlot(page,defslot); //restore slot
    
    PrintFNumber(value,' ',3);
    PRINT(" -");
        
    if(value==i) PRINT(stringOK);
    else PRINT(stringErr);
  
    //if(value==128) PRINT(" ERR page>3"); 
    PRINT("\n");
    WAIT(PAUSETIME);
  }
  
  PressKey();
//END TEST SetPageSlot <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//TEST IsExpanded <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  
  CLS();
  PRINT(">Test IsExpanded(slot)\n\n");

  for(i=0;i<4;i++)
  {
    PRINT("- IsExpanded(");
    PrintNumber(i);
    PRINT(") -> ");
    if(IsExpanded(i)==true) PRINT(stringYES);
    else PRINT(stringNO);    
    PRINT("\n");
    WAIT(PAUSETIME);
  }
  
  PressKey();
//END TEST IsExpanded <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//TEST GetPageSublot <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  CLS();
  PRINT(">Test GetPageSubslot(page)\n\n");
  for(i=0;i<4;i++)
  {
    PRINT("- GetPageSubslot(");
    PrintNumber(i);
    PRINT(") ->");
    value = GetPageSubslot(i);
    PrintFNumber(value,' ',3);
    //if(value==128) PRINT(" ERROR page>3"); 
    PRINT("\n");
    WAIT(PAUSETIME);
  }
  
  PressKey();
//END TEST GetPageSlot <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//TEST SetPageSubslot <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  CLS();
  PRINT(">Test SetPageSubslot(page,subslot)\n");
      
  page=2;
  defslot=GetPageSlot(page);
  for(slot=0;slot<4;slot++)
  {
    if(IsExpanded(slot)==true)
    {
      SetPageSlot(page,slot);
  
      PRINT("\nPage:");
      PrintNumber(page);
      PRINT("  Slot:");
      //value = GetPageSlot(page);
      PrintNumber(slot);
      PRINT(" Expanded\n");
      
      defSslot=GetPageSubslot(page);
      for(i=0;i<4;i++)
      {
        PRINT("- SetPageSubslot(");
        PrintNumber(page);
        PRINT(",");
        PrintNumber(i);
        PRINT(") ->");
        
        SetPageSubslot(page,i);
        
        //read slot and compare
        value = GetPageSubslot(page);
        
        PrintFNumber(value,' ',3);
        PRINT(" -");
            
        if(value==i){
          PRINT(stringOK);
          POKE(0x8000,0x80);
          if(PEEK(0x8000)==0x80) PRINT("- RAM"); 
          else PRINT("- ?");         
        }else PRINT(stringErr);
         
        //if(value==128) PRINT(" ERR page>3"); 
        PRINT("\n");
        WAIT(PAUSETIME);
      }
      SetPageSubslot(page,defSslot); //restore subslot      
    }
    SetPageSlot(page,defslot); //restore slot   
    
  }
  PressKey();
//END TEST SetPageSubslot <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




  CLS();
  
  LOCATE(16,12);
  PRINT("END TEST");
  
  WAIT(300);
}



void PressKey()
{
  PRINT("\n\n");
  PRINT(msg01);
  INKEY();
}
