# How to use the Memory MSX SDCC Library

---

### Sorry!: This text is pending correction of the English translation.

---

## Index

- [1 Description](#1-Description)
- [2 Requirements](#2-Requirements)
- [3 Functions](#3-Functions)
   - [3.1 Read/Write Memory](#31-Read/Write-Memory)
     - [3.1.1 PEEK](#311-PEEK)
     - [3.1.2 PEEKW](#312-PEEKW)
     - [3.1.3 POKE](#313-POKE)
     - [3.1.4 POKEW](#314-POKEW)
     - [3.1.5 CopyRAM](#315-CopyRAM)
     - [3.1.6 FillRAM](#316-FillRAM)
  
   - [3.2 Manage to memory pages](#32-Manage-to-memory-pages)
     - [3.2.7 GetPageSlot](#327-GetPageSlot)
     - [3.2.8 SetPageSlot](#328-SetPageSlot)
     - [3.2.9 IsExpanded](#329-IsExpanded)
     - [3.2.10 GetPageSubslot](#3210-GetPageSubslot)
     - [3.2.11 SetPageSubslot](#3211-SetPageSubslot)


<br/>

---

## 1 Description

Library with basic functions for Z80's memory and page slots/sublots access.

In the header file there is a definition of boolean type, need for the functions.
This type uses the values "true" or "false" in lowercase, which equals 1 and 0 respectively.

For more information about the MSX memory paging system, you can find the [MSX Assembly Page](http://map.grauw.nl/resources/msx_io_ports.php#ppi), 
in the points: Primary slot select register & Secondary slot select register.

This project is an Open Source library. You can add part or all of this code in your libraries/engines.

Use them for developing MSX applications using Small Device C Compiler (SDCC).

In the source code [`examples/`](examples/), you can find applications for testing and learning purposes.

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it! 


<br/>

---

## 2 Requirements

- [Small Device C Compiler (SDCC) v4.1](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)


<br/>

---

## 3 Functions

###  3.1 Read/Write Memory

#### 3.1.1 PEEK

<table>
<tr><th colspan=3 align="left">PEEK</th></tr>
<tr><td colspan=3>Read a 8 bit value from the memory.</td></tr>
<tr><th>Function</th><td colspan=2>PEEK(address)</td></tr>
<tr><th>Input</th><td>[unsigned int]</td><td>Memory address</td></tr>
<tr><th>Output</th><td>[char]</td><td>Value</td></tr>
<tr><th>Example:</th><td colspan=2><pre>char value;<br/>value = PEEK(0xE000);</pre></td></tr>
</table>


#### 3.1.2 PEEKW 

<table>
<tr><th colspan=3 align="left">PEEKW</th></tr>
<tr><td colspan=3>Read a 16 bit value from the memory.</td></tr>
<tr><th>Function</th><td colspan=2>PEEKW(address)</td></tr>
<tr><th>Input</th><td>[unsigned int]</td><td>Memory address</td></tr>
<tr><th>Output</th><td>[unsigned int]</td><td>Value</td></tr>
<tr><th>Example:</th><td colspan=2><pre>unsigned int value;<br/>value = PEEKW(0xE000);</pre></td></tr>
</table>

            
#### 3.1.3 POKE

<table>
<tr><th colspan=3 align="left">POKE</th></tr>
<tr><td colspan=3>Write an 8 bit value in RAM.</td></tr>
<tr><th>Function</th><td colspan=2>POKE(address,value)</td></tr>
<tr><th rowspan=2>Input</th><td>[unsigned int]</td><td>Memory address</td></tr>
<tr><td>[char]</td><td>Value</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
<tr><th>Example:</th><td colspan=2><pre>POKE(0xE000,0xFF);</pre></td></tr>
</table>


#### 3.1.4 POKEW
           
<table>
<tr><th colspan=3 align="left">POKEW</th></tr>
<tr><td colspan=3>Write an 16 bit value in RAM.</td></tr>
<tr><th>Function</th><td colspan=2>POKEW(address,value)</td></tr>
<tr><th rowspan=2>Input</th><td>[unsigned int]</td><td>Memory address</td></tr>
<tr><td>[unsigned int]</td><td>Value</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
<tr><th>Example:</th><td colspan=2><pre>POKEW(0xE000,12345);</pre></td></tr>
</table>

            
#### 3.1.5 CopyRAM

<table>
<tr><th colspan=3 align="left">CopyRAM</th></tr>
<tr><td colspan=3>Copy a block of memory to another address.</td></tr>
<tr><th>Function</th><td colspan=2>CopyRAM(source, destination, length)</td></tr>
<tr><th rowspan=3>Input</th><td>[unsigned int]</td><td>Source memory address</td></tr>
<tr><td>[unsigned int]</td><td>Destination RAM address</td></tr>
<tr><td>[unsigned int]</td><td>Length</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
<tr><th>Example:</th><td colspan=2><pre>CopyRAM(0x0000,0xE000,128);</pre></td></tr>
</table>


#### 3.1.6 FillRAM

<table>
<tr><th colspan=3 align="left">FillRAM</th></tr>
<tr><td colspan=3>Fills an area of the RAM with a value.</td></tr>
<tr><th>Function</th><td colspan=2>FillRAM(address,length,value)</td></tr>
<tr><th rowspan=3>Input</th><td>[unsigned int]</td><td>RAM address</td></tr>
<tr><td>[unsigned int]</td><td>Length</td></tr>
<tr><td>[char]</td><td>Value</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
<tr><th>Example:</th><td colspan=2><pre>FillRAM(0xE000,1234,0xFF);</pre></td></tr>
</table>



### 3.2 Manage to memory pages                                               

#### 3.2.7 GetPageSlot

<table>
<tr><th colspan=3 align="left">GetPageSlot</th></tr>
<tr><td colspan=3>Provide the slot of the indicated page.</td></tr>
<tr><th>Function</th><td colspan=2>GetPageSlot(page)</td></tr>
<tr><th>Input</th><td>[char]</td><td>Page (0-3)</td></tr>
<tr><th>Output</th><td>[char]</td><td>Slot (0-3)</td></tr>
<tr><th>Example:</th><td colspan=2><pre>char value;<br/>value = GetPageSlot(2);</pre></td></tr>
</table>


#### 3.2.8 SetPageSlot

<table>
<tr><th colspan=3 align="left">SetPageSlot</th></tr>
<tr><td colspan=3>Set a slot on the indicated page.</td></tr>
<tr><th>Function</th><td colspan=2>SetPageSlot(page, slot)</td></tr>
<tr><th rowspan=2>Input</th><td>[char]</td><td>Page (0-3)</td></tr>
<tr><td>[char]</td><td>Slot (0-3)</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
<tr><th>Example:</th><td colspan=2><pre>char slot;<br/>slot = GetPageSlot(1);<br/>SetPageSlot(2,slot);</pre></td></tr>
</table>


#### 3.2.9 IsExpanded

<table>
<tr><th colspan=3 align="left">IsExpanded</th></tr>
<tr><td colspan=3>Returns if the slot is of the expanded type.</td></tr>
<tr><th>Function</th><td colspan=2>IsExpanded(slot)</td></tr>
<tr><th>Input</th><td>[char]</td><td>Slot (0-3)</td></tr>
<tr><th>Output</th><td>[boolean]</td><td>true = Yes; false = No</td></tr>
<tr><th>Example:</th><td colspan=2><code>if(IsExpanded(2)) PRINT("Yes");</code></td></tr>
</table>


#### 3.2.10 GetPageSubslot

<table>
<tr><th colspan=3 align="left">GetPageSubslot</th></tr>
<tr><td colspan=3>Provide the subslot of the indicated page (For expanded slots)</td></tr>
<tr><th>Function</th><td colspan=2>GetPageSubslot(page)</td></tr>
<tr><th>Input</th><td>[char]</td><td>Page (0-3)</td></tr>
<tr><th>Output</th><td>[char]</td><td>Subslot (0-3)</td></tr>
<tr><th>Example:</th><td colspan=2><pre>char subslot;<br/>subslot = GetPageSubslot(1);</pre></td></tr>
</table>
            

#### 3.2.11 SetPageSubslot

<table>
<tr><th colspan=3 align="left">SetPageSubslot</th></tr>
<tr><td colspan=3>Set a subslot on the indicated page (For expanded slots)</td></tr>
<tr><th>Function</th><td colspan=2>SetPageSubslot(page, subslot)</td></tr>
<tr><th rowspan=2>Input</th><td>[char]</td><td>Page (0-3)</td></tr>
<tr><td>[char]</td><td>Subslot (0-3)</td></tr>
<tr><th>Output</th><td colspan=2> --- </td></tr>
<tr><th>Example:</th><td colspan=2><pre>
if(IsExpanded(3))
{
  SetPageSlot(2,3);
  SetPageSubslot(2,1);
}
</pre></td></tr>
</table>


<br/>

---

![Creative Commons License](https://i.creativecommons.org/l/by-nc/4.0/88x31.png) 
<br/>This document is licensed under a [Creative Commons Attribution-NonCommercial 4.0 International License](http://creativecommons.org/licenses/by-nc/4.0/).
