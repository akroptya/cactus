// DistinguishSetSet.h: interface for the CDistinguishSetSet class.
//
//////////////////////////////////////////////////////////////////////


#ifndef DistinguishSet_h
	#include "DistinguishSet.h"
#endif

#define DistinguishSetSet_h

class CDistinguishSetSet  
{
public:
	CDistinguishSetSet();
	virtual ~CDistinguishSetSet();

	SetAllSubsetFlagsToZero();		
	// устанавливает в 0 флаги подмножеств для всех различительных множеств

	SetAllParticipationCountsToZero();
	// устанавливает в 0 счетчики участия для всех различительных множеств

	CDistinguishSet* GetElement( int num );
	// возвращает различительной множество по его номеру

	GetFirstAttr( );
	GetSecondAttr( );
	// возвращают соответственно номера первого и второго атрибутов для которых построены
	// различительные мноджества

	AddElement( CDistinguishSet* DS );
	// добавляет элемент, т.е. различительное множество
	
	SetAttributes( int FirstAttribute, int SecondAttr );
	// устанавливает для каких атрибутов получены различительные множества

	GetCardinality();
	// возвращает мощность множества
protected:
	int FirstAttr;
	int SecondAttr;
	
	int cardinality;

	CDistinguishSet** elements;
};
