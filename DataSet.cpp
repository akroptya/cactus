// DataSet.cpp: implementation of the CDataSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CACTUS.h"
#include "DataSet.h"

#include "string.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataSet::CDataSet()
{

}

CDataSet::~CDataSet()
{

}

CDataSet::GetAttribute( int instance, int attribute )
{
	return *(data_set + instance*NumOfAttributes + attribute);
}

CDataSet::GetNumOfInstances()
{
	return NumOfInstances; 
}

// посчитать максимальные значения атрибутов - т.е. границы области их значений
CDataSet::EvMaxAttribute( )
{
	this->max_attrib = new int[NumOfAttributes];

	int i;
	for( i = 0; i < this->NumOfAttributes; i++ )
	{
		this->max_attrib[i] = 0;
		for(int j = 0; j < this->NumOfInstances; j++ )
		{
			if( this->GetAttribute(j,i) > this->max_attrib[i] )
			{
				this->max_attrib[i] = this->GetAttribute(j,i);
			}
		}
	}

	for( i = 0; i < NumOfAttributes; i++ )
	{
		this->max_attrib[i]++;
	}
	return 1;
}



CDataSet::PPMaxAttributes( )
{
	FILE* fp = fopen( "test\\maxattrib.txt", "w" );

	for( int i = 0; i < this->NumOfAttributes; i++ )
	{
		fprintf( fp, "Attibute # %d  - %d\n", i, this->max_attrib[i] );
	}
	fclose(fp);

	return 1;
}

CDataSet::PPInterSummaries( )
{
	FILE* fp = fopen( "test\\intersum.txt", "w" );

	for( int FirstAttr = 0; FirstAttr < this->NumOfAttributes; FirstAttr++ )
	{
		for( int SecondAttr = 0; SecondAttr < this->NumOfAttributes; SecondAttr++ )
		{
			if( FirstAttr != SecondAttr )
			{
				int* summary = sigma_ij[FirstAttr*NumOfAttributes + SecondAttr];
				
				int i = 0;
				int j = 0;

				fprintf( fp, "\\Sigma_%d %d \n", FirstAttr, SecondAttr );

				for( i = 0; i < max_attrib[FirstAttr]; i++ )
				{
					for( j = 0; j < max_attrib[SecondAttr]; j++ )
					{
						fprintf(fp, "%d\t", summary[i*max_attrib[SecondAttr]+j]);	
					}
					fprintf( fp, "\n" );
				}	
				fprintf( fp, "\n" );
			}
		}
	}

	fclose(fp);

	return 1;
}

CDataSet::PPIntraSummaries(  )
{

	FILE* fp = fopen( "test\\intrasum.txt", "w" );

	for( int FirstAttr = 0; FirstAttr < this->NumOfAttributes; FirstAttr++ )
	{
		for( int SecondAttr = 0; SecondAttr < this->NumOfAttributes; SecondAttr++ )
		{
			if( FirstAttr != SecondAttr )
			{
				int* summary = sigma_ii_j[FirstAttr*NumOfAttributes + SecondAttr];
				
				int i = 0;
				int j = 0;

				fprintf( fp, "\\Sigma_%d %d ^ %d \n", FirstAttr, FirstAttr, SecondAttr );

				for( i = 0; i < max_attrib[FirstAttr]; i++ )
				{
					for( j = 0; j < max_attrib[FirstAttr]; j++ )
					{
						if( i != j)
						{
							fprintf(fp, "%d\t", summary[i*max_attrib[FirstAttr]+j]);	
						}
						else
						{
							fprintf(fp, "*\t" );
						}
					}
					fprintf( fp, "\n" );
				}	
				fprintf( fp, "\n" );
			}
		}
	}
	
	fclose(fp);

	return 1;
}

CDataSet::PPAllDistinguishingSets( )
{
	FILE* fp = fopen( "test\\distinguish.txt", "w" );

	for( int i1 = 0; i1 < this->NumOfAttributes; i1++ )
	{
		for( int i2 = 0; i2 < this->NumOfAttributes; i2++ )
		{	
			if( (i1 != i2) && (this->DistinguishSetSet_ij[i1*this->NumOfAttributes+i2] != NULL) )
			{
				fprintf( fp, "Distinguishing sets on %d  respect to %d\n", i1, i2 );
				fprintf( fp, "Cardinality %d\n", this->DistinguishSetSet_ij[i1*this->NumOfAttributes+i2]->GetCardinality() );
				for( int j1 = 0; j1 < this->DistinguishSetSet_ij[i1*this->NumOfAttributes+i2]->GetCardinality(); j1++ )			
				{
					fprintf( fp, "Distinguishing set # %d \n", j1 );
					for( int j2 = 0; j2 < this->DistinguishSetSet_ij[i1*this->NumOfAttributes+i2]->GetElement(j1)->GetCardinality(); j2++ )	
					{
						fprintf( fp, "%d, ", this->DistinguishSetSet_ij[i1*this->NumOfAttributes+i2]->GetElement(j1)->GetElement(j2) );		
					}
					fprintf( fp, "\n" );
				}
				fprintf( fp, "\n" );
			}
			fprintf( fp, "\n" );
		}
	}
	fclose(fp);

	return 1;
}

CDataSet::PPAllClusterProjections()
{
	FILE* fp = fopen( "test\\projections.txt", "w" );

	for( int i1 = 0; i1 < this->NumOfAttributes; i1++ )
	{
		for( int i2 = 0; i2 < this->NumOfAttributes; i2++ )
		{	
			if( (i1 != i2) && (this->ClusterProjectionSet_ij[i1*this->NumOfAttributes+i2] != NULL) )
			{
				fprintf( fp, "Cluster projections on %d  respect to %d\n", i1, i2 );
				fprintf( fp, "Cardinality %d\n", this->ClusterProjectionSet_ij[i1*this->NumOfAttributes+i2]->GetCardinality() );
				for( int j1 = 0; j1 < this->ClusterProjectionSet_ij[i1*this->NumOfAttributes+i2]->GetCardinality(); j1++ )			
				{
					fprintf( fp, "Cluster projection # %d \n", j1 );
					for( int j2 = 0; j2 < this->ClusterProjectionSet_ij[i1*this->NumOfAttributes+i2]->GetElement(j1)->GetCardinality(); j2++ )	
					{
						fclose(fp);
						fp = fopen( "test\\projections.txt", "a" );
						fprintf( fp, "%d, ", this->ClusterProjectionSet_ij[i1*this->NumOfAttributes+i2]->GetElement(j1)->GetElement(j2) );		
					}
					fprintf( fp, "\n" );
				}
				fprintf( fp, "\n" );
			}
			fprintf( fp, "\n" );
		}
	}

	fclose(fp);

	return 1;
}

CDataSet::PPIntersectClusterProjections()
{
	FILE* fp = fopen( "test\\intersect.txt", "w" );

	for( int i1 = 0; i1 < this->NumOfAttributes; i1++ )
	{	
		if( this->C_i[i1] != NULL )
		{
			fprintf( fp, "Cluster projections on %d\n", i1 );
			fprintf( fp, "Cardinality %d\n", this->C_i[i1]->GetCardinality() );
			for( int j1 = 0; j1 < this->C_i[i1]->GetCardinality(); j1++ )			
			{
				fprintf( fp, "Cluster projection # %d \n", j1 );
				for( int j2 = 0; j2 < this->C_i[i1]->GetElement(j1)->GetCardinality(); j2++ )	
				{
					fclose(fp);
					fp = fopen( "test\\intersect.txt", "a" );
					fprintf( fp, "%d, ", this->C_i[i1]->GetElement(j1)->GetElement(j2) );		
				}
				fprintf( fp, "\n" );
			}
			fprintf( fp, "\n" );
		}
		fprintf( fp, "\n" );
	}

	fclose(fp);

	return 1;
}



CDataSet::EvAllInterSummaries( )
{
	int j, i;
	sigma_ij = (int**)new int*[NumOfAttributes*NumOfAttributes];

	for( i = 0; i < NumOfAttributes; i++ )
	{
		for( j = 0; j < NumOfAttributes; j++ )
		{
			sigma_ij[i*NumOfAttributes+j] = NULL;
		}
	}

	for( i = 0; i < NumOfAttributes; i++ )
	{
		for( j = 0; j < NumOfAttributes; j++ )
		{
			if( i != j )
			{
				EvInterSummaries( i, j );
			}
		}
	}

	return 1;
}


CDataSet::EvInterSummaries( int FirstAttr, int SecondAttr )
{
	sigma_ij[FirstAttr*NumOfAttributes + SecondAttr] = new int[max_attrib[FirstAttr]*max_attrib[SecondAttr]];		
	
	int* summary = sigma_ij[FirstAttr*NumOfAttributes + SecondAttr];
	
	int i = 0;
	int j = 0;

	for( i = 0; i < max_attrib[FirstAttr]; i++ )
	{
		for( j = 0; j < max_attrib[SecondAttr]; j++ )
		{
			summary[i*max_attrib[SecondAttr]+j] = 0;	
		}
	}

	for(int count = 0; count < NumOfInstances; count++ )
	{
		summary[GetAttribute(count,FirstAttr)*max_attrib[SecondAttr]+GetAttribute(count,SecondAttr)]++;
	}

	int k_ij = EvThreshold( FirstAttr, SecondAttr );

	for( i = 0; i < max_attrib[FirstAttr]; i++ )
	{
		for( j = 0; j < max_attrib[SecondAttr]; j++ )
		{
			if( summary[i*max_attrib[SecondAttr]+j] < k_ij )
			{
				summary[i*max_attrib[SecondAttr]+j] = 0;
			}
		}
	}

	return 1;
}

CDataSet::EvThreshold( int FirstAttr, int SecondAttr )
{
	alpha = 1;

	return (int)(alpha*NumOfInstances/(max_attrib[FirstAttr]*max_attrib[SecondAttr]));
}

CDataSet::EvAllIntraSummaries( )
{
	sigma_ii_j = (int**)new int*[NumOfAttributes*NumOfAttributes];
	
	int j;
	
	for( j = 0; j < NumOfAttributes*NumOfAttributes; j++ )
	{
		sigma_ii_j[j] = NULL;
	}


	for( int i = 0; i < NumOfAttributes; i++ )
	{
		for( j = 0; j < NumOfAttributes; j++ )
		{
			if( i != j ) 
			{
				EvIntraSummaries( i, j );
			}
		}
	}

	return 1;
}

CDataSet::EvIntraSummaries( int FirstAttr, int SecondAttr )
{
	// для каждого атрибута все возможные пары значений 
	
	sigma_ii_j[FirstAttr*NumOfAttributes + SecondAttr] = new int[max_attrib[FirstAttr]*max_attrib[FirstAttr]];
	
	int* summary = sigma_ii_j[FirstAttr*NumOfAttributes + SecondAttr];

	int* inter_sum;

	int i1 = 0;
	int i2 = 0;
	int j = 0;

	inter_sum = sigma_ij[FirstAttr*NumOfAttributes + SecondAttr];

	int count = 0;
	for( i1 = 0; i1 < max_attrib[FirstAttr]; i1++ )
	{
		for( i2 = 0; i2 < max_attrib[FirstAttr]; i2++ )
		{
			summary[count] = 0;
			
			for( int jc = 0; jc < max_attrib[SecondAttr]; jc++ )
			{
				if( (inter_sum[i1*max_attrib[SecondAttr]+jc] > 0) && (inter_sum[i2*max_attrib[SecondAttr]+jc] > 0) )
				{
					summary[count]++;
				}
			}
				
			count++;
		}
	}
	
	return 1;
}

// производит расширение кластер-проекций
// из множеств для всех пар атрибутов
CDataSet::AllExtension( )
{
	this->ClusterProjectionSet_ij = new CClusterProjectionSet*[NumOfAttributes*NumOfAttributes]; 

	for( int i = 0; i < NumOfAttributes; i++ )
	{
		for( int j = 0; j < NumOfAttributes; j++ )
		{
			if( j != i )
			{
				this->ClusterProjectionSet_ij[i*NumOfAttributes+j] = this->Extension( i, j );
			}
		}
	}

	return 1;
}


CClusterProjectionSet* CDataSet::Extension( int FirstAttr, int SecondAttr )
{
	
	// Output CS_i^j - множество кластер-проекций на A_i 2-кластеров (A_i, A_j)
	// мощность заранее не известна

	// инициализация

	// установка флагов подмножеств и счетчиков участия всех 
	// множеств из множества различительных множеств DS_ij равными 0
	
	CDistinguishSetSet* DSij = this->DistinguishSetSet_ij[FirstAttr*NumOfAttributes+SecondAttr];
	
	if( DSij != NULL )
	{

		CClusterProjectionSet* CSij = (CClusterProjectionSet*)new CClusterProjectionSet;
		
		DSij->SetAllSubsetFlagsToZero();
		DSij->SetAllParticipationCountsToZero();

		CClusterProjection* CiS = NULL;

		int count = 0;
		int SiblingStrength = 0;

		CDistinguishSet* S_i = DSij->GetElement( count );
		
		while( S_i != NULL )
		{
			if( S_i->GetSubsetFlag() == 0 )
			{
				int tmp1 = DSij->GetFirstAttr( );
				int tmp2 = DSij->GetSecondAttr( );
				CiS = this->Extend( S_i, DSij->GetFirstAttr( ), DSij->GetSecondAttr( ), &SiblingStrength );			
				CSij->AddElement( CiS );

				CiS->SetSubsetFlags( DSij );
				CiS->IncreaseParticipationCounts( DSij, SiblingStrength );
			}

			count++;
			S_i = DSij->GetElement( count );
		}

		// Нахождение малых кластер-проекций, если счетчик участия S_i \in DS_i^j
		// не равен мощности sibling множества построенного для нее, то добавляем
		// S_i в CS_i^j (без расширения)
/*		count = 0;
		S_i = DSij->GetElement( count );
		while( S_i != NULL )
		{
			this->BuildSiblingSet( S_i, DSij->GetFirstAttr( ), DSij->GetSecondAttr( ), &SiblingStrength );
			
			if( SiblingStrength != S_i->GetParticipationCount() )
			{
				CiS->Create( S_i );
				CSij->AddElement( CiS );
			}

			count++;
			S_i = DSij->GetElement( count );
		}
*/
/*		if( CiS != NULL )
		{
			delete CiS;
			CiS = NULL;
		}
*/
		return CSij;
	}
	else
	{
		return NULL;
	}
}

// возвращает плотность при предположении о независимости
// атрибутов
double CDataSet::GetIndependentDensity()
{
	double  res = this->NumOfInstances;
	
	for( int i =0; i < this->NumOfAttributes; i++ )
	{
		res = res / this->max_attrib[i];
	}

	return res;
}



CDataSet::AllClusterProjectionsIntersection(  )
{
	C_i = new CClusterProjectionSet*[this->NumOfAttributes];

	for( int i = 0; i < this->NumOfAttributes; i++ )
	{
		C_i[i] = this->ClusterProjectionsIntersection( i );
	}
	return 1;
}

CClusterProjectionSet* CDataSet::ClusterProjectionsIntersection( int i )
{
	CClusterProjectionSet* S = (CClusterProjectionSet*)new CClusterProjectionSet;
	
	int j1;
	if( i > 0 )
	{
		j1 = 0;
	}
	else
	{
		j1 = 1;
	}

	S->CopyFrom( this->ClusterProjectionSet_ij[i*NumOfAttributes + j1] );
	
	for( int k = 0; k < this->NumOfAttributes; k++ )
	{
		if( k != i )
		{
			S->InterSectionJoin( this->ClusterProjectionSet_ij[i*NumOfAttributes + k] );
		}
	}

	return S;

	// получаем кластер-проекции на A_i кластеров на всем множестве атрибутов
	// путем объединения кластер проекций от 2-кластеров на (A_i,A_j), j \neq i

	// CS_i^j - набор кастер-проекций на A_i в соответствии с A_j

	// операция intersection join
	// двух наборов множеств значений атрибута A_i, s - множество значений, 
	// S_1, S_2  - множества состоящие из s.

	// берем все члены S_1 - s_1 и все члены S_2 - s_2, в S_1 П S_2 попадают s - все попарные 
	// пересечения членов S_1, S_2

	// j_1 = 1 если i > 1, иначе j1 = 2;
	// начинаем S = CS_i^{j_1}, \forall k \neq i
	// S = S intersection join CS_i^k

	// В результате S - все кластер-проекции полных кластеров на A_i, далее именуется C_i
}

CClusterSet* CDataSet::BuildCandidateClusters()
{

	// C^1 = C_1 - т.е. просто множеству кластер-проекций полных кластеров на первый атрибут

	// while( не будет сгенерировано NumOfAttributes множеств кластер кандидатов
	// || пока одно из них не окажется пустым ) {

		// Получение C^{k+1} из C^k
		// каждый элемент из C^k получит приращение в виде C_{k+1} - кластер-проекции на A_{k+1}
		// дополняется до существующего кортежа, если с каждым элементом из существующего
		// две кластер-проекции (C_i,C_{k+1}) образуют подкластер на (A_i,A_{k+1})
		
		// кластер-проекция на атрибут  - это множество значений фтрибута
		// это проверяется по интер-сводкам - каждый элемент из C_i должен иметь > 0 для
		// всех элементов из C_{k+1} и наоборот
	// }
	
	CClusterSet** ClustersCandidates = (CClusterSet**)new CClusterSet*[this->NumOfAttributes]; 
	for( int count = 0; count < this->NumOfAttributes; count++ )
	{
		ClustersCandidates[count] = NULL;
	}
	
	CClusterSet* C_1 = new CClusterSet;

	int k = 0;
	C_1->CopyFrom( *(C_i+k) );

	this->PPC_1( C_1 );

	CClusterSet* CurrentCandidates;
	CurrentCandidates = C_1;
	ClustersCandidates[k++] = CurrentCandidates;

	while( ( k < this->NumOfAttributes ) && ( CurrentCandidates != NULL ) )
	{
		CurrentCandidates = ClustersCandidates[k-1]->GenerateFromDec(*(C_i+k), this->sigma_ij, this->max_attrib, this->NumOfAttributes);
		ClustersCandidates[k++] = CurrentCandidates;
		this->PPC_1( CurrentCandidates );
	}
	
	return ClustersCandidates[k-1];
}

CDataSet::PPC_1( CClusterSet* C_1 )
{
	FILE* fp = fopen( "test\\c_1.txt", "w" );

	for( int i = 0; i < C_1->GetCardinality(); i++ )
	{
		fprintf(fp, "Cluster # %d\n", i);

		CCluster* Cl_tmp = C_1->GetElement(i);

		for( int count_proj = 0; count_proj < Cl_tmp->Getk(); count_proj++ )
		{
			fprintf(fp, "Attirbute # %d\t", count_proj);

			CClusterProjection* CP_tmp = Cl_tmp->GetProjection(count_proj);

			for(int count_values = 0; count_values < CP_tmp->GetCardinality(); count_values++ )
			{
				fprintf(fp, "%d, ", CP_tmp->GetElement(count_values) );
			}
			fprintf(fp, "\n" );
		}

		fprintf(fp, "\n" );
	}
	
	fclose(fp);

	return 1;
}

CDataSet::PPFinalClusters( char* FileName )
{
	FILE* fp = fopen( FileName, "w" );

	for( int i = 0; i < this->FinalCusters->GetCardinality(); i++ )
	{
		fprintf(fp, "Cluster # %d\n", i);

		CCluster* Cl_tmp = this->FinalCusters->GetElement(i);

		for( int count_proj = 0; count_proj < Cl_tmp->Getk(); count_proj++ )
		{
			fprintf(fp, "Attirbute # %d\t", count_proj);

			CClusterProjection* CP_tmp = Cl_tmp->GetProjection(count_proj);

			for(int count_values = 0; count_values < CP_tmp->GetCardinality(); count_values++ )
			{
				fprintf(fp, "%d, ", CP_tmp->GetElement(count_values) );
			}
			fprintf(fp, "\n" );
		}

		fprintf(fp, "\n" );
	}
	
	fclose(fp);

	return 1;
}

CDataSet::AllDistinguishingSets( )
{
	this->DistinguishSetSet_ij = new CDistinguishSetSet*[NumOfAttributes*NumOfAttributes];

	for( int i = 0; i < NumOfAttributes; i++ )
	{
		for( int j = 0; j < NumOfAttributes; j++ )
		{
			if( i != j )
			{
				this->DistinguishSetSet_ij[i*NumOfAttributes+j] = this->CreateDistinguishingSets( i, j );
			}
		}
	}
	
	return 1;
}

CDistinguishSetSet* CDataSet::CreateDistinguishingSets( int FirstAttr, int SecondAttr )
{
	this->kappa = 40;	// различительное число


	CC_k** DistSets = (CC_k**)new CC_k*[this->kappa-1]; 
	// Множество различительных множеств, надо для всех атрибутов 
	int i1, i2;
	for( i1 = 0; i1 < this->kappa-1; i1++ )
	{
		DistSets[i1] = NULL;
	}

	DistSets[0] = (CC_k*)new CC_k;
	DistSets[0]->SetLevel( 2 );

	int* summary = sigma_ii_j[FirstAttr*NumOfAttributes + SecondAttr];

	int* buf = new int[2];

	for( i1 = 0; i1 < max_attrib[FirstAttr]; i1++ )
	{
 		for( i2 = i1+1; i2 < max_attrib[FirstAttr]; i2++ )
		{
			if( i1 != i2 )
			{
				if( summary[i1*max_attrib[FirstAttr]+i2] > 0 )
				{
					buf[0] = i1;
					buf[1] = i2;
					DistSets[0]->AddClique( buf );
				}
			}
		}
	}

	delete []buf;

	int k = 1;

	while( (DistSets[k-1] != NULL) && (k < this->kappa-1) )
	{
		DistSets[k] = (CC_k*)new CC_k;
		DistSets[k]->SetLevel( k+2 );
		DistSets[k]->Create( DistSets[k-1] );
		if( DistSets[k]->GetCardinality() <= 0 )
		{
			delete DistSets[k];
			DistSets[k] = NULL;
		}
		k++;
	}


	// Надо создать множество различительных множеств, чтобы потом брать по одному
	CDistinguishSetSet* DS_ij = new CDistinguishSetSet;	
	CDistinguishSet* DS = new CDistinguishSet;

	k = 0;
	while( (DistSets[k] != NULL) && (k < this->kappa-1) )
	{
		for( int i = 0; i < DistSets[k]->GetCardinality( ); i++ )
		{
			DS = new CDistinguishSet;
			DS->FromClique(DistSets[k]->GetClique(i));
			DS_ij->AddElement( DS );
		}
		k++;
	}
	DS_ij->SetAttributes( FirstAttr, SecondAttr );
	
	k = 0;
	while( DistSets[k] != NULL )
	{
		delete DistSets[k];
		k++;
	}

	delete []DistSets;

	return DS_ij;
}

// операция расширения, второй шаг.
// Extend - собственно опреация расширения
CClusterProjection* CDataSet::Extend( CDistinguishSet* S_i, int FirstAttr, int SecondAttr, int* SiblingStrength )
{
	CClusterProjection* CiS = (CClusterProjection*)new CClusterProjection;

	CDistinguishSet* S_ij = BuildSiblingSet( S_i, FirstAttr, SecondAttr, SiblingStrength ); 
	
	int tmp;

	CDistinguishSet* DS_CiS = BuildSiblingSet( S_ij, SecondAttr, FirstAttr, &tmp ); 
	CiS->Create( DS_CiS );

	return CiS;
}

// ВНИМАНИЕ! Нумерация атрибутов с 1
CDistinguishSet* CDataSet::BuildSiblingSet( CDistinguishSet* S_i, int FirstAttr, int SecondAttr, int* SiblingStrength )
{
	// для различительного множества S_i \in DS_i^j по атрибуту A_j
	// состоит из значений атрибута a_j, таких, что для всех a_i \in S_i,
	// что sigma_ij > 0
	
	CDistinguishSet* S_ij = new CDistinguishSet;

	int* inter_sum = this->sigma_ij[FirstAttr*this->NumOfAttributes + SecondAttr];
	
	bool flag;
	for( int jc = 0; jc < this->max_attrib[SecondAttr]; jc++ )
	{
		flag = true;
		for( int ic = 0; ic < this->max_attrib[FirstAttr]; ic++ )
		{
			if( (inter_sum[ic*max_attrib[SecondAttr]+jc] <= 0) && ( S_i->Contain(ic) == 1 ) )
			{
				flag = false;
			}
		}
		if( flag )
		{
			S_ij->AddElement( jc );
		}
	}

	*SiblingStrength = S_ij->GetCardinality();
	
	return S_ij;
}

CDataSet::Validation()
{
	// Предварительно убрать одинаковые кластеры
	int i, j;
/*	for( i = 0; i < this->ClCandidates->GetCardinality(); i++ )
	{
		for( j = 0; j < i; j++ )
		{
			if(  )
		}
		for( j = i+1; j < this->ClCandidates->GetCardinality(); j++ )
		{
			if(  )
		}
	}
*/
	int* buf;
	
	int tmp = this->ClCandidates->GetCardinality();
	for( i = 0; i < this->ClCandidates->GetCardinality(); i++ )
	{
		for( j = 0; j < this->NumOfInstances; j++ )
		{
			buf = this->GetInstance( j );
			this->ClCandidates->GetElement( i )->TrySupport(buf);
		}
	}

	int threshold = (int)(alpha*this->GetIndependentDensity());

	this->FinalCusters = new CClusterSet;

	for( i = 0; i < this->ClCandidates->GetCardinality(); i++ )
	{
		if( this->ClCandidates->GetElement( i )->GetSupport() >= threshold )
		{
			this->FinalCusters->AddElement( this->ClCandidates->GetElement( i ) );
		}
	}

	return 1;
}

CDataSet::CACTUS( const char* FileName )
{
	// Предварительная часть
	this->LoadFromFile(FileName); // Загрузка данных

	this->EvMaxAttribute();		
	// Определение областей значений атрибутов

	this->PPMaxAttributes( );

	//+ Фаза сводок

		//+ вычисление всех интер-сводок

		this->EvAllInterSummaries( );	
		// в результате интер-сводки хранятся в sigma_ij
		// обращение для конкретной пары 
		// sigma_ij[(FirstAttr-1)*NumOfAttributes + (SecondAttr-1)]

		this->PPInterSummaries();
		//+ Конец вычисление всех интер-сводок

		//+ вычисление всех интра-сводок
		
		this->EvAllIntraSummaries( ); 
		// в результате интра-сводки хранятся в sigma_ii_j
		// обращение для конкретной пары 
		// sigma_ii_j[(FirstAttr-1)*NumOfAttributes + (SecondAttr-1)]

		this->PPIntraSummaries();
		//+ Конец вычисление всех интра-сводок

	//+ Конец фазы сводок

	// Фаза кластеризации
	
		//+ Первый шаг фазы кластеризации
		// Анализируем каждый атрибут, для вычисления
		// всех кластер-проекций на нем

		//+ Вычисление попарных кластер-проекций
	
			//+ Вычисление различительных множеств
			
			this->AllDistinguishingSets( );

			this->PPAllDistinguishingSets( );
			//+ Конец Вычисление различительных множеств

			//+ Операция Расширения

			this->AllExtension( );

			this->PPAllClusterProjections();
			//+ Конец Операция Расширения

		//+ Конец Вычисление попарных кластер-проекций
		

		//+ Пересечение кластер-проекций
			
		this->AllClusterProjectionsIntersection();

		this->PPIntersectClusterProjections();
		//+ Конец Пересечение кластер-проекций


	//+ Конец Первого шага фазы кластеризации

	// Второй шаг фазы кластеризации
	// Синтез клатстеров на основе кластер-проекций на 
	// индивидуальные атрибуты

		//+ По-уровневый синтез кластеров
	
		this->ClCandidates = this->BuildCandidateClusters();

		//+ Конец По-уровневый синтез кластеров

	// Конец Второй шаг фазы кластеризации

	// Конец фазы кластеризации

	//+ Проверка

	this->Validation();

	//+ Конец Проверка

	// Вывод результатов работы алгоритма

	this->PPFinalClusters( "final.txt" );

	// Конец Вывод результатов работы алгоритма

	return 1;
}

CDataSet::LoadFromFile( const char* FileName )
{
	FILE* fp = fopen( FileName, "r" );

	int count = 0;
	// в первой строке - количество записей в файле
	// во второй - количество атрибутов в записи
	
	fscanf( fp, "%d\t", &NumOfInstances);
	fscanf( fp, "%d\t", &NumOfAttributes );
	
	data_set = new int[NumOfInstances*NumOfAttributes];

	while( fscanf( fp, "%d\t", (data_set+count) ) != EOF )
	{
		count++;
		if( count >= NumOfInstances*NumOfAttributes )
		{
			break;
		}
	}

	fclose(fp);

	return 1;
}

//+
// возвращает кортеж под номером instance
int* CDataSet::GetInstance( int instance )
{
	return (this->data_set+instance*this->NumOfAttributes);
}	



