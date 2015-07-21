// DistinguishSet.h: interface for the CDistinguishSet class.
//
//////////////////////////////////////////////////////////////////////

#ifndef Clique_h
	#include "Clique.h"
#endif

#define DistinguishSet_h 

class CDistinguishSet  
{
public:
	CDistinguishSet();
	virtual ~CDistinguishSet();

	GetSubsetFlag( );
	// ���������� ��������� ����� ������������

	GetParticipationCount( );
	// ���������� �������� �������� �������

	FromClique( CClique* SourceClique );
	// ������� �������������� ��������� �� �����

	SetSubsetFlagToZero();		
	// ������������� � 0 ���� ������������

	SetParticipationCountToZero();
	// ������������� � 0 ������� �������

	GetCardinality();
	// ���������� �������� ���������

	GetElement( int num );
	// ���������� ������� � ������� num

	SetSubsetFlagTo1( );
	// ������������� ���� ������������ � 1

	IncreaseParticipationCount( int num );
	// ����������� ������� ������� �� num 

	AddElement( int elem );
	// ��������� ������� �� ���������

	Contain( int elem );
	// ���������, ���������� �� ������� �� ���������
	// 1 - ��, 0 - ���

	int cardinality;	// �������� ���������
	int* elements;
protected:
	int SubsetFlag;
	int ParticipationCount;

	
	
};
