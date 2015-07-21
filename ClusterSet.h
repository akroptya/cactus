// ClusterSet.h: interface for the CClusterSet class.
//
////////////////////////////////////////////////////////////////////// 

#ifndef ClusterProjectionSet_h
	#include "ClusterProjectionSet.h"
#endif

#ifndef Cluster_h
	#include "Cluster.h"
#endif

#define ClusterSet_h

class CClusterSet  
{
public:
	CClusterSet();
	virtual ~CClusterSet();

	CopyFrom( CClusterProjectionSet* SourceCPS );
	// ������� ������� ������� ������ �� ��������� �������-��������

	CClusterSet* GenerateFromDec( CClusterProjectionSet* C_k, int** sigma_ij, int* max_attrib, int NumOfAttributes );
	// ������ �� ��������� ���������� �� ���� ������� ���� � 
	// �������-�������� k-�� ������, ��������� �������-����������
	// k-�� ������

//	Validate( CDataSet *D );
	// �������� ���������� ���������

	AddElement( CCluster* Cl );
	// ��������� ������� �� ��������� ���������

	GetCardinality();
	// ���������� ���������� ��������� �� ���������

	CCluster* GetElement( int num );
	// ���������� ������� - num-�� �������
protected:
	int cardinality;
	CCluster** elements;
};
