// DistinguishSet.h: interface for the CDistinguishSet class.
//
//////////////////////////////////////////////////////////////////////

#ifndef Clique_h
	#include "Clique.h"
#endif

#define DistinguishSet_h 

class CDistinguishSet  
{
public:
	CDistinguishSet();
	virtual ~CDistinguishSet();

	GetSubsetFlag( );
	// возвращает состояние флага подмножества

	GetParticipationCount( );
	// возвращает значения счетчика участия

	FromClique( CClique* SourceClique );
	// создает различительное множество по клике

	SetSubsetFlagToZero();		
	// устанавливает в 0 флаг подмножества

	SetParticipationCountToZero();
	// устанавливает в 0 счетчик участия

	GetCardinality();
	// возвращает мощность множества

	GetElement( int num );
	// возвращает элемент с номером num

	SetSubsetFlagTo1( );
	// Устанавливает флаг подмножества в 1

	IncreaseParticipationCount( int num );
	// Увеличивает счетчик участия на num 

	AddElement( int elem );
	// добавляет элемент во множество

	Contain( int elem );
	// проверяет, содержится ли элемент во множестве
	// 1 - да, 0 - нет

	int cardinality;	// мощность множества
	int* elements;
protected:
	int SubsetFlag;
	int ParticipationCount;

	
	
};
