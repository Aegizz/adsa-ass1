#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>



int schoolMethod(char I1[], char I2[], int base){
    int len1 = strlen(I1);
    int len2 = strlen(I2);
    int max = std::max(len1, len2);

    int carry = 0;
    int tempA = 0;
    int tempB = 0;
    int tempC = 0;
    int sum = 0;
    for (int i = 0; i < max; i++){
        tempA = 0;
        tempB = 0;
        tempC = 0;
        if (i < len1){
            tempA = I1[len1 - 1 - i] - '0';
        }
        if (i < len2){
            tempB = I2[len2 - 1 - i] - '0';
        }
        tempC = tempA + tempB + carry;
        if (tempC > base - 1){
            tempC = tempC - base;
            carry = 1;
        } else {
            carry = 0;
        }
        sum += (tempC * pow(base, i));

    }
    if (carry){
        sum+=1 * pow(10, max + 1);
    }
    return sum;

}

int main(int argc, char ** argv){
    char I1[101], I2[101];
    int base;

    std::cin >> I1 >> I2 >> base;

    std::cout << schoolMethod(I1, I2, base) << std::endl;


}