#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define GPR_NUMS 16
#define RAM_SIZE 0x1000000
uint32_t PC = 0;
uint32_t R[GPR_NUMS];
uint8_t M[RAM_SIZE] = {
    // 0x11200513
    0x13, 0x05, 0x20, 0x11,
    // 0x10a00023
    0x23, 0x00, 0xa0, 0x10,
    // 0x10004583
    0x83, 0x45, 0x00, 0x10,
};

#define INST_ebreak (0x00100073)

int meet_break = 0;
void inst_test();

void inst_cycle(){

    uint32_t inst =  *(uint32_t*)(M+PC);
    uint32_t rd = (inst >> 7) & 0x1f;
    uint32_t func3 = (inst >> 12) & 0x07;
    uint32_t func7 = (inst >> 25) & 0x7f;
    uint32_t rs1 = (inst >> 15) & 0x1f;
    uint32_t rs2 = (inst >> 20) & 0x1f;

    int32_t  imm_i = ((int32_t)inst >> 20);
    uint32_t imm_u = (inst >> 12) << 12;
    int32_t  imm_s = (((int32_t)inst >> 25) << 5) | ((inst >> 7) & 0x1f) ; 
    uint32_t opcode = (inst) & 0x7f;

    uint32_t next_pc = PC+4;

    printf("[PC:%x]", PC );
    switch(opcode){
        case 0b1100111:
            // jalr
            next_pc = (uint32_t)((int32_t)R[rs1] + imm_i);
            printf("jalr: rs1: %d, rd: %d, imm: %d, next_pc: %x\n", rs1, rd, imm_i, next_pc);
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
                case 0b100:
                    // lbu
                    printf("lbu: R[%d] = addr %x \n", rd, R[rs1] + imm_i);
                    R[rd] = M[R[rs1] + imm_i];
                    break;
                default:
                    printf("invalid load\n");
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
                case 0b000:
                    // sb
                    printf("sb: %x to R[%d] \n", R[rs1] + imm_s, rs2);
                    M[R[rs1] + imm_s] = (uint8_t)R[rs2];
                    break;
                default:
                    printf("invalid store\n");
            }
            break;
        case 0b1110011:
            // ebreak
            meet_break = 1;
            printf("meet ebreak\n");
            break;
        default:
            // invalid opcode.
            printf("invalid opcode\n");
            assert(0);
            break;
        
    }

    R[0] = 0; // force zero to zero.
    PC = next_pc;
    
}

void fill_ebreak(){
    uint32_t *inst_stream = (uint32_t*)M;
    for(uint32_t i=0; i<RAM_SIZE/sizeof(uint32_t); i++){
        inst_stream[i] = INST_ebreak;
    }
}
void read_program(char *path){
    struct stat st;
    uint64_t len = 0;
    int fd = open(path, O_RDONLY);
    if(fd == -1){
        perror("inst stream read fail");
        exit(1);
    }
    fstat(fd, &st);
    len = st.st_size;
    if(len <= RAM_SIZE){
        fill_ebreak();
        read(fd, M, len);
        *(uint32_t*)(M+0x228) = INST_ebreak;
    }else{
        printf("inst stream too big\n");
        exit(1);
    }

}
int main(int argc, char *argv[]){
    uint32_t cycle = 0;
    if(argc == 2){
        read_program(argv[1]);
    }else{
        inst_test();
    }
    while(1){
        cycle++;
        printf("cycle %d \n", cycle);
        inst_cycle();
        if(meet_break){
            if(R[10] == 0){
                printf("HIT GOOD TRAP\n");
                return 0;
            }else{
                printf("HIT BAD TRAP a0 == %x\n", R[10]);
                return 1;
            }
        }
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

    // test lbu, sb
        addi a0, zero, 0x0112
        sb a0, 0x100(zero)
        lbu a1, 0x100(zero)

*/

void test_lbu(){
    uint32_t target_addr = 0x100;
    uint32_t test_inst[] = {
        // lw a0, 0x100(zero)
        0x10002503,
        // lbu a1, 0x100(zero)
        0x10004583,
        // lbu a2, 0x101(zero)
        0x10104603,
        // lbu a3, 0x102(zero)
        0x10204683,
        // lbu a4, 0x103(zero)
        0x10304703
    };
    *(uint32_t *)(M+target_addr) = 0x12345678;
    memcpy(M, test_inst, sizeof(test_inst));
}
void test_sb(){
    uint32_t target_addr = 0x100;
    *(uint32_t *)(M+target_addr) = 0x12345678;
    uint32_t test_inst[] = {
        // lw a0, 0x100(zero)
        0x10002503,
        // addi a1, zero, 0x123456ab
        0x6ab00593,
        // sb a1, 0x103(zero)
        0x10b001a3,
        // addi a1, zero, 0x123456cd
        0x6cd00593,
        // sb a1, 0x102(zero)
        0x10b00123,
        // addi a1, zero, 0x123456ef
        0x6ef00593,
        // sb a1, 0x101(zero)
        0x10b000a3,
        // addi a1, zero, 0x12345690
        0x69000593,
        // sb a1, 0x100(zero)
        0x10b00023
    };
    memcpy(M, test_inst, sizeof(test_inst));

}
void inst_test(){
    // test_lbu();
    test_sb();
}