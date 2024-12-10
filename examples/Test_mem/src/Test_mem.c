/* =============================================================================
   Test Memory MSX Libraries
   Version: 1.3 (10/12/2024)
   Author: mvac7/303bcn
   Architecture: MSX
   Format: ROM 8K
   Programming language: C
   Compiler: SDCC 4.4 or newer 

   Description:
     Testing of the memoryZ80 and memoryMSXSlots libraries functions.
     
   History of versions:
     - v1.3 (10/12/2024) Separation in two libraries: memoryZ80 and memoryMSXSlots
     - v1.2 (12/02/2024) Z80 calling conventions (SDCC 4.1.12)
     - v1.1 (28/06/2018)
     - v1.0 (11/02/2016)
     
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxSystemVariables.h"
#include "../include/msxBIOS.h"

#include "../include/textmode_MSX.h"
#include "../include/memoryZ80.h"
#include "../include/memoryMSXSlots.h"



#define  HALT __asm halt __endasm   //wait for the next interrupt



// Definitions of Labels -------------------------------------------------------


#define VALUE8B  123
#define VALUE16B 12345

#define PAUSETIME  50



//  definition of functions  ---------------------------------------------------

char INKEY(void);
void WAIT(uint cicles);
void PressAnyKey(void);

void test(void);
void TestGetSlotFromPage(void);
void TestSetPageSlot(void);
void TestIsSlotExpanded(void);
void TestGetSubslotFromPage(void);
void TestSetPageSubslot(void);

boolean isRAM(char page);



// constants  ------------------------------------------------------------------

const char text01[] = "Test Memory MSX Libraries";
const char text02[] = "memoryZ80 & memoryMSXSlots";

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

}



/* =============================================================================
One character input (waiting)
============================================================================= */
char INKEY(void) __naked
{
__asm 
  
  jp BIOS_CHGET

__endasm;
}



// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
}



void PressAnyKey(void)
{
  PRINT("\n\n");
  PRINT(msg01);
  INKEY();
}



void test(void)
{
  uint addr;
  char value;
  char i;
  //char slot;
  //char defSlot;
  //char page=2;
  uint valueW;
  boolean testResult;
  
  
  COLOR(LIGHT_GREEN,BLACK,BLACK);
  WIDTH(40);
  SCREEN0();  
  
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);
  

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Test memoryZ80
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
  testResult=true;
  CopyRAM((uint) testBloq,addr,100);
  for(i=0;i<100;i++){
    HALT;
	if(testBloq[i]!=PEEK(addr++)) testResult = false;
    LOCATE(21,8);
    PrintFNumber(i+1,' ',5);
  } 
  if(testResult==true) PRINT(stringOK);
  else PRINT(stringErr);  
  WAIT(PAUSETIME);
     
  //test fill
  //void FillRAM(uint address, uint length, byte value)
  LOCATE(0,10);
  PRINT(">Test FillRAM() --->");
  addr=0xE000;
  testResult=true;
  FillRAM(addr,100,170);
  //for(i=0;i<100;i++) valueW=valueW+PEEK(addr++);
  for(i=0;i<100;i++){
    HALT;
    if(PEEK(addr++)!=170) testResult = false;
    LOCATE(21,10);
    PrintFNumber(i+1,' ',5);
  } 
  if(testResult==true) PRINT(stringOK);
  else PRINT(stringErr);
  WAIT(PAUSETIME);
  
  PRINT("\n");
  PressAnyKey();
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Test memoryMSXSlots
  TestGetSlotFromPage();

  TestSetPageSlot();

  TestIsSlotExpanded();

  TestGetSubslotFromPage();

  TestSetPageSubslot();
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



  CLS();
  
  LOCATE(16,12);
  PRINT("END TEST");
  
  WAIT(300);
}



void TestGetSlotFromPage(void)
{
	char page;
	char slot;
	
	CLS();
	PRINT(">Test GetSlotFromPage(page)\n\n");
	
	for(page=0;page<4;page++)
	{
		PRINT("- GetSlotFromPage(");
		PrintNumber(page);
		PRINT(") ->");
		slot = GetSlotFromPage(page);
		PrintFNumber(slot,' ',3);
		
		if(isRAM(page)==true) PRINT("- RAM"); 
		else PRINT("- ?");

		PRINT("\n");
		WAIT(PAUSETIME);
	}

	PressAnyKey();
}



void TestSetPageSlot(void)
{
	char page=2;
	char slot;
	char defSlot;
	char value;
	
	CLS();
	PRINT(">Test SetPageSlot(page,slot)\n\n");
	
	defSlot=GetSlotFromPage(page);
	
	for(slot=0;slot<4;slot++)
	{
		PRINT("- SetPageSlot(");
		PrintNumber(page);
		PRINT(",");
		PrintNumber(slot);
		PRINT(") ->");

		SetPageSlot(page,slot);

		//read slot and compare
		value = GetSlotFromPage(page);

		SetPageSlot(page,defSlot); //restore slot

		PrintFNumber(value,' ',3);
		PRINT(" -");
			
		if(value==slot) PRINT(stringOK);
		else PRINT(stringErr);

		PRINT("\n");
		WAIT(PAUSETIME);
	}

	PressAnyKey();	
}



void TestIsSlotExpanded(void)
{
	char slot;
	
	CLS();
	PRINT(">Test IsSlotExpanded(slot)\n\n");

	for(slot=0;slot<4;slot++)
	{
		PRINT("- IsSlotExpanded(");
		PrintNumber(slot);
		PRINT(") -> ");
		if(IsSlotExpanded(slot)==true) PRINT(stringYES);
		else PRINT(stringNO);    
		PRINT("\n");
		WAIT(PAUSETIME);
	}

	PressAnyKey();
}



void TestGetSubslotFromPage(void)
{
	char page;
	char slot;
	char subslot;
	
	CLS();
	PRINT(">Test GetSubslotFromPage(page)\n\n");
	
	for(page=0;page<4;page++)
	{
		PRINT("- Page:");
		PrintFNumber(page,' ',2);
		PRINT(" Slot:");
		slot = GetSlotFromPage(page);
		PrintFNumber(slot,' ',2);
				
		if(IsSlotExpanded(slot)==true)
		{			
			PRINT(" Subslot:");
			subslot = GetSubslotFromPage(page);
			PrintFNumber(subslot,' ',2);
			
			if(isRAM(page)==true) PRINT(" - RAM\n"); 
			else PRINT(" - ?\n");

			WAIT(PAUSETIME);
		}else{
			PRINT(" Not Expanded\n");
			WAIT(PAUSETIME);
		}
	}

	PressAnyKey();
}



void TestSetPageSubslot(void)
{
	char i;
	char page;
	char slot;
	char defSlot;
	char tmpValue;
	char defSubSlot;
	
	CLS();
	PRINT(">Test SetPageSubslot(page,subslot)\n");
	  
	page=2; // <<--- only test page 2
	defSlot=GetSlotFromPage(page);
	for(slot=0;slot<4;slot++)
	{
		PRINT("\nPage:");
		PrintNumber(page);
		PRINT("  Slot:");
		PrintNumber(slot);
	  
		if(IsSlotExpanded(slot)==true)
		{
			SetPageSlot(page,slot);

			PRINT(" Expanded\n");

			defSubSlot=GetSubslotFromPage(page);
			for(i=0;i<4;i++)
			{
				PRINT("- SetPageSubslot(");
				PrintNumber(page);
				PRINT(",");
				PrintNumber(i);
				PRINT(") ->");

				SetPageSubslot(page,i);

				//read slot and compare
				tmpValue = GetSubslotFromPage(page);

				PrintFNumber(tmpValue,' ',3);
				PRINT(" -");
					
				if(tmpValue==i) PRINT(stringOK);		
				else PRINT(stringErr);
				 
				PRINT("\n");
				WAIT(PAUSETIME);
			}
			SetPageSubslot(page,defSubSlot); //restore subslot      
		}else{
			PRINT(" Not Expanded\n");
		}
		SetPageSlot(page,defSlot); //restore slot   

	}
	PressAnyKey();
}



boolean isRAM(char page)
{
	uint addr;
	char tmpValue;
	char newValue;
	
	addr=0x4000*page;
	
	tmpValue=PEEK(addr);
	newValue=tmpValue+170;

	POKE(addr,newValue);
	if(PEEK(addr)==newValue){ 
		POKE(addr,tmpValue); //restore value
		return true;
	}
	
	return false;	
}