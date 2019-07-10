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
#include <osrng.h>

#pragma comment(lib, "C:\\Cryptopp\\x64\\Output\\Release\\cryptlib.lib")
using namespace CryptoPP;

string decrypt(RSA::PrivateKey priKey, const Integer& n,
	const Integer& e, const Integer& d, const Integer& c);

int main()
{
	ofstream ofile;
	ofile.open("out.txt", fstream::app);
	Integer n("0xae20a831558c0d69"), e("0x11"), d("0x111242af5740d14d");
	RSA::PrivateKey priKey;
	Integer c("0x194d5cdc0ec8efbc");
	decrypt(priKey, n, e, d, c);

	n = Integer("0xa0c432951d9e7da10fa929ba570bfee52db56fc477e60b742581a35d1723ad6f");
	d = Integer("0x974f3eaa763ad0979644dbfaac47867bd87b4c5c8b7fcd72943d0dde4303639");
	c = Integer("0x404ea0a1c26fc6562ff17a61849520e0fdf70654c6460b0954918e8447d6cdba");
	string out = decrypt(priKey, n, e, d, c);
	ofile << out << endl;

	ofile.close();

	system("pause");

	return 0;
}

string decrypt(RSA::PrivateKey priKey, const Integer& n,
	const Integer& e, const Integer& d, const Integer& c) {
	AutoSeededRandomPool prng;
	priKey.Initialize(n, e, d);
	if (c > priKey.MaxImage()) {
		cout << "Cipher text is larger than n!!!" << endl;
		return "";
	}
	Integer r = priKey.CalculateInverse(prng, c);
	size_t req = r.MinEncodedSize();
	string recovered;
	recovered.resize(req);
	r.Encode((byte *)recovered.data(), recovered.size());
	cout << "Plain text: " << recovered << endl;

	return recovered;
}