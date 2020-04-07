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
	//len = 0;
}

Password::Password(const Password &cpy){
	pass = new char[strlen(cpy.pass) + 1];
	salt = new char[strlen(cpy.salt) + 1];

	hash = new unsigned char;

	strcpy(pass, cpy.pass);
	strcpy(salt, cpy.salt);
	hash = cpy.hash;

}
/*
 * const String & String::operator=(const String & s)
{
	if (this != &s) {
		delete[] c_string;
		c_string = new char[strlen(s.c_string) + 1];
		strcpy(c_string, s.c_string);
	}
	return *this;
}
String String::operator+(String &s1) const
{
	String sum;
	delete sum.c_string;
	sum = new char[strlen(c_string) + strlen(s1.c_string)];
	strcpy(sum.c_string, c_string);
	strcat(sum.c_string, s1.c_string);
	return sum;
}
 */
const Password & Password::operator=(const Password &eq){
	if(this != &eq){
		delete[] pass;
		delete[] salt;
		pass = new char[strlen(eq.pass) + 1];
		salt = new char[strlen(eq.pass) + 1];
		strcpy(pass, eq.pass);
		strcpy(salt, eq.salt);
	}
	return *this;
}



void Password::hash256(){
	char* tmp = new char[strlen(pass) + strlen(salt)];
	const size_t len = sizeof((*pass + *salt) -1 );
	delete[] hash;
	strcpy(tmp, pass);
	strcat(tmp, salt);

	hash = (unsigned char*) tmp;
	delete[] tmp;
	//delete[] pass;
	//delete[] salt;

	mbedtls_sha256_ret(hash, len, digest, 0);



}

/*const unsigned char Password::getDigest(const unsigned char save[]) const{
	save = new unsigned char[sizeof(digest) + 1]();
	for (size_t i; i <= sizeof(digest); i++){
		save[i] = digest[i];
	}
	return save;
}*/

const unsigned char* Password::digestTest() const{
	return hash;
}

const char* Password::passR() const{
	return pass;
}


Password::~Password() {
	delete[] hash;
	delete[] salt;
	delete[] pass;
}

