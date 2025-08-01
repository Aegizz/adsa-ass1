#include <iostream>
#include <algorithm>
#include <vector>

void schoolMethod(std::string I1, std::string I2, int base, std::string &sum) {
    int len1 = I1.length();
    int len2 = I2.length();
    int max = std::max(len1, len2);

    int carry = 0;
    int tempA, tempB, tempC;
    std::vector<char> temp(max + 2);
    
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
    int len3 = max;
    if (carry > 0){
        temp[max] = carry + '0';
        len3 = max + 1;
    }
    sum.resize(len3);
    for (int i = 0; i < len3; i++){
        sum[i] = temp[len3 - 1 - i];
    }
    return;
}


void multiply(std::string I1, std::string I2, int base, std::string &product) {
    if (I1 == "0" || I2 == "0") {
        product = "0";
        return;
    }
    
    int len1 = I1.length();
    int len2 = I2.length();
    std::vector<int> result(len1 + len2, 0);
    
    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int digit1 = I1[i] - '0';
            int digit2 = I2[j] - '0';
            int pos = (len1 - 1 - i) + (len2 - 1 - j);
            
            result[pos] += digit1 * digit2;
            
            if (result[pos] >= base) {
                result[pos + 1] += result[pos] / base;
                result[pos] %= base;
            }
        }
    }
    
    int i = result.size() - 1;
    while (i > 0 && result[i] == 0) i--;
    
    product = "";
    for (; i >= 0; i--) {
        product += (result[i] + '0');
    }
}

void negativeSchoolMethod(std::string I1, std::string I2, int base, std::string &result) {
    int len1 = I1.length();
    int len2 = I2.length();
    int max = std::max(len1, len2);
    
    std::vector<char> temp(max + 1);
    int borrow = 0;
    
    for (int i = 0; i < max; i++) {
        int digit1 = (i < len1) ? (I1[len1 - 1 - i] - '0') : 0;
        int digit2 = (i < len2) ? (I2[len2 - 1 - i] - '0') : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }
        temp[i] = diff + '0';
    }
    
    int endIndex = max - 1;
    while (endIndex > 0 && temp[endIndex] == '0') endIndex--;
    
    result.resize(endIndex + 1);
    for (int i = 0; i <= endIndex; i++) {
        result[i] = temp[endIndex - i];
    }
}

void removeLeadingZeros(std::string &str) {
    while (str.length() > 1 && str[0] == '0') {
        str = str.substr(1);
    }
}


void karatsuba(std::string I1, std::string I2, int base, std::string &product){
    int len1 = I1.length();
    int len2 = I2.length();

    if (len1 < 2 || len2 < 2){
        if (I1 == "0" || I2 == "0"){
            product = "0";
            return;
        }
        multiply(I1, I2, base, product);
        return;
    }

    int maxLen = std::max(len1, len2);
    while (I1.length() < maxLen) I1 = "0" + I1;
    while (I2.length() < maxLen) I2 = "0" + I2;
    
    int len3 = maxLen/2;
    std::string subA = I1.substr(0, maxLen - len3);  
    std::string subB = I1.substr(maxLen - len3);     
    std::string subC = I2.substr(0, maxLen - len3);  
    std::string subD = I2.substr(maxLen - len3);     


    std::string ac, bd;
    karatsuba(subA, subC, base, ac);
    karatsuba(subB, subD, base, bd);

    std::string sumA, sumB;
    schoolMethod(subA, subB, base, sumA);
    schoolMethod(subC, subD, base, sumB);

    std::string abcd;
    karatsuba(sumA, sumB, base, abcd);

    std::string temp_sum, cross;
    schoolMethod(ac, bd, base, temp_sum);

    negativeSchoolMethod(abcd, temp_sum, base, cross);

    std::string ac_shift = ac;
    for (int i = 0; i < 2 * len3; ++i) ac_shift += "0";
    std::string cross_shift = cross;
    for (int i = 0; i < len3; ++i) cross_shift += "0";

    std::string temp1;
    schoolMethod(ac_shift, cross_shift, base, temp1);
    schoolMethod(temp1, bd, base, product);
    
    removeLeadingZeros(product);
    return;
}

int main(int argc, char ** argv){
    std::string I1, I2;
    int b;
    std::cin >> I1 >> I2 >> b;
    std::string sum, product;
    schoolMethod(I1, I2, b, sum);
    karatsuba(I1, I2, b, product);
    std::cout << sum << " " << product << " " << 0 <<std::endl;
    return 0;
}