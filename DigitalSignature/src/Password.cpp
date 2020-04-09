/*
 * Password.cpp
 *
 *  Created on: Mar 27, 2020
 *      Author: Ville Vainio
 */

#include <Password.h>

Password::Password(const char *pass0, const char *salt0) {
	pass = new char[strlen(pass0) + 1];
	salt = new char[strlen(salt0) + 1];
	strcpy(pass, pass0);
	strcpy(salt, salt0);
	hash = new unsigned char;
	hash = NULL;
}

Password::Password(const Password &cpy){
	pass = new char[strlen(cpy.pass) + 1];
	salt = new char[strlen(cpy.salt) + 1];

	hash = new unsigned char;

	strcpy(pass, cpy.pass);
	strcpy(salt, cpy.salt);
	hash = cpy.hash;

}


void Password::hash256(){
	char* tmp = new char[strlen(pass) + strlen(salt)];
	const size_t len = sizeof((*pass + *salt) -1 );
	delete[] hash;
	strcpy(tmp, pass);
	strcat(tmp, salt);

	hash = (unsigned char*) tmp;
	delete[] tmp;

	mbedtls_sha256_ret(hash, len, digest, 0);



}



const unsigned char* Password::digestTest() const{
	return digest;
}

const char* Password::passR() const{
	return pass;
}


Password::~Password() {
	delete[] hash;
	delete[] salt;
	delete[] pass;
}

