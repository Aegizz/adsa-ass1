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

// Helper function to add zeros to the left of a number (multiply by base^n)
void addZeros(char num[], int zeros, char result[]){
    int len = strlen(num);
    strcpy(result, num);
    for (int i = 0; i < zeros; i++){
        result[len + i] = '0';
    }
    result[len + zeros] = '\0';
}

// Helper function to add two numbers represented as strings
void addNumbers(char num1[], char num2[], int base, char result[]){
    schoolMethod(num1, num2, base, result);
}

void karatsuba(char I1[], char I2[], int base, char product[202]){
    int len1 = strlen(I1);
    int len2 = strlen(I2);
    
    // Base case: if numbers are small, use school multiplication
    if (len1 < 10 || len2 < 10){
        schoolMultiplication(I1, I2, base, product);
        return;
    }
    
    // Make both numbers the same length by padding with leading zeros
    int maxLen = std::max(len1, len2);
    if (maxLen % 2 == 1) maxLen++; // Make it even
    
    char num1[202], num2[202];
    
    // Pad I1 with leading zeros
    int padding1 = maxLen - len1;
    for (int i = 0; i < padding1; i++){
        num1[i] = '0';
    }
    strcpy(num1 + padding1, I1);
    
    // Pad I2 with leading zeros  
    int padding2 = maxLen - len2;
    for (int i = 0; i < padding2; i++){
        num2[i] = '0';
    }
    strcpy(num2 + padding2, I2);
    
    int half = maxLen / 2;
    
    // Split the numbers
    char a[102], b[102], c[102], d[102];
    
    // a = left half of num1, b = right half of num1
    strncpy(a, num1, half);
    a[half] = '\0';
    strcpy(b, num1 + half);
    
    // c = left half of num2, d = right half of num2
    strncpy(c, num2, half);
    c[half] = '\0';
    strcpy(d, num2 + half);
    
    // Remove leading zeros
    leadingZeros(a);
    leadingZeros(b);
    leadingZeros(c);
    leadingZeros(d);
    
    // Handle edge cases where parts become empty
    if (strlen(a) == 0) strcpy(a, "0");
    if (strlen(b) == 0) strcpy(b, "0");
    if (strlen(c) == 0) strcpy(c, "0");
    if (strlen(d) == 0) strcpy(d, "0");
    
    // Recursively compute the three products
    char ac[202], bd[202], temp1[202], temp2[202], temp3[202];
    
    // ac = a * c
    karatsuba(a, c, base, ac);
    
    // bd = b * d
    karatsuba(b, d, base, bd);
    
    // (a+b) * (c+d)
    char a_plus_b[102], c_plus_d[102];
    addNumbers(a, b, base, a_plus_b);
    addNumbers(c, d, base, c_plus_d);
    karatsuba(a_plus_b, c_plus_d, base, temp3);
    
    // temp3 = (a+b)(c+d) - ac - bd
    char ac_plus_bd[202];
    addNumbers(ac, bd, base, ac_plus_bd);
    substitute(temp3, ac_plus_bd, base, temp3);
    
    // Calculate final result: ac * base^(2*half) + temp3 * base^half + bd
    char ac_shifted[400], temp3_shifted[300];
    
    addZeros(ac, 2 * half, ac_shifted);
    addZeros(temp3, half, temp3_shifted);
    
    // Add all three terms
    char partial[400];
    addNumbers(ac_shifted, temp3_shifted, base, partial);
    addNumbers(partial, bd, base, product);
    
    // Remove leading zeros from final result
    leadingZeros(product);
    if (strlen(product) == 0){
        strcpy(product, "0");
    }
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