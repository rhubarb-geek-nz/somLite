/**************************************************************************
 *
 *  Copyright 2008, Roger Brown
 *
 *  This file is part of somFree.
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
 * $Id$
 */

#include <rhbopt.h>
#ifdef _WIN32
	/* this stops exports from exe */
	#define SOMDLLEXPORT
#endif

#define SOM_Module_simple_Source
#define Simple_SimpleBase_Class_Source
#define Simple_SimpleBase2_Class_Source
#define Simple_SimpleBase3_Class_Source
#define Simple_SimpleBase4_Class_Source
#define Simple_SimpleObject_Class_Source
#define Simple_SimpleClass_Class_Source
#define Simple_Useless_Class_Source
#define Simple_Simplest_Class_Source
#define Simple_M_Simplest_Class_Source
#define Simple_Simplex_Class_Source
#define Simple_octet_class_Class_Source
#define Simple_double_class_Class_Source
#define Simple_float_class_Class_Source
#define Simple_short_class_Class_Source
#define Simple_octet_octet_class_Class_Source
#define Simple_octet_double_class_Class_Source
#define Simple_octet_float_class_Class_Source
#define Simple_octet_short_class_Class_Source

#include <rhbsomex.h>

#ifdef __cplusplus
	#include <somir.xh>
	#include <somd.xh>
	#include <simple.xih>

	#define SOMObject_somGetClassName(x)	((x)->somGetClassName())
#else
	#include <somir.h>
	#include <somd.h>
	#include <simple.ih>
#endif

/*void _somDeallocate(SOMClass *cls,corbastring d)
{
	SOMClass_somDeallocate(cls,d);
}*/


SOM_Scope void  SOMLINK ifSimple(Simple_SimpleClass SOMSTAR somSelf, 
                                                    Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
}

SOM_Scope void  SOMLINK m1(Simple_SimpleObject SOMSTAR somSelf, 
                                               Environment *ev)
{
    Simple_SimpleObjectData *somThis = Simple_SimpleObjectGetData(somSelf);

	SOM_IgnoreWarning(somThis);
	SOM_IgnoreWarning(ev);
}

SOM_Scope void  SOMLINK m2(Simple_SimpleObject SOMSTAR somSelf, 
                                               Environment *ev, 
                                              corbastring m)
{
    Simple_SimpleObjectData *somThis = Simple_SimpleObjectGetData(somSelf);

	SOM_IgnoreWarning(somThis);
	SOM_IgnoreWarning(m);
	SOM_IgnoreWarning(ev);
}

SOM_Scope long SOMLINK return_long(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}

SOM_Scope char SOMLINK return_char(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}

SOM_Scope octet SOMLINK return_octet(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}

SOM_Scope boolean SOMLINK return_boolean(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}


SOM_Scope float SOMLINK return_float(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return (float)0;
}

SOM_Scope double SOMLINK return_double(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0.0;
}

SOM_Scope unsigned long SOMLINK return_ulong(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}

SOM_Scope unsigned short SOMLINK return_ushort(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}


SOM_Scope short SOMLINK return_short(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}

SOM_Scope any SOMLINK return_any(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	any a;
	a._type=0;
	a._value=0;
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return a;
}

SOM_Scope corbastring SOMLINK return_string(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}

SOM_Scope void SOMLINK return_void(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
}


SOM_Scope Simple_SimpleObject_i SOMLINK return_i(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}

SOM_Scope _IDL_SEQUENCE_octet SOMLINK return_seq(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	_IDL_SEQUENCE_octet seq={0,0,NULL};
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return seq;
}	

SOM_Scope Simple_SimpleObject_h SOMLINK return_struct(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	Simple_SimpleObject_h h;
	memset(&h,0,sizeof(h));
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return h;
}

SOM_Scope TypeCode SOMLINK return_tc(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}

SOM_Scope SOMObject SOMSTAR SOMLINK return_object(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	return 0;
}

SOM_Scope void SOMLINK flim(Simple_M_Simplest SOMSTAR somSelf,Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
}

SOM_Scope void SOMLINK flam(Simple_Simplex SOMSTAR somSelf,Environment *ev)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
}

SOM_Scope void SOMLINK inout_array(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev,
	/* inout */ Simple_an_array array)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	SOM_IgnoreWarning(array);
}

SOM_Scope void SOMLINK out_array(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev,
	/* out */ Simple_an_array array)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	SOM_IgnoreWarning(array);
}

SOM_Scope void SOMLINK in_array(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev,
	/* in */ Simple_an_array array)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	SOM_IgnoreWarning(array);
}

struct octet_class_complete
{
	somMethodTabPtr mtab;
	Simple_octet_classData base;
};

struct short_class_complete
{
	somMethodTabPtr mtab;
	Simple_short_classData base;
};

struct float_class_complete
{
	somMethodTabPtr mtab;
	Simple_float_classData base;
};

struct double_class_complete
{
	somMethodTabPtr mtab;
	Simple_double_classData base;
};

struct octet_octet_class_complete
{
	somMethodTabPtr mtab;
	Simple_octet_classData base;
	Simple_octet_octet_classData child;
};

struct octet_short_class_complete
{
	somMethodTabPtr mtab;
	Simple_octet_classData base;
	Simple_octet_short_classData child;
};

struct octet_float_class_complete
{
	somMethodTabPtr mtab;
	Simple_octet_classData base;
	Simple_octet_float_classData child;
};

struct octet_double_class_complete
{
	somMethodTabPtr mtab;
	Simple_octet_classData base;
	Simple_octet_double_classData child;
};

#ifndef offsetof
#define offsetof(y,x)     ((long)&(((*y)(0))->x))
#endif

#define check_offset(x)	if (somThis != &(somThat->x)) { somPrintf("%s,%p,%p\n",SOMObject_somGetClassName(somSelf),somThis,&(somThat->x));   exit(1); }
#define check_base		check_offset(base)
#define check_child		check_offset(child)

SOM_Scope void SOMLINK octet_somDumpSelfInt(Simple_octet_class SOMSTAR somSelf,long x)
{
	Simple_octet_classData *somThis=Simple_octet_classGetData(somSelf);
	struct octet_class_complete *somThat=(struct octet_class_complete *)(void *)somSelf;
	check_base
	Simple_octet_class_parent_SOMObject_somDumpSelfInt(somSelf,x);
}

SOM_Scope void SOMLINK short_somDumpSelfInt(Simple_short_class SOMSTAR somSelf,long x)
{
	Simple_short_classData *somThis=Simple_short_classGetData(somSelf);
	struct short_class_complete *somThat=(struct short_class_complete *)(void *)somSelf;
	check_base
	Simple_short_class_parent_SOMObject_somDumpSelfInt(somSelf,x);
}

SOM_Scope void SOMLINK float_somDumpSelfInt(Simple_float_class SOMSTAR somSelf,long x)
{
	Simple_float_classData *somThis=Simple_float_classGetData(somSelf);
	struct float_class_complete *somThat=(struct float_class_complete *)(void *)somSelf;
	check_base
	Simple_float_class_parent_SOMObject_somDumpSelfInt(somSelf,x);
}

SOM_Scope void SOMLINK double_somDumpSelfInt(Simple_double_class SOMSTAR somSelf,long x)
{
	Simple_double_classData *somThis=Simple_double_classGetData(somSelf);
	struct double_class_complete *somThat=(struct double_class_complete *)(void *)somSelf;
	check_base
	Simple_double_class_parent_SOMObject_somDumpSelfInt(somSelf,x);
}

SOM_Scope void SOMLINK octet_octet_somDumpSelfInt(Simple_octet_octet_class SOMSTAR somSelf,long x)
{
	Simple_octet_octet_classData *somThis=Simple_octet_octet_classGetData(somSelf);
	struct octet_octet_class_complete *somThat=(struct octet_octet_class_complete *)(void *)somSelf;
	check_child
	Simple_octet_octet_class_parent_Simple_octet_class_somDumpSelfInt(somSelf,x);
}

SOM_Scope void SOMLINK octet_short_somDumpSelfInt(Simple_octet_short_class SOMSTAR somSelf,long x)
{
	Simple_octet_short_classData *somThis=Simple_octet_short_classGetData(somSelf);
	struct octet_short_class_complete *somThat=(struct octet_short_class_complete *)(void *)somSelf;
	check_child
	Simple_octet_short_class_parent_Simple_octet_class_somDumpSelfInt(somSelf,x);
}

SOM_Scope void SOMLINK octet_float_somDumpSelfInt(Simple_octet_float_class SOMSTAR somSelf,long x)
{
	Simple_octet_float_classData *somThis=Simple_octet_float_classGetData(somSelf);
	struct octet_float_class_complete *somThat=(struct octet_float_class_complete *)(void *)somSelf;
	check_child
	Simple_octet_float_class_parent_Simple_octet_class_somDumpSelfInt(somSelf,x);
}

SOM_Scope void SOMLINK octet_double_somDumpSelfInt(Simple_octet_double_class SOMSTAR somSelf,long x)
{
	Simple_octet_double_classData *somThis=Simple_octet_double_classGetData(somSelf);
	struct octet_double_class_complete *somThat=(struct octet_double_class_complete *)(void *)somSelf;
	check_child
	Simple_octet_double_class_parent_Simple_octet_class_somDumpSelfInt(somSelf,x);
}

SOM_Scope void SOMLINK in_matrix(Simple_SimpleObject SOMSTAR somSelf,
								 Environment *ev,
								 Simple_a_matrix matrix)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	SOM_IgnoreWarning(matrix);
}

SOM_Scope void SOMLINK out_matrix(Simple_SimpleObject SOMSTAR somSelf,
								 Environment *ev,
								 Simple_a_matrix matrix)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	SOM_IgnoreWarning(matrix);
}


SOM_Scope void SOMLINK put_my_array(
		Simple_SimpleObject SOMSTAR somSelf,
		Environment *ev,
		Simple_my_array f)
{
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	SOM_IgnoreWarning(f);
}

SOM_Scope void SOMLINK fetch_my_array(
	Simple_SimpleObject SOMSTAR somSelf,
	Environment *ev,
	Simple_my_array f)
{
	void *pv=&f;
	SOM_IgnoreWarning(somSelf);
	SOM_IgnoreWarning(ev);
	SOM_IgnoreWarning(pv);	/* strange internal compiler (AMD64 gcc) error when just (f) */
}

#ifdef __cplusplus
extern "C"
#endif
long simpleFunction(void)
{
	int original=SOM_TraceLevel;
	long res=SOM_SubstituteClass(Simple_SimpleBase,Simple_SimpleObject);

	if (res)
	{
		somPrintf("substitution failed %ld\n",res);
		exit(1);
	}

	SOM_TraceLevel=SOM_TraceLevel+1;

	SOM_Trace("simpleFunction","SOM_Trace");

	SOM_TraceLevel=original;

	return res;
}
