# Cryptology-HW2
Just for homework

## Prerequisite
* g++ >= 5.4.0
* Crypto++ >= 8.1.0

## Files
* DES.cpp: DES that can encrypt and decrypt messages
* DES-Key-Ciphertext.txt: Pairs of key and cipher text
* DES-Key-Plaintext.txt: Pairs of key and plain text
* Homework2.pdf: Description file.

## Usage
DES.cpp can use the key and message in two text files to perform DES encryption and decryption. It will show the average running time.
```
$ g++ DES.cpp -o DES.out -O3
$ ./DES.out
```
