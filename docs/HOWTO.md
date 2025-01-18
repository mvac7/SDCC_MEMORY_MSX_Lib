# How to use the Memory MSX Library

| Attention! |
| :---       |
| The following document has been written using an English translator.<br/>You can participate in the improvement of this document, transmitting your corrections or suggestions in the issues of this project or the main fR3eL project.<br/>Thanks for understanding. |

<br/>

## Index

- [1 Description](#1-Description)
- [2 Requirements](#2-Requirements)
- [3 Libraries](#3-Libraries)
   - [3.1 memoryZ80 · Read/Write Memory](#31-memoryZ80-·-Read/Write-Memory)
     - [3.1.1 PEEK](#311-PEEK)
     - [3.1.2 PEEKW](#312-PEEKW)
     - [3.1.3 POKE](#313-POKE)
     - [3.1.4 POKEW](#314-POKEW)
     - [3.1.5 CopyRAM](#315-CopyRAM)
     - [3.1.6 FillRAM](#316-FillRAM)
  
   - [3.2 memoryMSXSlots · Manage to memory pages](#32-memoryMSXSlots-·-Manage-to-memory-pages)
     - [3.2.7 GetSlotFromPage](#327-GetSlotFromPage)
     - [3.2.8 SetPageSlot](#328-SetPageSlot)
     - [3.2.9 IsSlotExpanded](#329-IsSlotExpanded)
     - [3.2.10 GetSubslotFromPage](#3210-GetSubslotFromPage)
     - [3.2.11 SetPageSubslot](#3211-SetPageSubslot)

- [4 References](#4-References)

<br/>

---

## 1 Description

This project provides two libraries for accessing the memory of MSX systems:
- **memoryZ80** provides you with functions to read or write to the memory. 
- **memoryMSXSlots** allows you to configure the pages of the slots and subslots.

This project is an Open Source library. 
You can add part or all of this code in your application development or include it in other libraries/engines.

Use them for developing MSX applications using Small Device C Compiler [`SDCC`](http://sdcc.sourceforge.net/).

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

<br/>

---

## 2 Requirements

- [Small Device C Compiler (SDCC) v4.4](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)

<br/>

---

## 3 Libraries

###  3.1 memoryZ80 · Read/Write Memory

This library provides you with functions to read or write to the memory.

<br/>

#### 3.1.1 PEEK

<table>
<tr><th colspan=3 align="left">PEEK</th></tr>
<tr><td colspan=3>Read a 8 bit value from the memory.</td></tr>
<tr><th>Function</th><td colspan=2>PEEK(address)</td></tr>
<tr><th>Input</th><td>[unsigned int]</td><td>Memory address</td></tr>
<tr><th>Output</th><td>[char]</td><td>Value</td></tr>
</table>

##### Example:

```c
	char value;
	value = PEEK(0xE000);
```

<br/>  

#### 3.1.2 PEEKW 

<table>
<tr><th colspan=3 align="left">PEEKW</th></tr>
<tr><td colspan=3>Read a 16 bit value from the memory.</td></tr>
<tr><th>Function</th><td colspan=2>PEEKW(address)</td></tr>
<tr><th>Input</th><td>[unsigned int]</td><td>Memory address</td></tr>
<tr><th>Output</th><td>[unsigned int]</td><td>Value</td></tr>
</table>

##### Example:

```c
	unsigned int value;
	value = PEEKW(0xE000);
```

<br/>  

#### 3.1.3 POKE

<table>
<tr><th colspan=3 align="left">POKE</th></tr>
<tr><td colspan=3>Write an 8 bit value in RAM.</td></tr>
<tr><th>Function</th><td colspan=2>POKE(address,value)</td></tr>
<tr><th rowspan=2>Input</th><td>[unsigned int]</td><td>Memory address</td></tr>
<tr><td>[char]</td><td>Value</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
</table>

##### Example:

```c
	POKE(0xE000,0xFF);
```

<br/>  

#### 3.1.4 POKEW
           
<table>
<tr><th colspan=3 align="left">POKEW</th></tr>
<tr><td colspan=3>Write an 16 bit value in RAM.</td></tr>
<tr><th>Function</th><td colspan=2>POKEW(address,value)</td></tr>
<tr><th rowspan=2>Input</th><td>[unsigned int]</td><td>Memory address</td></tr>
<tr><td>[unsigned int]</td><td>Value</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
</table>

##### Example:

```c
	POKEW(0xE000,12345);
```

<br/>  

#### 3.1.5 CopyRAM

<table>
<tr><th colspan=3 align="left">CopyRAM</th></tr>
<tr><td colspan=3>Copy a block of memory to another address.</td></tr>
<tr><th>Function</th><td colspan=2>CopyRAM(source, destination, length)</td></tr>
<tr><th rowspan=3>Input</th><td>[unsigned int]</td><td>Source memory address</td></tr>
<tr><td>[unsigned int]</td><td>Destination RAM address</td></tr>
<tr><td>[unsigned int]</td><td>Length</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
</table>

##### Example:

```c
	CopyRAM(0x0000,0xE000,128);
```

<br/>  

#### 3.1.6 FillRAM

<table>
<tr><th colspan=3 align="left">FillRAM</th></tr>
<tr><td colspan=3>Fills an area of the RAM with a value.</td></tr>
<tr><th>Function</th><td colspan=2>FillRAM(address,length,value)</td></tr>
<tr><th rowspan=3>Input</th><td>[unsigned int]</td><td>RAM address</td></tr>
<tr><td>[unsigned int]</td><td>Length</td></tr>
<tr><td>[char]</td><td>Value</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
</table>

##### Example:

```c
	FillRAM(0xE000,1024,0xFF);
```

<br/>  

---

### 3.2 memoryMSXSlots · Manage to memory pages

This library allows you to configure the pages of the slots and subslots.

In the header file there is a definition of boolean type, need for the functions.
This type uses the values "true" or "false" in lowercase, which equals 1 and 0 respectively.

<br/>

#### 3.2.7 GetSlotFromPage

<table>
<tr><th colspan=3 align="left">GetSlotFromPage</th></tr>
<tr><td colspan=3>Returns the slot number of the indicated page.</td></tr>
<tr><th>Function</th><td colspan=2>char GetSlotFromPage(page)</td></tr>
<tr><th>Input</th><td>[char]</td><td>Page (0-3)</td></tr>
<tr><th>Output</th><td>[char]</td><td>Slot (0-3)</td></tr>
</table>

##### Example:

```c
	char value;
	value = GetSlotFromPage(2);
```

<br/>  

#### 3.2.8 SetPageSlot

<table>
<tr><th colspan=3 align="left">SetPageSlot</th></tr>
<tr><td colspan=3>Set a slot on the indicated page.</td></tr>
<tr><th>Function</th><td colspan=2>SetPageSlot(page, slot)</td></tr>
<tr><th rowspan=2>Input</th><td>[char]</td><td>Page (0-3)</td></tr>
<tr><td>[char]</td><td>Slot (0-3)</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
</table>

##### Example:

```c
	char slot;
	slot = GetSlotFromPage(1);
	SetPageSlot(2,slot);
```

<br/>  

#### 3.2.9 IsSlotExpanded

<table>
<tr><th colspan=3 align="left">IsSlotExpanded</th></tr>
<tr><td colspan=3>Returns if the slot is of the expanded type.</td></tr>
<tr><th>Function</th><td colspan=2>boolean IsSlotExpanded(slot)</td></tr>
<tr><th>Input</th><td>[char]</td><td>Slot (0-3)</td></tr>
<tr><th>Output</th><td>[boolean]</td><td>true = Yes; false = No</td></tr>
</table>

##### Example:

```c
	if(IsSlotExpanded(2)==true) PRINT("Yes");
```

<br/>  

#### 3.2.10 GetSubslotFromPage

<table>
<tr><th colspan=3 align="left">GetSubslotFromPage</th></tr>
<tr><td colspan=3>Returns the Subslot number of the indicated page (For expanded slots)</td></tr>
<tr><th>Function</th><td colspan=2>char GetSubslotFromPage(page)</td></tr>
<tr><th>Input</th><td>[char]</td><td>Page (0-3)</td></tr>
<tr><th>Output</th><td>[char]</td><td>Subslot (0-3)</td></tr>
</table>

##### Example:

```c
	char subslot;
	if(IsSlotExpanded(1)) subslot = GetSubslotFromPage(1);
```

<br/>            

#### 3.2.11 SetPageSubslot

<table>
<tr><th colspan=3 align="left">SetPageSubslot</th></tr>
<tr><td colspan=3>Set a subslot on the indicated page (For expanded slots)</td></tr>
<tr><th>Function</th><td colspan=2>SetPageSubslot(page, subslot)</td></tr>
<tr><th rowspan=2>Input</th><td>[char]</td><td>Page (0-3)</td></tr>
<tr><td>[char]</td><td>Subslot (0-3)</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
</table>

##### Example:

```c
	if(IsSlotExpanded(3))
	{
	  SetPageSlot(2,3);
	  SetPageSubslot(2,1);
	}
```

<br/>

---

## 4 References

- Wiki > [Slots](https://www.msx.org/wiki/Slots) `MSX Resource Center`
- MSX I/O ports > [Programmable Peripheral Interface](https://map.grauw.nl/resources/msx_io_ports.php#ppi) `MSX Assembly Page`
- [Primary slots and secondary slots](https://www.msx.org/forum/semi-msx-talk/emulation/primary-slots-and-secondary-slots) (forum discussion) `MSX Resource Center`

<br/>

---

![Creative Commons License](https://i.creativecommons.org/l/by-nc/4.0/88x31.png) 
<br/>This document is licensed under a [Creative Commons Attribution-NonCommercial 4.0 International License](http://creativecommons.org/licenses/by-nc/4.0/).
