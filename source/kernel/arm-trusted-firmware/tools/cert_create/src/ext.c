/*
 * Copyright (c) 2015, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include <openssl/err.h>
#include <openssl/x509v3.h>

#include "cmd_opt.h"
#include "ext.h"

DECLARE_ASN1_ITEM(ASN1_INTEGER)
DECLARE_ASN1_ITEM(X509_ALGOR)
DECLARE_ASN1_ITEM(ASN1_OCTET_STRING)

typedef struct {
	X509_ALGOR *hashAlgorithm;
	ASN1_OCTET_STRING *dataHash;
} HASH;

ASN1_SEQUENCE(HASH) = {
	ASN1_SIMPLE(HASH, hashAlgorithm, X509_ALGOR),
	ASN1_SIMPLE(HASH, dataHash, ASN1_OCTET_STRING),
} ASN1_SEQUENCE_END(HASH)

DECLARE_ASN1_FUNCTIONS(HASH)
IMPLEMENT_ASN1_FUNCTIONS(HASH)

/*
 * This function adds the TBB extensions to the internal extension list
 * maintained by OpenSSL so they can be used later.
 *
 * It also initializes the methods to print the contents of the extension. If an
 * alias is specified in the TBB extension, we reuse the methods of the alias.
 * Otherwise, only methods for V_ASN1_INTEGER and V_ASN1_OCTET_STRING are
 * provided. Any other type will be printed as a raw ascii string.
 *
 * Return: 0 = success, Otherwise: error
 */
int ext_init(void)
{
	ext_t *ext;
	X509V3_EXT_METHOD *m;
	int nid, ret;
	unsigned int i;

	for (i = 0; i < num_extensions; i++) {
		ext = &extensions[i];
		/* Register command line option */
		if (ext->opt) {
			if (cmd_opt_add(ext->opt, required_argument,
					CMD_OPT_EXT)) {
				return 1;
			}
		}
		/* Register the extension OID in OpenSSL */
		if (ext->oid == NULL) {
			continue;
		}
		nid = OBJ_create(ext->oid, ext->sn, ext->ln);
		if (ext->alias) {
			X509V3_EXT_add_alias(nid, ext->alias);
		} else {
			m = &ext->method;
			memset(m, 0x0, sizeof(X509V3_EXT_METHOD));
			switch (ext->asn1_type) {
			case V_ASN1_INTEGER:
				m->it = ASN1_ITEM_ref(ASN1_INTEGER);
				m->i2s = (X509V3_EXT_I2S)i2s_ASN1_INTEGER;
				m->s2i = (X509V3_EXT_S2I)s2i_ASN1_INTEGER;
				break;
			case V_ASN1_OCTET_STRING:
				m->it = ASN1_ITEM_ref(ASN1_OCTET_STRING);
				m->i2s = (X509V3_EXT_I2S)i2s_ASN1_OCTET_STRING;
				m->s2i = (X509V3_EXT_S2I)s2i_ASN1_OCTET_STRING;
				break;
			default:
				continue;
			}
			m->ext_nid = nid;
			ret = X509V3_EXT_add(m);
			if (!ret) {
				ERR_print_errors_fp(stdout);
				return 1;
			}
		}
	}
	return 0;
}

/*
 * Create a new extension
 *
 * Extension  ::=  SEQUENCE  {
 *      id          OBJECT IDENTIFIER,
 *      critical    BOOLEAN DEFAULT FALSE,
 *      value       OCTET STRING  }
 *
 * Parameters:
 *   pex: OpenSSL extension pointer (output parameter)
 *   nid: extension identifier
 *   crit: extension critical (EXT_NON_CRIT, EXT_CRIT)
 *   data: extension data. This data will be encapsulated in an Octet String
 *
 * Return: Extension address, NULL if error
 */
static
X509_EXTENSION *ext_new(int nid, int crit, unsigned char *data, int len)
{
	X509_EXTENSION *ex;
	ASN1_OCTET_STRING *ext_data;

	/* Octet string containing the extension data */
	ext_data = ASN1_OCTET_STRING_new();
	ASN1_OCTET_STRING_set(ext_data, data, len);

	/* Create the extension */
	ex = X509_EXTENSION_create_by_NID(NULL, nid, crit, ext_data);

	/* The extension makes a copy of the data, so we can free this object */
	ASN1_OCTET_STRING_free(ext_data);

	return ex;
}

/*
 * Creates a x509v3 extension containing a hash
 *
 * DigestInfo ::= SEQUENCE {
 *     digestAlgorithm  AlgorithmIdentifier,
 *     digest           OCTET STRING
 * }
 *
 * AlgorithmIdentifier ::=  SEQUENCE  {
 *     algorithm        OBJECT IDENTIFIER,
 *     parameters       ANY DEFINED BY algorithm OPTIONAL
 * }
 *
 * Parameters:
 *   nid: extension identifier
 *   crit: extension critical (EXT_NON_CRIT, EXT_CRIT)
 *   md: hash algorithm
 *   buf: pointer to the buffer that contains the hash
 *   len: size of the hash in bytes
 *
 * Return: Extension address, NULL if error
 */
X509_EXTENSION *ext_new_hash(int nid, int crit, const EVP_MD *md,
		unsigned char *buf, size_t len)
{
	X509_EXTENSION *ex = NULL;
	ASN1_OCTET_STRING *octet = NULL;
	HASH *hash = NULL;
	ASN1_OBJECT *algorithm = NULL;
	X509_ALGOR *x509_algor = NULL;
	unsigned char *p = NULL;
	int sz = -1;

	/* OBJECT_IDENTIFIER with hash algorithm */
	algorithm = OBJ_nid2obj(md->type);
	if (algorithm == NULL) {
		return NULL;
	}

	/* Create X509_ALGOR */
	x509_algor = X509_ALGOR_new();
	if (x509_algor == NULL) {
		return NULL;
	}
	x509_algor->algorithm = algorithm;
	x509_algor->parameter = ASN1_TYPE_new();
	ASN1_TYPE_set(x509_algor->parameter, V_ASN1_NULL, NULL);

	/* OCTET_STRING with the actual hash */
	octet = ASN1_OCTET_STRING_new();
	if (octet == NULL) {
		X509_ALGOR_free(x509_algor);
		return NULL;
	}
	ASN1_OCTET_STRING_set(octet, buf, len);

	/* HASH structure containing algorithm + hash */
	hash = HASH_new();
	if (hash == NULL) {
		ASN1_OCTET_STRING_free(octet);
		X509_ALGOR_free(x509_algor);
		return NULL;
	}
	hash->hashAlgorithm = x509_algor;
	hash->dataHash = octet;

	/* DER encoded HASH */
	sz = i2d_HASH(hash, &p);
	if ((sz <= 0) || (p == NULL)) {
		HASH_free(hash);
		X509_ALGOR_free(x509_algor);
		return NULL;
	}

	/* Create the extension */
	ex = ext_new(nid, crit, p, sz);

	/* Clean up */
	OPENSSL_free(p);
	HASH_free(hash);

	return ex;
}

/*
 * Creates a x509v3 extension containing a nvcounter encapsulated in an ASN1
 * Integer
 *
 * Parameters:
 *   pex: OpenSSL extension pointer (output parameter)
 *   nid: extension identifier
 *   crit: extension critical (EXT_NON_CRIT, EXT_CRIT)
 *   value: nvcounter value
 *
 * Return: Extension address, NULL if error
 */
X509_EXTENSION *ext_new_nvcounter(int nid, int crit, int value)
{
	X509_EXTENSION *ex = NULL;
	ASN1_INTEGER *counter = NULL;
	unsigned char *p = NULL;
	int sz = -1;

	/* Encode counter */
	counter = ASN1_INTEGER_new();
	ASN1_INTEGER_set(counter, value);
	sz = i2d_ASN1_INTEGER(counter, NULL);
	i2d_ASN1_INTEGER(counter, &p);

	/* Create the extension */
	ex = ext_new(nid, crit, p, sz);

	/* Free objects */
	OPENSSL_free(p);
	ASN1_INTEGER_free(counter);

	return ex;
}

/*
 * Creates a x509v3 extension containing a public key in DER format:
 *
 *  SubjectPublicKeyInfo  ::=  SEQUENCE  {
 *       algorithm            AlgorithmIdentifier,
 *       subjectPublicKey     BIT STRING }
 *
 * Parameters:
 *   pex: OpenSSL extension pointer (output parameter)
 *   nid: extension identifier
 *   crit: extension critical (EXT_NON_CRIT, EXT_CRIT)
 *   k: key
 *
 * Return: Extension address, NULL if error
 */
X509_EXTENSION *ext_new_key(int nid, int crit, EVP_PKEY *k)
{
	X509_EXTENSION *ex = NULL;
	unsigned char *p = NULL;
	int sz = -1;

	/* Encode key */
	BIO *mem = BIO_new(BIO_s_mem());
	if (i2d_PUBKEY_bio(mem, k) <= 0) {
		ERR_print_errors_fp(stderr);
		return NULL;
	}
	p = (unsigned char *)OPENSSL_malloc(4096);
	sz = BIO_read(mem, p, 4096);

	/* Create the extension */
	ex = ext_new(nid, crit, p, sz);

	/* Clean up */
	OPENSSL_free(p);

	return ex;
}

ext_t *ext_get_by_opt(const char *opt)
{
	ext_t *ext = NULL;
	unsigned int i;

	/* Sequential search. This is not a performance concern since the number
	 * of extensions is bounded and the code runs on a host machine */
	for (i = 0; i < num_extensions; i++) {
		ext = &extensions[i];
		if (ext->opt && !strcmp(ext->opt, opt)) {
			return ext;
		}
	}

	return NULL;
}
