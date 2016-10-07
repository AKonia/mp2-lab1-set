// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
//	 Написана реализация во время выполнения лабораторной работы №1 Конаковым А.В.
//   Примечание: классы сделаны независимыми от длины беззнакового целого системы
//
// Битовое поле
// 

#include "tbitfield.h"

TBitField::TBitField(int len): BitLen(len)
{
	if(len <= 0) 
		throw -1;
	MemLen = ((len - 1 + sizeof(TELEM)<<3) >> (sizeof(TELEM)+2-sizeof(TELEM)>>2));
	pMem = new TELEM[MemLen];
	if(pMem != NULL)	
		for(int i = 0; i < MemLen; i++)
			pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	this->MemLen = bf.MemLen;
	this->BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	if(pMem != NULL)
		for(int i = 0; i < MemLen;i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if(n < 0) 
		throw -1;
	return ((n - 1 + sizeof(TELEM)<<3) >> (sizeof(TELEM)+2-sizeof(TELEM)>>2))-1; //чуть магии
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if(n < 0) 
		throw -1;
	return 1 << (n & ((sizeof(TELEM) << 3) - 1)); 
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if(!(n >= 0 && n < BitLen))
		throw -1;
	pMem[GetMemIndex(n)]  |= GetMemMask(n);	
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if(n >= 0 && n < BitLen)
	{
		pMem[GetMemIndex(n)]  &= ~GetMemMask(n);	
		return;
	}
	throw -1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if(n >= 0 && n < BitLen)
		return pMem[GetMemIndex(n)]  & GetMemMask(n);	
	throw -1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	if(MemLen != bf.MemLen)
	{
		if(pMem != 0)
			delete[] pMem;
		pMem = new TELEM[MemLen];
	}	
	for(int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if(BitLen != bf.BitLen)
		return 0;
	for(int i = 0; i < MemLen; i++)
		if(pMem[i] != bf.pMem[i])
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if(BitLen != bf.BitLen)
		return 1;
	for(int i = 0; i < MemLen; i++)
		if(pMem[i] != bf.pMem[i])
			return 1;	
	return 0; 
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int MaxBitLen = BitLen > bf.BitLen ? BitLen : bf.BitLen;
	TBitField buf(MaxBitLen);
	for(int i = 0; i < MemLen; i++)
		buf.pMem[i] |= pMem[i];
	for(int i = 0; i < bf.MemLen; i++)
		buf.pMem[i] |= bf.pMem[i];
	return buf;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int MaxBitLen = BitLen > bf.BitLen ? BitLen : bf.BitLen;
	TBitField buf(MaxBitLen);
	for(int i = 0; i < MemLen; i++)
		buf.pMem[i] |= pMem[i];
	for(int i = 0; i < bf.MemLen; i++)
		buf.pMem[i] &= bf.pMem[i];
	return buf;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField buf(BitLen);
	for(int i = 0; i<BitLen; i++)
		if(!GetBit(i)) 
			buf.SetBit(i);
	return buf;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{	// ограничение на ввод представляет собой 
	const int INPUT_MAX_SIZE = 256;
	char line[INPUT_MAX_SIZE];
	istr.get(line, INPUT_MAX_SIZE-1, ' ');
	int length = 0;
	while(line[length++]);
	bf = TBitField(length);
	for(int i = 0; i < length; i++)
		bf.SetBit(line[i]);
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for(int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
