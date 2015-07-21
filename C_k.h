// C_k.h: interface for the CC_k class.
//
//////////////////////////////////////////////////////////////////////

#ifndef Clique_h
	#include "Clique.h"
#endif

#define C_k_h 

struct CClique_list
{
	CClique* value;
	CClique_list* prev;
	CClique_list* next;
};

class CC_k  
{
public:
	CC_k();
	CC_k( int level );
	virtual ~CC_k();

	SetLevel( int level );
	AddClique( int* buf );	// buf - последовательно записаны номера вершин
	
	Create( CC_k* Lkdec );

	GetCardinality();	// возвращает число клик в структуре
	CClique* GetClique( int i ); // возвращает указатель на i-ую клику
protected:
	// список клик
	CClique_list* bottom;

	int k;
	int card;
	
	CClique** cliques;

	int Cmpkdec2( int first, int second );
	RemoveNotSubset( CC_k* Lkdec, int* buf );
};
