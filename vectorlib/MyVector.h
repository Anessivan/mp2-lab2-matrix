#ifndef _MY_VECTOR_
#define _MY_VECTOR_

#include <iostream>


template <class ValType>
class TVector
{
protected:
  ValType* pVector;
  int Size; // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector& v); // конструктор копирования
  ~TVector();
  int GetSize() { return Size; } // размер вектора
  int GetStartIndex() { return StartIndex; } // индекс первого элемента
  ValType& GetValue(int pos); // доступ с контролем индекса
  ValType& operator[](int pos); // доступ
  bool operator==(const TVector& v) const; // сравнение
  TVector& operator= (const TVector& v); // присванивание
  // скалярные операции
  TVector operator+ (const ValType& val); // прибавить скаляр
  TVector operator- (const ValType& val); // вычесть скаляр
  TVector operator* (const ValType& val); // умножить на скаляр
  // векторные операции
  TVector operator+ (const TVector& v); // сложение
  TVector operator- (const TVector& v); // вычитание
  ValType operator* (const TVector& v); // скалярное произведение
  // ввод-вывод
  friend istream& operator>>(istream& in, TVector& v)
  {
    for (int i = 0; i < v.Size - v.StartIndex; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream& out, const TVector& v)
  {
    for (int i = 0; i < v.Size; i++)
    {
      while (i < v.StartIndex)
      {
        out << 0 << ' ';
        i++;
      }
      out << v.pVector[i - v.StartIndex] << ' ';
    }
    return out;
  }
};




template<class ValType>
TVector<ValType>::TVector(int s, int si)
{
  Size = s;
  StartIndex = si;
  pVector = nullptr;
  pVector = new ValType[Size - StartIndex];
  if (pVector == nullptr) throw "Memmory Error";
}

template <class ValType>
TVector<ValType>::TVector(const TVector& v)  // конструктор копирования
{
  Size = v.Size;
  StartIndex = v.StartIndex;
  pVector = nullptr;
  pVector = new ValType[Size - StartIndex];
  if (pVector == nullptr) throw "Memmory Error";
  for (int i = 0; i < Size; i++)
    pVector[i] = v.pVector[i];
}

template <class ValType>
TVector<ValType>::~TVector()
{
  if (pVector != nullptr)
    delete[] pVector;
  pVector = nullptr;
}


template <class ValType>
int TVector<ValType>::GetSize()
{
  return Size;
}


template <class ValType>
ValType& TVector<ValType>::GetValue(int pos) // доступ с контролем индекса
{
  if (pos < 0 || pos > Size) throw "Wrong Index";
  return pVector[pos - StartIndex];
}

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
  return pVector[pos - StartIndex];
}


template <class ValType>
bool TVector<ValType>::operator==(const TVector<ValType>& v) const
{
  if (this == &v) return true;
  if (size != v.Size) return false;
  for (StartIndex != v.StartIndex) return false;
  for (int i = 0; i < Size - StartIndex; i++)
    if (pVector[i] != v.pVector[i]) return false;
  return true;
}

template<class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector<ValType>& v)
{
  if (this == &v) return *this;
  if ((Size - StartIndex) != (v.Size - v.StartIndex))
  {
    if (pVector != nullptr)
      delete[] pVector;
    Size = v.Size;
    pVector = nullptr;
    pVector = new ValType[Size - v.StartIndex];
    if (pVector == nullptr) throw "Memmory Error";
  }
  StartIndex = v.StartIndex;
  for (int i = 0; i < Size - StartIndex; i++)
    pVector[i] = v.pVector[i];
  return *this;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
  TVector<ValType> copy(*this);
  for (int i = 0; i < Size - StartIndex; i++)
    copy.pVector[i] += val;
  return copy;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
  TVector<ValType> copy(*this);
  copy = copy + ((-1) * val);
  return copy;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
  TVector<ValType> copy(*this);
  for (int i = 0; i < Size - StartIndex; i++)
    copy.pVector[i] *= val;
  return copy;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& v)
{
  if (Size != v.Size) throw "Sizes are not Equal";
  TVector<ValType> res(Size - StartIndex < v.Size - v.StartIndex ? v : *this);
  if (StartIndex <= v.StartIndex)                                                      //// Проверить случай равенста(возможна ошибка в форах
    for (int i = v.StartIndex - StartIndex; i < Size - StartIndex; i++)
      res.pVector[i] += pVector[i];
  else
    for (int i = StartIndex - v.StartIndex; i < v.Size - v.StartIndex; i++)
      res.pVector[i] += v.pVector[i];
  return res;
}

template<class ValType>
inline TVector<ValType> TVector<ValType>::operator-(const TVector& v)// проверить
{
  if (Size != v.Size) throw "Sizes are not Equal";
  TVector<ValType> res(Size - StartIndex < v.Size - v.StartIndex ? v : *this);
  if (StartIndex < v.StartIndex)
  {
    for (int i = 0; i < v.StartIndex - StartIndex; i++)
      res.pVector[i] = pVector[i];
    for (int i = v.StartIndex - StartIndex; i < v.Size - v.StartIndex; i++)
      res.pVector[i] = pVector[i] - v.pVector[i];
  }
  else
  {
    for (int i = 0; i < StartIndex - v.StartIndex; i++)
      res.pVector[i] = (-1) * pVector[i];
    for (int i = StartIndex - v.StartIndex; i < Size - StartIndex; i++)
      res.pVector[i] = pVector[i] - v.pVector[i];
  }
}

template<class ValType>
inline ValType TVector<ValType>::operator*(const TVector& v)
{
  if (Size != v.Size) throw "Sizes are not equal";
  ValType iSize = Size - (StartIndex > v.StartIndex ? StartIndex : v.StartIndex);
  ValType res = 0;
  for (int i = 0; i < iSize; i++)
    res += pVector[Size - StartIndex - 1 - i] * v.pVector[Size - v.StartIndex - 1 - i];
  return res;
}



template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);
  TMatrix(const TMatrix& mt);
  TMatrix(const TVector<TVector<ValType> >& mt);
  bool operator==(const TMatrix& mt)const;
  bool operator!=(const TMatrix& mt) const;
  TMatrix& operator= (const TMatrix& mt);
  TMatrix operator+ (const TMatrix& mt);
  TMatrix operator- (const TMatrix& mt);
  friend istream& operator>>(istream& in, TMatrix& mt);
  friend ostream& operator<<(ostream& out, const TMatrix& mt);
};

template<class ValType>
inline TMatrix<ValType>::TMatrix(int s)
{
  if (MAX_MATRIX_SIZE < Size) throw "Wrong argument";
  for (int i = 0; i < Size; i++)
    pVector[i] = TVector<ValType>(Size, i);
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
  TVector<TVector<ValType> >(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
  TVector<TVector<ValType> >(mt) {}


template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
  if (this != &mt)
  {
    if (Size != mt.Size) return false;
    for (int i = 0; i < Size; i++)
      if (pVector[i] != mt.pVector[i]) return false;
  }
  return true;
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
  return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
  if (this != &mt)
  {
    delete[] pVector;
    Size = mt.Size;
    pVector = new TVector<ValType>[Size];
    for (int i = 0; i < Size; i++)
      pVector[i] = mt.pVector[i];
  }
  return *this;
}


template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
  if (Size != mt.Size) throw "Sizes are Not Equal");
  TMatrix<ValType> tmp(*this);
  for (int i = 0; i < Size; i++)
    tmp.pVector[i] = tmp.pVector[i] + mt.pVector[i];
  return tmp;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
  if (Size != mt.Size) throw "Sizes are Not Equal";
  TMatrix<ValType> tmp(*this);
  for (int i = 0; i < Size; i++)
    tmp.pVector[i] = tmp.pVector[i] - mt.pVector[i];
  return tmp;
}

#endif