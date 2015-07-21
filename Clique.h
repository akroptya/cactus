// Clique.h: interface for the CClique class.
//
//////////////////////////////////////////////////////////////////////

#define Clique_h 

class CClique  
{
public:
	CClique( );
	CClique( int level );
	virtual ~CClique();
	GetComponent( int num );
	SetComponent( int num, int value );
	SetLevel( int new_level );
	GetLevel( );
	Create( int* buf, int level );
	CmpCliqueBuf( int* buf ); // 1 - если совпали, 0 - иначе
protected:
	int k;
	int* body;
};
