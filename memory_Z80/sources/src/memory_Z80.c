/* =============================================================================
Memory Z80 Library (fR3eL Project)
Version: 1.4 (10/12/2024)
Author: mvac7/303bcn
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and z80 assembler
Compiler: SDCC 4.4 or newer 

Description:
Library with basic functions for working with memory on Z80 processors

History of versions:
- v1.4 (10/12/2024) Page management has been removed and added to a new library.
- v1.3 (09/02/2024) Update to SDCC (4.1.12) Z80 calling conventions
- v1.2 (29/09/2021) small optimization in PEEK
- v1.1 (28/06/2018) add slot access functions
- v1.0 (01/03/2016) First version  
============================================================================= */

#include "../include/memory_Z80.h"
#include "../include/msxSystemVariables.h"



/* =============================================================================
   PEEK
 
   Function : Read a 8 bit value from the RAM.
   Input    : [unsigned int] RAM address
   Output   : [char] value
============================================================================= */
char PEEK(unsigned int address) __naked
{
address;	//HL
__asm

  ld   A,(HL)

  ret
__endasm;
}



/* =============================================================================
   PEEKW
 
   Function : Read a 16 bit value from the RAM
   Input    : [unsigned int] RAM address
   Output   : [unsigned int] value
============================================================================= */
unsigned int PEEKW(unsigned int address) __naked
{
address;	//HL
__asm

  ld   E,(HL)
  inc  HL
  ld   D,(HL)
  
  ret
__endasm;
}



/* =============================================================================
   POKE
 
   Function : Write an 8 bit value in RAM
   Input    : [unsigned int] RAM address
              [char] value
   Output   : -
============================================================================= */
void POKE(unsigned int address, char value)
{
address; //HL
value;   //stack
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   A,4(IX)
  ld   (HL),A

  pop  IX
__endasm;
}



/* =============================================================================
   POKEW
 
   Function : Write an 16 bit value in RAM
   Input    : [unsigned int] RAM address
              [unsigned int] value
   Output   : -
============================================================================= */
void POKEW(unsigned int address, unsigned int value) __naked
{
address;	//HL
value;		//DE
__asm
  
  ld   (HL),E
  inc  HL
  ld   (HL),D
  
  ret
__endasm;
}



/* =============================================================================
   CopyRAM
 
   Function : Copy a block of memory to another address.
   Input    : [unsigned int] Source memory address
              [unsigned int] Destination RAM address
              [unsigned int] length 
   Output   : -
============================================================================= */
void CopyRAM(unsigned int source, unsigned int destination, unsigned int length)
{
source;			//HL
destination;	//DE
length;			//Stack
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   C,4(IX)
  ld   B,5(IX) ;length
  
  ldir
  
  pop  IX
__endasm;
}



/* =============================================================================
   FillRAM
 
   Function : Fills an area of the RAM with a value.
   Input    : [unsigned int] RAM address
              [unsigned int] length
              [char] value
   Output   : -
============================================================================= */
void FillRAM(unsigned int address, unsigned int length, char value)
{
address;	//HL
length;		//DE
value;		//Stack
__asm 
  push IX
  ld   IX,#0
  add  IX,SP
    
  ld   C,E
  ld   B,D
  
  ld   A,4(IX) ; value
  
  dec  BC
  
  ld   D,H
  ld   E,L
  
  inc  DE
  
  ld   (HL),A
  ldir
  
  pop  IX
__endasm;
}

