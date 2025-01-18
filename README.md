# MSX Memory SDCC Libraries (fR3eL Project)

<table>
<tr><td>Architecture</td><td>MSX</td></tr>
<tr><td>Format</td><td>C Object (SDCC .rel)</td></tr>
<tr><td>Programming language</td><td>C and Z80 assembler</td></tr>
</table>

<br/>

---

## Description

This project provides two libraries for accessing the memory of MSX systems:
- **memoryZ80** provides you with functions to read or write to the memory. 
- **memoryMSXSlots** allows you to configure the pages of the slots and subslots.

Use them for developing MSX applications using Small Device C Compiler (SDCC).

You can access the documentation here with [`How to use the library`](docs/HOWTO.md).

In the source code [`examples/`](examples/), you can find applications for testing and learning purposes.

This project is an Open Source library. You can add part or all of this code in your libraries/engines.

These libraries are part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!   

<br/>

---

## History of versions

- v1.4 (10/12/2024) It has been divided into two libraries: memoryZ80 and memoryMSXSlots

### memory_MSX.rel
- v1.3 (09/02/2024) Update to SDCC (4.1.12) Z80 calling conventions. Separated into two libraries.
- v1.2 (29/09/2021) Small optimization in PEEK
- v1.1 (28/06/2018) Add slot access functions
- v1.0 (01/03/2016) First version

<br/>

---

## Requirements

- [Small Device C Compiler (SDCC) v4.4](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)




