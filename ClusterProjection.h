// ClusterProjection.h: interface for the CClusterProjection class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DistinguishSet_h
	#include "DistinguishSet.h"
#endif

#ifndef DistinguishSetSet_h
	#include "DistinguishSetSet.h"
#endif

#define ClusterProjection_h

class CClusterProjection  
{
public:
	CClusterProjection();
	virtual ~CClusterProjection();

	bool operator==( CClusterProjection RightSide );
	Create( int* buf, int level );
	
	Create( CDistinguishSet *S_i );
	// создает кластер-проекцию, заданную различительным множеством (равную ему)

	SetSubsetFlags( CDistinguishSetSet  *DSij );
	// устанавливает в 1 флаги подмножеств в DSij всех подмножеств данной 
	// кластер-проекции

	IncreaseParticipationCounts( CDistinguishSetSet *DSij, int num );
	// увеличивает счтечики участия всех подмножеств данной
	// кластер-проекции, входящих в DSij,  на num, 

	CClusterProjection* Intersect( CClusterProjection *IntersectCP );
	// возвращает кластер-проекцию, являющуюся пересечением данной 
	// с аргументом

	GetCardinality();
	// возвращает мощность кластер-проекции как множества

	GetElement( int num );
	// возвращает элемент с номером num

	SubsetIs( CDistinguishSet* DS );
	// возвращает 1 если заданное параметром различительное множество
	// является подмножеством кластер-проекции

	IsStronglyConnected( CClusterProjection* CP, int* sigma_ij, int max_i, int max_j );
	// проверяет, связана ли строго данная кластер-проекция,
	// с кластер-проекцией, заданной параметром,
	// по интер-сводке также заданной в параметрах
	// NumOfAttributes - количество атрибутов, чтоб можно было работать с 
	// 1 - да, 0 - нет

	Contain( int elem );
	// Проверяет, принадлежит ли заданный параметром элемент
	// данной кластер-проекции
	// 1 - yes, 0 - иначе

	bool EqualTo( CClusterProjection* CP );
	// Проверяет на равенство проекции указанной параметром
protected:

	int k;		// мощность кластер-проекции как множества
	int* body;  // сами элементв множества

};
