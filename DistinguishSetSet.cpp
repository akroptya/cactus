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

// устанавливает в 0 флаги подмножеств для всех различительных множеств
CDistinguishSetSet::SetAllSubsetFlagsToZero()
{
	for( int i = 0; i < this->cardinality; i++ )
	{
		this->elements[i]->SetSubsetFlagToZero();
	}

	return 1;
}


// устанавливает в 0 счетчики участия для всех различительных множеств
CDistinguishSetSet::SetAllParticipationCountsToZero()
{
	for( int i = 0; i < this->cardinality; i++ )
	{
		this->elements[i]->SetParticipationCountToZero();
	}

	return 1;
}

// возвращает различительной множество по его номеру
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
	
// возвращают соответственно номера первого и второго атрибутов для которых построены
// различительные мноджества
CDistinguishSetSet::GetFirstAttr( )
{
	return this->FirstAttr;
}

CDistinguishSetSet::GetSecondAttr( )
{
	return this->SecondAttr;
}
	
// добавляет элемент, т.е. различительное множество
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

// устанавливает для каких атрибутов получены различительные множества	
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

