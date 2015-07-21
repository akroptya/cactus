// DistinguishSet.cpp: implementation of the CDistinguishSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CACTUS.h"
#include "DistinguishSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDistinguishSet::CDistinguishSet()
{
	this->SubsetFlag = 0;
	this->ParticipationCount = 0;
	this->elements = NULL;
	this->cardinality = 0;
}

CDistinguishSet::~CDistinguishSet()
{
	if( this->elements != NULL )
	{
		delete []this->elements;
	}
}

// ���������� ��������� ����� ������������
CDistinguishSet::GetSubsetFlag( )
{
	return this->SubsetFlag;
}	

// ���������� �������� �������� �������
CDistinguishSet::GetParticipationCount( )
{
	return this->ParticipationCount;
}	

// ������� �������������� ��������� �� �����
CDistinguishSet::FromClique( CClique* SourceClique )
{
	this->SubsetFlag = 0;
	this->ParticipationCount = 0;

	if( this->elements != NULL )
	{
		delete []this->elements;
	}

	this->cardinality = SourceClique->GetLevel();
	this->elements = (int*)new int[this->cardinality];

	for( int i = 0; i < this->cardinality; i++ )
	{
		this->elements[i] = SourceClique->GetComponent(i);
	}
	return 1;
}	

// ������������� � 0 ���� ������������
CDistinguishSet::SetSubsetFlagToZero()
{
	this->SubsetFlag = 0;
	return 1;
}
	
// ������������� � 0 ������� �������
CDistinguishSet::SetParticipationCountToZero()
{
	this->ParticipationCount = 0;
	return 1;
}		

// ���������� �������� ���������
CDistinguishSet::GetCardinality()
{
	return this->cardinality;
}

// ���������� ������� � ������� num
CDistinguishSet::GetElement( int num )
{
	if( num < this->cardinality )
	{
		return this->elements[num];
	}
	else
	{
		return -1;
	}
}

//+
// ������������� ���� ������������ � 1
CDistinguishSet::SetSubsetFlagTo1()
{
	this->SubsetFlag = 1;
	return 1;
}	

//+
// ����������� ������� ������� �� num 
CDistinguishSet::IncreaseParticipationCount( int num )
{
	this->ParticipationCount += num;
	return 1;
}

//
// ��������� ������� �� ���������
CDistinguishSet::AddElement( int elem )
{
	int* elements_tmp = new int[this->cardinality];
	int i;
	for( i = 0; i < this->cardinality; i++ )
	{
		elements_tmp[i] = this->elements[i];
	}

	this->cardinality++;
	if( this->elements != NULL )
	{
		delete []this->elements;
	}
	
	this->elements = (int*)new int[this->cardinality];
	for( i = 0; i < this->cardinality-1; i++ )
	{
		 this->elements[i] = elements_tmp[i];
	}
	this->elements[this->cardinality-1] = elem;

	if( elements_tmp != NULL )
	{
		delete []elements_tmp;
	}

	return 1;
}	

CDistinguishSet::Contain( int elem )
{
	int res = 0;
	for( int i = 0; i < this->cardinality; i++ )
	{
		 if( this->elements[i] == elem )
		 {
			 res = 1;
			 break;
		 }
	}

	return res;
}