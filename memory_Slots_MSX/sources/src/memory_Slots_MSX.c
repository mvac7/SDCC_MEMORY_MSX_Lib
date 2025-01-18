/* =============================================================================
Memory Slots MSX Library (fR3eL Project)
Version: 1.4 (19/12/2024)
Author: mvac7/303bcn
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and z80 assembler
Compiler: SDCC 4.4 or newer 

Description:
 Library for accessing page slots and subslots on MSX systems.

History of versions:
- v1.4 (10/12/2024) This library contains only the paging management of 
				   the MSX system.
- v1.3 (09/02/2024) Update to SDCC (4.1.12) Z80 calling conventions
- v1.2 (29/09/2021) small optimization in PEEK
- v1.1 (28/06/2018) add slot access functions
- v1.0 (01/03/2016) First version  
============================================================================= */

#include "../include/memory_Slots_MSX.h"
#include "../include/msxSystemVariables.h"

#define  PPIregA 0xA8




/* =============================================================================
   GetSlotFromPage
 
   Function : Returns the slot number of the indicated page.
   Input    : [char] page (0-3)              
   Output   : [char] slot (0-3)   
============================================================================= */
char GetSlotFromPage(char page) __naked
{
page;	//A
__asm 
   
  di
  
  and  #0x03  
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
;  A <--- output value
   
  ei
  
  ret
__endasm;
}



/* =============================================================================
   SetPageSlot
 
   Function : Set a slot on the indicated page.
   Input    : [char] page (0-3)
              [char] slot (0-3)
   Output   : -

  
   More Info: 
   - Wiki > Slots (by MSX REsource Center) https://www.msx.org/wiki/Slots
   - MSX I/O ports > Programmable Peripheral Interface (by MSX Assembly Page) https://map.grauw.nl/resources/msx_io_ports.php#ppi
   
   Primary slot select register
      page 0 > 0x0000 - 0x3FFF
      page 1 > 0x4000 - 0x7FFF
      page 2 > 0x8000 - 0xBFFF
      page 3 > 0xC000 - 0xFFFF
			   
	PPI-register A (0xA8) Primary slot select register:	
	 76    | 54    | 32    | 10    | bits
	-------|-------|-------|-------|
	page 3 |page 2 |page 1 |page 0 | slot value
============================================================================= */
void SetPageSlot(char page, char slot) __naked
{
page;	//A
slot;	//L
__asm 
  
  ; A  <--------- page
  and  #0x03
  ld   E,A
  
  ld   A,L   ;<-- slot
  and  #0x03
  ld   D,A 
  
  di
  in   A,(PPIregA)
  call EditSLOTval
  out  (PPIregA),A
  ei
  
  ret
  

; set page in slot position in slot config value
; --> D (slot)
; --> E (page)
; --> A  last slot config value
; A <-- New slot config value
;------------------------------------------------------------------------------- EditSLOTval
EditSLOTval:
	ld   L,A
  
	call setPagePos

writeSlotVal:  
	and  #0b11111100	;set to 0 the two first bits  
	add  A,D			;sumo el valor del slot
  
	ld   L,A
  
setPagePos: 
;set page position
	ld   A,E
	or   A
	jr   Z,ifPAGE0

	ld   B,A	
	ld   A,L
;rotate the value until it is in the correct position
RotPage:
	RLCA
	RLCA
	djnz RotPage  
	ret

ifPAGE0:
;no need to rotate the value
	ld   A,L
	ret  
;------------------------------------------------------------------- END EditSLOTval    

__endasm;
}






// ############################################################################# <<<
//   Functions for computers with expanded slots.


/* =============================================================================
   IsSlotExpanded
 
   Function : Returns if the slot is of the expanded type.
   Input    : [char] slot (0-3)
   Output   : [boolean] true = Yes; false = No
   
        EXPTBL 0xFCC1 Slot 0 expanded?
               0xFCC2 Slot 1 expanded?
               0xFCC3 Slot 2 expanded?
               0xFCC4 Slot 3 expanded?
               Yes = 0x80 ; No = 0
============================================================================= */
boolean IsSlotExpanded(char slot) __naked
{
slot;		//A
__asm 

  and  #0x03
  ld   C,A
  ld   B,#0
  ld   HL,#EXPTBL
  
  add  HL,BC
  
  ld   A,(HL)
  cp   #0x80
  jr   NZ,expandFALSE
  
  ld   A,#1		;true
  ret
  
expandFALSE:
  xor  A		;false
  ret
__endasm;
}



/* =============================================================================
   GetSubslotFromPage
 
   Function : Returns the Subslot number of the indicated page.
   Input    : [char] page (0-3)              
   Output   : [char] subslot (0-3)   
============================================================================= */
char GetSubslotFromPage(char page) __naked
{
page;		//A
__asm 

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
;  A <--- output value
  
  ret
__endasm;
}



/* =============================================================================
   SetPageSubslot
 
   Function : Set a subslot on the indicated page.
              If the slot is not expanded it will have no effect.
			  
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
page;		//A
subslot;	//L
__asm 
  
  ; A  <--------- page
  and  #0x03
  ld   E,A
  
  ld   A,L ;<---- subslot
  and  #0x03
  ld   D,A 
  
  ld   A,(#SLTSL)		;0xFFFF Secondary Slot select register system variable.
						;(Reading returns the inverted previously written value)
  cpl	;invert A  
  
  call EditSLOTval
  ld   (#SLTSL),A
  
  ret
__endasm;
}


// ############################################################################# <<<




/*
char WhereIsRAMslot() or SearchRAMslot() or GetRAMslot()
uint getRAM() slot + subslot
*/
