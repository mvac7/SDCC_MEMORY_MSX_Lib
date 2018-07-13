# SDCC MSX Z80 Memory Functions Library (object type)

Version: 1.1

Date: 28/06/2018

Author: mvac7/303bcn

Architecture: MSX

Format: C Object (SDCC .rel)

Programming language: C

WEB:
 
mail: mvac7303b@gmail.com


History of versions:
- v1.1 (28/06/2018)<Add slot access functions
- v1.0 (01/03/2016) First version



## 1. Introduction

This project is an Open Source library with basic functions for Z80's memory 
and page slots/sublots access.
  
Use them for developing MSX applications using Small Device C Compiler (SDCC).

Includes an application for test and learning purposes.

For more information about the MSX memory paging system, you can find the 
MSX Assembly Page, in the points: Primary slot select register & Secondary slot 
select register.

http://map.grauw.nl/resources/msx_io_ports.php#ppi


## 2. Acknowledgments
  
Thanks for Info & help, to:

* Avelino Herrera > http://msx.atlantes.org/index_es.html
* Nerlaska > http://albertodehoyonebot.blogspot.com.es
* Fubu > http://www.gamerachan.org/fubu/
* Marq/Lieves!Tuore > http://www.kameli.net/lt/
* Sapphire/Z80ST > http://z80st.auic.es/
* Pentacour > http://pentacour.com/
* JamQue/TPM > http://www.thepetsmode.com/
* Andrear > http://andrear.altervista.org/home/msxsoftware.php
* Konamiman > https://www.konamiman.com
* MSX Assembly Page > http://map.grauw.nl/resources/msxbios.php
* Portar MSX Tech Doc > http://nocash.emubase.de/portar.htm
* MSX Resource Center > http://www.msx.org/
* Karoshi MSX Community > http://karoshi.auic.es/
* BlueMSX >> http://www.bluemsx.com/
* OpenMSX >> http://openmsx.sourceforge.net/
* Meisei  >> ?



## 3. Requirements

* Small Device C Compiler (SDCC) v3.6 http://sdcc.sourceforge.net/
* Hex2bin v2.2 http://hex2bin.sourceforge.net/ 



## 4. Functions

* char PEEK(address) - Read a 8 bit value from the RAM
* unsigned int PEEKW(address) - Read a 16 bit value from the RAM
* POKE(address,value) - Write an 8 bit value in RAM
* POKEW(address,value) - Write an 16 bit value in RAM
* CopyRAM(source, destination, length) - Copy a block of memory to another address
* FillRAM(address,length,value) - Fills an area of the RAM with a value
* char GetPageSlot(page) - Provide the slot of the indicated page
* SetPageSlot(page, slot) - Set a slot on the indicated page
* boolean IsExpanded(slot) - Returns if the slot is of the expanded type
* char GetPageSubslot(page) - Provide the subslot of the indicated page (For expanded slots)
* void SetPageSubslot(page, subslot) - Set a subslot on the indicated page (For expanded slots)

