// DataSet.h: interface for the CDataSet class.
//
//////////////////////////////////////////////////////////////////////

#ifndef C_k_h
	#include "C_k.h"
#endif

#ifndef DistinguishSet_h
	#include "DistinguishSet.h"
#endif

#ifndef DistinguishSetSet_h
	#include "DistinguishSetSet.h"
#endif

#ifndef ClusterProjectionSet_h
	#include "ClusterProjectionSet.h"
#endif

#ifndef ClusterSet_h
	#include "ClusterSet.h"
#endif

#define DataSet_h

class CDataSet  // набор экземпляров
{
public:
	CDataSet();
	virtual ~CDataSet();

	virtual LoadFromFile( const char* FileName );
	
	GetAttribute( int instance, int attribute );

	int* GetInstance( int instance );
	// возвращает кортеж под номером instance

	GetNumOfInstances();

	EvMaxAttribute( );
	EvThreshold( int FirstAttr, int SecondAttr );

	EvAllInterSummaries( );
	EvAllIntraSummaries( );

	EvInterSummaries( int FirstAttr, int SecondAttr );
	EvIntraSummaries( int FirstAttr, int SecondAttr );

	PPInterSummaries( );
	PPMaxAttributes( );
	PPIntraSummaries( );
	PPAllDistinguishingSets();
	PPAllClusterProjections();
	PPIntersectClusterProjections();
	PPC_1( CClusterSet* C_1 );
	PPFinalClusters( char* FileName );
	

	CDistinguishSetSet* CreateDistinguishingSets( int FirstAttr, int SecondAttr );

	CClusterProjectionSet* Extension( int FirstAttr, int SecondAttr );

	CClusterProjectionSet* ClusterProjectionsIntersection( int i );
	
	CACTUS( const char* FileName  );

	CClusterProjection* Extend( CDistinguishSet* S_i, int FirstAttr, int SecondAttr, int* SiblingStrength );
	// операция расширения, второй шаг.

	CDistinguishSet* BuildSiblingSet( CDistinguishSet* S_i, int FirstAttr, int SecondAttr, int* SiblingStrength );

	CClusterSet* BuildCandidateClusters();

	Validation();
	
	AllDistinguishingSets( );

	AllExtension( );
	// производит расширение кластер-проекций
	// из множеств для всех пар атрибутов

	AllClusterProjectionsIntersection(  );
	// находит все проекции полных кластеров на каждый из атрибутов
	// результат в C_i

	double GetIndependentDensity();
	// возвращает плотность при предположении о независимости
	// атрибутов

	int NumOfAttributes;
	int NumOfInstances;

	char** AttributesNames;
	char*  AttributesTypes;

	CClusterProjectionSet** C_i; 

	int* data_set;

	CClusterSet* ClCandidates;
	CClusterSet* FinalCusters;

	CDistinguishSetSet **DistinguishSetSet_ij;
	CClusterProjectionSet** ClusterProjectionSet_ij;
protected:

	int* max_attrib;
	int kappa;

	int** sigma_ij;
	int** sigma_ii_j;

	double alpha;

private:
};
