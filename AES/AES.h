//AES.H

#ifndef _AES_H_
#define _AES_H_

#define AES_KEY_ROW_NUMBER 4
#define AES_KEY_COLUMN_NUMBER 4
#define AES_ROUND_COUNT 10

class AES// : public Encryption
{
public:
	AES(void);
	AES(BYTE* key);
	virtual ~AES(void);

	void Encrypt(BYTE *, BYTE *,size_t);
	void Decrypt(BYTE *, BYTE *,size_t);

private:

	BYTE swapbox[11][4][4];

	BYTE* Cipher(BYTE* input);
	BYTE* InvCipher(BYTE* input);

	BYTE* Cipher(void * input, size_t length);
	BYTE* InvCipher(void * input, size_t length);	

	void KeyExpansion(BYTE* key, BYTE w[][4][AES_KEY_COLUMN_NUMBER]);
	BYTE FFmul(BYTE a, BYTE b);

	void SubBytes(BYTE state[][AES_KEY_COLUMN_NUMBER]);
	void ShiftRows(BYTE state[][AES_KEY_COLUMN_NUMBER]);
	void MixColumns(BYTE state[][AES_KEY_COLUMN_NUMBER]);
	void AddRoundKey(BYTE state[][AES_KEY_COLUMN_NUMBER], BYTE k[][AES_KEY_COLUMN_NUMBER]);

	void InvSubBytes(BYTE state[][AES_KEY_COLUMN_NUMBER]);
	void InvShiftRows(BYTE state[][AES_KEY_COLUMN_NUMBER]);
	void InvMixColumns(BYTE state[][AES_KEY_COLUMN_NUMBER]);


};
#endif // _AES_H_
