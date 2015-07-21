// Clique.cpp: implementation of the CClique class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CACTUS.h"
#include "Clique.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClique::Create( int* buf, int level )
{
	k = level;

	if( body != NULL )
	{
		delete []body;
	}

	body = (int*)new int[k];

	for( int i = 0; i < k; i++ )
	{
		body[i] = buf[i];
	}

	return 1;
}

CClique::CClique( )
{
	k = 0;
	body = NULL;
}

CClique::CClique( int level )
{
	if( k != level )
	{
		body = (int*)new int[k];
		k = level;
	}
}


CClique::~CClique()
{
	if( body != NULL )
	{
		delete []body;
	}	
}

CClique::CmpCliqueBuf( int* buf )
{
	int res = 1;
	for(int i = 0; i < k; i++ )
	{
		if( buf[i] != body[i] )
		{
			res = 0;
		}
	}

	return res;
}

CClique::SetLevel( int new_level )
{
	k = new_level;
	if( body != NULL )
	{
		delete []body;
	}
	body = new int[k];
}

CClique::GetLevel( )
{
	return k;
}

CClique::SetComponent( int num, int value )
{
	if( num < k )
	{
		body[num] = value;
	}
	return 1;
}

CClique::GetComponent( int num )
{
	if( num < k )
	{
		return body[num];
	}
	else
	{
		return -1;
	}
}