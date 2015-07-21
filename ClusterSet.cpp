// ClusterSet.cpp: implementation of the CClusterSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CACTUS.h"
#include "ClusterSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClusterSet::CClusterSet()
{
	this->cardinality = 0;
	this->elements = NULL;
}

CClusterSet::~CClusterSet()
{
	if( this->elements != NULL )
	{
		delete []this->elements;
	}
}

// ������� ������� ������� ������ �� ��������� �������-��������
CClusterSet::CopyFrom( CClusterProjectionSet* SourceCPS )
{
	if( this->elements != NULL )
	{
		delete []this->elements;
	}
	this->cardinality = SourceCPS->GetCardinality();

	this->elements = new CCluster*[this->cardinality];
	for( int i = 0; i < this->cardinality; i++ )
	{
		this->elements[i] = new CCluster;
		this->elements[i]->CopyFrom( SourceCPS->GetElement(i) );
	}

	return 1;
}
	
	
// ������ �� ���������-���������� ������� k-1-�� ������ � 
// �������-�������� k-�� ������, ��������� �������-����������
// k-�� ������
CClusterSet* CClusterSet::GenerateFromDec( CClusterProjectionSet* C_k, int** sigma_ij, int* max_attrib, int NumOfAttributes )
{
	CClusterSet* Res = new CClusterSet;

	CCluster* Cl;

	for( int i1 = 0; i1 < this->cardinality; i1++ )
	{
		for( int i2 = 0; i2 < C_k->GetCardinality(); i2++ )
		{
			Cl = this->elements[i1]->Augment( C_k->GetElement(i2), sigma_ij, max_attrib, NumOfAttributes );
			if( Cl != NULL )
			{
				Res->AddElement( Cl );
			}
		}
	}

//	delete Cl;

	return Res;
}

CClusterSet::AddElement( CCluster* Cl )
{
	CCluster** Elem_tmp = new CCluster*[this->cardinality];
	for( int i1 = 0; i1 < this->cardinality; i1++ )
	{
		Elem_tmp[i1] = this->elements[i1];
	}
	this->cardinality++;
	
	if( this->elements != NULL )
	{
		delete []this->elements;
	}

	this->elements = new CCluster*[this->cardinality];
	for( int i2 = 0; i2 < this->cardinality-1; i2++ )
	{
		this->elements[i2] = Elem_tmp[i2];
	}

	this->elements[this->cardinality-1] = Cl;

	return 1;
}

// ���������� ���������� ��������� �� ���������
CClusterSet::GetCardinality()
{
	return this->cardinality;
}
	

// ���������� ������� - num-�� �������
CCluster* CClusterSet::GetElement( int num )
{
	return this->elements[num];
}
	