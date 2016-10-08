// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
	
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if(Elem >= 0 && Elem <= MaxPower)
    	return BitField.GetBit(Elem);
	throw -1;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if(Elem >= 0 && Elem <= MaxPower)
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if(Elem >= 0 && Elem <= MaxPower)
		BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	TBitField sse(s.BitField), fse(BitField);
    return ((fse & sse) == fse);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	TBitField sse(s.BitField), fse(BitField);
    return ((fse & sse) != fse);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TBitField bf(BitField);
	bf.SetBit(Elem);
	if(Elem >=0 && Elem < MaxPower)
		return TSet(bf);	
}

TSet TSet::operator-(const int Elem) // разность с элементом
{	
	TBitField bf(BitField);
	bf.ClrBit(Elem);
	if(Elem >=0 && Elem < MaxPower)
		return TSet(bf);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
	return TSet(~BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	s.MaxPower = s.BitField.GetLength();
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
