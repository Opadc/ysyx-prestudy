#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
uint8_t PC = 0;
uint8_t R[4];
uint8_t M[16] = {
  // 0b10001010, // li r0, 10
  0b10010000, // li r1, 0
  0b10100000, // li r2, 0
  0b10110001, // li r3, 1
  0b00010111, // add r1, r1, r3
  0b00101001, // add r2, r2, r1
  0b11001101, // bner0 r1, 3
  0b01001000, // out r2
  0b11011111, // bner0 r3, 7
};

/*
 7  6 5  4 3   2 1   0
+----+----+-----+-----+
| 00 | rd | rs1 | rs2 | R[rd]=R[rs1]+R[rs2]       add指令, 寄存器相加
+----+----+-----+-----+
| 10 | rd |    imm    | R[rd]=imm                 li指令, 装入立即数, 高位补0
+----+----+-----+-----+
| 11 |   addr   | rs2 | if (R[0]!=R[rs2]) PC=addr bner0指令, 若不等于R[0]则跳转
+----+----------+-----+
| 01 | 00 | rs1 |  00 | out rs                     out, R[rs] to console.
+----+----+-----+-----+

*/

char *inst_type_str[] = {
    [0b00] = "add",
    [0b01] = "out",
    [0b10] = "li",
    [0b11] = "bner0",
    "invalid"
};

void inst_cycle(){
    uint8_t inst = M[PC];
    uint8_t opcode = (inst & 0xC0) >> 6;
    uint8_t rd = (inst & 0x30) >> 4;
    uint8_t rs1 = (inst & 0x0C) >> 2;
    uint8_t rs2 = (inst & 0x03);
    uint8_t imm = (inst & 0x0f);
    uint8_t addr = (inst & 0x3C) >> 2;
    uint8_t next_pc = PC+1;
    // printf("[PC %d] type: %s, rs1: %d rs2: %d, rd: %d \n", PC, inst_type_str[opcode], rs1, rs2, rd);

    switch(opcode){
        case 0b00: 
            R[rd] = R[rs1] + R[rs2];
            break;
        case 0b01:
            printf("R[%d]=%d\n", rs1, R[rs1]);
            break;
        case 0b10:
            R[rd] = imm;
            break;
        case 0b11:
            if(R[0] != R[rs2]){
                next_pc = addr;
            }
            break;
    }
    PC = next_pc;
}
int main(int argc, char *argv[]){
    int n = 1;
    if(argc == 2){
        n = atoi(argv[1]);
    }
    R[0] = n;
    while(PC < sizeof(M)){
        inst_cycle();
    }
    return 0;
}