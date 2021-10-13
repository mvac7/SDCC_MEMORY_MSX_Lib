# Memory MSX SDCC Library (fR3eL Project)

```
Author: mvac7
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and Z80 assembler
```

<br/>

---

## Description

Library with basic functions for Z80's memory and page slots/sublots access.

In the header file there is a definition of boolean type, need for the functions.
This type uses the values "true" or "false" in lowercase, which equals 1 and 0 respectively.

For more information about the MSX memory paging system, you can find the [MSX Assembly Page](http://map.grauw.nl/resources/msx_io_ports.php#ppi), 
in the points: Primary slot select register & Secondary slot select register.

This project is an Open Source library. You can add part or all of this code in your libraries/engines.

Use them for developing MSX applications using Small Device C Compiler (SDCC).

You can access the documentation here with [`How to use the library`](docs/HOWTO.md).

In the source code [`examples/`](examples/), you can find applications for testing and learning purposes.

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!   

<br/>

---

## History of versions

- v1.2 (29/09/2021)< small optimization in PEEK
- v1.1 (28/06/2018)<Add slot access functions
- v1.0 (01/03/2016) First version

<br/>

---

## Requirements

- [Small Device C Compiler (SDCC) v4.1](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)

<br/>

---

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


<br/>

---
## Acknowledgments
  
I want to give a special thanks to all those who freely share their knowledge with the MSX developer community.

- Avelino Herrera > [`WEB`](http://msx.avelinoherrera.com/index_es.html)
- Nerlaska > [`Blog`](http://albertodehoyonebot.blogspot.com.es)
- Marq > [`Marq`](http://www.kameli.net/marq/)
- MSXKun/Paxanga soft > [`WEB`](http://paxangasoft.retroinvaders.com/)
- Fubukimaru [`gitHub`](https://github.com/Fubukimaru)
- Andrear > [`Blog`](http://andrear.altervista.org/home/msxsoftware.php)
- Sapphire/Z80ST > [`WEB`](http://z80st.auic.es/)
- Fernando García > [`Video Tutorial`](http://www.z80st.es/cursos/bitvision-assembler)
- Ramones > [`MSXblog`](https://www.msxblog.es/tutoriales-de-programacion-en-ensamblador-ramones/) - [`MSXbanzai`](http://msxbanzai.tni.nl/dev/faq.html)
- Eric Boez > [`gitHub`](https://github.com/ericb59)
- MSX Assembly Page > [`WEB`](http://map.grauw.nl/resources/msxbios.php)
- Portar MSX Tech Doc > [`WEB`](https://problemkaputt.de/portar.htm)
- MSX Resource Center > [`WEB`](http://www.msx.org/)
- Karoshi MSX Community > [`WEB`](http://karoshi.auic.es/)
- BlueMSX emulator >> [`WEB`](http://www.bluemsx.com/)
- OpenMSX emulator >> [`WEB`](http://openmsx.sourceforge.net/)
- [`WebMSX`](https://webmsx.org/) emulator by Paulo A. Peccin >> [`gitHub`](https://github.com/ppeccin/webmsx)
- fMSX emulator by Marat Fayzullin [`WEB`](https://fms.komkon.org/fMSX/)
- Meisei emulator by Hap >> `?`
