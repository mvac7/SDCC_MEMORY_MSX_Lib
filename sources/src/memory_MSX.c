/* =============================================================================
   Memory MSX SDCC Library (fR3eL Project)
   Version: 1.2
   Date: 29/09/2021
   Author: mvac7
   Architecture: MSX
   Format: C Object (SDCC .rel)
   Programming language: C and z80 assembler

   Description:
     Basic functions to access the memory of the Z80 and functions for the 
     selection of slots and subslots of the MSX
   
   History of versions:
   - v1.2 (29/09/2021)< small optimization in PEEK
   - v1.1 (28/06/2018) add slot access functions
   - v1.0 (01/03/2016) First version  
============================================================================= */

#include "../include/memory_MSX.h"
#include "../include/msxSystemVars.h"

#define  PPIregA 0xA8



/* =============================================================================
   PEEK
 
   Function : Read a 8 bit value from the RAM.
   Input    : [unsigned int] RAM address
   Output   : [char] value
============================================================================= */
char PEEK(unsigned int address) __naked
{
address;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   L,4(IX)
  ld   H,5(IX)
  ld   L,(HL)

  pop  IX
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
void POKE(unsigned int address, char value) __naked
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
  ret
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
void CopyRAM(unsigned int source, unsigned int destination, unsigned int length) __naked
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
  ret
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
void FillRAM(unsigned int address, unsigned int length, char value) __naked
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
  ret
__endasm;
}



/* =============================================================================
   GetPageSlot
 
   Function : Provide the slot of the indicated page.
   Input    : [char] page (0-3)              
   Output   : [char] slot (0-3)   
============================================================================= */
char GetPageSlot(char page) __naked
{
page;
__asm 
  push IX
  ld   IX,#0
  add  IX,SP
   
  di
  
  ld   A,4(IX)        ;slot
  and  #0x03
  
;  cp   #4
;  jr   NC,PAGEERROR  ;A>=4
  
  or   A              ;A=0?
  jr   Z,PAGE0        ;if (A==0) GOTO PAGE0
  
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
  ld   L,A      ;<--- output value
  
  ei
  
;  pop  IX  
;  ret    
;PAGEERROR:
;  ld   L,#128  ;<-- error code

  pop  IX
  ret
__endasm;
}



/* =============================================================================
   GetPageSubslot
 
   Function : Provide the subslot of the indicated page.
   Input    : [char] page (0-3)              
   Output   : [char] subslot (0-3)   
============================================================================= */
char GetPageSubslot(char page) __naked
{
page;
__asm 
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   A,4(IX)      ;slot
  and  #0x03
  
  or   A            ;A=0?
  jr   Z,PAGE0SS    ;if (A==0) GOTO PAGE0
  
  ld   B,A
  ld   A,(#SLTSL)   ;0xFFFF
  cpl
  ; for B
nextRRCASS:
  RRCA
  RRCA
  djnz nextRRCASS
  jr   getPageValueSS

PAGE0SS:
  ld   A,(#SLTSL)
  cpl
    
getPageValueSS:  
  and  #0x03
  ld   L,A ;<--- output value
  
  pop  IX
  ret
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
============================================================================= */
void SetPageSlot(char page, char slot) __naked
{
page;slot;
__asm 
  push IX
  ld   IX,#0
  add  IX,SP
  
  
  ld   A,4(IX) ;page
  and  #0x03
  ld   E,A
  
  ld   A,5(IX) ;slot
  and  #0x03
  ld   C,A 
  
  di
  in   A,(PPIregA)
  ld   D,A
  
  call SETSLOT
  out  (PPIregA),A
  ei
  
  pop  IX
  ret
  

;------------------------------------------------------------------------------- SETSLOT
SETSLOT:
  ld   A,E
  or   A           ;A=0?
  jr   Z,ifPAGE0   ;if (A==0) GOTO PAGE0  -- si la pagina es la 0 no hay que rotar 
  
  ld   B,E
  ld   A,D
; for B --- roto para que la posicion de la pagina que queremos modificar ocupe los bits 0 y 1
nextPage:
  RRCA
  RRCA
  djnz nextPage
  jr   setSlot

ifPAGE0:
  ld   A,D

setSlot:  
  and  #0xFC   ;pongo a 0 los dos primeros bits  
  add  A,C     ;sumo el valor del slot
  
  ex   AF,AF
  
  ld   A,E
  or   A           ;A=0?
  jr   Z,noRLCA
    
  ld   B,E
  ex   AF,AF
;restore A - roto el valor hasta situarlo en la posicion correcta
nextPage2:
  RLCA
  RLCA
  djnz nextPage2  
  ret
  
noRLCA:
  ex   AF,AF
  ret 
;------------------------------------------------------------------- END SETSLOT    
__endasm;
}



/* =============================================================================
   SetPageSubslot
 
   Function : Set a subslot on the indicated page (For expanded slots)
   Input    : [char] page (0-3)
              [char] subslot (0-3)
   Output   : -

  
   More Info: (by MSX Assembly Page)  
   http://map.grauw.nl/resources/msx_io_ports.php
               
           Secondary slot select register:
               The subslot select register can be found at memory address #FFFF:
               0-1 Subslot for page 0 (#0000-#3FFF)
               2-3 Subslot for page 1 (#4000-#7FFF)
               4-5 Subslot for page 2 (#8000-#BFFF)
               6-7 Subslot for page 3 (#C000-#FFFF)
============================================================================= */
void SetPageSubslot(char page, char subslot) __naked
{
page;subslot;
__asm 
  push IX
  ld   IX,#0
  add  IX,SP  
  
  ld   A,4(IX) ;page
  and  #0x03
  ld   E,A
  
  ld   A,5(IX) ;subslot
  and  #0x03
  ld   C,A 
  
  ld   A,(#SLTSL)  ;0xFFFF
  cpl
  ld   D,A
  
  call SETSLOT       ;Use the SETSLOT routine included in SetPageSlot 
  ld   (#SLTSL),A
  
  pop  IX
  ret
__endasm;
}




/* =============================================================================
   IsExpanded
 
   Function : Returns if the slot is of the expanded type.
   Input    : [char] slot (0-3)
   Output   : [boolean] true = Yes; false = No
   
        EXPTBL 0xFCC1 Slot 0 expanded?
               0xFCC2 Slot 1 expanded?
               0xFCC3 Slot 2 expanded?
               0xFCC4 Slot 3 expanded?
               Yes = 0x80 ; No = 0
============================================================================= */
boolean IsExpanded(char slot) __naked
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
  ld   HL,#EXPTBL
  
  add  HL,BC
  
  ld   A,(HL)
  ld   L,#0   ;false
  cp   #0x80
  jr   NZ,expandedExit
  ld   L,#1   ;true

expandedExit:
  pop  IX
  ret
__endasm;
}



/*

char WhereIsRAMslot() or SearchRAMslot() or GetRAMslot()
uint getRAM() slot + subslot
*/