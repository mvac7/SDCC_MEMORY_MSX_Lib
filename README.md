# Memory MSX SDCC Library (fR3eL Project)

```
Author: mvac7 [mvac7303b@gmail.com]
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and Z80 assembler
```



## Description

This project is an Open Source library with basic functions for Z80's memory and page slots/sublots access.
  
Use them for developing MSX applications using Small Device C Compiler (SDCC).

The source code includes an application to test or learn how to use the library. 

In the header file there is a definition of boolean type, need for the functions.
This type uses the values "true" or "false" in lowercase, which equals 1 and 0 respectively.

For more information about the MSX memory paging system, you can find the [MSX Assembly Page](http://map.grauw.nl/resources/msx_io_ports.php#ppi), 
in the points: Primary slot select register & Secondary slot select register.

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!   



## History of versions

* v1.1 (28/06/2018)<Add slot access functions
* v1.0 (01/03/2016) First version



## Requirements

* Small Device C Compiler (SDCC) v3.9 http://sdcc.sourceforge.net/
* Hex2bin v2.5 http://hex2bin.sourceforge.net/



## Functions

* char **PEEK**(address) - Read a 8 bit value from the RAM
* unsigned int **PEEKW**(address) - Read a 16 bit value from the RAM
* **POKE**(address,value) - Write an 8 bit value in RAM
* **POKEW**(address,value) - Write an 16 bit value in RAM
* **CopyRAM**(source, destination, length) - Copy a block of memory to another address
* **FillRAM**(address,length,value) - Fills an area of the RAM with a value
* char **GetPageSlot**(page) - Provide the slot of the indicated page
* **SetPageSlot**(page, slot) - Set a slot on the indicated page
* boolean **IsExpanded**(slot) - Returns if the slot is of the expanded type
* char **GetPageSubslot**(page) - Provide the subslot of the indicated page (For expanded slots)
* void **SetPageSubslot**(page, subslot) - Set a subslot on the indicated page (For expanded slots)



## Acknowledgments
  
I want to give a special thanks to all those who freely share their knowledge with the MSX developer community.

* Avelino Herrera > [WEB](http://msx.atlantes.org/index_es.html)
* Nerlaska > [Blog](http://albertodehoyonebot.blogspot.com.es)
* Marq/Lieves!Tuore > [Marq](http://www.kameli.net/marq/) [Lieves!Tuore](http://www.kameli.net/lt/)
* [Fubukimaru](https://github.com/Fubukimaru) > [Blog](http://www.gamerachan.org/fubu/)
* Andrear > [Blog](http://andrear.altervista.org/home/msxsoftware.php)
* Ramones > [MSXblog](https://www.msxblog.es/tutoriales-de-programacion-en-ensamblador-ramones/) - [MSXbanzai](http://msxbanzai.tni.nl/dev/faq.html)
* Sapphire/Z80ST > [WEB](http://z80st.auic.es/)
* Fernando García > [youTube](https://www.youtube.com/user/bitvision)
* Eric Boez > [gitHub](https://github.com/ericb59)
* MSX Assembly Page > [WEB](http://map.grauw.nl/resources/msxbios.php)
* Portar MSX Tech Doc > [WEB](http://nocash.emubase.de/portar.htm)
* MSX Resource Center > [WEB](http://www.msx.org/)
* Karoshi MSX Community (RIP 2007-2020)
* BlueMSX emulator >> [WEB](http://www.bluemsx.com/)
* OpenMSX emulator >> [WEB](http://openmsx.sourceforge.net/)
* Meisei emulator >> ?
