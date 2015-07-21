// ClusterSet.h: interface for the CClusterSet class.
//
////////////////////////////////////////////////////////////////////// 

#ifndef ClusterProjectionSet_h
	#include "ClusterProjectionSet.h"
#endif

#ifndef Cluster_h
	#include "Cluster.h"
#endif

#define ClusterSet_h

class CClusterSet  
{
public:
	CClusterSet();
	virtual ~CClusterSet();

	CopyFrom( CClusterProjectionSet* SourceCPS );
	// создает кластер первого уровня из множества кластер-проекций

	CClusterSet* GenerateFromDec( CClusterProjectionSet* C_k, int** sigma_ij, int* max_attrib, int NumOfAttributes );
	// делает из кластеров кандидатов на один уровень ниже и 
	// кластер-проекций k-го уровня, множество кластер-кандидатов
	// k-го уровня

//	Validate( CDataSet *D );
	// проверка истинности кластеров

	AddElement( CCluster* Cl );
	// добавляет кластер во множетсов кластеров

	GetCardinality();
	// возвращает количество кластеров во множестве

	CCluster* GetElement( int num );
	// возвращает кластер - num-ый элемент
protected:
	int cardinality;
	CCluster** elements;
};
