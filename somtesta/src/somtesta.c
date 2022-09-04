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
#include <rhbsomex.h>
#include <somd.h>
#include <somtesta.h>
#include <somir.h>
#include <paramdef.h>
#include <excptdef.h>
#include <operatdf.h>
#include <attribdf.h>
#include <intfacdf.h>
#include <stdio.h>
#include <stdlib.h>
#include <repostry.h>
#include <typedef.h>

static TypeCode somtesta_get_tc(Repository SOMSTAR rep,char *name)
{
	TypeCode tc=NULL;
	Contained SOMSTAR cnd=NULL;
	somId id=somIdFromString("lookup_id");
	Environment ev;

	SOM_InitEnvironment(&ev);

	somva_SOMObject_somDispatch(rep,
			(somToken *)(void *)&cnd,
			id,
			rep,&ev,name);

	SOMFree(id);

	if ((!cnd) || (ev._major!=NO_EXCEPTION)) 
	{
		somPrintf("failed to lookup %s\n",name);
		cnd=NULL;
	}
	else
	{
		id=somIdFromString("_get_type");

		somva_SOMObject_somDispatch(cnd,
				(somToken *)(void *)&tc,
				id,
				cnd,&ev);

		SOMFree(id);

		if ((!tc) || (ev._major!=NO_EXCEPTION))
		{
			somPrintf("failed to get typecode for %s\n",name);
			if (ev._major)
			{
				somPrintf("ex=%s\n",somExceptionId(&ev));
			}

			tc=NULL;
		}
	}

	if (ev._major != NO_EXCEPTION)
	{
		const char *p=somExceptionId(&ev);
		somPrintf("somtesta_get_tc(%s) raised %s\n",name,p);
	}
	else
	{
		somPrintf("%s, typeCode=%p\n",name,tc);
		if (tc)
		{
			TypeCode_print(tc,&ev);
			somPrintf("\n");
		}
	}

	if (tc && (ev._major==NO_EXCEPTION))
	{
		tc=TypeCode_copy(tc,&ev);
	}

	if (cnd)
	{
		Contained_somFree(cnd);
	}

	SOM_UninitEnvironment(&ev);

	return tc;
}

#define cast_any_to(a,t)  (*((t *)a._value))


#define test_type(magic_type,TC_magic_type)					\
	{														\
		typedef struct										\
		{													\
			octet o;										\
			magic_type u;									\
		} p;												\
		int s=sizeof(magic_type);							\
		int a=(int)(size_t)&(((p *)0)->u);					\
		int s_t=TypeCode_size(TC_magic_type,ev);			\
		int a_t=TypeCode_alignment(TC_magic_type,ev);		\
		if ((a != a_t)|| (s != s_t))						\
		{													\
			char *q=#magic_type;							\
			somPrintf("testing type %s\n",q);				\
			somPrintf("size=%d,align=%d\n",s,a);			\
			somPrintf("tc_size=%d,tc_align=%d\n",s_t,a_t);	\
			return 1;										\
		}													\
	}

#define test_named_type(type,name)							\
	{														\
		TypeCode tc=somtesta_get_tc(rep,name);				\
		test_type(type,tc)									\
		TypeCode_free(tc,ev);								\
	}														

static int test_alignments(SOMClassMgr SOMSTAR mgr)
{
	Environment ev2;
	Environment *ev=&ev2;
	Repository SOMSTAR rep=NULL;

	SOM_InitEnvironment(ev);

#ifdef somNewObject
	rep=somNewObject(Repository);
#else
	rep=SOMClassMgr__get_somInterfaceRepository(mgr);
#endif

	{
		const char *p=irGetFileNames();
		if (p)
		{
			somPrintf("SOMIR=%s\n",p);
		}
		else
		{
			somPrintf("SOMIR not set\n");
		}
	}
	
	test_type(long,TC_long)
	test_type(char,TC_char)
	test_type(octet,TC_octet)
	test_type(boolean,TC_boolean)
	test_type(float,TC_float)
	test_type(double,TC_double)
	test_type(NamedValue,TC_NamedValue)
	test_type(corbastring,TC_string)
	test_type(InterfaceDef_FullInterfaceDescription,TC_FullInterfaceDescription)
	test_type(InterfaceDef_InterfaceDescription,TC_InterfaceDescription)
	test_type(OperationDef_OperationDescription,TC_OperationDescription)
	test_type(AttributeDef_AttributeDescription,TC_AttributeDescription)
	test_type(ExceptionDef_ExceptionDescription,TC_ExceptionDescription)
	test_type(TypeDef_TypeDescription,TC_TypeDescription)

	{
		TypeCode TC_ex=somtesta_get_tc(rep,ex_StExcep_UNKNOWN);
		unsigned long *pm;
		completion_status *pc;

		StExcep_UNKNOWN ex;
		test_type(StExcep_UNKNOWN,TC_ex);
		if (5!=TypeCode_param_count(TC_ex,ev))
		{
			somPrintf("wrong TypeCode_param_count for StExcep\n");
			return 1;
		}
		pm=&ex.minor;
		pc=&ex.completed;
		{
			typedef unsigned long unsigned_long_t;
			any a=TypeCode_parameter(TC_ex,ev,2);
			TypeCode *ptc=a._value;
			TypeCode_print(*ptc,ev);
			somPrintf("\n");
			test_type(unsigned_long_t,*ptc);
		}
		{
			any a=TypeCode_parameter(TC_ex,ev,4);
			TypeCode *ptc=a._value;
			TypeCode_print(*ptc,ev);
			somPrintf("\n");
			test_type(completion_status,*ptc);
		}
		TypeCode_free(TC_ex,ev);

		RHBOPT_unused(pc);
		RHBOPT_unused(pm);
	}

	{
		typedef struct
		{
			octet _d;
			union
			{
				octet o;
			} _u;
		} a;
		a *ap=0;
		int al=(int)(size_t)&ap->_u;
		somPrintf("minimum contained union alignment is %d\n",al);
	}

	{
		typedef struct
		{
			octet _d;
			struct
			{
				octet o;
			} _s;
		} a;
		a *ap=0;
		int al=(int)(size_t)&ap->_s;
		somPrintf("minimum contained struct alignment is %d\n",al);
	}

	test_named_type(Contained_Description,"::Contained::Description")
	test_named_type(InterfaceDef_FullInterfaceDescription,"::InterfaceDef::FullInterfaceDescription")
	test_named_type(InterfaceDef_InterfaceDescription,"::InterfaceDef::InterfaceDescription")

	test_named_type(somtesta_u_one,"::somtesta::u_one")
	test_named_type(somtesta_u_two,"::somtesta::u_two")
	test_named_type(somtesta_u_three,"::somtesta::u_three")
	test_named_type(somtesta_u_four,"::somtesta::u_four")
	test_named_type(somtesta_u_five,"::somtesta::u_five")
	test_named_type(somtesta_u_six,"::somtesta::u_six")
	test_named_type(somtesta_u_seven,"::somtesta::u_seven")
	test_named_type(somtesta_u_eight,"::somtesta::u_eight")
	test_named_type(somtesta_u_nine,"::somtesta::u_nine")
	test_named_type(somtesta_u_ten,"::somtesta::u_ten")
	test_named_type(somtesta_u_eleven,"::somtesta::u_eleven")
	test_named_type(somtesta_u_roo,"::somtesta::u_roo")

	test_named_type(somtesta_s_one,"::somtesta::s_one")
	test_named_type(somtesta_s_two,"::somtesta::s_two")

	test_named_type(somtesta_s_align_octet,"::somtesta::s_align_octet")
	test_named_type(somtesta_s_align_short,"::somtesta::s_align_short")
	test_named_type(somtesta_s_align_long,"::somtesta::s_align_long")
	test_named_type(somtesta_s_align_float,"::somtesta::s_align_float")
	test_named_type(somtesta_s_align_double,"::somtesta::s_align_double")
	test_named_type(somtesta_s_align_array,"::somtesta::s_align_array")
	test_named_type(somtesta_s_align_sequence,"::somtesta::s_align_sequence")
	test_named_type(somtesta_s_align_string,"::somtesta::s_align_string")
	test_named_type(somtesta_s_align_any,"::somtesta::s_align_any")
	test_named_type(somtesta_s_align_TypeCode,"::somtesta::s_align_TypeCode")
	test_named_type(somtesta_s_align_SOMObject,"::somtesta::s_align_SOMObject")

	SOM_UninitEnvironment(ev);
	SOMObject_somFree(rep);

	return 0;
}

int main(int argc,char **argv)
{
	int err=1;
	SOMClassMgr SOMSTAR mgr=somEnvironmentNew();

#if defined(BUILD_STATIC) || defined(__ELF__)
	RepositoryNewClass(Repository_MajorVersion,Repository_MinorVersion);
#endif
	
	err=test_alignments(mgr);
	
	somEnvironmentEnd();
	
	return err;
}
