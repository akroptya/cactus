// DistinguishSetSet.cpp: implementation of the CDistinguishSetSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CACTUS.h"
#include "DistinguishSetSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDistinguishSetSet::CDistinguishSetSet()
{
	this->FirstAttr = 0;
	this->SecondAttr = 0;
	this->elements = NULL;
	this->cardinality = 0;
}

CDistinguishSetSet::~CDistinguishSetSet()
{
	if( this->elements != NULL )
	{
		delete []this->elements;
	}
}

// ������������� � 0 ����� ����������� ��� ���� �������������� ��������
CDistinguishSetSet::SetAllSubsetFlagsToZero()
{
	for( int i = 0; i < this->cardinality; i++ )
	{
		this->elements[i]->SetSubsetFlagToZero();
	}

	return 1;
}


// ������������� � 0 �������� ������� ��� ���� �������������� ��������
CDistinguishSetSet::SetAllParticipationCountsToZero()
{
	for( int i = 0; i < this->cardinality; i++ )
	{
		this->elements[i]->SetParticipationCountToZero();
	}

	return 1;
}

// ���������� �������������� ��������� �� ��� ������
CDistinguishSet* CDistinguishSetSet::GetElement( int num )
{
	if( num < cardinality )
	{
		return this->elements[num];
	}
	else
	{
		return NULL;
	}
}	
	
// ���������� �������������� ������ ������� � ������� ��������� ��� ������� ���������
// �������������� ����������
CDistinguishSetSet::GetFirstAttr( )
{
	return this->FirstAttr;
}

CDistinguishSetSet::GetSecondAttr( )
{
	return this->SecondAttr;
}
	
// ��������� �������, �.�. �������������� ���������
CDistinguishSetSet::AddElement( CDistinguishSet* DS )
{
	this->cardinality++;
	
	CDistinguishSet** elements_tmp = new CDistinguishSet*[this->cardinality];
	for( int i = 0; i < (this->cardinality-1); i++ )
	{
		elements_tmp[i] = this->elements[i];
	}
	elements_tmp[this->cardinality-1] = DS;

	if( this->elements != NULL )
	{
		delete []this->elements;
	}
	this->elements = elements_tmp;

	return 1;
}	

// ������������� ��� ����� ��������� �������� �������������� ���������	
CDistinguishSetSet::SetAttributes( int FirstAttribute, int SecondAttr )
{
	this->FirstAttr = FirstAttribute;
	this->SecondAttr = SecondAttr;

	return 1;
}

//+
CDistinguishSetSet::GetCardinality()
{
	return this->cardinality;
}

