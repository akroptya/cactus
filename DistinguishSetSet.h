// DistinguishSetSet.h: interface for the CDistinguishSetSet class.
//
//////////////////////////////////////////////////////////////////////


#ifndef DistinguishSet_h
	#include "DistinguishSet.h"
#endif

#define DistinguishSetSet_h

class CDistinguishSetSet  
{
public:
	CDistinguishSetSet();
	virtual ~CDistinguishSetSet();

	SetAllSubsetFlagsToZero();		
	// ������������� � 0 ����� ����������� ��� ���� �������������� ��������

	SetAllParticipationCountsToZero();
	// ������������� � 0 �������� ������� ��� ���� �������������� ��������

	CDistinguishSet* GetElement( int num );
	// ���������� �������������� ��������� �� ��� ������

	GetFirstAttr( );
	GetSecondAttr( );
	// ���������� �������������� ������ ������� � ������� ��������� ��� ������� ���������
	// �������������� ����������

	AddElement( CDistinguishSet* DS );
	// ��������� �������, �.�. �������������� ���������
	
	SetAttributes( int FirstAttribute, int SecondAttr );
	// ������������� ��� ����� ��������� �������� �������������� ���������

	GetCardinality();
	// ���������� �������� ���������
protected:
	int FirstAttr;
	int SecondAttr;
	
	int cardinality;

	CDistinguishSet** elements;
};
