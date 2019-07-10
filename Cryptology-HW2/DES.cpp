// 0510002
// Steven Yuan

#include <ctime>
#include <fstream>
#include <bitset>
#include <string>
#include <sstream>

using namespace std;

// Initial Permutation
//int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2,
//			   60, 52, 44, 36, 28, 20, 12, 4,
//			   62, 54, 46, 38, 30, 22, 14, 6,
//			   64, 56, 48, 40, 32, 24, 16, 8,
//			   57, 49, 41, 33, 25, 17,  9, 1,
//			   59, 51, 43, 35, 27, 19, 11, 3,
//			   61, 53, 45, 37, 29, 21, 13, 5,
//			   63, 55, 47, 39, 31, 23, 15, 7 };
//int IP[] = { 6, 14, 22, 30, 38, 46, 54, 62,
//			   4, 12, 20, 28, 36, 44, 52, 60,
//			   2, 10, 18, 26, 34, 42, 50, 58,
//			   0,  8, 16, 24, 32, 40, 48, 56,
//			   7, 15, 23, 31, 39, 47, 55, 63,
//			   5, 13, 21, 29, 37, 45, 53, 61,
//			   3, 11, 19, 27, 35, 43, 51, 59,
//			   1,  9, 17, 25, 33, 41, 49, 57 };
int IP[] = { 57, 49, 41, 33, 25, 17,  9,  1,
			 59, 51, 43, 35, 27, 19, 11,  3,
			 61, 53, 45, 37, 29, 21, 13,  5,
			 63, 55, 47, 39, 31, 23, 15,  7,
			 56, 48, 40, 32, 24, 16,  8,  0,
			 58, 50, 42, 34, 26, 18, 10,  2,
			 60, 52, 44, 36, 28, 20, 12,  4,
			 62, 54, 46, 38, 30, 22, 14,  6 };

// Inverse Initial Permutation
//int IP_1[] = { 40, 8, 48, 16, 56, 24, 64, 32,
//			     39, 7, 47, 15, 55, 23, 63, 31,
//			     38, 6, 46, 14, 54, 22, 62, 30,
//			     37, 5, 45, 13, 53, 21, 61, 29,
//			     36, 4, 44, 12, 52, 20, 60, 28,
//			     35, 3, 43, 11, 51, 19, 59, 27,
//			     34, 2, 42, 10, 50, 18, 58, 26,
//			     33, 1, 41,  9, 49, 17, 57, 25 };
//int IP_1[] = { 24, 56, 16, 48,  8, 40,  0, 32,
//			     25, 57, 17, 49,  9, 41,  1, 33,
//			     26, 58, 18, 50, 10, 42,  2, 34,
//			     27, 59, 19, 51, 11, 43,  3, 35,
//			     28, 60, 20, 52, 12, 44,  4, 36,
//			     29, 61, 21, 53, 13, 45,  5, 37,
//			     30, 62, 22, 54, 14, 46,  6, 38,
//			     31, 63, 23, 55, 15, 47,  7, 39 };
int IP_1[] = { 39,  7, 47, 15, 55, 23, 63, 31,
			   38,  6, 46, 14, 54, 22, 62, 30,
			   37,  5, 45, 13, 53, 21, 61, 29,
			   36,  4, 44, 12, 52, 20, 60, 28,
			   35,  3, 43, 11, 51, 19, 59, 27,
			   34,  2, 42, 10, 50, 18, 58, 26,
			   33,  1, 41,  9, 49, 17, 57, 25,
			   32,  0, 40,  8, 48, 16, 56, 24 };

// Expansion
//int E[] = { 32,  1,  2,  3,  4,  5,
//			   4,  5,  6,  7,  8,  9,
//			   8,  9, 10, 11, 12, 13,
//			  12, 13, 14, 15, 16, 17,
//			  16, 17, 18, 19, 20, 21,
//			  20, 21, 22, 23, 24, 25,
//			  24, 25, 26, 27, 28, 29,
//			  28, 29, 30, 31, 32,  1 };
//int E[] = {  0, 31, 30, 29, 28, 27,
//		      28, 27, 26, 25, 24, 23,
//		      24, 23, 22, 21, 20, 19,
//		      20, 19, 18, 17, 16, 15,
//		      16, 15, 14, 13, 12, 11,
//		      12, 11, 10,  9,  8,  7,
//			   8,  7,  6,  5,  4,  3,
//			   4,  3,  2,  1,  0, 31 };
int E[] = { 31,  0,  1,  2,  3,  4,
			 3,  4,  5,  6,  7,  8,
			 7,  8,  9, 10, 11, 12,
			11, 12, 13, 14, 15, 16,
			15, 16, 17, 18, 19, 20,
			19, 20, 21, 22, 23, 24,
			23, 24, 25, 26, 27, 28,
			27, 28, 29, 30, 31,  0 };

// S-box 8x4x16
int S_BOX[8][4][16] = {
	{
		{ 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7 },
		{  0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8 },
		{  4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0 },
		{ 15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13 }
	},
	{
		{ 15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10 },
		{  3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5 },
		{  0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15 },
		{ 13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9 }
	},
	{
		{ 10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8 },
		{ 13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1 },
		{ 13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7 },
		{  1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12 }
	},
	{
		{  7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15 },
		{ 13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9 },
		{ 10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4 },
		{  3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14 }
	},
	{
		{  2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9 },
		{ 14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6 },
		{  4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14 },
		{ 11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3 }
	},
	{
		{ 12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11 },
		{ 10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8 },
		{  9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6 },
		{  4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 }
	},
	{
		{  4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1 },
		{ 13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6 },
		{  1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2 },
		{  6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12 }
	},
	{
		{ 13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7 },
		{  1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2 },
		{  7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8 },
		{  2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 }
	} };

// Permutation
//int P[] = { 16,  7, 20, 21, 29, 12, 28, 17,
//			   1, 15, 23, 26,  5, 18, 31, 10,
//			   2,  8, 24, 14, 32, 27,  3,  9,
//			  19, 13, 30,  6, 22, 11,  4, 25 };
//int P[] = { 16, 25, 12, 11,  3, 20,  4, 15,
//			  31, 17,  9,  6, 27, 14,  1, 22,
//			  30, 24,  8, 18,  0,  5, 29, 23,
//			  13, 19,  2, 26, 10, 21, 28,  7 };
int P[] = {  7, 28, 21, 10, 26,  2, 19, 13,
			23, 29,  5,  0, 18,  8, 24, 30,
			22,  1, 14, 27,  6,  9, 17, 31,
			15,  4, 20,  3, 11, 12, 25, 16 };

// Permutation Choice 1
//int PC_1[] = { 57, 49, 41, 33, 25, 17,  9,
//				  1, 58, 50, 42, 34, 26, 18,
//			     10,  2, 59, 51, 43, 35, 27,
//			     19, 11,  3, 60, 52, 44, 36,
//			     63, 55, 47, 39, 31, 23, 15,
//				  7, 62, 54, 46, 38, 30, 22,
//			     14,  6, 61, 53, 45, 37, 29,
//			     21, 13,  5, 28, 20, 12,  4 };
//int PC_1[] = {  7, 15, 23, 31, 39, 47, 55,
//			   63,  6, 14, 22, 30, 38, 46,
//			   54, 62,  5, 13, 21, 29, 37,
//			   45, 53, 61,  4, 12, 20, 28,
//			    1,  9, 17, 25, 33, 41, 49,
//			   57,  2, 10, 18, 26, 34, 42,
//			   50, 58,  3, 11, 19, 27, 35,
//			   43, 51, 59, 36, 44, 52, 60 };
int PC_1_1[] = { 28, 20, 12,  4, 61, 53, 45,
				 37, 29, 21, 13,  5, 62, 54,
				 46, 38, 30, 22, 14,  6, 63,
				 55, 47, 39, 31, 23, 15,  7 };
int PC_1_2[] = { 60, 52, 44, 36, 59, 51, 43,
				 35, 27, 19, 11,  3, 58, 50,
				 42, 34, 26, 18, 10,  2, 57,
				 49, 41, 33, 25, 17,  9,  1 };

// Permutation Choice 2
//int PC_2[] = { 14, 17, 11, 24,  1,  5,
//				  3, 28, 15,  6, 21, 10,
//			     23, 19, 12,  4, 26,  8,
//			     16,  7, 27, 20, 13,  2,
//			     41, 52, 31, 37, 47, 55,
//			     30, 40, 51, 45, 33, 48,
//			     44, 49, 39, 56, 34, 53,
//			     46, 42, 50, 36, 29, 32 };
//int PC_2[] = { 42, 39, 45, 32, 55, 51,
//			   53, 28, 41, 50, 35, 46,
//			   33, 37, 44, 52, 30, 48,
//			   40, 49, 29, 36, 43, 54,
//			   15,  4, 25, 19,  9,  1,
//			   26, 16,  5, 11, 23,  8,
//			   12,  7, 17,  0, 22,  3,
//			   10, 14,  6, 20, 27, 24 };
int PC_2[] = { 24, 27, 20,  6, 14, 10,
			    3, 22,  0, 17,  7, 12,
			    8, 23, 11,  5, 16, 26,
			    1,  9, 19, 25,  4, 15,
			   54, 43, 36, 29, 49, 40,
			   48, 30, 52, 44, 37, 33,
			   46, 35, 50, 41, 28, 53,
			   51, 55, 32, 45, 39, 42 };

// Bits Rotated
int shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };



class DES {
public:
	DES();
	void setText(const string& inputText);
	void setKey(const string& inputKey);
	string encrypt();
	string decrypt();

private:
	bitset<32> Ltext;
	bitset<32> Rtext;
	bitset<28> Lkey;
	bitset<28> Rkey;
	bitset<48> subKeys[16];

	void singleRound(const int& round);
	bitset<48> expand();
	bitset<32> sBox(const int& round, const bitset<48>& expandText);
	bitset<32> permutation(const bitset<32>& input);
	void getSubKey();
	void leftCircularShift(const int& round);
	string bitToString(const int& input);
};



int main() {
	clock_t start, end;
	double cpu_time_used = 0;

	ifstream iPfile("DES-Key-Plaintext.txt");
	ifstream iCfile("DES-Key-Ciphertext.txt");
	ofstream ofile("out.txt");
	DES des;
	for (int i = 0; i < 20; i++) {
		string key, text;
		if (i < 10) {
			getline(iPfile, key, ' ');
			getline(iPfile, text, '\n');
		}
		else {
			getline(iCfile, key, ' ');
			getline(iCfile, text, '\n');
		}

		string output;
		start = clock();
		des.setKey(key);
		des.setText(text);
		if (i < 10)
			output = des.encrypt();
		else
			output = des.decrypt();
		end = clock();
		ofile << output << endl;

		cpu_time_used += ((double)(end - start)) / CLOCKS_PER_SEC;
	}

	ofile << cpu_time_used / 20 * 1000 << " ms";

	iPfile.close();
	iCfile.close();
	ofile.close();

	return 0;
}



DES::DES() {}

void DES::setText(const string& inputText) {
	string inputString = "0x" + inputText;
	stringstream ss;
	ss << hex << inputString;
	unsigned long long n;
	ss >> n;

	bitset<64> input(n);
	for (int i = 0; i < 64; i++)
		if (i > 31)
			this->Ltext[i - 32] = input[IP[i]];
		else
			this->Rtext[i] = input[IP[i]];
}

void DES::setKey(const string& inputKey) {
	string inputString = "0x" + inputKey;
	stringstream ss;
	ss << hex << inputString;
	unsigned long long n;
	ss >> n;

	bitset<64> input(n);
	for (int i = 0; i < 28; i++) {
		this->Lkey[i] = input[PC_1_1[i]];
		this->Rkey[i] = input[PC_1_2[i]];
	}

	this->getSubKey();
}

string DES::encrypt() {
	for (int round = 0; round < 16; round++)
		this->singleRound(round);
	bitset<64> cipher;
	for (int i = 31; i >= 0; i--) {
		cipher[i + 32] = this->Rtext[i];
		cipher[i] = this->Ltext[i];
	}
	bitset<64> cipherText;
	for (int i = 0; i < 64; i++)
		cipherText[i] = cipher[IP_1[i]];

	string output;
	for (int i = 63; i > 2; i -= 4)
		output.append(this->bitToString((cipherText[i] << 3)
			+ (cipherText[i - 1] << 2)
			+ (cipherText[i - 2] << 1)
			+ cipherText[i - 3]));

	return output;
}

string DES::decrypt() {
	for (int round = 15; round >= 0; round--)
		this->singleRound(round);
	bitset<64> plain;
	for (int i = 31; i >= 0; i--) {
		plain[i + 32] = this->Rtext[i];
		plain[i] = this->Ltext[i];
	}
	bitset<64> plainText;
	for (int i = 0; i < 64; i++)
		plainText[i] = plain[IP_1[i]];

	string output;
	for (int i = 63; i > 2; i -= 4)
		output.append(this->bitToString((plainText[i] << 3)
			+ (plainText[i - 1] << 2)
			+ (plainText[i - 2] << 1)
			+ plainText[i - 3]));

	return output;
}

void DES::singleRound(const int& round) {
	bitset<32> preOutput = this->permutation(this->sBox(round, this->expand()));
	preOutput ^= this->Ltext;
	this->Ltext = this->Rtext;
	this->Rtext = preOutput;
}

bitset<48> DES::expand() {
	bitset<48> expandText;
	for (int i = 0; i < 48; i++)
		expandText[i] = this->Rtext[E[i]];

	return expandText;
}

bitset<32> DES::sBox(const int& round, const bitset<48>& expandText) {
	subKeys[round] ^= expandText;

	bitset<32> output;
	for (int i = 8; i > 0; i--) {
		int index = i * 6 - 1;
		int row = (subKeys[round][index] << 1) + subKeys[round][index - 5];
		int col = (subKeys[round][index - 1] << 3)
			+ (subKeys[round][index - 2] << 2)
			+ (subKeys[round][index - 3] << 1)
			+ subKeys[round][index - 4];
		output <<= 4;
		bitset<32> temp(S_BOX[8 - i][row][col]);
		output |= temp;
	}

	return output;
}

bitset<32> DES::permutation(const bitset<32>& input) {
	bitset<32> output;
	for (int i = 0; i < 32; i++)
		output[i] = input[P[i]];

	return output;
}

void DES::getSubKey() {
	for (int round = 0; round < 16; round++) {
		this->leftCircularShift(round);
		for (int i = 0; i < 48; i++) {
			int index = PC_2[i];
			if (index > 27)
				subKeys[round][i] = this->Lkey[index - 28];
			else
				subKeys[round][i] = this->Rkey[index];
		}
	}
}

void DES::leftCircularShift(const int& round) {
	bool Lmsb[2] = { this->Lkey.test(27), this->Lkey.test(26) };
	bool Rmsb[2] = { this->Rkey.test(27), this->Rkey.test(26) };
	this->Lkey <<= shiftBits[round];
	this->Rkey <<= shiftBits[round];
	if (shiftBits[round] == 2) {
		Lkey.set(0, Lmsb[1]);
		Lkey.set(1, Lmsb[0]);
		Rkey.set(0, Rmsb[1]);
		Rkey.set(1, Rmsb[0]);
	}
	else {
		Lkey.set(0, Lmsb[0]);
		Rkey.set(0, Rmsb[0]);
	}
}

string DES::bitToString(const int& input) {
	switch (input) {
	case 10: return "A";
	case 11: return "B";
	case 12: return "C";
	case 13: return "D";
	case 14: return "E";
	case 15: return "F";
	default: stringstream ss; ss << input; string output; ss >> output; return output;
	}
}
