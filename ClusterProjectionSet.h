// ClusterProjectionSet.h: interface for the CClusterProjectionSet class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ClusterProjection_h
	#include "ClusterProjection.h"
#endif

#define ClusterProjectionSet_h

class CClusterProjectionSet  
{
public:
	CClusterProjectionSet();
	virtual ~CClusterProjectionSet();
	
	AddElement( CClusterProjection* ClPr );
	// добавляет кластер-проекцию во множество
	
	GetCardinality();
	// возвращает мощность множества

	CClusterProjection* GetElement( int num );
	// возвращает элемент, нумерация с 0

	CopyFrom( CClusterProjectionSet* SourceCPS );
	// копирует заданное параметром множество

	InterSectionJoin( CClusterProjectionSet* JoinCPS );
	// присоеденяет опреаций пересекающего объединения множество
	// заданное параметром


protected:
	CClusterProjection** elements;
	int cardinality;
};
