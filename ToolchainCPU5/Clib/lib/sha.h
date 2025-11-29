#ifndef SHA_H
#define SHA_H
short sha1_h0_h;
short sha1_h0_l;
short sha1_h1_h;
short sha1_h1_l;
short sha1_h2_h;
short sha1_h2_l;
short sha1_h3_h;
short sha1_h3_l;
short sha1_h4_h;
short sha1_h4_l;
short sha1_buffer[64];
short sha1_buflen;
short sha1_bitlen_0;
short sha1_bitlen_1;
short sha1_bitlen_2;
short sha1_bitlen_3;
short w_h[80];
short w_l[80];
void add32(short ah1, short al1, short bh1, short bl1) {
    short temp_l1;
    short carry;
    temp_l1 = al1 + bl1;
    carry = 0;
    if(temp_l1 < al1) {
        carry = 1;
    }
    sha1_h0_l = temp_l1;
    sha1_h0_h = ah1 + bh1 + carry;
    return;
}
void rotl32(short h1, short l1, short n1) {
    short rh = 0;
    short rl = 0;
    if(n1 == 1) {
        rh = (h1 << 1) | (l1 >> 15);
        rl = l1 << 1;
    }
    if(n1 == 5) {
        rh = (h1 << 5) | (l1 >> 11);
        rl = (l1 << 5) | (h1 >> 11);
    }
    if(n1 == 30) {
        rh = (h1 >> 14) | (l1 << 2);
        rl = (l1 >> 14) | (h1 << 2);
    }
    sha1_h0_h = rh;
    sha1_h0_l = rl;
    return;
}
void sha1_f1(short bh2, short bl2, short ch2, short cl2, short dh2, short dl2) {
    short bc_h1;
    short bc_l1;
    short nb_h1;
    short nb_l1;
    short nbd_h1;
    short nbd_l1;
    bc_h1 = bh2 & ch2;
    bc_l1 = bl2 & cl2;
    nb_h1 = ~bh2;
    nb_l1 = ~bl2;
    nbd_h1 = nb_h1 & dh2;
    nbd_l1 = nb_l1 & dl2;
    sha1_h0_h = bc_h1 | nbd_h1;
    sha1_h0_l = bc_l1 | nbd_l1;
    return;
}
void sha1_f2(short bh3, short bl3, short ch3, short cl3, short dh3, short dl3) {
    sha1_h0_h = bh3 ^ ch3 ^ dh3;
    sha1_h0_l = bl3 ^ cl3 ^ dl3;
}
void sha1_f3(short bh4, short bl4, short ch4, short cl4, short dh4, short dl4) {
    short bc_h;
    short bc_l;
    short bd_h;
    short bd_l;
    short cd_h;
    short cd_l;
    bc_h = bh4 & ch4;
    bc_l = bl4 & cl4;
    bd_h = bh4 & dh4;
    bd_l = bl4 & dl4;
    cd_h = ch4 & dh4;
    cd_l = cl4 & dl4;
    sha1_h0_h = bc_h | bd_h | cd_h;
    sha1_h0_l = bc_l | bd_l | cd_l;
    return;
}
void sha1_transform(short* data) {
    short a_h;
    short a_l;
    short b_h;
    short b_l;
    short c_h;
    short c_l;
    short d_h;
    short d_l;
    short e_h;
    short e_l;
    short f_h;
    short f_l;
    short k_h;
    short k_l;
    short temp_h;
    short temp_l;
    short i1;
    short t_h;
    short t_l;
    i1 = 0;
    while(i1 < 16) {
        w_h[i1] = data[i1 + i1];
        w_l[i1] = data[i1 + i1 + 1];
        i1++;
    }
    i1 = 16;
    while(i1 < 80) {
        t_h = w_h[i1 - 3] ^ w_h[i1 - 8] ^ w_h[i1 - 14] ^ w_h[i1 - 16];
        t_l = w_l[i1 - 3] ^ w_l[i1 - 8] ^ w_l[i1 - 14] ^ w_l[i1 - 16];
        rotl32(t_h, t_l, 1);
        w_h[i1] = sha1_h0_h;
        w_l[i1] = sha1_h0_l;
        i1++;
    }
    a_h = sha1_h0_h;
    a_l = sha1_h0_l;
    b_h = sha1_h1_h;
    b_l = sha1_h1_l;
    c_h = sha1_h2_h;
    c_l = sha1_h2_l;
    d_h = sha1_h3_h;
    d_l = sha1_h3_l;
    e_h = sha1_h4_h;
    e_l = sha1_h4_l;
    i1 = 0;
    while(i1 < 80) {
        if(i1 < 20) {
            sha1_f1(b_h, b_l, c_h, c_l, d_h, d_l);
            f_h = sha1_h0_h;
            f_l = sha1_h0_l;
            k_h = 0x5A82;
            k_l = 0x7999;
        }
        if(i1 >= 20) {
            if(i1 < 40) {
                sha1_f2(b_h, b_l, c_h, c_l, d_h, d_l);
                f_h = sha1_h0_h;
                f_l = sha1_h0_l;
                k_h = 0x6ED9;
                k_l = 0xEBA1;
            }
        }
        if(i1 >= 40) {
            if(i1 < 60) {
                sha1_f3(b_h, b_l, c_h, c_l, d_h, d_l);
                f_h = sha1_h0_h;
                f_l = sha1_h0_l;
                k_h = 0x8F1B;
                k_l = 0xBCDC;
            }
        }
        if(i1 >= 60) {
            sha1_f2(b_h, b_l, c_h, c_l, d_h, d_l);
            f_h = sha1_h0_h;
            f_l = sha1_h0_l;
            k_h = 0xCA62;
            k_l = 0xC1D6;
        }
        rotl32(a_h, a_l, 5);
        temp_h = sha1_h0_h;
        temp_l = sha1_h0_l;
        add32(temp_h, temp_l, f_h, f_l);
        temp_h = sha1_h0_h;
        temp_l = sha1_h0_l;
        add32(temp_h, temp_l, e_h, e_l);
        temp_h = sha1_h0_h;
        temp_l = sha1_h0_l;
        add32(temp_h, temp_l, k_h, k_l);
        temp_h = sha1_h0_h;
        temp_l = sha1_h0_l;
        add32(temp_h, temp_l, w_h[i1], w_l[i1]);
        temp_h = sha1_h0_h;
        temp_l = sha1_h0_l;
        e_h = d_h;
        e_l = d_l;
        d_h = c_h;
        d_l = c_l;
        rotl32(b_h, b_l, 30);
        c_h = sha1_h0_h;
        c_l = sha1_h0_l;
        b_h = a_h;
        b_l = a_l;
        a_h = temp_h;
        a_l = temp_l;
        i1++;
    }
    add32(sha1_h0_h, sha1_h0_l, a_h, a_l);
    sha1_h0_h = sha1_h0_h;
    sha1_h0_l = sha1_h0_l;
    add32(sha1_h1_h, sha1_h1_l, b_h, b_l);
    sha1_h1_h = sha1_h0_h;
    sha1_h1_l = sha1_h0_l;
    add32(sha1_h2_h, sha1_h2_l, c_h, c_l);
    sha1_h2_h = sha1_h0_h;
    sha1_h2_l = sha1_h0_l;
    add32(sha1_h3_h, sha1_h3_l, d_h, d_l);
    sha1_h3_h = sha1_h0_h;
    sha1_h3_l = sha1_h0_l;
    add32(sha1_h4_h, sha1_h4_l, e_h, e_l);
    sha1_h4_h = sha1_h0_h;
    sha1_h4_l = sha1_h0_l;
    return;
}
void sha1_init() {
    sha1_h0_h = 0x6745;
    sha1_h0_l = 0x2301;
    sha1_h1_h = 0xEFCD;
    sha1_h1_l = 0xAB89;
    sha1_h2_h = 0x98BA;
    sha1_h2_l = 0xDCFE;
    sha1_h3_h = 0x1032;
    sha1_h3_l = 0x5476;
    sha1_h4_h = 0xC3D2;
    sha1_h4_l = 0xE1F0;
    sha1_buflen = 0;
    sha1_bitlen_0 = 0;
    sha1_bitlen_1 = 0;
    sha1_bitlen_2 = 0;
    sha1_bitlen_3 = 0;
    return;
}
void sha1_update(short* data0, short len) {
    short i = 0;
    while(i < len) {
        sha1_buffer[sha1_buflen] = data0[i];
        sha1_buflen++;
        if(sha1_buflen == 64) {
            sha1_transform(sha1_buffer);
            sha1_buflen = 0;
            sha1_bitlen_0 = sha1_bitlen_0 + 512;
            if(sha1_bitlen_0 < 512) {
                sha1_bitlen_1++;
                if(sha1_bitlen_1 == 0) {
                    sha1_bitlen_2++;
                }
            }
        }
        i++;
    }
    return;
}
void sha1_final(short* hash) {
    short padding_len;
    short i2 = sha1_buflen;
    sha1_buffer[i2] = 0x80;
    i2++;
    if(sha1_buflen < 56) {
        while(i2 < 56) {
            sha1_buffer[i2] = 0;
            i2++;
        }
    }
    if(sha1_buflen >= 56) {
        while(i2 < 64) {
            sha1_buffer[i2] = 0;
            i2++;
        }
        sha1_transform(sha1_buffer);
        i2 = 0;
        while(i2 < 56) {
            sha1_buffer[i2] = 0;
            i2++;
        }
    }
    sha1_bitlen_0 = sha1_bitlen_0 + (sha1_buflen << 3);
    sha1_buffer[56] = (sha1_bitlen_3 >> 8) & 0xFF;
    sha1_buffer[57] = sha1_bitlen_3 & 0xFF;
    sha1_buffer[58] = (sha1_bitlen_2 >> 8) & 0xFF;
    sha1_buffer[59] = sha1_bitlen_2 & 0xFF;
    sha1_buffer[60] = (sha1_bitlen_1 >> 8) & 0xFF;
    sha1_buffer[61] = sha1_bitlen_1 & 0xFF;
    sha1_buffer[62] = (sha1_bitlen_0 >> 8) & 0xFF;
    sha1_buffer[63] = sha1_bitlen_0 & 0xFF;
    sha1_transform(sha1_buffer);
    hash[0] = sha1_h0_h;
    hash[1] = sha1_h0_l;
    hash[2] = sha1_h1_h;
    hash[3] = sha1_h1_l;
    hash[4] = sha1_h2_h;
    hash[5] = sha1_h2_l;
    hash[6] = sha1_h3_h;
    hash[7] = sha1_h3_l;
    hash[8] = sha1_h4_h;
    hash[9] = sha1_h4_l;
    return;
}
#endif