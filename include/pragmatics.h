
/*******************************************************************************

    pragmatics.h

    Compiler, Operating System, and Debug Logging Particulars.

*******************************************************************************/
    
#ifndef  PRAGMATICS_H       /* Has the file been INCLUDE'd already? */
#define  PRAGMATICS_H  yes


/*******************************************************************************
    Data types of interest.
*******************************************************************************/

/* Define the C99 _Bool data type if <stdbool.h> is not available. */

#if defined(__GNUC__) && !defined(HAVE_STDBOOL_H)
#    define  HAVE_STDBOOL_H  1
#endif

#if defined(HAVE_STDBOOL_H) && HAVE_STDBOOL_H
#    include  <stdbool.h>		/* C99 boolean type and values. */
#elif defined(_WIN32) && defined(__cplusplus)
					/* In "yvals.h" via "limits.h" below. */
#elif !defined(_Bool) && (!defined(HAVE__BOOL) || (!HAVE__BOOL))
#    define  _Bool  int
#    if !defined(__cplusplus) || defined(OS_ALTERNATIVE_STL_NAMES)
#        define  OS_OMIT_BOOL  0
#        define  bool  _Bool
#        ifndef true
#            define  true  1
#        endif
#        ifndef false
#            define  false  0
#        endif
#    endif
#endif

#endif				/* If this file was not INCLUDE'd previously. */
