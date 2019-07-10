// 0510002
// Steven Yuan

#include <iostream>
#include <string>
#include <fstream>
#include <aes.h>
#include <modes.h>
#include <filters.h>
#include <hex.h>

#pragma comment(lib, "C:\\Cryptopp\\x64\\Output\\Release\\cryptlib.lib")

using namespace std;
using namespace CryptoPP;

void ECBencrypt(const string& plainText, const string& paddingType,
	string& cipherText, ofstream& ofile,
	ECB_Mode<AES>::Encryption& encryption,
	const StreamTransformationFilter::BlockPaddingScheme& padding);

void ECBdecrypt(const string& cipherText,
	ECB_Mode<AES>::Decryption& decryption,
	const StreamTransformationFilter::BlockPaddingScheme& padding);

void CBCencrypt(const string& plainText, const string& paddingType,
	string& cipherText, ofstream& ofile,
	CBC_Mode<AES>::Encryption& encryption,
	const StreamTransformationFilter::BlockPaddingScheme& padding);

void CBCdecrypt(const string& cipherText,
	CBC_Mode<AES>::Decryption& decryption,
	const StreamTransformationFilter::BlockPaddingScheme& padding);

int main()
{
	CryptoPP::byte key[AES::DEFAULT_KEYLENGTH], iv[AES::BLOCKSIZE];
	string keyString = "1234567890123456";
	string ivString = "0000000000000000";
	memcpy(key, keyString.c_str(), AES::DEFAULT_KEYLENGTH);
	memcpy(iv, ivString.c_str(), AES::BLOCKSIZE);

	string plainText = "AES is efficient in both software and hardware.";
	ofstream ofile("Out.txt");
	ECB_Mode<AES>::Encryption eECB;
	CBC_Mode<AES>::Encryption eCBC;
	ECB_Mode<AES>::Decryption dECB;
	CBC_Mode<AES>::Decryption dCBC;

	// ECB mode with zero padding
	string cipherECBzero;
	eECB.SetKey(key, AES::DEFAULT_KEYLENGTH);
	dECB.SetKey(key, AES::DEFAULT_KEYLENGTH);
	ECBencrypt(plainText, "Zero", cipherECBzero, ofile, eECB, StreamTransformationFilter::ZEROS_PADDING);
	ECBdecrypt(cipherECBzero, dECB, StreamTransformationFilter::ZEROS_PADDING);

	// ECB mode with pkcs7 padding
	string cipherECBpkcs;
	eECB.SetKey(key, AES::DEFAULT_KEYLENGTH);
	dECB.SetKey(key, AES::DEFAULT_KEYLENGTH);
	ECBencrypt(plainText, "PKCS7", cipherECBpkcs, ofile, eECB, StreamTransformationFilter::PKCS_PADDING);
	ECBdecrypt(cipherECBpkcs, dECB, StreamTransformationFilter::PKCS_PADDING);

	// CBC mode with zero padding
	string cipherCBCzero;
	eCBC.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
	dCBC.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
	CBCencrypt(plainText, "Zero", cipherCBCzero, ofile, eCBC, StreamTransformationFilter::ZEROS_PADDING);
	CBCdecrypt(cipherCBCzero, dCBC, StreamTransformationFilter::ZEROS_PADDING);

	// CBC mode with pkcs7 padding
	string cipherCBCpkcs;
	eCBC.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
	dCBC.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
	CBCencrypt(plainText, "PKCS7", cipherCBCpkcs, ofile, eCBC, StreamTransformationFilter::PKCS_PADDING);
	CBCdecrypt(cipherCBCpkcs, dCBC, StreamTransformationFilter::PKCS_PADDING);

	system("pause");

    return 0;
}

void ECBencrypt(const string& plainText, const string& paddingType,
	string& cipherText, ofstream& ofile,
	ECB_Mode<AES>::Encryption& encryption,
	const StreamTransformationFilter::BlockPaddingScheme& padding) {
	string outputText;

	StringSource ssECB(plainText, true,
		new StreamTransformationFilter(encryption,
			new StringSink(cipherText),
			padding
		) // StreamTransformationFilter      
	); // StringSource

	StringSource ss(cipherText, true,
		new HexEncoder(
			new StringSink(outputText)
		) // HexEncoder
	); // StringSource

	ofile << outputText << endl << endl;
	cout << "ECB " << paddingType << ": " << outputText << endl;
}

void ECBdecrypt(const string& cipherText,
	ECB_Mode<AES>::Decryption& decryption,
	const StreamTransformationFilter::BlockPaddingScheme& padding) {
	string decipherText;
	StringSource ssECB(cipherText, true,
		new StreamTransformationFilter(decryption,
			new StringSink(decipherText),
			padding
		) // StreamTransformationFilter
	); // StringSource

	cout << "Plain text: " << decipherText << endl << endl;
}

void CBCencrypt(const string& plainText, const string& paddingType,
	string& cipherText, ofstream& ofile,
	CBC_Mode<AES>::Encryption& encryption,
	const StreamTransformationFilter::BlockPaddingScheme& padding) {
	string outputText;

	StringSource ssCBC(plainText, true,
		new StreamTransformationFilter(encryption,
			new StringSink(cipherText),
			padding
		) // StreamTransformationFilter      
	); // StringSource

	StringSource ss(cipherText, true,
		new HexEncoder(
			new StringSink(outputText)
		) // HexEncoder
	); // StringSource

	ofile << outputText << endl << endl;
	cout << "CBC " << paddingType << ": " << outputText << endl;
}

void CBCdecrypt(const string& cipherText,
	CBC_Mode<AES>::Decryption& decryption,
	const StreamTransformationFilter::BlockPaddingScheme& padding) {
	string decipherText;
	StringSource ss(cipherText, true,
		new StreamTransformationFilter(decryption,
			new StringSink(decipherText),
			padding
		) // StreamTransformationFilter
	); // StringSource

	cout << "Plain text: " << decipherText << endl << endl;
}
