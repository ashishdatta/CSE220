//**************************************************************************************************************
// FILE: Disas.c
//
// DESCRIPTION
// K1 disassembler. I wrote this in about a half-an-hour. It's sleazy, but seems to work.
//
// AUTHOR INFORMATION
// Kevin R. Burger
//
// Mailing Address:
// Computer Science & Engineering
// School of Computing, Informatics, and Decision Systems Engineering
// Arizona State University
// Tempe, AZ 85287-8809
//
// Email: burgerk@asu
// Web:	  http://kevin.floorsoup.com
//**************************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int int32;
typedef unsigned int  Address;
typedef unsigned char Byte;
typedef unsigned int  Word;

char *regstring(Byte reg)
{
	if (reg == 0) return "%A ";
	else return "%B ";
}

char *decode(Word instr)
{
	static char chinstr[128];
	char chbuf[128];
	Byte opcode, reg;
	Address labaddr, varaddr;
	int32 imm;

	chinstr[0] = '\0';
	opcode = (instr & 0xF8000000) >> 27;
	if (opcode == 0x00) {
		strcat(chinstr, "LD ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
		varaddr = instr & 0x000FFFFF;
		sprintf(chbuf, "0x%08x", varaddr);
		strcat(chinstr, chbuf);
	} else if (opcode == 0x01) {
		strcat(chinstr, "LDI ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
		imm = instr & 0x03FFFFFF;
		if (imm & 0x02000000) imm |= 0xFC000000;
		sprintf(chbuf, "%d", imm);
		strcat(chinstr, chbuf);
	} else if (opcode == 0x02) {
		strcat(chinstr, "LDA ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
		varaddr = instr & 0x000FFFFF;
		sprintf(chbuf, "0x%08x", varaddr);
		strcat(chinstr, chbuf);
	} else if (opcode == 0x03) {
		strcat(chinstr, "ST ");
		varaddr = instr & 0x000FFFFF;
		sprintf(chbuf, "0x%08x", varaddr);
		strcat(chinstr, chbuf);
		strcat(chinstr, " ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
	} else if (opcode == 0x04) {
		strcat(chinstr, "ADD ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
	} else if (opcode == 0x05) {
		strcat(chinstr, "NEG ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
	} else if (opcode == 0x06) {
		strcat(chinstr, "ROL ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
	} else if (opcode == 0x07) {
		strcat(chinstr, "NOR ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
	} else if (opcode == 0x08) {
		strcat(chinstr, "PUSH ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
	} else if (opcode == 0x09) {
		strcat(chinstr, "POP ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
	} else if (opcode == 0x0A) {
		strcat(chinstr, "BR ");
		labaddr = instr & 0x000FFFFF;
		sprintf(chbuf, "0x%08x", labaddr);
		strcat(chinstr, chbuf);
	} else if (opcode == 0x0B) {
		strcat(chinstr, "BEQ ");
		labaddr = instr & 0x000FFFFF;
		sprintf(chbuf, "0x%08x", labaddr);
		strcat(chinstr, chbuf);
	} else if (opcode == 0x0C) {
		strcat(chinstr, "BLT ");
		labaddr = instr & 0x000FFFFF;
		sprintf(chbuf, "0x%08x", labaddr);
		strcat(chinstr, chbuf);
	} else if (opcode == 0x0D) {
		strcat(chinstr, "BSUB ");
		labaddr = instr & 0x000FFFFF;
		sprintf(chbuf, "0x%08x", labaddr);
		strcat(chinstr, chbuf);
	} else if (opcode == 0x0E) {
		strcat(chinstr, "RET ");
	} else if (opcode == 0x0F) {
		strcat(chinstr, "IN ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
		imm = instr & 0x00000001;
		sprintf(chbuf, "%d", imm);
		strcat(chinstr, chbuf);
	} else if (opcode == 0x10) {
		strcat(chinstr, "OUT ");
		reg = (instr & 0x04000000) >> 26;
		strcat(chinstr, regstring(reg));
		imm = instr & 0x00000001;
		sprintf(chbuf, "%d", imm);
		strcat(chinstr, chbuf);
	} else if (opcode == 0x11) {
		strcat(chinstr, "HALT ");
	} else {
		sprintf(chinstr, "Invalid Opcode = %u", opcode);
	}
	return chinstr;
}

int main(int argc, char *argv[])
{
	char srcfname[128];
	int i;
	int32 varinit;
	Word instr;
	unsigned int offset = 0, segsize;
	Byte magic[6], segtype, zeros[7];
	Address initpc, instraddr, segaddr, varaddr;
	FILE *bin, *sout;

	if (argc != 2) {
		fprintf(stdout, "usage: disas binfile\n");
		exit(-1);
	}

	bin = fopen(argv[1], "rb");
	strcpy(srcfname, argv[1]);
	strcat(srcfname, ".dis");
	sout = fopen(srcfname, "wt");

	magic[5] = '\0';
	fread(magic, 1, 5, bin); offset += 5;
	fprintf(sout, "Magic = [%s]\n", magic);
	if (strcmp((char *)magic, "K1BIN")) {
		fprintf(sout, "Magic bytes are incorrect.\n");
		exit(-1);
	}

	fread(&initpc, 4, 1, bin); offset += 4;
	fprintf(sout, "Init PC = %u (0x%08x)\n", initpc, initpc);

	fread(zeros, 1, 7, bin); offset += 7;
	for (i = 0; i < 7; i++) {
		if (zeros[i] != 0) {
			fprintf(sout, "Error at byte offset 0x%08x: expected 0x00, found 0x%02x\n", 9 + i, zeros[i]);
			exit(-1);
		}
	}

	fread(&segtype, 1, 1, bin); offset++;
	if (segtype != 0) {
		fprintf(sout, "Error at byte offset 0x%08x: expected 0x00, found 0x%02x\n", offset, segtype);
		exit(-1);
	}

	fread(&segsize, 4, 1, bin); offset += 4;
	fprintf(sout, "Data Segment Size = %u (0x%08x)\n", segsize, segsize);

	fread(&segaddr, 4, 1, bin); offset += 4;
	fprintf(sout, ".DATA %d\n", segaddr);

	for (i = 0; i < (segsize - 9) / 4; i++) {
		fread(&varinit, 4, 1, bin); offset += 4;
		varaddr = segaddr + i;
		fprintf(sout, "[0x%08x] %d (0x%08x)\n", varaddr, varinit, varinit);
	}

	fread(&segtype, 1, 1, bin); offset++;
	if (segtype != 1) {
		fprintf(sout, "Error at byte offset 0x%08x: expected 0x01, found 0x%02x\n", offset, segtype);
		exit(-1);
	}

	fread(&segsize, 4, 1, bin); offset += 4;
	fprintf(sout, "Text Segment Size = %u (0x%08x)\n", segsize, segsize);

	fread(&segaddr, 4, 1, bin); offset += 4;
	fprintf(sout, ".TEXT %d\n", segaddr);

	instraddr = segaddr;

	for (i = 0; i < (segsize - 9) / 4; i++) {
		fread(&instr, 4, 1, bin); offset += 4;
		fprintf(sout, "[0x%08x] 0x%08x %s\n", instraddr++, instr, decode(instr));
	}

	fclose(bin);
	fclose(sout);

	return 0;
}
