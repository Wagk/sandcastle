/*!************************************************************
	Created	:	2016/03/06
	Intent	:		
		
	Usage	:
		
	Note	:
		
**************************************************************/
#ifndef util_assert_h__
#define util_assert_h__

#include <cassert>

#ifdef _DEBUG

#define ASSERT(__EXPR__, __MESG__) assert(__EXPR__ && __MESG__)
#define ABORT(__MESG__) ASSERT(false , __MESG__)
#define EXPECT(__EXPR__) ASSERT(__EXPR__, "Expected " #__EXPR__ ) 
#define ENSURE(__EXPR__) ASSERT(__EXPR__, "Failed to ensure " #__EXPR__ )

#else

#define ASSERT(__EXPR__, __MESG__)
#define ABORT(__MESG__)
#define EXPECT(__EXPR__) 
#define ENSURE(__EXPR__) 

#endif


#endif // util_assert_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


