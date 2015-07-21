// Cluster.h: interface for the CCluster class.
//
//////////////////////////////////////////////////////////////////////


// кластер- набор значений по каждому атрибуту
#ifndef ClusterProjection_h
	#include "ClusterProjection.h"
#endif


#define Cluster_h

class CCluster  
{
public:
	CCluster();
	virtual ~CCluster();

	SetDimension( int dim );
	AddAttributeValue( int attribute, int value );
	SetSupportThreshold( double new_threshold );

	CopyFrom( CClusterProjection* CP );
	// Создает кластер из кластер-проекции

	AddProjection( CClusterProjection* CP );
	// Добавляет проекцию на следующий атрибут

	CCluster* Augment( CClusterProjection* CP, int** sigma_ij, int* max_attrib, int NumOfAttributes );
	// Производит, если это возможно, расширение
	// кластера на кластер-проекцию, возвращает
	// расширенный кластер, или NULL если невозможно

	Getk();
	// возвращает размерность кластера k

	CopyFrom( CCluster* SourceCl );
	// копирует кластер-источник

	CClusterProjection* GetProjection( int num );
	// возвращает проекцию на заданный атрибут

	IncSupport();
	// увеличивает поддержку кластера на 1
	
	GetSupport();
	// возвращает поддержку кластера

	TrySupport( int* buf );
	// проверяет поддерживает ли данный кластер, заданный параметром
	// кортеж и увеличивает поддержку если да

	//+
	Contain( int* buf );
	// Проверяет, попадает ли кортеж в данный кластер
	// если да 1, иначе 0

	//+
	GetCardinalityOfSupportRange();
	// возвращает мощность декартового произведения проекций

protected:
	int k;
	CClusterProjection** projections;

	double alpha;	// порог поддержки кластера на множестве данных
	int n;			// количество атрибутов
	int** cluster;	// указатель на буферы по каждому из атрибутов
	int* card_atr;	// мощности множеств по каждому из атрибутов

	int support;
};

