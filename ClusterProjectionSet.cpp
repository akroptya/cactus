// ClusterProjectionSet.cpp: implementation of the CClusterProjectionSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CACTUS.h"
#include "ClusterProjectionSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClusterProjectionSet::CClusterProjectionSet()
{
	this->elements = NULL;
	this->cardinality = 0;
}

CClusterProjectionSet::~CClusterProjectionSet()
{
	if( this->elements != NULL )
	{
		delete []this->elements;
	}
}

// добавляет кластер-проекцию во множество
CClusterProjectionSet::AddElement( CClusterProjection* ClPr )
{
	this->cardinality++;
	
	CClusterProjection** elements_tmp = new CClusterProjection*[this->cardinality];
	for( int i = 0; i < (this->cardinality-1); i++ )
	{
		elements_tmp[i] = this->elements[i];
	}
	elements_tmp[this->cardinality-1] = ClPr;

	if( this->elements != NULL )
	{
		delete []this->elements;
	}
	this->elements = elements_tmp;

	return 1;
}

// возвращает мощность множества
CClusterProjectionSet::GetCardinality()
{
	return this->cardinality;
}
	
// возвращает элемент, нумерация с 0
CClusterProjection* CClusterProjectionSet::GetElement( int num )
{
	if( num < this->cardinality )
	{
		return this->elements[num];
	}
	else
	{
		return NULL;
	}
}
	

// копирует заданное параметром множество
CClusterProjectionSet::CopyFrom( CClusterProjectionSet* SourceCPS )
{
	this->cardinality = SourceCPS->GetCardinality();
	if( this->elements != NULL )
	{
		delete []this->elements;
	}
	
	this->elements = new CClusterProjection*[this->cardinality];
	for( int i = 0; i < this->cardinality; i++ )
	{
		this->elements[i] = SourceCPS->GetElement(i);
	}

	return 1;
}

// присоеденяет опреаций пересекающего объединения множество
// заданное параметром
CClusterProjectionSet::InterSectionJoin( CClusterProjectionSet* JoinCPS )
{
	CClusterProjectionSet* Res = new CClusterProjectionSet;
	
	CClusterProjection* s; 

	for( int i1 = 0; i1 < this->cardinality; i1++ )
	{
		for( int i2 = 0; i2 < JoinCPS->GetCardinality(); i2++ )
		{
			s = this->GetElement(i1)->Intersect(JoinCPS->GetElement(i2));	
			if( s->GetCardinality() >= 1 )
			{
				bool already_exists = false;
				for( int count = 0; count < Res->GetCardinality(); count++ )
				{
					if( s->EqualTo(Res->GetElement(count)) )
					{
						already_exists = true;
					}
				}
				if( !already_exists )
				{
					Res->AddElement( s );
				}
			}
		}
	}
	
	this->CopyFrom( Res );
	delete Res;

	return 1;
}	
