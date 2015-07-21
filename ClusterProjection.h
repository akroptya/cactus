// ClusterProjection.h: interface for the CClusterProjection class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DistinguishSet_h
	#include "DistinguishSet.h"
#endif

#ifndef DistinguishSetSet_h
	#include "DistinguishSetSet.h"
#endif

#define ClusterProjection_h

class CClusterProjection  
{
public:
	CClusterProjection();
	virtual ~CClusterProjection();

	bool operator==( CClusterProjection RightSide );
	Create( int* buf, int level );
	
	Create( CDistinguishSet *S_i );
	// ������� �������-��������, �������� �������������� ���������� (������ ���)

	SetSubsetFlags( CDistinguishSetSet  *DSij );
	// ������������� � 1 ����� ����������� � DSij ���� ����������� ������ 
	// �������-��������

	IncreaseParticipationCounts( CDistinguishSetSet *DSij, int num );
	// ����������� �������� ������� ���� ����������� ������
	// �������-��������, �������� � DSij,  �� num, 

	CClusterProjection* Intersect( CClusterProjection *IntersectCP );
	// ���������� �������-��������, ���������� ������������ ������ 
	// � ����������

	GetCardinality();
	// ���������� �������� �������-�������� ��� ���������

	GetElement( int num );
	// ���������� ������� � ������� num

	SubsetIs( CDistinguishSet* DS );
	// ���������� 1 ���� �������� ���������� �������������� ���������
	// �������� ������������� �������-��������

	IsStronglyConnected( CClusterProjection* CP, int* sigma_ij, int max_i, int max_j );
	// ���������, ������� �� ������ ������ �������-��������,
	// � �������-���������, �������� ����������,
	// �� �����-������ ����� �������� � ����������
	// NumOfAttributes - ���������� ���������, ���� ����� ���� �������� � 
	// 1 - ��, 0 - ���

	Contain( int elem );
	// ���������, ����������� �� �������� ���������� �������
	// ������ �������-��������
	// 1 - yes, 0 - �����

	bool EqualTo( CClusterProjection* CP );
	// ��������� �� ��������� �������� ��������� ����������
protected:

	int k;		// �������� �������-�������� ��� ���������
	int* body;  // ���� �������� ���������

};
