#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>



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



// void karatsuba(char I1[], char I2[], int base, char product[]){
//     int len1 = strlen(I1);
//     int len2 = strlen(I2);

//     if (len1 == 0 || len2 == 0){
//         product[0] == '0';
//         product[1] = '\0';
//     }


// }






int main(int argc, char ** argv){
    char I1[101], I2[101];
    int base;
    
    std::cin >> I1 >> I2 >> base;
    char output[102];
    schoolMethod(I1, I2, base, output);
    std::cout << output << " " << 0 << " " << 0 <<std::endl;


}