// Cluster.h: interface for the CCluster class.
//
//////////////////////////////////////////////////////////////////////


// �������- ����� �������� �� ������� ��������
#ifndef ClusterProjection_h
	#include "ClusterProjection.h"
#endif


#define Cluster_h

class CCluster  
{
public:
	CCluster();
	virtual ~CCluster();

	SetDimension( int dim );
	AddAttributeValue( int attribute, int value );
	SetSupportThreshold( double new_threshold );

	CopyFrom( CClusterProjection* CP );
	// ������� ������� �� �������-��������

	AddProjection( CClusterProjection* CP );
	// ��������� �������� �� ��������� �������

	CCluster* Augment( CClusterProjection* CP, int** sigma_ij, int* max_attrib, int NumOfAttributes );
	// ����������, ���� ��� ��������, ����������
	// �������� �� �������-��������, ����������
	// ����������� �������, ��� NULL ���� ����������

	Getk();
	// ���������� ����������� �������� k

	CopyFrom( CCluster* SourceCl );
	// �������� �������-��������

	CClusterProjection* GetProjection( int num );
	// ���������� �������� �� �������� �������

	IncSupport();
	// ����������� ��������� �������� �� 1
	
	GetSupport();
	// ���������� ��������� ��������

	TrySupport( int* buf );
	// ��������� ������������ �� ������ �������, �������� ����������
	// ������ � ����������� ��������� ���� ��

	//+
	Contain( int* buf );
	// ���������, �������� �� ������ � ������ �������
	// ���� �� 1, ����� 0

	//+
	GetCardinalityOfSupportRange();
	// ���������� �������� ����������� ������������ ��������

protected:
	int k;
	CClusterProjection** projections;

	double alpha;	// ����� ��������� �������� �� ��������� ������
	int n;			// ���������� ���������
	int** cluster;	// ��������� �� ������ �� ������� �� ���������
	int* card_atr;	// �������� �������� �� ������� �� ���������

	int support;
};

