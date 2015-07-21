// ClusterProjection.cpp: implementation of the CClusterProjection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CACTUS.h"
#include "ClusterProjection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//+
CClusterProjection::CClusterProjection()
{
	this->k = 0;
	this->body = NULL;
}

//+
CClusterProjection::~CClusterProjection()
{
	if( this->body != NULL )
	{
		delete []this->body;
	}
}

//
bool CClusterProjection::operator==( CClusterProjection RightSide )
{
	bool res = true;
	 
	for( int i = 0; i < k; i++ )
	{
		if( this->body[i] != RightSide.body[i] )
		{
			res = false;
		}
	}

	return res;
}

//
CClusterProjection::Create( int* buf, int level )
{
	if( this->body != NULL )
	{
		delete []this->body;
	}
	if( level >= 0 )
	{
		this->k = level;
		
		this->body = new int[k];
		for( int i = 0; i < k; i++ )
		{
			this->body[i] = buf[i];
		}
	}

	return 1; 
}

//+
// создает кластер-проекцию, заданную различительным множеством (равную ему)	
CClusterProjection::Create( CDistinguishSet* S_i )
{
	this->k = S_i->GetCardinality();
	if( this->body != NULL )
	{
		delete []this->body;
	}
	this->body = new int[this->k];
	for( int i = 0; i < this->k; i++ )
	{
		this->body[i] = S_i->GetElement(i);
	}

	return 1; 
}

// +
// устанавливает в 1 флаги подмножеств в DSij всех подмножеств данной 
// кластер-проекции
CClusterProjection::SetSubsetFlags( CDistinguishSetSet* DSij )
{
	CDistinguishSet* DS_tmp;

	for( int i = 0; i < DSij->GetCardinality(); i++ )
	{
		DS_tmp = DSij->GetElement(i); 

		if( this->SubsetIs(DS_tmp) == 1 )
		{
			DS_tmp->SetSubsetFlagTo1();
		}
	}

	return 1; 
}

// +
// увеличивает счтечики участия всех подмножеств данной
// кластер-проекции, входящих в DSij,  на num, 
CClusterProjection::IncreaseParticipationCounts( CDistinguishSetSet* DSij, int num )
{
	CDistinguishSet* DS_tmp;

	for( int i = 0; i < DSij->GetCardinality(); i++ )
	{
		DS_tmp = DSij->GetElement(i); 

		if( this->SubsetIs(DS_tmp) == 1 )
		{
			DS_tmp->IncreaseParticipationCount(num);
		}
	}

	return 1; 
}

// +
// возвращает кластер-проекцию, являющуюся пересечением данной 
// с аргументом
CClusterProjection* CClusterProjection::Intersect( CClusterProjection* IntersectCP )
{
	CClusterProjection* Res = new CClusterProjection;
	
	int* buf_tmp = new int[max( this->GetCardinality(), IntersectCP->GetCardinality() )];
	int count = 0;

	for( int i1 = 0; i1 < this->GetCardinality(); i1++ )
	{
		for( int i2 = 0; i2 < IntersectCP->GetCardinality(); i2++ )
		{
			if( this->GetElement(i1) == IntersectCP->GetElement(i2) )
			{
				buf_tmp[count++] = this->GetElement(i1);
				break;
			}
		}
	}

	Res->Create( buf_tmp, count );

	delete []buf_tmp;

	return Res; 
}

//+	
// возвращает мощность кластер-проекции как множества
CClusterProjection::GetCardinality()
{
	return this->k; 
}	

//+
CClusterProjection::GetElement( int num )
{
	if( num < this->k )
	{
		return this->body[num];
	}
	else
	{
		return -1;
	}
}

//+
// возвращает 1 если заданное параметром различительное множество
// является подмножеством кластер-проекции
CClusterProjection::SubsetIs( CDistinguishSet* DS )
{
	int res = 1;
	bool flag;

	for( int i1 = 0; i1 < DS->GetCardinality(); i1++ )
	{
		flag = false;

		for( int i2 = 0; i2 < this->GetCardinality(); i2++ )
		{
			if( DS->GetElement(i1) == this->GetElement(i2) )
			{
				flag = true;
				break;
			}
		}
		
		if( !flag )
		{
			res = 0;
			break;
		}
	}

	return res;
}

//
// проверяет, связана ли строго данная кластер-проекция,
// с кластер-проекцией, заданной параметром,
// по интер-сводке также заданной в параметрах
// 1 - да, 0 - нет
CClusterProjection::IsStronglyConnected( CClusterProjection* CP, int* sigma_ij, int max_i, int max_j )
{
	int res = 1;
	
	for( int i1 = 0; i1 < this->GetCardinality(); i1++ )
	{
		for( int i2 = 0; i2 < CP->GetCardinality(); i2++ )
		{
			if( sigma_ij[this->GetElement(i1)*max_j+CP->GetElement(i2)] <= 0 )
			{
				res = 0;
				break;
			}
		}
		if( res == 0 )
		{
			break;
		}
	}

	return res;
}

//+
// Проверяет, принадлежит ли заданный параметром элемент
// данной кластер-проекции
// 1 - yes, 0 - иначе
CClusterProjection::Contain( int elem )
{
	int res = 0;
	for( int i1 = 0; i1 < this->GetCardinality(); i1++ )
	{
		if(this->GetElement(i1) == elem )
		{
			res = 1;
			break;
		}
	}

	return res;
}
	
// Проверяет на равенство проекции указанной параметром	
bool CClusterProjection::EqualTo( CClusterProjection* CP )
{
	if( this->k == CP->GetCardinality() )
	{
		bool res = true;
		for( int i = 0; i < k; i++ )
		{
			if( this->body[i] != CP->body[i] )
			{
				res = false;
			}
		}

		return res; 
	}
	else
	{
		return false;
	}
}
	
