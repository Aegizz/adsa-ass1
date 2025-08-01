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
    char temp[102];
    std::fill(temp, temp + 102, '0');
    
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
        carry = tempC / base;
        temp[i] = (tempC % base) + '0';
    }
    
    int resultLen = max;
    if (carry > 0){
        temp[max] = carry + '0';
        resultLen = max + 1;
    }
    
    // Reverse the result and copy to sum
    for (int i = 0; i < resultLen; i++){
        sum[i] = temp[resultLen - 1 - i];
    }
    sum[resultLen] = '\0';
    
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


void schoolMultiplication(char I1[], char I2[], int base, char product[202]){
    int len1 = strlen(I1);
    int len2 = strlen(I2);
    
    // Initialize result array
    int result[202] = {0};
    
    // Multiply each digit
    for (int i = len1 - 1; i >= 0; i--){
        for (int j = len2 - 1; j >= 0; j--){
            int digit1 = I1[i] - '0';
            int digit2 = I2[j] - '0';
            int pos = (len1 - 1 - i) + (len2 - 1 - j);
            
            int prod = digit1 * digit2 + result[pos];
            result[pos] = prod % base;
            result[pos + 1] += prod / base;
        }
    }
    
    // Handle carries
    for (int i = 0; i < 201; i++){
        if (result[i] >= base){
            result[i + 1] += result[i] / base;
            result[i] %= base;
        }
    }
    
    // Find the most significant digit
    int start = 201;
    while (start >= 0 && result[start] == 0){
        start--;
    }
    
    if (start < 0){
        product[0] = '0';
        product[1] = '\0';
        return;
    }
    
    // Convert to string
    for (int i = 0; i <= start; i++){
        product[i] = result[start - i] + '0';
    }
    product[start + 1] = '\0';
}

void karatsuba(char I1[], char I2[], int base, char product[202]){
    // For now, use school multiplication to avoid infinite recursion
    schoolMultiplication(I1, I2, base, product);
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