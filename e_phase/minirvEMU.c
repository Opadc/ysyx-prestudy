#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define GPR_NUMS 16
#define RAM_SIZE 0x100000
uint32_t PC = 0;
uint32_t R[GPR_NUMS];
uint8_t M[RAM_SIZE] = {
    // 0x01fff537
    0x37, 0xf5, 0xff, 0x01,
    // 0x20000593
    0x93, 0x05, 0x00, 0x20,
    // 0xF0A5A023
    0x23, 0xA0, 0xa5, 0xF0,
    // 0x10002603
    0x03, 0x26, 0x00, 0x10,
};



void inst_cycle(){
    uint32_t inst =  *(uint32_t*)(M+PC);
    uint32_t rd = (inst >> 7) & 0x1f;
    uint32_t func3 = (inst >> 12) & 0x07;
    uint32_t func7 = (inst >> 25) & 0x7f;
    uint32_t rs1 = (inst >> 15) & 0x1f;
    uint32_t rs2 = (inst >> 20) & 0x1f;

    int32_t  imm_i = ((int32_t)inst >> 20);
    uint32_t imm_u = (inst >> 12) << 12;
    int32_t  imm_s = (((int32_t)inst >> 25) << 5) | ((inst >> 6) & 0x1f) ; 
    uint32_t opcode = (inst) & 0x7f;

    uint32_t next_pc = PC+4;
    printf("[PC:%d]", PC);
    switch(opcode){
        case 0b1100111:
            // jalr
            printf("jalr: rs1: %d, rd: %d, imm: %d\n", rs1, rd, imm_i);
            next_pc = (uint32_t)((int32_t)R[rs1] + imm_i);
            R[rd] = PC+4;
            break;
        case 0b0010011:
            // addi
            printf("addi: rs1: %d, rd: %d, imm: %d\n", rs1, rd, imm_i);
            R[rd] = (uint32_t)((int32_t)R[rs1] + imm_i);
            break;
        case 0b0110011:
            switch(func7){
                case 0b0000000:
                // add
                    printf("add: rs1: %d, rs2: %d, rd: %d\n", rs1, rs2, rd);
                    R[rd] = R[rs1] + R[rs2];
                    break;
                default:
                    printf("invalid op\n");
                    break;
            }
            break;

        case 0b0110111:
            // lui
            printf("lui: rd: %x, imm: %x \n", rd, imm_u);
            R[rd] = imm_u;
            break;
        case 0b0000011:
            switch(func3){
                case 0b010:
                    // lw
                    printf("lw: R[%d] = addr %x \n", rd, R[rs1] + imm_i);
                    R[rd] = *(uint32_t *)(M + R[rs1] + imm_i);
                    break;
                default:
                    break;
            }
            break;
        case 0b0100011:
            switch(func3){
                case 0b010:
                    // sw
                    printf("sw: %x to R[%d] \n", R[rs1] + imm_s, rs2);
                    *(uint32_t *)(M + R[rs1] + imm_s) = R[rs2];
                    break;
                    
            }
            break;
        default:
            // invalid opcode.
            break;
        
    }

    R[0] = 0; // force zero to zero.
    PC = next_pc;
    
}
int main(int argc, char *argv[]){
    while(1){
        inst_cycle();
    }
    return 0;
}


/*
    test ld, sw

    case0: 
        lui a0, 0x1fff
        sw a0, 0x100(zero)
        lw a1, 0x100(zero)
        a1 == a0 == 0x1fff000
    case1:
        lui a0, 0x1fff
        addi a1, 0x200
        sw  a0, 0x100(zero) 
        lw  a2, -0x100(a1)
        a0 == a2 == 0x1fff000
    case3:
        lui a0, 0x1fff
        addi a1, 0x200
        sw  a0, -0x100(a1)
        lw  a2, 0x100(zero)
        a0 == a2 == 0x1fff000

*/