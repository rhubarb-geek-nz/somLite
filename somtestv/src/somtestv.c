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

#define WIN32_DLLEXPORT
#include <rhbopt.h>

#define SOM_Module_simple_Source
#include <stdio.h>
#include <rhbsomex.h>
#include <somir.h>
#include <somd.h>

#ifdef _WIN32
	#include <windows.h>
#endif

#include <simple.h>
#include <somtc.h>
#include <somtcnst.h>
#include <somdext.h>
#include <orb.h>
#include <somoa.h>
#include <somdobj.h>
#include <request.h>
#include <somderr.h>
#include <somdserv.h>
#include <rhbsomut.h>
#include <containd.h>
#include <containr.h>
#include <repostry.h>
#include <paramdef.h>
#include <excptdef.h>
#include <operatdf.h>
#include <attribdf.h>
#include <intfacdf.h>
#include <impldef.h>
#include <nvlist.h>
#include <cntxt.h>
#include <somdom.h>
#include <somdcprx.h>
#include <somd.h>
#include <rhbsomex.h>
#include <time.h>

extern long simpleFunction(void);

static void mustnt_work(const char *line,int num,Environment *ev)
{
	if (!ev->_major)
	{
		somPrintf("exception should have been raised on line %s:%d\n",line,num);
		exit(1);
	}

	somExceptionFree(ev);
}

static void must_work(const char *line,int num,Environment *ev)
{
	if (ev->_major)
	{
		somPrintf("exception raised on line %s:%d=%s\n",line,num,somExceptionId(ev));
		exit(1);
	}
}

#define MUST_WORK    must_work(__FILE__,__LINE__,ev);
#define MUSTNT_WORK  mustnt_work(__FILE__,__LINE__,ev);

static void test_enum_marshal(Environment *ev)
{
TypeCode tc=tcNew(tk_enum,"name","one","two","three",NULL);
long l2;

	somExceptionFree(ev);

	/* this should work */
	l2=RHBCDR_GIOPenumToIDLenum(0,ev,tc); MUST_WORK
	l2=RHBCDR_GIOPenumToIDLenum(1,ev,tc); MUST_WORK
	l2=RHBCDR_GIOPenumToIDLenum(2,ev,tc); MUST_WORK

	/* these should fail */

	l2=RHBCDR_GIOPenumToIDLenum(3,ev,tc); MUSTNT_WORK
	l2=RHBCDR_GIOPenumToIDLenum((unsigned)-1,ev,tc); MUSTNT_WORK

	/* these should work */

	l2=RHBCDR_IDLenumToGIOPenum(1,ev,tc); MUST_WORK
	l2=RHBCDR_IDLenumToGIOPenum(2,ev,tc); MUST_WORK
	l2=RHBCDR_IDLenumToGIOPenum(3,ev,tc); MUST_WORK

	/* these should fail */
	l2=RHBCDR_IDLenumToGIOPenum((unsigned)-1,ev,tc); MUSTNT_WORK
	l2=RHBCDR_IDLenumToGIOPenum(0,ev,tc); MUSTNT_WORK
	l2=RHBCDR_IDLenumToGIOPenum(4,ev,tc); MUSTNT_WORK

/*		RHBGIOPORB_IDLenumToGIOPenum*/

	tcSetZeroOriginEnum(tc,ev,1); 
	
	/* this should work */
	l2=RHBCDR_GIOPenumToIDLenum(0,ev,tc); MUST_WORK
	l2=RHBCDR_GIOPenumToIDLenum(1,ev,tc); MUST_WORK
	l2=RHBCDR_GIOPenumToIDLenum(2,ev,tc); MUST_WORK

	/* these should fail */

	l2=RHBCDR_GIOPenumToIDLenum(3,ev,tc); MUSTNT_WORK
	l2=RHBCDR_GIOPenumToIDLenum((unsigned)-1,ev,tc); MUSTNT_WORK

	/* these should work */

	l2=RHBCDR_IDLenumToGIOPenum(0,ev,tc); MUST_WORK
	l2=RHBCDR_IDLenumToGIOPenum(1,ev,tc); MUST_WORK
	l2=RHBCDR_IDLenumToGIOPenum(2,ev,tc); MUST_WORK

	/* these should fail */
	l2=RHBCDR_IDLenumToGIOPenum((unsigned)-1,ev,tc); MUSTNT_WORK
	l2=RHBCDR_IDLenumToGIOPenum(3,ev,tc); MUSTNT_WORK

	tcFree(tc,ev);

	RHBOPT_unused(l2);
}

static void test_somForeign_tc(Environment *ev)
{
	char *impctx="SOM,static(somIdMarshal,0)";
	char *name="somId";
	long len=sizeof(somId);
	va_list list;
	somToken vabuf;
	TypeCode tc=tcNew(tk_foreign,name,impctx,sizeof(somId));
	if (tcSize(tc,ev)!=sizeof(somId)) { somPrintf("size error\n"); exit(1); }
	TypeCode_print(tc,ev); somPrintf("\n");
	TypeCode_free(tc,ev);

	vabuf=somVaBuf_create(0,0);
	somVaBuf_add(vabuf,&name,tk_string);
	somVaBuf_add(vabuf,&impctx,tk_string);
	somVaBuf_add(vabuf,&len,tk_long);
	somVaBuf_get_valist(vabuf,&list);
	tc=tcNewVL(tk_foreign,list);
	if (tcSize(tc,ev)!=sizeof(somId)) { somPrintf("size error\n"); exit(1); }

	somVaBuf_destroy(vabuf);
	TypeCode_print(tc,ev); somPrintf("\n");

	if (tcSize(tc,ev)!=sizeof(somId)) { somPrintf("size error\n"); exit(1); }

	TypeCode_free(tc,ev);
}

int main(int argc,char **argv)
{
	Environment ev;
	Simple_SimpleObject SOMSTAR o=NULL;
	SOMClass SOMSTAR cls=NULL;
	corbastring p=NULL,f=NULL;
	void *pv=NULL;
#ifdef USE_THREADS
	somToken mutex=NULL;
#endif
	TypeCode t=NULL;
	SOMClassMgr SOMSTAR mgr=somEnvironmentNew();

	{
		Simple_Simplest SOMSTAR x=Simple_SimplexNew();
		Simple_M_Simplest SOMSTAR c=Simple_Simplest_somGetClass(x);
		Simple_Simplest_somDumpSelf(x,0);
		Simple_M_Simplest_somDumpSelf(c,0);
		Simple_Simplest_somFree(x);
	}

	{
		SOMObject SOMSTAR obj=Simple_octet_classNew();
		SOMObject_somDumpSelf(obj,0);
		SOMObject_somFree(obj);
	}

	{
		SOMObject SOMSTAR obj=Simple_short_classNew();
		SOMObject_somDumpSelf(obj,0);
		SOMObject_somFree(obj);
	}

	{
		SOMObject SOMSTAR obj=Simple_float_classNew();
		SOMObject_somDumpSelf(obj,0);
		SOMObject_somFree(obj);
	}

	{
		SOMObject SOMSTAR obj=Simple_double_classNew();
		SOMObject_somDumpSelf(obj,0);
		SOMObject_somFree(obj);
	}

	{
		SOMObject SOMSTAR obj=Simple_octet_octet_classNew();
		SOMObject_somDumpSelf(obj,0);
		SOMObject_somFree(obj);
	}

	{
		SOMObject SOMSTAR obj=Simple_octet_short_classNew();
		SOMObject_somDumpSelf(obj,0);
		SOMObject_somFree(obj);
	}

	{
		SOMObject SOMSTAR obj=Simple_octet_float_classNew();
		SOMObject_somDumpSelf(obj,0);
		SOMObject_somFree(obj);
	}

	{
		SOMObject SOMSTAR obj=Simple_octet_double_classNew();
		SOMObject_somDumpSelf(obj,0);
		SOMObject_somFree(obj);
	}

	{
		SOMClassMgr SOMSTAR mgr2=SOMClassMgrNew();
		SOMClassMgr_somDumpSelf(mgr2,0);
		SOMClassMgr_somFree(mgr2);
	}

#ifdef USE_THREADS
	SOMCreateMutexSem(&mutex);
	SOMRequestMutexSem(mutex);
	SOMReleaseMutexSem(mutex);
	SOMDestroyMutexSem(mutex);
#endif

	p=SOMObject_somGetClassName(mgr);

	p=SOMMalloc(5);

	SOMFree(p);

	p=SOMCalloc(5,6);

	p=SOMRealloc(p,10);

	SOMFree(p);

	SOM_InitEnvironment(&ev);

	tcPrint(TC_FullInterfaceDescription,&ev);

	test_somForeign_tc(&ev);
	test_enum_marshal(&ev);

	p="SOMRefObject";

	cls=SOMClassMgr_somFindClsInFile(mgr,&p,0,0,"somref.dll");

	if (cls)
	{
		SOMObject SOMSTAR o;

		p=SOMClass_somGetName(cls);

		somPrintf("loaded class %s\n",p);

		o=SOMClass_somNew(cls);

		p=SOMObject_somGetClassName(o);

		somReleaseObjectReference(o);
	}

	SOMObject_somDumpSelf(mgr,0);

	cls=Simple_SimpleObjectNewClass(0,0);

	if (cls)
	{
		long maj_v,min_v,res;

		SOMClass_somGetVersionNumbers(SOMObjectClassData.classObject,&maj_v,&min_v);

#ifdef somNewObject
		o=somNewObject(Simple_SimpleObject);
#else
		o=Simple_SimpleObjectNew();
#endif

		if (o)
		{
			SOMClass SOMSTAR cls1;
			SOMClass_somOffsets off;

			Simple_SimpleObject_m2(o,&ev,"Hello simple");

			p=SOMObject_somGetClassName(o);

			somPrintf("it is a %s\n",p);

			cls1=SOMObject_somGetClass(o);

			p=SOMClass_somGetName(cls1);

			somPrintf("class is %s\n",p);

			pv=SOMClass_somGetPClsMtab(cls1);

			somPrintf("somGetPClsMtab=%p\n",pv);

			pv=o->mtab;

			somPrintf("o->mtab=%p\n",pv);

			pv=Simple_SimpleObjectCClassData.parentMtab;

			somPrintf("ccds->parentMTab=%p\n",pv);

			p=SOMObject_somGetClassName(cls1);

			somPrintf("class is a %s\n",p);

			off=SOMClass__get_somInstanceDataOffsets(cls1);

			if (off._length)
			{
				unsigned long i=0;

				while (i < off._length)
				{
					SOMClass SOMSTAR cls3=off._buffer[i].cls;
					
					somPrintf("class %s is %d\n",
							SOMClass_somGetName(cls3),
							off._buffer[i].offset);

					i++;
				}

				SOMFree(off._buffer);
			}

			p=0;

			{
				corbastring q="somGetClassName";

				somva_SOMObject_somDispatch(o,
					(somToken *)(void *)&p,&q,o);
			}

			somReleaseObjectReference(o);

			{
				unsigned int i=0;
				_IDL_SEQUENCE_SOMClass seq=SOMClass_somGetParents(cls);

				while (i < seq._length)
				{
					p=SOMClass_somGetName(seq._buffer[i]);

					somPrintf("derived from %s\n",p);

					i++;
				}

				SOMFree(seq._buffer);
			}

			{
				_IDL_SEQUENCE_SOMClass seq;
				SOMClass SOMSTAR buf[2];
				SOMClass SOMSTAR cls2;
				SOMClassMgr SOMSTAR m;
				corbastring p;

				seq._length=2;
				seq._maximum=2;
				seq._buffer=buf;

				p="Simple::SimpleObject";
				buf[0]=SOMClassMgr_somFindClass(mgr,&p,0,0);
				p="SOMClassMgr";
				buf[1]=SOMClassMgr_somFindClass(mgr,&p,0,0);

				cls2=SOMClass_somNew(SOMClassClassData.classObject);

				SOMClass_somInitMIClass(cls2,1,
					"MI_Fred",
					&seq,
					16,0,4,0,0);

				SOMClass_somClassReady(cls2);

				m=SOMClass_somNew(cls2);

				SOMObject_somPrintSelf(m);
				SOMObject_somDumpSelf(m,0);

				somReleaseObjectReference(m);
			}
		}

		res=simpleFunction();

		if (res)
		{
			somPrintf("substitution failed %ld\n",res);
			exit(1);
		}
		else
		{
			SOMObject SOMSTAR z=SOMClass_somNew(Simple_SimpleBaseClassData.classObject);
			const char *q="Simple::SimpleObject";

			p=SOMObject_somGetClassName(z);

			somPrintf("%s\n",p);

			if (strcmp(p,q))
			{
				somPrintf("substitution failed - %s %s\n",p,q);
				exit(1);
			}

			somReleaseObjectReference(z);
		}

		SOMObject_somDumpSelf(mgr,0);

		somReleaseClassReference(cls);
	}

	if (!mgr)
	{

		SOMObject_somDumpSelf(mgr,0);

		p="SOMEEMan";

		f=SOMClassMgr_somLocateClassFile(mgr,&p,2,1);

		if (f)
		{
			somPrintf("SOMEEMan should be in %s\n",f);

			SOMClassMgr_somLoadClassFile(mgr,&p,2,1,f);

	/* SOM bombs if this is free'd */		
	/*		SOMFree(f);*/
		}

		SOMClassMgr_somFindClass(mgr,&p,2,1);

		if (mgr)
		{
			SOMObject SOMSTAR o;

			o=SOMClassMgr__get_somInterfaceRepository(mgr);

			if (o)
			{
				somTD_Repository_lookup_id pfn2;
				somTD_Repository_lookup_modifier pfn=(somTD_Repository_lookup_modifier)
					somResolveByName(o,"lookup_modifier");

				if (pfn)
				{
					corbastring p=pfn(o,&ev,"::Repository","dllname");

					somPrintf("%s\n",p);

					if (p) SOMFree(p);
				}

				pfn2=(somTD_Repository_lookup_id)
					somResolveByName(o,"lookup_id");

				if (pfn2)
				{
					SOMObject SOMSTAR o2=pfn2(o,&ev,"::CosNaming::NamingContext::bind");
					somTD_Contained_describe pfn3=(somTD_Contained_describe)
						somResolveByName(o2,"describe");
					Contained_Description desc=pfn3(o2,&ev);

					TypeCode_print(desc.value._type,&ev);
					somPrintf("\n");

					SOMFree(desc.name);

					SOMD_FreeType(&ev,&desc.value,TC_any);

					if (o2)
					{
						somTD_Contained_within pfn4=(somTD_Contained_within)
							somResolveByName(o2,"within");
						_IDL_SEQUENCE_Container seq=pfn4(o2,&ev);

						if (seq._length)
						{
							unsigned int i=0;

							while (i < seq._length)
							{
								somReleaseObjectReference(seq._buffer[i]);

								i++;
							}

							SOMFree(seq._buffer);
						}
					}

					somReleaseObjectReference(o2);
				}

				if (pfn2)
				{
					SOMObject SOMSTAR o2=pfn2(o,&ev,"::CosNaming::NamingContext");
					somTD_Contained_describe pfn3=(somTD_Contained_describe)
						somResolveByName(o2,"describe");
					Contained_Description desc=pfn3(o2,&ev);

					TypeCode_print(desc.value._type,&ev);
					somPrintf("\n");

					SOMFree(desc.name);

					SOMD_FreeType(&ev,&desc.value,TC_any);
					somReleaseObjectReference(o2);
				}


				if (pfn2)
				{
					SOMObject SOMSTAR o2=pfn2(o,&ev,"::SOMClassMgr::somInterfaceRepository");
					somTD_Contained_describe pfn3=(somTD_Contained_describe)
						somResolveByName(o2,"describe");
					Contained_Description desc=pfn3(o2,&ev);

					TypeCode_print(desc.value._type,&ev);
					somPrintf("\n");

					SOMFree(desc.name);
					SOMD_FreeType(&ev,&desc.value,TC_any);
					somReleaseObjectReference(o2);
				}


				if (pfn2)
				{
					SOMObject SOMSTAR o2=pfn2(o,&ev,"::CosNaming::NamingContext");
					somTD_InterfaceDef_describe_interface pfn3=(somTD_InterfaceDef_describe_interface)
						somResolveByName(o2,"describe_interface");
					InterfaceDef_FullInterfaceDescription desc=pfn3(o2,&ev);

					tcPrint(TC_FullInterfaceDescription,&ev);
					somPrintf("\n");

					SOMD_FreeType(&ev,&desc,TC_FullInterfaceDescription);

					somPrintf("done.\n");
					somReleaseObjectReference(o2);
				}

				if (pfn2)
				{
					SOMObject SOMSTAR o2=pfn2(o,&ev,"::ImplementationDef");
					somTD_Container_describe_contents pfn3=(somTD_Container_describe_contents)
						somResolveByName(o2,"describe_contents");
					_IDL_SEQUENCE_Container_ContainerDescription desc=pfn3(o2,&ev,"all",0,0);

					if (desc._length)
					{
						unsigned int i=0;

						while (i < desc._length)
						{
							somReleaseObjectReference(desc._buffer[i].contained_object);

							SOMFree(desc._buffer[i].name);

							SOMD_FreeType(&ev,&desc._buffer[i].value,TC_any);

							i++;
						}

						SOMFree(desc._buffer);
					}

					somPrintf("done.\n");
					somReleaseObjectReference(o2);
				}

				somReleaseObjectReference(o);
			}
		}

		SOMObject_somDumpSelf(mgr,0);
	}

	RHBOPT_unused(t);

	SOM_UninitEnvironment(&ev);

	somEnvironmentEnd();

	return 0;
}

