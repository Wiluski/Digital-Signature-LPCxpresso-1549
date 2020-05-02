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
	//hash = new unsigned char[];

}

Password::Password(const Password &cpy){
	pass = new char[strlen(cpy.pass) + 1];
	salt = new char[strlen(cpy.salt) + 1];

	//hash = new unsigned char[strlen(cpy.pass) + strlen(cpy.salt) + 1];

	strcpy(pass, cpy.pass);
	strcpy(salt, cpy.salt);
	//hash = cpy.hash;

}

const Password & Password::operator=(const Password &eq){
	if(this != &eq){
		delete[] pass;
		delete[] salt;
		pass = new char[strlen(eq.pass) + 1];
		salt = new char[strlen(eq.salt) + 1];
		strcpy(pass, eq.pass);
		strcpy(salt, eq.salt);
	}
	return *this;
}


void Password::hash256(){
	mbedtls_md_context_t sha_ctx;
	//int ret;
	char* tmp = new char[strlen(pass) + strlen(salt)];
	const size_t len = sizeof((*pass + *salt) -1 );
	//delete hash;
	unsigned char* buffer = new unsigned char[len];
	strcpy(tmp, pass);
	strcat(tmp, salt);

	memcpy(buffer,tmp,len);
	//unsigned char* buffer = (unsigned char*) tmp;
	//hash = (unsigned char*) tmp;
	delete[] tmp;
	//delete buffer;
	//buffer = NULL;

	//mbedtls_sha256_ret(hash, len, digest, 0);
	mbedtls_md_init(&sha_ctx);
	mbedtls_md_setup(&sha_ctx, mbedtls_md_info_from_type( MBEDTLS_MD_SHA256 ), 1);
	mbedtls_md_starts(&sha_ctx);
	mbedtls_md_update(&sha_ctx, buffer, len);
	mbedtls_md_finish(&sha_ctx, digest);


	mbedtls_md_free(&sha_ctx);

	delete[] buffer;
	buffer = NULL;

//	delete sha_ctx;
	//if(mbedtls_sha256_ret(hash, len, digest, 0) != 0){
		//DEBUGOUT("FAIL");
	//}

}



const unsigned char* Password::digestTest() const{
	return digest;
}

const char* Password::passR() const{
	return pass;
}


Password::~Password() {
	//delete hash;
	delete[] salt;
	delete[] pass;
}

