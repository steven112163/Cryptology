// hashchain.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <thread>
#include <mutex>
#include <ctime>
#include <cstdlib>

using namespace std;

#include <integer.h>
#include <hex.h>
#include <sha.h>
#include <cryptlib.h>
#include <files.h>
#pragma comment(lib, "C:\\Cryptopp\\x64\\Output\\Release\\cryptlib.lib")

using namespace CryptoPP;

void simple_sha256(const vector<string>& msgs, ofstream& ofile);

void blockchain(ofstream& ofile, string initialHash);

mutex key;
void run(int leadingZeros, string previousHash, unsigned long long start, unsigned long long upperbound, ofstream& ofile, bool& found, string& nextHash);

int main()
{
	vector<string> msgs;
	msgs.push_back("Hello!");
	msgs.push_back("Bitcoin is a cryptocurrency, a form of electronic cash.");
	ofstream ofile("out.txt");
	simple_sha256(msgs, ofile);

	blockchain(ofile, "0xB4056DF6691F8DC72E56302DDAD345D65FEAD3EAD9299609A826E2344EB63AA4");
	ofile.close();

	system("pause");

	return 0;
}

void simple_sha256(const vector<string>& msgs, ofstream& ofile) {
	SHA256 hash;

	for (unsigned int i = 0; i < msgs.size(); i++) {
		string digest;
		StringSource(msgs[i], true,
			new HashFilter( hash, 
				new StringSink(digest)
			) // Hash Filter
		); // String Source
		cout << "Message: " << msgs[i] << endl;

		string encoded;
		StringSource(digest, true,
			new HexEncoder(
				new StringSink(encoded)
			) // Hex Encoder
		); // String Source
		cout << "Digest: " << encoded << endl << endl;

		if (i > 0) ofile << encoded << endl;
	}
}

void blockchain(ofstream& ofile, string initialHash) {
	string previousHash = initialHash.substr(2, initialHash.length() - 2);
	bool found = false;
	string nextHash;

	srand((unsigned) time(0));
	unsigned long long start[] = { 0, 536870912, 1073741824, 1610612736, 2147483648,
								   2684354560, 3221225472, 3758096384 };
	unsigned long long upperbound[] = { 536870912, 1073741824, 1610612736, 2147483648,
										2684354560, 3221225472, 3758096384, 4294967296 };
	vector<short> index = { 0, 1, 2, 3, 4, 5, 6, 7 };
	

	for (unsigned int leadingZeros = 0; leadingZeros < 11; leadingZeros++) {
		cout << "Difficulty: " << leadingZeros << endl;
		ofile << leadingZeros << endl;
		found = false;

		if (leadingZeros > 1)
			random_shuffle(index.begin(), index.end());
		thread myThread0(run, leadingZeros, previousHash, start[index[0]], upperbound[index[0]], std::ref(ofile), std::ref(found), std::ref(nextHash));
		thread myThread1(run, leadingZeros, previousHash, start[index[1]], upperbound[index[1]], std::ref(ofile), std::ref(found), std::ref(nextHash));
		thread myThread2(run, leadingZeros, previousHash, start[index[2]], upperbound[index[2]], std::ref(ofile), std::ref(found), std::ref(nextHash));
		thread myThread3(run, leadingZeros, previousHash, start[index[3]], upperbound[index[3]], std::ref(ofile), std::ref(found), std::ref(nextHash));
		thread myThread4(run, leadingZeros, previousHash, start[index[4]], upperbound[index[4]], std::ref(ofile), std::ref(found), std::ref(nextHash));
		thread myThread5(run, leadingZeros, previousHash, start[index[5]], upperbound[index[5]], std::ref(ofile), std::ref(found), std::ref(nextHash));
		thread myThread6(run, leadingZeros, previousHash, start[index[6]], upperbound[index[6]], std::ref(ofile), std::ref(found), std::ref(nextHash));
		thread myThread7(run, leadingZeros, previousHash, start[index[7]], upperbound[index[7]], std::ref(ofile), std::ref(found), std::ref(nextHash));
		myThread0.join();
		myThread1.join();
		myThread2.join();
		myThread3.join();
		myThread4.join();
		myThread5.join();
		myThread6.join();
		myThread7.join();

		if (!found) break;

		previousHash.clear();
		previousHash = nextHash;
	}
}

void run(int leadingZeros, string previousHash, unsigned long long start, unsigned long long upperbound, ofstream& ofile, bool& found, string& nextHash) {
	for (unsigned long long nonce = start; nonce < upperbound; nonce++) {
		stringstream ss;
		ss << hex << nonce;
		string nonceString;
		ss >> nonceString;
		size_t zerobits = 8 - nonceString.length();
		for (unsigned int i = 0; i < zerobits; i++)
			nonceString = "0" + nonceString;
		//if (start == 0)
		//	cout << "\r" << nonceString << flush;

		string preimage;
		preimage = previousHash + nonceString;

		string decoded;
		StringSource(preimage, true,
			new HexDecoder(
				new StringSink(decoded)
			) // Hex Decoder
		); // String Source

		SHA256 hash;
		string digest;
		StringSource(decoded, true,
			new HashFilter(hash,
				new StringSink(digest)
			) // Hash Filter
		); // String Source

		string encoded;
		StringSource(digest, true,
			new HexEncoder(
				new StringSink(encoded)
			) // Hex Encoder
		); // String Source

		int count = 0;
		for (unsigned int i = 0; i < encoded.length(); i++)
			if (encoded[i] == '0')
				count++;
			else
				break;

		key.lock();
		if (found) {
			//cout << "\r" << flush;
			key.unlock();
			return;
		}
		key.unlock();

		if (count == leadingZeros) {
			key.lock();
			if (found) {
				//cout << "\r" << flush;
				key.unlock();
				return;
			}
			found = true;
			nextHash.clear();
			nextHash = encoded;
			key.unlock();

			cout << "\r" << "Previous hash: " << previousHash << flush << endl;
			ofile << previousHash << endl;

			cout << "Nonce: " << nonceString << endl;
			ofile << nonceString << endl;

			cout << "Hash value: " << encoded << endl << endl;
			ofile << encoded << endl;

			break;
		}
	}

	return;
}