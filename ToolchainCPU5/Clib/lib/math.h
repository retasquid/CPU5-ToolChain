#ifndef MATH_H
#define MATH_H


int mult(int mult_a, int mult_b){
    int result = 0;
    if(mult_a < mult_b){
        mult_a ^= mult_b;
        mult_b ^= mult_a;
        mult_a ^= mult_b;
    }
    while(mult_b){
        if(mult_b & 1){
            result += mult_a;
        }
        mult_a <<= 1;
        mult_b >>= 1;
    }
    return result;
}

short div(short dividend, short divisor) {
    if (divisor == 0) return 0xFFFF; // Division par zéro protection
    short quotient = 0;
    short remainder = dividend;
    // Trouver le nombre de bits à aligner
    short shift = 0;
    char cond = 1;
    while (cond) {
        if((divisor << shift) <= remainder){
            if(shift < 16){
                shift++;
            }else{
                cond=0;
            }
        }else{
            cond=0;
        }
    }
    // Revenir d'un cran en arrière si on a dépassé
    if (shift) shift--;
    while(shift<65535){
        short sub = divisor << shift;
        if (remainder >= sub) {
            remainder -= sub;
            quotient |= 1 << shift;
        }
        shift--;
    }
    return quotient;
}

#endif