// 0510002
// Steven Yuan

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

#include <integer.h>
#include <rsa.h>

#pragma comment(lib, "C:\\Cryptopp\\x64\\Output\\Release\\cryptlib.lib")
using namespace CryptoPP;

string encrypt(RSA::PublicKey pubKey, const Integer& n,
	const Integer& e, const string& message);

int main()
{
	ofstream ofile;
	ofile.open("out.txt");
	Integer n("0xab9df7c82818bab3"), e("0x11");
	RSA::PublicKey pubKey;
	string message("Alice");
	encrypt(pubKey, n, e, message);

	n = Integer("0xcebe9e0617c706c632e64c3405cda5d1");
	message = "Hello World!";
	string out = encrypt(pubKey, n, e, message);
	ofile << out << endl;

	n = Integer("0xaf195de7988cfaa1dbb18c5862e3853f0e79a12bbfa7aa326a52da97caa60c39");
	message = "RSA is public key.";
	out = encrypt(pubKey, n, e, message);
	ofile << out << endl;

	ofile.close();

	system("pause");

    return 0;
}

string encrypt(RSA::PublicKey pubKey, const Integer& n,
	const Integer& e, const string& message) {
	pubKey.Initialize(n, e);
	Integer m = Integer((const byte*)message.data(), message.size());
	if (m > pubKey.MaxImage()) {
		cout << "Message is larger than n!!!" << endl;
		return "";
	}
	Integer c = pubKey.ApplyFunction(m);
	stringstream ss;
	ss << hex << c;
	string outputString;
	ss >> outputString;
	cout << "Cipher text: "
		<< outputString.substr(0, outputString.length() - 1)
		<< endl;

	return outputString.substr(0, outputString.length() - 1);
}