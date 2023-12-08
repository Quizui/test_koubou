
#include "MathBit.h"

namespace SonikMathBit
{
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg(�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1�ｿｽ�ｽｿ�ｽｽ�ｾ後ン�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg)�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽJ�ｿｽ�ｽｿ�ｽｽE�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB8bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ吶ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ
	uint8_t OnBitCountFor8bit(uint8_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue = (BitValue & 0x55) + ( (BitValue >> 1) & 0x55 );
		BitValue = (BitValue & 0x33) + ( (BitValue >> 2) & 0x33 );

		return (BitValue & 0x0F) + ( (BitValue >> 4) & 0x0F );
	};

	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg(�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1�ｿｽ�ｽｿ�ｽｽ�ｾ後ン�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg)�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽJ�ｿｽ�ｽｿ�ｽｽE�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB16bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ吶ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ
	uint8_t OnBitCountFor16bit(uint16_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue = (BitValue & 0x5555) + ( (BitValue >> 1) & 0x5555 );
		BitValue = (BitValue & 0x3333) + ( (BitValue >> 2) & 0x3333 );
		BitValue = (BitValue & 0x0F0F) + ( (BitValue >> 4) & 0x0F0F );

		return (BitValue & 0x00FF) + ( (BitValue >> 8) & 0x00FF );
	};

	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg(�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1�ｿｽ�ｽｿ�ｽｽ�ｾ後ン�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg)�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽJ�ｿｽ�ｽｿ�ｽｽE�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB32bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ吶ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ
	uint8_t OnBitCountFor32bit(uint32_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		/*unsigned long OddBit; //0x55555555, 0x33333333, 0x0000FFFF �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ&�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽl
		unsigned long EvenBit; //0xAAAAAAAA, 0xCCCCCCCC, 0xFFFF0000 �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ&�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽl
		unsigned long MathValue; //�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽv�ｿｽ�ｽｿ�ｽｽl

		//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ鮟ｷ�ｽｼ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ後ン�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
		OddBit = ( BitValue & 0x55555555 );
		EvenBit = ( BitValue & 0xAAAAAAAA );

		//0xAAAAAAAA�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ&�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1bit�ｿｽ�ｽｿ�ｽｽE�ｿｽ�ｽｿ�ｽｽ�ｾ峨す�ｿｽ�ｽｿ�ｽｽt�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
		EvenBit = ( EvenBit >> 1 );

		//OddBit �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
		MathValue = OddBit + EvenBit;

		//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽv�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�縺ｳ繝難ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
		OddBit = ( MathValue & 0x33333333 );
		EvenBit = ( MathValue & 0xCCCCCCCC );

		//0xCCCCCCCC �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ & �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ2bit�ｿｽ�ｽｿ�ｽｽE�ｿｽ�ｽｿ�ｽｽ�ｾ峨す�ｿｽ�ｽｿ�ｽｽt�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB(0xC �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ 1 �ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾゅｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ代ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ2bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾゅ�ｮ繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ溘��)
		EvenBit = ( EvenBit >> 2 );

		//�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽOddBit�ｿｽ�ｽｿ�ｽｽ�ｾ画汚�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
		MathValue = OddBit + EvenBit;

		//�ｿｽ�ｽｿ�ｽｽ�ｾ�縺ｳ謳ｾ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽv�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
		OddBit = ( MathValue & 0x0F0F0F0F );
		EvenBit = ( MathValue & 0xF0F0F0F0 );

		//0xF0F0F0F0�ｿｽ�ｽｿ�ｽｽ�ｾ�謳ｾ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ4bit�ｿｽ�ｽｿ�ｽｽE�ｿｽ�ｽｿ�ｽｽ�ｾ峨す�ｿｽ�ｽｿ�ｽｽt�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB( 0xF �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ 1 �ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�闌ｨ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ 4bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾゅ�ｮ繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ溘��)
		EvenBit = ( EvenBit >> 4 );

		//�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽOddBit�ｿｽ�ｽｿ�ｽｽ�ｾ画汚�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
		MathValue = OddBit + EvenBit;

		//�ｿｽ�ｽｿ�ｽｽ�ｾ�縺ｳ謳ｾ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽv�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
		OddBit = (MathValue & 0x00FF00FF);
		EvenBit = ( MathValue & 0xFF00FF00 );

		//0xFF00FF00 �ｿｽ�ｽｿ�ｽｽ�ｾ�謳ｾ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ 8bit �ｿｽ�ｽｿ�ｽｽE�ｿｽ�ｽｿ�ｽｽ�ｾ峨す�ｿｽ�ｽｿ�ｽｽt�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
		EvenBit = (EvenBit >> 8);

		//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
		MathValue = OddBit + EvenBit;

		//�ｿｽ�ｽｿ�ｽｽ�ｾ�魃会ｽｿ�ｽｽ�ｾ後ン�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ謌撰ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽs�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
		OddBit = ( MathValue & 0x0000FFFF );
		EvenBit = ( MathValue & 0xFFFF0000 );

		//0xFFFF0000�ｿｽ�ｽｿ�ｽｽ�ｾ�謳ｾ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ16bit �ｿｽ�ｽｿ�ｽｽE�ｿｽ�ｽｿ�ｽｽ�ｾ峨す�ｿｽ�ｽｿ�ｽｽt�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
		EvenBit = (EvenBit >> 16);

		//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ翫ｑ�ｽｿ�ｽｽ�ｾ斐ｑ�ｽｿ�ｽｽ
		return (OddBit + EvenBit);*/

		//�ｿｽ�ｽｿ�ｽｽ�ｾ域�楢ｨ假ｿｽ�ｽｿ�ｽｽq�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ@�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽG�ｿｽ�ｽｿ�ｽｽL�ｿｽ�ｽｿ�ｽｽq
		BitValue = (BitValue & 0x55555555) + ( (BitValue >> 1) & 0x55555555 );
		BitValue = (BitValue & 0x33333333) + ( (BitValue >> 2) & 0x33333333 );
		BitValue = (BitValue & 0x0F0F0F0F) + ( (BitValue >> 4) & 0x0F0F0F0F );
		BitValue = (BitValue & 0x00FF00FF) + ( (BitValue >> 8) & 0x00FF00FF );

		return (BitValue & 0x0000FFFF) + ( (BitValue >> 16) & 0x0000FFFF);

   };

	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg(�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1�ｿｽ�ｽｿ�ｽｽ�ｾ後ン�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg)�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽJ�ｿｽ�ｽｿ�ｽｽE�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB64bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ吶ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｾ梧腸�ｽｿ�ｽｽ
	uint8_t OnBitCountFor64bit(uint64_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue = (BitValue & 0x5555555555555555) + ( (BitValue >> 1) & 0x5555555555555555 );
		BitValue = (BitValue & 0x3333333333333333) + ( (BitValue >> 2) & 0x3333333333333333 );
		BitValue = (BitValue & 0x0F0F0F0F0F0F0F0F) + ( (BitValue >> 4) & 0x0F0F0F0F0F0F0F0F );
		BitValue = (BitValue & 0x00FF00FF00FF00FF) + ( (BitValue >> 8) & 0x00FF00FF00FF00FF );
		BitValue = (BitValue & 0x0000FFFF0000FFFF) + ( (BitValue >> 16) & 0x0000FFFF0000FFFF );

		return (BitValue & 0x00000000FFFFFFFF) + ( (BitValue >> 32) & 0x00000000FFFFFFFF);
	};


	//�ｿｽ�ｽｿ�ｽｽw�ｿｽ�ｽｿ�ｽｽ髢ｧ�ｽｳ�ｿｽ�ｽｿ�ｽｽ鮟ｷ�ｽｽ�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ MSB(�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ瑚肩�ｽｿ�ｽｽ�ｾ泌､ｧ縺搾ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼繧托ｽｿ�ｽｽ) �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: MSB�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽl
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼縺ｮ繝難ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ後ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ悟�､
	//8bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	uint8_t GetMSBFor8bit(uint8_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue |= (BitValue >> 1);
		BitValue |= (BitValue >> 2);
		BitValue |= (BitValue >> 4);

		return OnBitCountFor8bit(BitValue) -1;
	};

	//�ｿｽ�ｽｿ�ｽｽw�ｿｽ�ｽｿ�ｽｽ髢ｧ�ｽｳ�ｿｽ�ｽｿ�ｽｽ鮟ｷ�ｽｽ�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ MSB(�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ瑚肩�ｽｿ�ｽｽ�ｾ泌､ｧ縺搾ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼繧托ｽｿ�ｽｽ) �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: MSB�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽl
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼縺ｮ繝難ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ後ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ悟�､
	//16bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	uint8_t GetMSBFor16bit(uint16_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue |= (BitValue >> 1);
		BitValue |= (BitValue >> 2);
		BitValue |= (BitValue >> 4);
		BitValue |= (BitValue >> 8);

		return OnBitCountFor16bit(BitValue) -1;
	};

	//�ｿｽ�ｽｿ�ｽｽw�ｿｽ�ｽｿ�ｽｽ髢ｧ�ｽｳ�ｿｽ�ｽｿ�ｽｽ鮟ｷ�ｽｽ�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ MSB(�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ瑚肩�ｽｿ�ｽｽ�ｾ泌､ｧ縺搾ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼繧托ｽｿ�ｽｽ) �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: MSB�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽl
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼縺ｮ繝難ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ後ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ悟�､
	//32bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	uint8_t GetMSBFor32bit(uint32_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue |= (BitValue >> 1);
		BitValue |= (BitValue >> 2);
		BitValue |= (BitValue >> 4);
		BitValue |= (BitValue >> 8);
		BitValue |= (BitValue >> 16);

		return OnBitCountFor32bit(BitValue) -1;
	};

	//�ｿｽ�ｽｿ�ｽｽw�ｿｽ�ｽｿ�ｽｽ髢ｧ�ｽｳ�ｿｽ�ｽｿ�ｽｽ鮟ｷ�ｽｽ�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ MSB(�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ瑚肩�ｽｿ�ｽｽ�ｾ泌､ｧ縺搾ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼繧托ｽｿ�ｽｽ) �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: MSB�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽl
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼縺ｮ繝難ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ後ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ悟�､
	//64bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	uint8_t GetMSBFor64bit(uint64_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue |= (BitValue >> 1);
		BitValue |= (BitValue >> 2);
		BitValue |= (BitValue >> 4);
		BitValue |= (BitValue >> 8);
		BitValue |= (BitValue >> 16);
		BitValue |= (BitValue >> 32);

		return OnBitCountFor64bit(BitValue) -1;
	};

	//�ｿｽ�ｽｿ�ｽｽw�ｿｽ�ｽｿ�ｽｽ髢ｧ�ｽｳ�ｿｽ�ｽｿ�ｽｽ鮟ｷ�ｽｽ�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ LSB(�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ瑚肩�ｽｿ�ｽｽ�ｾ疲得�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼繧托ｽｿ�ｽｽ) �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: LSB�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽl
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼縺ｮ繝難ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ後ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ悟�､
	//8bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	uint8_t GetLSBFor8bit(uint32_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue |= (BitValue << 1);
		BitValue |= (BitValue << 2);
		BitValue |= (BitValue << 4);

		return 8 - OnBitCountFor8bit(BitValue);

	};

	//�ｿｽ�ｽｿ�ｽｽw�ｿｽ�ｽｿ�ｽｽ髢ｧ�ｽｳ�ｿｽ�ｽｿ�ｽｽ鮟ｷ�ｽｽ�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ LSB(�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ瑚肩�ｽｿ�ｽｽ�ｾ疲得�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼繧托ｽｿ�ｽｽ) �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: LSB�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽl
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼縺ｮ繝難ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ後ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ悟�､
	//16bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	uint8_t GetLSBFor16bit(uint16_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue |= (BitValue << 1);
		BitValue |= (BitValue << 2);
		BitValue |= (BitValue << 4);
		BitValue |= (BitValue << 8);

		return 16 - OnBitCountFor16bit(BitValue);

	};

	//�ｿｽ�ｽｿ�ｽｽw�ｿｽ�ｽｿ�ｽｽ髢ｧ�ｽｳ�ｿｽ�ｽｿ�ｽｽ鮟ｷ�ｽｽ�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ LSB(�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ瑚肩�ｽｿ�ｽｽ�ｾ疲得�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼繧托ｽｿ�ｽｽ) �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: LSB�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽl
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼縺ｮ繝難ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ後ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ悟�､
	//32bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	uint8_t GetLSBFor32bit(uint32_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue |= (BitValue << 1);
		BitValue |= (BitValue << 2);
		BitValue |= (BitValue << 4);
		BitValue |= (BitValue << 8);
		BitValue |= (BitValue << 16);

		return 32 - OnBitCountFor32bit(BitValue);

	};

	//�ｿｽ�ｽｿ�ｽｽw�ｿｽ�ｽｿ�ｽｽ髢ｧ�ｽｳ�ｿｽ�ｽｿ�ｽｽ鮟ｷ�ｽｽ�ｿｽ�ｽｿ�ｽｽl�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ LSB(�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ瑚肩�ｽｿ�ｽｽ�ｾ疲得�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽr�ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼繧托ｽｿ�ｽｽ) �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ懊ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽB
	//�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ1: LSB�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ隰ｫ�ｽｾ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽl
	//�ｿｽ�ｽｿ�ｽｽ�ｾ溘ｑ�ｽｿ�ｽｽl: �ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ皮岼縺ｮ繝難ｿｽ�ｽｿ�ｽｽb�ｿｽ�ｽｿ�ｽｽg�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ�繧托ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ後ｑ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ�ｾ悟�､
	//64bit�ｿｽ�ｽｿ�ｽｽ�ｿｽ�ｽｿ�ｽｽ
	uint8_t GetLSBFor64bit(uint64_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue |= (BitValue << 1);
		BitValue |= (BitValue << 2);
		BitValue |= (BitValue << 4);
		BitValue |= (BitValue << 8);
		BitValue |= (BitValue << 16);
		BitValue |= (BitValue << 32);

		return 64 - OnBitCountFor64bit(BitValue);

	};


	uint8_t BitSwapFor8bit(uint8_t BitValue)
	{
		BitValue = ((BitValue & 0x55) << 1) | ((BitValue & 0xAA) >> 1);
		BitValue = ((BitValue & 0x33) << 2) | ((BitValue & 0xCC) >> 2);

		return ((BitValue & 0x0F) << 4) | ((BitValue & 0xF0) >> 4);
	};

	uint16_t BitSwapFor16bit(uint16_t BitValue)
	{
		BitValue = ((BitValue & 0x5555) << 1) | ((BitValue & 0xAAAA) >> 1);
		BitValue = ((BitValue & 0x3333) << 2) | ((BitValue & 0xCCCC) >> 2);
		BitValue = ((BitValue & 0x0F0F) << 4) | ((BitValue & 0xF0F0) >> 4);

		return ((BitValue & 0x00FF) << 8) | ((BitValue & 0xFF00) >> 8);
	};


	uint32_t BitSwapFor32bit(uint32_t BitValue)
	{
		BitValue = ((BitValue & 0x55555555) << 1) | ((BitValue & 0xAAAAAAAA) >> 1);
		BitValue = ((BitValue & 0x33333333) << 2) | ((BitValue & 0xCCCCCCCC) >> 2);
		BitValue = ((BitValue & 0x0F0F0F0F) << 4) | ((BitValue & 0xF0F0F0F0) >> 4);
		BitValue = ((BitValue & 0x00FF00FF) << 8) | ((BitValue & 0xFF00FF00) >> 8);

		return ((BitValue & 0x0000FFFF) << 16) | ((BitValue & 0xFFFF0000) >> 16);
	};

	uint64_t BitSwapFor64bit(uint64_t BitValue)
	{
		BitValue = ((BitValue & 0x5555555555555555) << 1) | ((BitValue & 0xAAAAAAAAAAAAAAAA) >> 1);
		BitValue = ((BitValue & 0x3333333333333333) << 2) | ((BitValue & 0xCCCCCCCCCCCCCCCC) >> 2);
		BitValue = ((BitValue & 0x0F0F0F0F0F0F0F0F) << 4) | ((BitValue & 0xF0F0F0F0F0F0F0F0) >> 4);
		BitValue = ((BitValue & 0x00FF00FF00FF00FF) << 8) | ((BitValue & 0xFF00FF00FF00FF00) >> 8);
		BitValue = ((BitValue & 0x0000FFFF0000FFFF) << 16) | ((BitValue & 0xFFFF0000FFFF0000) >> 16);

		return ((BitValue & 0x00000000FFFFFFFF) << 32) | ((BitValue & 0xFFFFFFFF00000000) >> 32);

	};


};

