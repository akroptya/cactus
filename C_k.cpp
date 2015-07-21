// C_k.cpp: implementation of the CC_k class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CACTUS.h"
#include "C_k.h"

#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// проверяет совпадение первых k-1 элементов
// заданных номерами двух клик,

int CC_k::RemoveNotSubset( CC_k* Lkdec, int* buf )
{
	int res = 0;
	CClique* fc;

	int* new_buf = (int*)new int[k-1];
	for( int count = 0; count < k; count++ )
	{
		if( res == 0 )
		{
			// убираем count компоненту из buf
			int i;
			int for_new_buf = 0;
			for( i = 0; i < count; i++ )
			{
				new_buf[for_new_buf++] = buf[i];
			}
			for( i = count+1; i < k; i++ )
			{
				new_buf[for_new_buf++] = buf[i];
			}

			// ищем полученное подмножество среди предидущих клик
			bool flag = false; // пока не нашли
			for( i = 0; i < Lkdec->GetCardinality(); i++ )
			{
				fc = Lkdec->GetClique( i );
				if( fc->CmpCliqueBuf( new_buf ) == 1 )
				{
					flag = true;
				}
			}
			if( flag == false )
			{
				res = 1;
				break;
			}
		}
	}

	return res;
}

CC_k::GetCardinality()
{
	return card;
}

int CC_k::Cmpkdec2( int first, int second ) 
{
	CClique* fc = GetClique( first );
	CClique* sc = GetClique( second );

	int res = 0;
	bool flag = true;

	for( int i = 0; (i <  k-1) && (flag == true); i++ )
	{
		if( fc->GetComponent(i) != sc->GetComponent(i) )
		{
			flag = false;
			if( fc->GetComponent(i) > sc->GetComponent(i) )
			{
				res = 1;
			}
			else
			{
				res = -1;
			}
		}
	}

	return res;
	// возвращает 0 - если равны
	// 1- если первая больше
	// -1 - если вторая больше
}

CC_k::Create( CC_k* Lkdec )
{
	// joining step we join L_{k-1} with L_{k-1}
	/*
	insert into C_k
	select p.item_1, p.item_2, ... , p.item_{k-1}, q.item_{k-1}
	from L_{k-1} p, L_{k-1} q
	where
	p.item_1 = q.item_1, ..., p.item_{k-2} = q.item_{k-2}, p.item_{k-1} < q.item_{k-1}
	*/

	int* buf = new int[k];
	
	for( int i = 0; i < Lkdec->GetCardinality(); i++ )
	{
		for( int j = i+1; j < Lkdec->GetCardinality(); j++ )
		{
			if( Lkdec->Cmpkdec2(i, j) == 0 )
			{
				for( int count = 0; count < k-2; count++ )
				{
					buf[count] = Lkdec->GetClique(i)->GetComponent(count);
				}
				buf[k-2] = __min( Lkdec->GetClique(i)->GetComponent(k-2), Lkdec->GetClique(j)->GetComponent(k-2) );
				buf[k-1] = __max( Lkdec->GetClique(i)->GetComponent(k-2), Lkdec->GetClique(j)->GetComponent(k-2) );
			
				// компоненты новой клики полностью найдены

				// проверить все ли подмножества входили в предидущую
				if( RemoveNotSubset( Lkdec, buf ) == 0)
				{
					AddClique( buf );
				}
			}
		}	
	}

	return 1;
}

CClique* CC_k::GetClique( int i )
{	
	return this->cliques[i];
}

CC_k::AddClique( int* buf )
{
	CClique** cliques_tmp = new CClique*[card];
	
	int i;
	for( i = 0; i < this->card; i++ )
	{
		cliques_tmp[i] = this->cliques[i];
	}

	if( this->cliques != NULL )
	{
		delete []this->cliques;
	}
	card++;

	cliques = new CClique*[card];

	for( i = 0; i < this->card-1; i++ )
	{
		this->cliques[i] = cliques_tmp[i];
	}

	CClique* NewCq = new CClique;
	NewCq->Create( buf, k );
	this->cliques[this->card-1] = NewCq;


/*
	// надо поставить в порядке упорядочивания

	if( bottom == NULL )
	{
		bottom =  (CClique_list*)new CClique_list;
		
		bottom->next = NULL;
		bottom->prev = NULL;
		bottom->value = (CClique*)new CClique;
		bottom->value->Create( buf, k );
	}
	else
	{
		CClique_list* CurCl = bottom;
			
		while( CurCl->next != NULL )
		{
			CurCl = CurCl->next;
		}
		CurCl->next = (CClique_list*)new CClique_list;
		CurCl->next->next = NULL;
		CurCl->next->prev = CurCl;
		CurCl->next->value = (CClique*)new CClique;
		CurCl->next->value->Create( buf, k );
	}*/

	return 1;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CC_k::CC_k()
{
	k = 0;
	card = 0;
	bottom = NULL;

	cliques = NULL;
}

CC_k::~CC_k()
{

}

CC_k::CC_k( int level )
{
	k = level;
	card = 0;
	bottom = NULL;
}

//+
CC_k::SetLevel( int level )
{
	k = level;

	return 1;
}