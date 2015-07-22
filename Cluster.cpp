// Cluster.cpp: implementation of the CCluster class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CACTUS.h"
#include "Cluster.h"

#include "DataSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCluster::CCluster()
{
	this->k = 0;
	this->projections = NULL;

	this->n = 0;
	this->cluster = NULL;
	this->card_atr = NULL;
	this->alpha = 2;

	this->support = 0;
}

CCluster::~CCluster()
{
	if( this->cluster != NULL )
	{
		delete []this->cluster;
	}
	if( this->card_atr != NULL )
	{
		delete []this->card_atr;
	}
	if( this->projections != NULL )
	{
		delete []this->projections;
	}
}

CCluster::SetDimension( int dim )
{
	this->n = dim;
	this->cluster = (int**)new int*[n];
	this->card_atr = (int*)new int[n];

	for( int i = 0; i < n; i++ )
	{
		this->cluster[i] = NULL;
		this->card_atr[i] = 0;
	}
	
	return 1;
}

CCluster::SetSupportThreshold( double new_threshold )
{
	this->alpha = new_threshold;

	return 1;
}

//+
CCluster::AddProjection( CClusterProjection* CP )
{
	CClusterProjection** projections_tmp = NULL;
	projections_tmp = new CClusterProjection*[k];

	int i;
	for( i = 0; i < k; i++ )
	{
		projections_tmp[i] = this->projections[i];
	}
	
	k++;
	if( this->projections != NULL )
	{
		delete []this->projections;
	}

	this->projections = new CClusterProjection*[k];
	for( i = 0; i < k-1; i++ )
	{
		this->projections[i] = projections_tmp[i];
	}
	this->projections[k-1] = CP;

	if( projections_tmp != NULL )
	{
		delete []projections_tmp;
	}
}

//    +
// Производит, если это возможно, расширение
// кластера на кластер-проекцию, возвращает
// расширенный кластер, или NULL если невозможно
CCluster* CCluster::Augment( CClusterProjection* CP, int** sigma_ij, int* max_attrib, int NumOfAttributes )
{
	bool flag = true;
	for( int i = 0; i < k; i++ )
	{ 
		if( this->projections[i]->IsStronglyConnected( CP, sigma_ij[i*NumOfAttributes + k], max_attrib[i], max_attrib[k] ) != 1 )
		{	
			flag = false;
			break;
		}
	}

	if( flag )
	{
		CCluster* Res = new CCluster;
		Res->CopyFrom( this );	
		Res->AddProjection( CP );
		return Res;
	}
	else
	{
		return NULL;
	}
}

//+
CCluster::CopyFrom( CCluster* SourceCl )
{
	this->k = SourceCl->Getk();
	
	if( this->projections != NULL )
	{
		delete []this->projections;
	}
	this->projections = new CClusterProjection*[this->k];

	for( int i = 0; i < this->k; i++ )
	{
		this->projections[i] = SourceCl->GetProjection(i);
	}
	return 1;
}

CCluster::CopyFrom( CClusterProjection* CP )
{
	this->k = 0;
	if( this->projections != NULL )
	{
		delete []this->projections;
	}

	this->AddProjection( CP );
	return 1;
}

//+
CCluster::Getk()
{
	return this->k;
}

//+
CClusterProjection* CCluster::GetProjection( int num )
{
	return this->projections[num];
}

//+
// увеличивает поддержку кластера на 1
CCluster::IncSupport()
{
	this->support++;
	return 1;
}
	
//+
// возвращает поддержку кластера	
CCluster::GetSupport()
{
	return this->support;
}	


// проверяет поддерживает ли данный кластер, заданный параметром
// кортеж и увеличивает поддержку если да
CCluster::TrySupport( int* buf )
{
	if( this->Contain( buf ) == 1 )
	{
		this->IncSupport();
	}
	return 1;
}

//+
// Проверяет, попадает ли кортеж в данный кластер
// если да 1, иначе 0
CCluster::Contain( int* buf )
{
	int res = 1;
	for( int i = 0; i < this->k; i++ )
	{
		if( this->projections[i]->Contain(buf[i]) != 1 )
		{
			res = 0;
			break;
		}
	}
	return res;
}

//+
// возвращает мощность декартового произведения проекций
CCluster::GetCardinalityOfSupportRange()
{
	int res = 1;
	for( int i = 0; i < this->k; k++ )
	{
		res *= this->projections[i]->GetCardinality();
	}
	return res;
}
	



CCluster::AddAttributeValue( int attribute, int value )
{
	int* buf;
	if( attribute <= n )
	{
		int* tmp;
		if( this->cluster[attribute] != NULL )
		{
			buf = this->cluster[attribute];
			tmp = (int*)new int[this->card_atr[attribute]+1];
			
			int i;
			for( i = 0; i < this->card_atr[attribute]; i++ )
			{
				tmp[i] = buf[i];
			}
			
			tmp[this->card_atr[attribute]] = value;
			buf = NULL;
			delete []this->cluster[attribute];
			this->card_atr[attribute]++;
			this->cluster[attribute] = (int*)new int[this->card_atr[attribute]];
			buf = this->cluster[attribute];
			for( i = 0; i < this->card_atr[attribute]; i++ )
			{
				buf[i] = tmp[i];
			}
			buf = NULL;
		}
		else
		{
			this->cluster[attribute] = (int*)new int[1];
			buf = this->cluster[attribute];
			buf[0] = value;
			this->card_atr[attribute] = 1;
		}
	}

	return 1;
}