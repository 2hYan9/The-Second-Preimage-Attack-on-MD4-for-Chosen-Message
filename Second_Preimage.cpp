#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

unsigned int chain_value[52] = {0};
unsigned int message[16] = {0};

unsigned int rot_L(unsigned int x,int y){
    unsigned int a = x << y;
    unsigned int b = x >> (32 - y);
    return a | b;
}

unsigned int rot_R(unsigned int x,int y){
    unsigned int a = x >> y;
    unsigned int b = x << (32 - y);
    return a | b;
}

unsigned int f_bool(unsigned int a,unsigned int b,unsigned int c){
    return (a & b) | ((~a) & c);
}

unsigned int g_bool(unsigned int a,unsigned int b,unsigned int c){
    return (a & b) | (a & c) | (b & c);
}

unsigned int h_bool(unsigned int a,unsigned int b,unsigned int c){
    return a ^ b ^ c;
}

unsigned int produce_1(int e, unsigned int m, int f){
    unsigned int a = chain_value[e-4];
    unsigned int b = chain_value[e-1];
    unsigned int c = chain_value[e-2];
    unsigned int d = chain_value[e-3];
    return rot_L((a + f_bool(b, c, d) + m), f);
}

unsigned int produce_2(int e, unsigned int m, int f){
     unsigned int a = chain_value[e-4];
    unsigned int b = chain_value[e-1];
    unsigned int c = chain_value[e-2];
    unsigned int d = chain_value[e-3];
    return rot_L((a + g_bool(b, c, d) + m + 0x5a827999), f);
}

unsigned int produce_3(int e, unsigned int m, int f){
    unsigned int a = chain_value[e-4];
    unsigned int b = chain_value[e-1];
    unsigned int c = chain_value[e-2];
    unsigned int d = chain_value[e-3];
    return rot_L((a + h_bool(b, c, d) + m + 0x6ed9eba1), f);
}

unsigned int message_production(int e, int f){
    unsigned int a = chain_value[e - 4];
    unsigned int b = chain_value[e - 1];
    unsigned int c = chain_value[e - 2];
    unsigned int d = chain_value[e - 3];
    return rot_R(chain_value[e], f) - (a + f_bool(b, c, d));
}

unsigned int getTheBit(int a){
    return 1 << (a - 1);
}

void generateMessage(){
    {
    unsigned int a1 = rand();
    unsigned int b0_7 = chain_value[3] & getTheBit(7);
    unsigned int a1_7 = a1 & getTheBit(7);
    a1 = a1 ^ (b0_7 ^ a1_7);
    chain_value[4] = a1;
    message[0] = message_production(4, 3);
    }

    {
    unsigned int d1 = (unsigned int)rand();
    d1 = d1 & (~getTheBit(7));
    unsigned int d1_8 = d1 & getTheBit(8);
    unsigned int a1_8 = chain_value[4] & getTheBit(8);
    unsigned int d1_11 = d1 & getTheBit(11);
    unsigned int a1_11 = chain_value[4] & getTheBit(11);
    d1 = d1 ^ (d1_8 ^ a1_8) ^ (d1_11 ^ a1_11);
    chain_value[5] = d1;
    message[1] = message_production(5, 7);
    }

    {
    unsigned int c1 = (unsigned int)rand();
    c1 = c1 | getTheBit(7);
    c1 = c1 | getTheBit(8);
    c1 = c1 & (~getTheBit(11));
    unsigned int c1_26 = c1 & getTheBit(26);
    unsigned int d1_26 = chain_value[5] & getTheBit(26);
    c1 = c1 ^ (c1_26 ^ d1_26);
    chain_value[6] = c1;
    message[2] = message_production(6, 11);
    }

    {
    unsigned int b1 = (unsigned int)rand();
    b1 = b1 | getTheBit(7);
    b1 = b1 & (~getTheBit(8));
    b1 = b1 & (~getTheBit(11));
    b1 = b1 & (~getTheBit(26));
    chain_value[7] = b1;
    message[3] = message_production(7, 19);
    }

    {
    unsigned int a2 = (unsigned int)rand();
    a2 = a2 | getTheBit(8);
    a2 = a2 | getTheBit(11);
    a2 = a2 & (~getTheBit(26));
    unsigned int a2_14 = a2 & getTheBit(14);
    unsigned int b1_14 = chain_value[7] & getTheBit(14);
    a2 = a2 ^ (a2_14 ^ b1_14);
    chain_value[8] = a2;
    message[4] = message_production(8, 3);
    }

    {
    unsigned int d2 = (unsigned int)rand();
    d2 = d2 | getTheBit(26);
    d2 = d2 & (~getTheBit(14));
    unsigned int d2_19 = d2 & getTheBit(19);
    unsigned int d2_20 = d2 & getTheBit(20);
    unsigned int d2_21 = d2 & getTheBit(21);
    unsigned int d2_22 = d2 & getTheBit(22);
    unsigned int a2_19 = chain_value[8] & getTheBit(19);
    unsigned int a2_20 = chain_value[8] & getTheBit(20);
    unsigned int a2_21 = chain_value[8] & getTheBit(21);
    unsigned int a2_22 = chain_value[8] & getTheBit(22);
    d2 = d2 ^ (d2_19 ^ a2_19) ^ (d2_20 ^ a2_20) ^ (d2_21 ^ a2_21) ^ (d2_22 ^ a2_22);
    chain_value[9] = d2;
    message[5] = message_production(9, 7);
    }

    {
    unsigned int c2 = (unsigned int)rand();
    c2 = c2 | getTheBit(21);
    c2 = c2 & (~getTheBit(14));
    c2 = c2 & (~getTheBit(19));
    c2 = c2 & (~getTheBit(20));
    c2 = c2 & (~getTheBit(22));
    unsigned int c2_13 = c2 & getTheBit(13);
    unsigned int c2_15 = c2 & getTheBit(15);
    unsigned int d2_13 = chain_value[9] & getTheBit(13);
    unsigned int d2_15 = chain_value[9] & getTheBit(15);
    c2 = c2 ^ (c2_13 ^ d2_13) ^ (c2_15 ^ d2_15);
    chain_value[10] = c2;
    message[6] = message_production(10, 11);
    }

    {
    unsigned int b2 = (unsigned int)rand();
    b2 = b2 | getTheBit(13);
    b2 = b2 | getTheBit(14);
    b2 = b2 & (~getTheBit(15));
    b2 = b2 & (~getTheBit(19));
    b2 = b2 & (~getTheBit(20));
    b2 = b2 & (~getTheBit(21));
    b2 = b2 & (~getTheBit(22));
    unsigned int b2_17 = b2 & getTheBit(17);
    unsigned int c2_17 = chain_value[10] & getTheBit(17);
    b2 = b2 ^ (b2_17 ^ c2_17);
    chain_value[11] = b2;
    message[7] = message_production(11, 19);
    }

    {
    unsigned int a3 = (unsigned int)rand();
    a3 = a3 | getTheBit(13);
    a3 = a3 | getTheBit(14);
    a3 = a3 | getTheBit(15);
    a3 = a3 | getTheBit(22);
    a3 = a3 & (~getTheBit(17));
    a3 = a3 & (~getTheBit(19));
    a3 = a3 & (~getTheBit(20));
    a3 = a3 & (~getTheBit(21));
    unsigned int a3_23 = a3 & getTheBit(23);
    unsigned int a3_26 = a3 & getTheBit(26);
    unsigned int b2_23 = chain_value[11] & getTheBit(23);
    unsigned int b2_26 = chain_value[11] & getTheBit(26);
    a3 = a3 ^ (a3_23 ^ b2_23) ^ (a3_26 ^ b2_26);
    chain_value[12] = a3;
    message[8] = message_production(12, 3);
    }

    {
    unsigned int d3 = (unsigned int)rand();
    d3 = d3 | getTheBit(13);
    d3 = d3 | getTheBit(14);
    d3 = d3 | getTheBit(15);
    d3 = d3 | getTheBit(21);
    d3 = d3 | getTheBit(22);
    d3 = d3 | getTheBit(26);
    d3 = d3 & (~getTheBit(17));
    d3 = d3 & (~getTheBit(20));
    d3 = d3 & (~getTheBit(23));
    unsigned int d3_30 = d3 & getTheBit(30);
    unsigned int a3_30 = chain_value[12] & getTheBit(30);
    d3 = d3 ^ (d3_30 ^ a3_30);
    chain_value[13] = d3;
    message[9] = message_production(13, 7);
    }

    {
    unsigned int c3 = (unsigned int)rand();
    c3 = c3 | getTheBit(17);
    c3 = c3 | getTheBit(30);
    c3 = c3 & (~getTheBit(20));
    c3 = c3 & (~getTheBit(21));
    c3 = c3 & (~getTheBit(22));
    c3 = c3 & (~getTheBit(23));
    c3 = c3 & (~getTheBit(26));
    unsigned int c3_32 = c3 & getTheBit(32);
    unsigned int d3_32 = chain_value[13] & getTheBit(32);
    c3 = c3 ^ (c3_32 ^ d3_32);
    chain_value[14] = c3;
    message[10] = message_production(14, 11);
    }

    {
    unsigned int b3 = (unsigned int)rand();
    b3=b3|getTheBit(21);
    b3=b3|getTheBit(22);
    b3=b3|getTheBit(26);
    b3=b3&(~getTheBit(20));
    b3=b3&(~getTheBit(30));
    b3=b3&(~getTheBit(32));
    unsigned int b3_23 = b3 & getTheBit(23);
    unsigned int c3_23 = chain_value[14] & getTheBit(23);
    b3 = b3 ^ (b3_23 ^ c3_23);
    chain_value[15] = b3;
    message[11] = message_production(15, 19);
    }

    {
    unsigned int a4 = (unsigned int)rand();
    a4 = a4 | getTheBit(30);
    a4 = a4 & (~getTheBit(23));
    a4 = a4 & (~getTheBit(26));
    a4 = a4 & (~getTheBit(32));
    unsigned int a4_27 = a4 & getTheBit(27);
    unsigned int a4_29 = a4 & getTheBit(29);
    unsigned int b3_27 = chain_value[15] & getTheBit(27);
    unsigned int b3_29 = chain_value[15] & getTheBit(29);
    a4 = a4 ^ (a4_27 ^ b3_27) ^ (a4_29 ^ b3_29);
    chain_value[16]=a4;
    message[12]=message_production(16, 3);
    }

    {
    unsigned int d4 = (unsigned int)rand();
    d4 = d4 | getTheBit(27);
    d4 = d4 | getTheBit(29);
    d4 = d4 | getTheBit(32);
    d4 = d4 & (~getTheBit(23));
    d4 = d4 & (~getTheBit(26));
    d4 = d4 & (~getTheBit(30));
    chain_value[17]=d4;
    message[13]=message_production(17, 7);
    }

    {
    unsigned int c4 = (unsigned int)rand();
    c4 = c4 | getTheBit(23);
    c4 = c4 | getTheBit(26);
    c4 = c4 & (~getTheBit(27));
    c4 = c4 & (~getTheBit(29));
    c4 = c4 & (~getTheBit(30));
    unsigned int c4_19 = c4 & getTheBit(19);
    unsigned int d4_19 = chain_value[17] & getTheBit(19);
    c4 = c4 ^ (c4_19 ^ d4_19);
    chain_value[18] = c4;
    message[14] = message_production(18, 11);
    }

    {
    unsigned int b4=(unsigned int)rand();
    b4 = b4 | getTheBit(26);
    b4 = b4 | getTheBit(27);
    b4 = b4 | getTheBit(29);
    b4 = b4 & (~getTheBit(19));
    b4 = b4 & (~getTheBit(30));
    chain_value[19] = b4;
    message[15] = message_production(19, 19);
    }
}

void correct_for_a5(int a){
    //printf("correction for a5 %d\n",a);
    a = a - 3;
    message[0] = message[0] ^ getTheBit(a);
    chain_value[4] = produce_1(4, message[0], 3);
    message[1] = message_production(5, 7);
    message[2] = message_production(6, 11);
    message[3] = message_production(7, 19);
    message[4] = message_production(8, 3);
    chain_value[20] = produce_2(20, message[0], 3);
}

void correct_for_d5(int a){
    //printf("correction for d5 %d\n",a);
    a = a - 5;
    message[4] = message[4] ^ getTheBit(a);
    chain_value[8] = produce_1(8, message[4], 3);
    message[5] = message_production(9, 7);
    message[6] = message_production(10, 11);
    message[7] = message_production(11, 19);
    message[8] = message_production(12, 3);
    chain_value[21] = produce_2(21, message[4], 5);
}

void correct_for_c5(int a){
    //printf("correction for c5 %d\n",a);
    a = a - 9;
    message[8] = message[8] ^ getTheBit(a);
    chain_value[12] = produce_1(12, message[8], 3);
    message[9] = message_production(13, 7);
    message[10] = message_production(14, 11);
    message[11] = message_production(15, 19);
    message[12] = message_production(16, 3);
    chain_value[22] = produce_2(22,message[8],9);
}

void correct_for_b5(int a){
    //printf("correction for b5 %d\n",a);
    a = a - 13;
    message[12] = message[12] ^ getTheBit(a);
    chain_value[16] = produce_1(16, message[12], 3);
    message[13] = message_production(17, 7);
    message[14] = message_production(18, 11);
    message[15] = message_production(19, 19);
    chain_value[23] = produce_2(23, message[12], 13);
}

void correct_for_a6(int a){
    //printf("correction for a6 %d\n",a);
    a = a - 3;
    message[1] = message[1] ^ getTheBit(a);
    chain_value[5] = produce_1(5, message[1], 7);
    message[2] = message_production(6, 11);
    message[3] = message_production(7, 19);
    message[4] = message_production(8, 3);
    message[5] = message_production(9, 7);
    chain_value[24] = produce_2(24, message[1], 3);
}

void correct_for_d6(int a){
    //printf("correction for d6 %d\n",a);
    a = a - 5;
    message[5] = message[5] ^ getTheBit(a);
    chain_value[9] = produce_1(9, message[5], 7);
    message[6] = message_production(10, 11);
    message[7] = message_production(11, 19);
    message[8] = message_production(12, 3);
    message[9] = message_production(13, 7);
    chain_value[25] = produce_2(25, message[5], 5);
}

void correct_for_c6(int a){
    //printf("correction for c6 %d\n",a);
    a = a - 9;
    message[9] = message[9] ^ getTheBit(a);
    chain_value[13] = produce_1(13, message[9], 7);
    message[10] = message_production(14, 11);
    message[11] = message_production(15, 19);
    message[12] = message_production(16, 3);
    message[13] = message_production(17, 7);
    chain_value[26] = produce_2(26, message[9], 9);
}

void mutipleMessageModify(){
    unsigned int a5 = produce_2(20, message[0], 3);
    unsigned int a5_19 = a5 & getTheBit(19);
    unsigned int c4_19 = chain_value[18] & getTheBit(19);
    if(a5_19 != c4_19)
        correct_for_a5(19);
    unsigned int a5_26 = a5 & getTheBit(26);
    if(a5_26 == 0)
        correct_for_a5(26);
    unsigned int a5_27 = a5 & getTheBit(27);
    if(a5_27 != 0)
        correct_for_a5(27);
    unsigned int a5_29 = a5 & getTheBit(29);
    if(a5_29 == 0)
        correct_for_a5(29);
    unsigned int a5_32 = a5 & getTheBit(32);
    if(a5_32 == 0)
        correct_for_a5(32);
    //chain_value[20] = produce_2(20, message[0], 3);

    unsigned int d5 = produce_2(21, message[4], 5);
    unsigned int d5_19 = d5 & getTheBit(19);
    a5_19 = chain_value[20] & getTheBit(19);
    if(d5_19 != a5_19)
        correct_for_d5(19);
    unsigned int d5_26 = d5 & getTheBit(26);
    if(d5_26 == 0)
        correct_for_d5(26);
    unsigned int d5_27 = d5 & getTheBit(27);
    if(d5_27 == 0)
        correct_for_d5(27);
    unsigned int d5_29 = d5 & getTheBit(29);
    if(d5_29 == 0)
        correct_for_d5(29);
    unsigned int d5_32 = d5 & getTheBit(32);
    unsigned int b4_32 = chain_value[19] & getTheBit(32);
    if(d5_32 != b4_32)
        correct_for_d5(32);
    //chain_value[21] = produce_2(21, message[4], 5);

    unsigned int c5 = produce_2(22, message[8], 9);
    unsigned int c5_26 = c5 & getTheBit(26);
    d5_26 = chain_value[21] & getTheBit(26);
    if(c5_26 != d5_26)
        correct_for_c5(26);
    unsigned int c5_27 = c5 & getTheBit(27);
    d5_27 = chain_value[21] & getTheBit(27);
    if(c5_27 != d5_27)
        correct_for_c5(27);
    unsigned int c5_29 = c5 & getTheBit(29);
    d5_29 = chain_value[21] & getTheBit(29);
    if(c5_29 != d5_29)
        correct_for_c5(29);
    unsigned int c5_30 = c5 & getTheBit(30);
    unsigned int d5_30 = chain_value[21] & getTheBit(30);
    if(c5_30 != d5_30)
        correct_for_c5(30);
    unsigned int c5_32 = c5 & getTheBit(32);
    d5_32 = chain_value[21] & getTheBit(32);
    if(c5_32 != d5_32)
        correct_for_c5(32);
    //chain_value[22] = produce_2(22,message[8],9);

    unsigned int b5 = produce_2(23, message[12], 13);
    unsigned int b5_29 = b5 & getTheBit(29);
    c5_29 = chain_value[22] & getTheBit(29);
    if(b5_29 != c5_29)
        correct_for_b5(29);
    unsigned int b5_30 = b5 & getTheBit(30);
    if(b5_30 == 0)
        correct_for_b5(30);
    unsigned int b5_32 = b5 & getTheBit(32);
    if(b5_32 != 0)
        correct_for_b5(32);
    //chain_value[23] = produce_2(23, message[12], 13);

    unsigned int a6 = produce_2(24, message[1], 3);
    unsigned int a6_29 = a6 & getTheBit(29);
    if(a6_29 == 0)
        correct_for_a6(29);
    unsigned int a6_32 = a6 & getTheBit(32);
    if(a6_32 == 0)
        correct_for_a6(32);
    //chain_value[24] = produce_2(24, message[1], 3);

    unsigned int d6 = produce_2(25, message[5], 5);
    unsigned int d6_29 = d6 & getTheBit(29);
    b5_29 = chain_value[24] & getTheBit(29);
    if(d6_29 != b5_29)
        correct_for_d6(29);
    //chain_value[25] = produce_2(25, message[5], 5);

    unsigned int c6 = produce_2(26, message[9], 9);
    unsigned int c6_29 = c6 & getTheBit(29);
    d6_29 = chain_value[25] & getTheBit(29);
    if(c6_29 != d6_29)
        correct_for_c6(29);
    unsigned int c6_30 = c6 & getTheBit(30);
    unsigned int d6_30 = chain_value[25] & getTheBit(30);
    if(c6_30 == d6_30)
        correct_for_c6(30);
    unsigned int c6_32 = c6 & getTheBit(32);
    unsigned int d6_32 = chain_value[25] & getTheBit(32);
    if(c6_32 == d6_32)
        correct_for_c6(32);
    //chain_value[26] = produce_2(26, message[9], 9);
}

vector<unsigned int> computeMD4(){
    /*Round 1*/
    chain_value[4] = produce_1(4, message[0], 3);
    //cout << ((chain_value[4] & getTheBit(7)) == (chain_value[3] & getTheBit(7))) << endl;
    chain_value[5] = produce_1(5, message[1], 7);
    //cout << ((chain_value[5] & getTheBit(7)) == 0) << endl;
    //cout << ((chain_value[5] & getTheBit(8)) == (chain_value[4] & getTheBit(8))) << endl;
    //cout << ((chain_value[5] & getTheBit(11)) == (chain_value[4] & getTheBit(11))) << endl;
    chain_value[6] = produce_1(6, message[2], 11);
    //cout << ((chain_value[6] & getTheBit(7)) != 0) << endl;
    //cout << ((chain_value[6] & getTheBit(8)) != 0) << endl;
    //cout << ((chain_value[6] & getTheBit(11)) == 0) << endl;
    //cout << ((chain_value[6] & getTheBit(26)) == (chain_value[5] & getTheBit(26))) << endl;
    chain_value[7] = produce_1(7, message[3], 19);
    //cout << ((chain_value[7] & getTheBit(7)) != 0) << endl;
    //cout << ((chain_value[7] & getTheBit(8)) == 0) << endl;
    //cout << ((chain_value[7] & getTheBit(11)) == 0) << endl;
    //cout << ((chain_value[7] & getTheBit(26)) == 0) << endl;
    chain_value[8] = produce_1(8, message[4], 3);
    //cout << ((chain_value[8] & getTheBit(8)) != 0) << endl;
    //cout << ((chain_value[8] & getTheBit(11)) != 0) << endl;
    //cout << ((chain_value[8] & getTheBit(26)) == 0) << endl;
    //cout << ((chain_value[8] & getTheBit(14)) == (chain_value[7] & getTheBit(14))) << endl;
    chain_value[9] = produce_1(9, message[5], 7);
    chain_value[10] = produce_1(10, message[6], 11);
    chain_value[11] = produce_1(11, message[7], 19);
    chain_value[12] = produce_1(12, message[8], 3);
    chain_value[13] = produce_1(13, message[9], 7);
    chain_value[14] = produce_1(14, message[10], 11);
    chain_value[15] = produce_1(15, message[11], 19);
    chain_value[16] = produce_1(16, message[12], 3);
    chain_value[17] = produce_1(17, message[13], 7);
    chain_value[18] = produce_1(18, message[14], 11);
    chain_value[19] = produce_1(19, message[15], 19);
    /*Round 2*/
    chain_value[20] = produce_2(20, message[0], 3);
    //cout << ((chain_value[20] & getTheBit(19)) == (chain_value[18] & getTheBit(19))) << endl;
    //cout << ((chain_value[20] & getTheBit(26)) != 0) << endl;
    //cout << ((chain_value[20] & getTheBit(27)) == 0) << endl;
    //cout << ((chain_value[20] & getTheBit(29)) != 0) << endl;
    //cout << ((chain_value[20] & getTheBit(32)) != 0) << endl;
    chain_value[21] = produce_2(21, message[4], 5);
    chain_value[22] = produce_2(22, message[8], 9);
    chain_value[23] = produce_2(23, message[12], 13);
    chain_value[24] = produce_2(24, message[1], 3);
    chain_value[25] = produce_2(25, message[5], 5);
    chain_value[26] = produce_2(26, message[9], 9);
    chain_value[27] = produce_2(27, message[13], 13);
    chain_value[28] = produce_2(28, message[2], 3);
    chain_value[29] = produce_2(29, message[6], 5);
    chain_value[30] = produce_2(30, message[10], 9);
    chain_value[31] = produce_2(31, message[14], 13);
    chain_value[32] = produce_2(32, message[3], 3);
    chain_value[33] = produce_2(33, message[7], 5);
    chain_value[34] = produce_2(34, message[11], 9);
    chain_value[35] = produce_2(35, message[15], 13);
    /*Round 3*/
    chain_value[36] = produce_3(36, message[0], 3);
    chain_value[37] = produce_3(37, message[8], 9);
    chain_value[38] = produce_3(38, message[4], 11);
    chain_value[39] = produce_3(39, message[12], 15);
    chain_value[40] = produce_3(40, message[2], 3);
    chain_value[41] = produce_3(41, message[10], 9);
    chain_value[42] = produce_3(42, message[6], 11);
    chain_value[43] = produce_3(43, message[14], 15);
    chain_value[44] = produce_3(44, message[1], 3);
    chain_value[45] = produce_3(45, message[9], 9);
    chain_value[46] = produce_3(46, message[5], 11);
    chain_value[47] = produce_3(47, message[13], 15);
    chain_value[48] = produce_3(48, message[3], 3);
    chain_value[49] = produce_3(49, message[11], 9);
    chain_value[50] = produce_3(50, message[7], 11);
    chain_value[51] = produce_3(51, message[15], 15);
    unsigned int a = chain_value[48] + chain_value[0];
    unsigned int d = chain_value[49] + chain_value[1];
    unsigned int c = chain_value[50] + chain_value[2];
    unsigned int b = chain_value[51] + chain_value[3];
    vector<unsigned int> result;
    result.push_back(a);
    result.push_back(b);
    result.push_back(c);
    result.push_back(d);
    return result;
}

int main()
{
    chain_value[0] = 0x67452301;
    chain_value[3] = 0xefcdab89;
    chain_value[2] = 0x98badcfe;
    chain_value[1] = 0x10325476;

    srand((unsigned)time(NULL));
    int i = 0;
    while(i++ < 3){
        generateMessage();
        mutipleMessageModify();
        {
            /*
            message[0] = 0x4d7a9c83;
            message[1] = 0x56cb927a;
            message[2] = 0xb9d5a578;
            message[3] = 0x57a7a5ee;
            message[4] = 0xde748a3c;
            message[5] = 0xdcc366b3;
            message[6] = 0xb683a020;
            message[7] = 0x3b2a5d9f;
            message[8] = 0xc69d71b3;
            message[9] = 0xf9e99198;
            message[10] = 0xd79f805e;
            message[11] = 0xa63bb2e8;
            message[12] = 0x45dd8e31;
            message[13] = 0x97e31fe5;
            message[14] = 0x2794bf08;
            message[15] = 0xb9e8c3e9;
            */
        }

        vector<unsigned int> m1;
        for(int j = 0; j < 16; j++) m1.push_back(message[j]);
        vector<unsigned int> H1 = computeMD4();
        //cout << "Generate the differential message...\n";
        //cout << endl;

        message[1] = message[1] + getTheBit(32);
        message[2] = message[2] + getTheBit(32) - getTheBit(29);
        message[12] = message[12] - getTheBit(17);
        vector<unsigned int> m2;
        for(int j = 0; j < 16; j++) m2.push_back(message[j]);
        vector<unsigned int> H2 = computeMD4();
        if(H1 == H2){
            cout << "Find a pair of collided message:\n";
            for(int j = 0; j < 16; j++) printf("%08x ", m1[j]);
            cout << "\nAnd:\n";
            for(int j = 0; j < 16; j++) printf("%08x ", m2[j]);
            cout << "\nWith the same hash value:\n";
            printf("%08x %08x %08x %08x\n", H1[0], H1[1], H1[2], H1[3]);
            break;
        }

    }
    return 0;
}
