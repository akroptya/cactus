// ClusterProjectionSet.h: interface for the CClusterProjectionSet class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ClusterProjection_h
	#include "ClusterProjection.h"
#endif

#define ClusterProjectionSet_h

class CClusterProjectionSet  
{
public:
	CClusterProjectionSet();
	virtual ~CClusterProjectionSet();
	
	AddElement( CClusterProjection* ClPr );
	// ��������� �������-�������� �� ���������
	
	GetCardinality();
	// ���������� �������� ���������

	CClusterProjection* GetElement( int num );
	// ���������� �������, ��������� � 0

	CopyFrom( CClusterProjectionSet* SourceCPS );
	// �������� �������� ���������� ���������

	InterSectionJoin( CClusterProjectionSet* JoinCPS );
	// ������������ �������� ������������� ����������� ���������
	// �������� ����������


protected:
	CClusterProjection** elements;
	int cardinality;
};
