#include "GaudiKernel/DeclareFactoryEntries.h"
#include "FSFilter/FSFilter.h"

//name as seen in .cxx
DECLARE_ALGORITHM_FACTORY( FSFilter )
	//name as on directory
	DECLARE_FACTORY_ENTRIES( FSFilter ) {
		//name as seen in .cxx
		DECLARE_ALGORITHM( FSFilter );
	}
