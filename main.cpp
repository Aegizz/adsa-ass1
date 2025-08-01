#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>


void leadingZeros(char IX[]){
    int pos = 0;
    while (IX[pos] == '0' && IX[pos + 1] != '\0'){
        pos++;
    }
    if (pos > 0){
        std::strcpy(IX, IX + pos);
    }
}

void schoolMethod(char I1[], char I2[], int base, char sum[102]){
    int len1 = strlen(I1);
    int len2 = strlen(I2);
    int max = std::max(len1, len2);

    int carry = 0;
    int tempA, tempB, tempC;
    std::fill(sum, sum+102, '0');
    for (int i = 0; i < max; i++){
        if (i < len1){
            tempA = I1[len1 - 1 - i] - '0';
        } else {
            tempA = 0;
        }
        if (i < len2){
            tempB = I2[len2 - 1 - i] - '0';
        } else {
            tempB = 0;
        }
        tempC = tempA + tempB + carry;
        carry = tempC/base;
        sum[max - 1 - i] = (tempC % base) + '0';
        
    }
    if (carry){
        memmove(sum + 1, sum, max);
        sum[0] = carry + '0';
        sum[max + 1] = '\0';
    } else {
        sum[max] = '\0';
    }

    return;
}
void substitute(char I1[], char I2[], int base, char diff[]){
    int len1 = std::strlen(I1);
    int len2 = std::strlen(I2);
    int max = std::max(len1, len2);

    char temp[1000] = "";
    int carry = 0;
    int tempA, tempB, tempC;

    for (int i = 0; i < max; i++){
        if (i < len1){
            tempA = I1[len1 - 1 - i] - '0';
        } else {
            tempA = 0;
        }
        if (i < len2){
            tempB = I2[len2 - 1 - i] - '0';
        } else {
            tempB = 0;
        }
        tempC = tempA - tempB - carry;
        if (tempC < 0){
            tempC += base;
            carry = 1;
        } else {
            carry = 0;
        }
        temp[i] = tempC + '0';
    }
    temp[max] = '\0';
    std::reverse(temp, temp + max);
    std::strcpy(diff, temp);
    leadingZeros(diff);
}


void karatsuba(char I1[], char I2[], int base, char product[202]){
    // if (std::strlen(I1) < 10 && std::strlen(I2) < 10){

    // }
    int max = std::max(std::strlen(I1), std::strlen(I2));
    int half = max/2;

    char temp1[1000] = "", temp2[1000] = "", temp3[1000] = "", temp4[1000] = "";
    char temp5[1000] = "", temp6[1000] = "", temp7[1000] = "", temp8[1000] = "", temp9[1000] = "", temp10[1000] = "";

    std::strncpy(temp1, I1, half);
    std::strcpy(temp2, I1 + half);
    std::strncpy(temp3, I2, half);
    std::strcpy(temp4, I2 + half);

    karatsuba(temp1, temp2, base, temp5);
    karatsuba(temp2, temp4, base, temp6);
    schoolMethod(temp1, temp2, base, temp8);
    schoolMethod(temp3, temp4, base, temp9);
    karatsuba(temp8, temp9, base, temp7);
    schoolMethod(temp5, temp6, base, temp10);
    substitute(temp7, temp10, base,temp7);

    char zeros1[1000] = "", zeros2[1000] = "";
    std::strcpy(zeros1, temp5);
    std::strcpy(zeros2, temp7);

}







int main(int argc, char ** argv){
    char I1[101], I2[101];
    int base;
    
    std::cin >> I1 >> I2 >> base;
    char sum[102];
    char product[100000];
    schoolMethod(I1, I2, base, sum);
    karatsuba(I1, I2, base, product);
    std::cout << sum << " " << product << " " << 0 <<std::endl;


}