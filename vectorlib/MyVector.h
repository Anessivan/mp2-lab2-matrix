#ifndef _MY_VECTOR_
#define _MY_VECTOR_

#include <iostream>


using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector
{
protected:
  ValType* pVector;
  int Size;       // ������ �������
  int StartIndex; // ������ ������� �������� �������
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector& v);                // ����������� �����������
  ~TVector();
  int GetSize() { return Size; } // ������ �������
  int GetStartIndex() { return StartIndex; } // ������ ������� ��������
  ValType& operator[](int pos);             // ������
  bool operator==(const TVector& v) const;  // ���������
  bool operator!=(const TVector& v) const;  // ���������
  TVector& operator=(const TVector& v);     // ������������

  // ��������� ��������
  TVector  operator+(const ValType& val);   // ��������� ������
  TVector  operator-(const ValType& val);   // ������� ������
  TVector  operator*(const ValType& val);   // �������� �� ������

  // ��������� ��������
  TVector  operator+(const TVector& v);     // ��������
  TVector  operator-(const TVector& v);     // ���������
  ValType  operator*(const TVector& v);     // ��������� ������������

  // ����-�����
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

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
  if ((s < 0 || MAX_VECTOR_SIZE < s)
    || (si < 0 || s < si)) throw  ("Illegal arguments");
  Size = s;
  StartIndex = si;
  pVector = nullptr;
  pVector = new ValType[Size - StartIndex];
  if (pVector == nullptr) throw "Memmory Error";
  for (int i = 0; i < Size - StartIndex; i++)
    pVector[i] = 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> //����������� �����������
TVector<ValType>::TVector(const TVector<ValType>& v) : Size(v.Size), StartIndex(v.StartIndex)
{
  pVector = new ValType[Size - StartIndex];
  for (int i = 0; i < Size - StartIndex; i++)
    pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
  if (pVector != nullptr)
  delete[] pVector;
  pVector = nullptr;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos)
{
  if (pos < 0 || Size <= pos) throw  ("Negative or too large index");
  ValType A = 0;
  if (pos < StartIndex) throw "Wrong index";
  return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector& v) const
{
  if (this != &v)
  {
    if (Size != v.Size || StartIndex != v.StartIndex) return false;
    for (int i = 0; i < Size - StartIndex; i++)
      if (pVector[i] != v.pVector[i]) return false;
  }
  return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector& v) const
{
  return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
  if (this != &v)
  {
    if(pVector != nullptr)
    delete[] pVector;
    pVector = nullptr;
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size - StartIndex];
    if (pVector == nullptr) throw "Memmory Error";
    for (int i = 0; i < Size - StartIndex; i++)
      pVector[i] = v.pVector[i];
  }
  return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
  TVector<ValType> tmp(*this);
  for (int i = 0; i < Size - StartIndex; i++)
    tmp.pVector[i] += val;
  return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
  TVector<ValType> tmp(*this);
  for (int i = 0; i < Size - StartIndex; i++)
    tmp.pVector[i] -= val;
  return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
  TVector<ValType> tmp(*this);
  for (int i = 0; i < Size - StartIndex; i++)
    tmp.pVector[i] *= val;
  return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
  if (Size != v.Size || StartIndex != v.StartIndex) throw "Sizes or StartIndexes are not equal";
  TVector<ValType> tmp(*this);
  for (int i = 0; i < Size - StartIndex; i++)
    tmp.pVector[i] += v.pVector[i];
  return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
  if (Size != v.Size || StartIndex != v.StartIndex) throw  ("Sizes or StartIndexes are not equal");
  TVector<ValType> tmp(*this);
  for (int i = 0; i < Size - StartIndex; i++)
    tmp.pVector[i] -= v.pVector[i];
  return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
  if (Size != v.Size) throw  ("Sizes are not equal");
  ValType iSize = Size - (StartIndex > v.StartIndex ? StartIndex : v.StartIndex);
  ValType sum = 0;
  for (int i = 0; i < iSize; i++)
    sum += pVector[Size - StartIndex - 1 - i] * v.pVector[Size - v.StartIndex - 1 - i];
  return sum;
} /*-------------------------------------------------------------------------*/


// ����������������� �������
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);
  TMatrix(const TMatrix& mt);                    // �����������
  TMatrix(const TVector<TVector<ValType> >& mt); // �������������� ����
  bool operator==(const TMatrix& mt) const;      // ���������
  bool operator!=(const TMatrix& mt) const;      // ���������
  TMatrix& operator= (const TMatrix& mt);        // ������������
  TMatrix  operator+ (const TMatrix& mt);        // ��������
  TMatrix  operator- (const TMatrix& mt);        // ���������

  // ���� / �����
  friend istream& operator>>(istream& in, TMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream& out, const TMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
  if (MAX_MATRIX_SIZE < s) throw ("Illegal argument");
  for (int i = 0; i < s; i++)
    pVector[i] = TVector<ValType>(s, i);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ����������� �����������
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // ����������� �������������� ����
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // ���������
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
  if (this != &mt)
  {
    if (TMatrix->Size != mt.Size) return false;
    for (int i = 0; i < Size; i++)
      if (pVector[i] != mt.pVector[i]) return false;
  }
  return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
  return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
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
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
  if (Size != mt.Size) throw  ("Sizes are not equal");
  TMatrix<ValType> tmp(*this);
  for (int i = 0; i < Size; i++)
    tmp.pVector[i] = tmp.pVector[i] + mt.pVector[i];
  return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
  if (Size != mt.Size) throw  ("Sizes are not equal");
  TMatrix<ValType> tmp(*this);
  for (int i = 0; i < Size; i++)
    tmp.pVector[i] = tmp.pVector[i] - mt.pVector[i];
  return tmp;
}

#endif
