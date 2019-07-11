# Cryptology-HW4
Just for homework

## Prerequisite
* g++ >= 5.4.0
* Crypto++ >= 8.1.0
* Visual Studio >= 2015

## Files
| File | Description |
| --- | --- |
| rsa-encrypt.cpp | Raw RSA that can encrypt messages |
| rsa-decrypt.cpp | Raw RSA that can decrypt messages given d|
| Homework4.pdf | Description file |
| Homework4_Ans.pdf | Answer file |

## Usage
rsa-encrypt.cpp can use given n and e to encrypt plain messages and detect whether messages are bigger than n.
rsa-decrypt.cpp can use given n, d and e to decrypt cipher messages and detect whether messages are bigger than n.
They run on Visual Studio with Crypto++.
