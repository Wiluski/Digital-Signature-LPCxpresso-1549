/*
 * Password.h
 *
 *  Created on: Mar 27, 2020
 *      Author: Ville Vainio
 */

#ifndef Password_H_
#define Password_H_

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if DEBUG_LEVEL > 0
#include "mbedtls/debug.h"
#endif

#include "mbedtls/platform.h"
#include "mbedtls/sha256.h"
#include "mbedtls/md.h"

#include "string.h"


class Password {
public:
	Password(const char *pass0 = "", const char *salt0 = "");
	Password(const Password &cpy);
	const Password &operator=(const Password &eq);
	void hash256();
	//const unsigned char getDigest(const unsigned char save[]) const;
	const unsigned char* digestTest() const;
	const char* passR() const;
	virtual ~Password();
private:
	char *pass;
	char *salt;
	//unsigned char *hash;
	unsigned char digest[32] = {};

};

typedef struct{
	char salt[5];
	char pass[8];
	int valueECC;
	int exp;
	int nbit;
}passSpecifications;

#endif /* Password_H_ */
