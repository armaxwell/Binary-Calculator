#include <iostream>
#include <vector>
#include <string>

using namespace std;

unsigned long int MAXADD = 31; // 2^31 - 1
unsigned long int MAXMUL = 16; // 2^16 - 1

bool isBinary(string &str, unsigned int length) { // Works
    for (unsigned int i = 0; i < length; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    return true;
}

int twoPow(int n) { // Works
    unsigned int x = 1;
    if (n == 0) {
        return 1;
    }
    for (int i = 1; i <= n; i++) {
        x *= 2;
    }
    return x;
}

unsigned int binary2Decimal(string &str, unsigned int length) { // Works
    unsigned int sum = 0;

    if (!isBinary(str, length)) {
        return -1;
    }

    for (unsigned int i = 0; i < length; i++) {
        if (str[i] == '0') {
            continue;
        } else {
            sum += twoPow(length - 1 - i);
        }

    }
    return sum;
}

bool getBit(char bit) {
    if (bit == '1') {
        return true;
    }
    return false;
}

string getString(bool bit) {
    if (bit) {
        return "1";
    }
    return "0";
}

string addition(string num1, string num2, unsigned int length1, unsigned int length2) { // addend 1 and addend 2
    string sum = "";
    // 1010101011010101010110 + 11101011101010110111 doesnt work? now it does...what?
    int longest = length1;
    int shortest = length2;
    string a = num1;
    string b = num2;

    if (length2 > length1) {
        longest = length2;
        shortest = length1;
        a = num2;
        b = num1;
    }

    bool x, carryin, carryout = false;
    for (int big = longest - 1; big >= 0; big--) {
        int small = big - (longest - shortest);
        // cout << "\nLoop " << big << endl;
        carryin = carryout;
        if (small < 0) {
            // cout << "if" << endl;
            // cout << "a: " << a[big] << endl;
            // cout << "b: " << b[small] << endl;
            // cout << "ci: " << carryin << endl;

            x = getBit(a[big]) ^ carryin;
            carryout = getBit(a[big]) && carryin;

            // cout << "x: " << x << endl;
            // cout << "co: " << carryout << endl;
            sum = getString(x) + sum;
        } else {
            // cout << "else" << endl;
            // cout << "a: " << a[big] << endl;
            // cout << "b: " << b[small] << endl;
            // cout << "ci: " << carryin << endl;

            x = (!getBit(a[big]) && !getBit(b[small]) && carryin) || (!getBit(a[big]) && getBit(b[small]) && !carryin) || (getBit(a[big]) && !getBit(b[small]) && !carryin) || (getBit(a[big]) && getBit(b[small]) && carryin);
            carryout = (getBit(a[big]) && getBit(b[small])) || (getBit(a[big]) && carryin) || (getBit(b[small]) && carryin);

            // cout << "x: " << x << endl;
            // cout << "x: " << getString(x) << endl;
            // cout << "co: " << carryout << endl;

            sum = getString(x) + sum;
        }
        // cout << "sum: " << sum << endl;
    }

    if (carryout) {
        sum = getString(carryout) + sum;
    }

    // cout << "sum fin: " << sum << endl;
    return sum;
}

string subtraction(string num1, string num2, unsigned int length1, unsigned int length2) {
    string difference = "";

    int longest = length1;
    int shortest = length2;
    string a = num1;
    string b = num2;

    if (length2 > length1) {
        longest = length2;
        shortest = length1;
        a = num2;
        b = num1;
    }

    for (unsigned int big = longest - 1; big >= 0; big--) {
        int small = big - (longest - shortest);
        if (small < 0) {
            
        } else {
            if (getBit(a[big]) < getBit(b[small])) {
                int i = big;
                while (i >= 0 && getBit(a[i])) {
                    i--;
                }
                char carry = a[i];
                a[i] = '0';
                
            } else {
                
            }
        }
    }

    return difference;
}

string multiplication(string num1, string num2, unsigned int length1, unsigned int length2) {
    string product = "0";

    int longest = length1;
    int shortest = length2;
    string a = num1;
    string b = num2;

    if (length2 > length1) {
        longest = length2;
        shortest = length1;
        a = num2;
        b = num1;
    }

    unsigned int place = 0;
    vector<string> sums;
    for (int small = shortest - 1; small >= 0; small--) {
        string sum = "";
        if (getBit(b[small])) {
            for (int i = 0; i < place; i++) {
                sum = "0" + sum;
            }
            sum = a + sum;
        }
        sums.push_back(sum);
        place++;
    }

    for (int j = 0; j < sums.size(); j++) {
        // cout << sums.at(j) << endl;
        product = addition(product, sums.at(j), product.length(), sums.at(j).length());
        // cout << product << endl;
    }

    return product;
}

string division(string num1, string num2, unsigned int length1, unsigned length2) {

}

int main (int argv, char** argc) {
    string input1;
    cout << "\nEnter the first number:\t";
    cin >> input1;

    string input2;
    cout << "Enter another number:\t";
    cin >> input2;

    // isBinary test bench
    /*unsigned int n1 = input1.length();
    unsigned int n2 = input2.length();
    cout << isBinary(input1, n1) << endl;
    cout << isBinary(input2, n2) << endl;*/

    unsigned int len1 = input1.length();
    unsigned int len2 = input2.length();
    if (!isBinary(input1, len1) || !isBinary(input2, len2)) {
        cout << "Error: Detected non-binary input. Exiting program" << endl;
        return 1;
    }

    // twoPow test bench
    /*int res = twoPow(16);
    cout << res << endl;*/

    // binary2Decimal test bench
    /*int num1 = binary2Decimal(input1, len1);
    int num2 = binary2Decimal(input2, len2);

    cout << "The numbers you entered are " << num1 << " and " << num2 << ".\n";*/

    cout << "The first number you entered in binary is:\t" << binary2Decimal(input1, len1) << endl;
    cout << "The second number you entered in binary is:\t" << binary2Decimal(input2, len2) << endl;

    cout << "\nChoose an operation (First Number [?] Second Number):\n  [1] Addition\n  [2] Subtraction\n  [3] Multiplication\n  [4] Division" << endl;
    
    int sel = 0;
    cout << "Select a number:\t";
    cin >> sel;

    if (sel % 2 == 0 && binary2Decimal(input1, len1) < binary2Decimal(input2, len2)) {
        cout << "The first number must be greater than the second number. Switch the inputs and rerun the program.\n" << endl;
        return 1;
    }

    string result;
    switch (sel) {
        case 1:
            if (len1 > MAXADD) {
                cout << "Error: First number is too big. Only 31 bits maximum per input for addition. Try a smaller number." << endl;
                return 1;
            } else if (len2 > MAXADD) {
                cout << "Error: Second number is too big. Only 31 bits maximum per input for addition. Try a smaller number." << endl;
                return 1;
            }
            result = addition(input1, input2, len1, len2);
            break;
        case 3:
            if (len1 > MAXMUL) {
                cout << "Error: First number is too big. Only 16 bits maximum per input for multiplication. Try a smaller number." << endl;
                return 1;
            } else if (len2 > MAXMUL) {
                cout << "Error: Second number is too big. Only 16 bits maximum per input for multiplication. Try a smaller number." << endl;
                return 1;
            }
            result = multiplication(input1, input2, len1, len2);
            break;
        default:
            result = "";
    }

    unsigned int resLen = result.length();
    cout << "\nBinary result is:\t" << result << endl;
    cout << "Decimal result is:\t" << binary2Decimal(result, resLen) << endl;
    return 0;
}