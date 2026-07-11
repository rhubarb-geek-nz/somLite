/**************************************************************************
 *
 *  Copyright 2008, Roger Brown
 *
 *  This file is part of Roger Brown's Toolkit.
 *
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 */

#include <rhbopt.h>

#ifdef _WIN32
	#include <windows.h>
#endif

#include <somkern.h>

/**************************************************
 * these are the C calling convention, not SOMLINK va stubs
 * they are legacy functions which really should be optlink
 * which requires some jumping through hoops with MSVC++
 * basically don't call these unless compiler defaulting
 * to optlink, they are only provided to meet the binary
 * contract, new code should use the somva_* functions
 */

#if defined(_WIN32) && defined(_M_IX86) && !defined(_WIN64)
	#define OPTLINK_3ARGS(a,b,c)		\
			__asm {	mov		a,eax	}	\
			__asm {	mov		b,edx	}	\
			__asm {	mov		c,ecx	}
	#define OPTLINK_DECL	__cdecl
#else
	#define OPTLINK_3ARGS(a,b,c)
	#define OPTLINK_DECL	
#endif

#ifdef va_SOMObject_somDispatch
#undef va_SOMObject_somDispatch
#endif /* va_SOMObject_somDispatch */

boolean OPTLINK_DECL va_SOMObject_somDispatch(SOMObject SOMSTAR somSelf,
		somToken *retValue,
		somId methodId,
		...)
{
	boolean __result;
	va_list ap;

	OPTLINK_3ARGS(somSelf,retValue,methodId)

	va_start(ap,methodId);

	__result=SOMObject_somDispatch(somSelf,retValue,methodId,ap);

	va_end(ap);
	return __result;
}
