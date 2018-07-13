/* =============================================================================
   SDCC Memory Functions Library (object type)
   Version: 1.0
   Date: 1 March 2016
   Author: mvac7/303bcn
   Architecture: MSX
   Format: C Object (SDCC .rel)
   Programming language: C
   WEB: 
   mail: mvac7303b@gmail.com

   Description:
     Memory access functions
     
============================================================================= */

#include "../include/memory.h"
#include "../include/msxSystemVars.h"

#define  PPIregA 0xA8



/* =============================================================================
   PEEK
 
   Function : Read a 8 bit value from the RAM.
   Input    : [unsigned int] RAM address
   Output   : [char] value
============================================================================= */
char PEEK(unsigned int address)
{
address;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   L,4(ix)
  ld   H,5(ix)
  ld   A,(hl)

  ld   L,A

  pop  IX
__endasm;
}



/* =============================================================================
   PEEKW
 
   Function : Read a 16 bit value from the RAM
   Input    : [unsigned int] RAM address
   Output   : [unsigned int] value
============================================================================= */
unsigned int PEEKW(unsigned int address)
{
address;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
     
  ld   L,4(IX)
  ld   H,5(IX)
  ld   E,(HL)
  inc  HL
  ld   D,(HL)
  ex   DE,HL
  
  pop  IX
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
address;value;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   L,4(IX)
  ld   H,5(IX)
  ld   A,6(IX)
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
void POKEW(unsigned int address, unsigned int value)
{
address;value;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   L,4(IX)
  ld   H,5(IX) ;Memory address
  
  ld   E,6(IX)
  ld   D,7(IX) ;16b value
  
  ld   A,E
  ld   (HL),A
  inc  HL
  ld   A,D
  ld   (HL),A
  
  pop  IX
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
source;destination;length;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   L,4(IX)
  ld   H,5(IX) ;source memory address
  
  ld   E,6(IX)
  ld   D,7(IX) ;Destination RAM address
  
  ld   C,8(IX)
  ld   B,9(IX) ;length
  
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
address;length;value;
__asm 
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   L,4(IX) ; HL direccion de origen
  ld   H,5(IX)
    
  ld   C,6(IX) ; DE num de bytes a copiar
  ld   B,7(IX)
  
  ld   A,8(IX) ; value
  
  dec  BC
  
  ld   D,H
  ld   E,L
  
  inc  DE
  
  ld   (HL),A
  ldir
  
  pop  IX
__endasm;
}



/* =============================================================================
   GetPageSlot
 
   Function : Provide the slot of the indicated page.
   Input    : [char] page (0-3)              
   Output   : [char] slot (0-3)   
============================================================================= */
char GetPageSlot(char page)
{
page;
__asm 
  push IX
  ld   IX,#0
  add  IX,SP
  
  
  di
  
  ld   A,4(IX) ;slot
  cp   #4
  jr   NC,PAGEERROR   ;A>=4
  
  or   A              ;A=0?
  jr   Z,PAGE0 ;if (A==0) GOTO PAGE0
  
  ld   B,A
  in   A,(PPIregA)
  ; for B
nextRRCA:
  RRCA
  RRCA
  djnz nextRRCA
  jr   getPageValue

PAGE0:
  in   A,(PPIregA)
  
getPageValue:  
  and  #0x03
  ld   L,A ;<--- output value
  
  ei
  
  pop  IX  
  ret
    
PAGEERROR:
  ld   L,#128  ;<-- error code
  pop  IX

__endasm;
}



/* =============================================================================
   SetPageSlot
 
   Function : Set a slot on the indicated page.
   Input    : [char] page (0-3)
              [char] slot (0-3)
   Output   : -

  
   More Info: (by MSX Assembly Page)  
   http://map.grauw.nl/resources/msx_io_ports.php
           Primary slot select register
               page 0 > 0x0000 - 0x3FFF
               page 1 > 0x4000 - 0x7FFF
               page 2 > 0x8000 - 0xBFFF
               page 3 > 0xC000 - 0xFFFF
               
           for future versions:
           Secondary slot select register:
               The subslot select register can be found at memory address #FFFF:
               0-1 Subslot for page 0 (#0000-#3FFF)
               2-3 Subslot for page 1 (#4000-#7FFF)
               4-5 Subslot for page 2 (#8000-#BFFF)
               6-7 Subslot for page 3 (#C000-#FFFF)
--------------------------------------------------------------------------------
   More Info:                
        EXPTBL 0xFCC1 Slot 0 expanded?
               0xFCC2 Slot 1 expanded?
               0xFCC3 Slot 2 expanded?
               0xFCC4 Slot 3 expanded?
               Yes = 0x80 ; No = 0
============================================================================= */
void SetPageSlot(char page, char slot)
{
page;slot;
__asm 
  push IX
  ld   IX,#0
  add  IX,SP
  
  
  ld   A,5(IX) ;slot
  and  #0x03
  ld   C,A 
  
  di

  ld   A,4(IX) ;page
  and  #0x03
  or   A           ;A=0?
  jr   Z,ifPAGE0   ;if (A==0) GOTO PAGE0  -- si la pagina es la 0 no hay que rotar 
  
  ld   B,A
  in   A,(PPIregA)
; for B --- roto para que la posicion de la pagina que queremos modificar ocupe los bits 0 y 1
nextPage:
  RRCA
  RRCA
  djnz nextPage
  jr   setSlot

ifPAGE0:
  in   A,(PPIregA)

setSlot:  
  and  #0xFC   ;pongo a 0 los dos primeros bits
  
  add  A,C     ;sumo el valor del slot
  
  push AF
  
  ld   A,4(IX) ;page
  and  #0x03
  or   A           ;A=0?
  jr   Z,noRLCA  
  ld   B,A

  pop  AF
;restore A - roto el valor hasta situarlo en la posicion correcta
nextPage2:
  RLCA
  RLCA
  djnz nextPage2  
  jr   setPPIA
  
noRLCA:
  pop  AF
setPPIA:  
  out  (PPIregA),A
  ei
  
  pop  IX
__endasm;
}


/* =============================================================================
   IsExpanded
 
   Function : 
   Input    : [char] slot (0-3)
   Output   : [boolean]
        EXPTBL 0xFCC1 Slot 0 expanded?
               0xFCC2 Slot 1 expanded?
               0xFCC3 Slot 2 expanded?
               0xFCC4 Slot 3 expanded?
               Yes = 0x80 ; No = 0
============================================================================= */
boolean IsExpanded(char slot)
{
slot;
__asm 
  push IX
  ld   IX,#0
  add  IX,SP

  ld   A,4(IX) ;slot
  and  #0x03
  ld   C,A
  ld   B,#0
  ld   HL,EXPTBL
  
  add  HL,BC
  
  ld   A,(HL)
  ld   L,#0
  cp   #0x80
  jr   NZ,expandedExit
  ld   L,#1   ;YES

expandedExit:
  pop  IX
__endasm;
}



/*

char WhereIsRAMslot() or SearchRAMslot() or GetRAMslot()
uint getRAM() slot + subslot
*/


/*

void SetPageSubslot(char page, char subslot);

*/