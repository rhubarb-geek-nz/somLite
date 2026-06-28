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
 */

#define WIN32_DLLIMPORT	  __declspec(dllimport)
#define MORE_THAN_SOM

#include <rhbopt.h>
#include <rhbsomex.h>
#include <som.h>

#include <stdlib.h>

struct class_data
{
	SOMClass SOMSTAR cls;
	long major;
	long minor;
	char *name;
	somMToken *ph;
	struct methods *methods;
	struct 
	{
		SOMAny obj;
		char buf[8192];
	} obj;
};

struct methods
{
	struct class_data *cls;
	somId id;
	struct methods *next;
};

static void confirm_class(struct class_data *cd,void *cds,SOMClass SOMSTAR cls,long major,long minor,char *name);
static void confirm_mtoken(struct class_data *cd,SOMClass SOMSTAR cls,somMToken token,char *name,somMToken *cdp);
static void confirm_ignore(struct class_data *cd,SOMClass SOMSTAR cls,char *name,somMToken *cdp);
static void confirm_cleanup(struct class_data *cd);

#define CHECK_CLASS(x)  { struct class_data cd_##x; somPrintf("checking class %s\n",#x); confirm_class(&cd_##x,&x##ClassData,_##x,x##_MajorVersion,x##_MinorVersion,#x);

#define CHECK_MTOKEN(x,y) { somTD_##x##_##y Z=NULL; } somPrintf("checking %s::%s\n",#x,#y); confirm_mtoken(&cd_##x,_##x,x##ClassData.y,#y,&(x##ClassData.y));
#define CHECK_MTOKEN_PRIVATE(x,y) somPrintf("checking %s::%s\n",#x,#y); confirm_mtoken(&cd_##x,_##x,x##ClassData.y,#y,&(x##ClassData.y));
#define CHECK_MTOKEN_IGNORE(x,y) somPrintf("ignoring %s::%s\n",#x,#y); confirm_ignore(&cd_##x,_##x,#y,(somToken *)&(x##ClassData.y));

#define END_CLASS(x)      confirm_cleanup(&cd_##x);  }


static void check_som(void)
{
	/* SOM.DLL */

	CHECK_CLASS(SOMObject)				/* somobj.idl */
	CHECK_MTOKEN(SOMObject,somInit)
	CHECK_MTOKEN(SOMObject,somUninit)
	CHECK_MTOKEN(SOMObject,somFree)
	CHECK_MTOKEN_PRIVATE(SOMObject,somDefaultVCopyInit)
	CHECK_MTOKEN(SOMObject,somGetClassName)
	CHECK_MTOKEN(SOMObject,somGetClass)
	CHECK_MTOKEN(SOMObject,somIsA)
	CHECK_MTOKEN(SOMObject,somRespondsTo)
	CHECK_MTOKEN(SOMObject,somIsInstanceOf)
	CHECK_MTOKEN(SOMObject,somGetSize)
	CHECK_MTOKEN(SOMObject,somDumpSelf)
	CHECK_MTOKEN(SOMObject,somDumpSelfInt)
	CHECK_MTOKEN(SOMObject,somPrintSelf)
	CHECK_MTOKEN_PRIVATE(SOMObject,somDefaultConstVCopyInit)
	CHECK_MTOKEN_IGNORE(SOMObject,somDispatchV)
	CHECK_MTOKEN_IGNORE(SOMObject,somDispatchL)
	CHECK_MTOKEN_IGNORE(SOMObject,somDispatchA)
	CHECK_MTOKEN_IGNORE(SOMObject,somDispatchD)
	CHECK_MTOKEN(SOMObject,somDispatch)
	CHECK_MTOKEN(SOMObject,somClassDispatch)
	CHECK_MTOKEN(SOMObject,somCastObj)
	CHECK_MTOKEN(SOMObject,somResetObj)
	CHECK_MTOKEN_PRIVATE(SOMObject,somDefaultInit)
	CHECK_MTOKEN_PRIVATE(SOMObject,somDestruct)
	CHECK_MTOKEN_IGNORE(SOMObject,somComputeForwardVisitMask)
	CHECK_MTOKEN_IGNORE(SOMObject,somComputeReverseVisitMask)
	CHECK_MTOKEN_PRIVATE(SOMObject,somDefaultCopyInit)
	CHECK_MTOKEN_PRIVATE(SOMObject,somDefaultConstCopyInit)
	CHECK_MTOKEN_PRIVATE(SOMObject,somDefaultAssign)
	CHECK_MTOKEN_PRIVATE(SOMObject,somDefaultConstAssign)
	CHECK_MTOKEN_PRIVATE(SOMObject,somDefaultVAssign)
	CHECK_MTOKEN_PRIVATE(SOMObject,somDefaultConstVAssign)
	END_CLASS(SOMObject)

	CHECK_CLASS(SOMClass)				/* somcls.idl */
	CHECK_MTOKEN(SOMClass,somNew)
	CHECK_MTOKEN(SOMClass,somRenew)
	CHECK_MTOKEN(SOMClass,somInitClass)
	CHECK_MTOKEN(SOMClass,somClassReady)
	CHECK_MTOKEN(SOMClass,somGetName)
	CHECK_MTOKEN(SOMClass,somGetParent)
	CHECK_MTOKEN(SOMClass,somDescendedFrom)
	CHECK_MTOKEN(SOMClass,somCheckVersion)
	CHECK_MTOKEN(SOMClass,somFindMethod)
	CHECK_MTOKEN(SOMClass,somFindMethodOk)
	CHECK_MTOKEN(SOMClass,somSupportsMethod)
	CHECK_MTOKEN(SOMClass,somGetNumMethods)
	CHECK_MTOKEN(SOMClass,somGetInstanceSize)
	CHECK_MTOKEN_IGNORE(SOMClass,somGetInstanceOffset)
 	CHECK_MTOKEN(SOMClass,somGetInstancePartSize)
	CHECK_MTOKEN(SOMClass,somGetMethodIndex)
	CHECK_MTOKEN(SOMClass,somGetNumStaticMethods)
 	CHECK_MTOKEN(SOMClass,somGetPClsMtab)
	CHECK_MTOKEN(SOMClass,somGetClassMtab)
 	CHECK_MTOKEN(SOMClass,somAddStaticMethod)
 	CHECK_MTOKEN(SOMClass,somOverrideSMethod)
	CHECK_MTOKEN(SOMClass,somAddDynamicMethod)
 	CHECK_MTOKEN_IGNORE(SOMClass,somGetMethodOffset)
 	CHECK_MTOKEN(SOMClass,somGetApplyStub)
	CHECK_MTOKEN(SOMClass,somFindSMethod)
  	CHECK_MTOKEN(SOMClass,somFindSMethodOk)
 	CHECK_MTOKEN(SOMClass,somGetMethodDescriptor)
 	CHECK_MTOKEN(SOMClass,somGetNthMethodInfo)
 	CHECK_MTOKEN(SOMClass,somSetClassData)
	CHECK_MTOKEN(SOMClass,somGetClassData)
 	CHECK_MTOKEN(SOMClass,somNewNoInit)
 	CHECK_MTOKEN(SOMClass,somRenewNoInit)
 	CHECK_MTOKEN(SOMClass,somGetInstanceToken)
 	CHECK_MTOKEN(SOMClass,somGetMemberToken)
 	CHECK_MTOKEN_IGNORE(SOMClass,somSetMethodDescriptor)
 	CHECK_MTOKEN(SOMClass,somGetMethodData)
  	CHECK_MTOKEN(SOMClass,somOverrideMtab)
	CHECK_MTOKEN(SOMClass,somGetMethodToken)
 	CHECK_MTOKEN(SOMClass,somGetParents)
	CHECK_MTOKEN_IGNORE(SOMClass,somGetPClsMtabs)
	CHECK_MTOKEN(SOMClass,somInitMIClass)
	CHECK_MTOKEN(SOMClass,somGetVersionNumbers)
	CHECK_MTOKEN(SOMClass,somLookupMethod)
 	CHECK_MTOKEN_PRIVATE(SOMClass,_get_somInstanceDataOffsets)
 	CHECK_MTOKEN(SOMClass,somRenewNoZero)
	CHECK_MTOKEN(SOMClass,somRenewNoInitNoZero)
	CHECK_MTOKEN(SOMClass,somAllocate)
	CHECK_MTOKEN(SOMClass,somDeallocate)
	CHECK_MTOKEN(SOMClass,somGetRdStub)
	CHECK_MTOKEN(SOMClass,somGetNthMethodData)
	CHECK_MTOKEN_IGNORE(SOMClass,somCloneClass)
	CHECK_MTOKEN_IGNORE(SOMClass,_get_somMethodOffsets);
	CHECK_MTOKEN(SOMClass,_get_somDirectInitClasses)
	CHECK_MTOKEN_PRIVATE(SOMClass,somClassAssert)
	CHECK_MTOKEN_IGNORE(SOMClass,somGetInstanceInitMask)
	CHECK_MTOKEN_IGNORE(SOMClass,somGetInstanceDestructionMask)
	CHECK_MTOKEN_IGNORE(SOMClass,somCastObjCls);
	CHECK_MTOKEN_IGNORE(SOMClass,somResetObjCls);
	CHECK_MTOKEN_IGNORE(SOMClass,_get_somTrueClass);
	CHECK_MTOKEN_IGNORE(SOMClass,_get_somCastedClass);
	CHECK_MTOKEN_IGNORE(SOMClass,somRegLPMToken)
	CHECK_MTOKEN(SOMClass,somDefinedMethod)
	CHECK_MTOKEN_IGNORE(SOMClass,somAddMethod);
	CHECK_MTOKEN_IGNORE(SOMClass,_get_somCClassData);
	CHECK_MTOKEN_IGNORE(SOMClass,_set_somCClassData)
	CHECK_MTOKEN_IGNORE(SOMClass,somClassOfNewClassWithParents);
	CHECK_MTOKEN_IGNORE(SOMClass,_set_somClassDataOrder)
	CHECK_MTOKEN_IGNORE(SOMClass,_get_somClassDataOrder)
	CHECK_MTOKEN_IGNORE(SOMClass,somGetClassDataEntry)
	CHECK_MTOKEN_IGNORE(SOMClass,somSetClassDataEntry)
	CHECK_MTOKEN(SOMClass,_get_somDataAlignment)
	CHECK_MTOKEN_IGNORE(SOMClass,somGetInstanceAssignmentMask)
	CHECK_MTOKEN_IGNORE(SOMClass,_get_somDirectAssignClasses)
	CHECK_MTOKEN_IGNORE(SOMClass,setUserPCallDispatch)
	CHECK_MTOKEN_IGNORE(SOMClass,_get_somClassAllocate)
	CHECK_MTOKEN_IGNORE(SOMClass,_get_somClassDeallocate)
	CHECK_MTOKEN_PRIVATE(SOMClass,somGetMarshalPlan)
	CHECK_MTOKEN_PRIVATE(SOMClass,somSetMarshalPlan)
	CHECK_MTOKEN_PRIVATE(SOMClass,somGetMethodDataWithoutDescriptor)
	CHECK_MTOKEN_PRIVATE(SOMClass,somJoin)
	CHECK_MTOKEN_PRIVATE(SOMClass,somEndow)
	CHECK_MTOKEN_IGNORE(SOMClass,somLookupTerminal)
	CHECK_MTOKEN_IGNORE(SOMClass,somMethodImplOwner)
	CHECK_MTOKEN_IGNORE(SOMClass,somSetUserPCallDispatch)
	CHECK_MTOKEN_IGNORE(SOMClass,somMakeUserRdStub)
	CHECK_MTOKEN_IGNORE(SOMClass,somGetMethodProc)
	CHECK_MTOKEN_IGNORE(SOMClass,somImportedClass)
	END_CLASS(SOMClass)

	CHECK_CLASS(SOMClassMgr)			/* somcm.idl */
	CHECK_MTOKEN(SOMClassMgr,somFindClsInFile)
	CHECK_MTOKEN(SOMClassMgr,somFindClass)
	CHECK_MTOKEN(SOMClassMgr,somClassFromId)
	CHECK_MTOKEN(SOMClassMgr,somRegisterClass)
	CHECK_MTOKEN(SOMClassMgr,somUnregisterClass)
	CHECK_MTOKEN(SOMClassMgr,somLocateClassFile)
	CHECK_MTOKEN(SOMClassMgr,somLoadClassFile)
	CHECK_MTOKEN(SOMClassMgr,somUnloadClassFile)
	CHECK_MTOKEN(SOMClassMgr,somGetInitFunction)
	CHECK_MTOKEN(SOMClassMgr,somMergeInto)
	CHECK_MTOKEN(SOMClassMgr,somGetRelatedClasses)
	CHECK_MTOKEN(SOMClassMgr,somSubstituteClass)
	CHECK_MTOKEN(SOMClassMgr,_get_somInterfaceRepository)
	CHECK_MTOKEN(SOMClassMgr,_set_somInterfaceRepository)
	CHECK_MTOKEN(SOMClassMgr,_get_somRegisteredClasses)
	CHECK_MTOKEN(SOMClassMgr,somBeginPersistentClasses)
	CHECK_MTOKEN(SOMClassMgr,somEndPersistentClasses)
	CHECK_MTOKEN_IGNORE(SOMClassMgr,somReleaseClasses)
	CHECK_MTOKEN_IGNORE(SOMClassMgr,somRegisterThreadUsage)
	CHECK_MTOKEN(SOMClassMgr,somRegisterClassLibrary)
	CHECK_MTOKEN(SOMClassMgr,somJoinAffinityGroup)
	CHECK_MTOKEN(SOMClassMgr,somUnregisterClassLibrary)
	CHECK_MTOKEN_PRIVATE(SOMClassMgr,somImportObject)
	CHECK_MTOKEN_PRIVATE(SOMClassMgr,somCIBFromClassId)
	CHECK_MTOKEN_PRIVATE(SOMClassMgr,somCopyOnImport)
	END_CLASS(SOMClassMgr)
}

int main(int argc,char **argv)
{
	SOMClassMgr SOMSTAR mgr=somEnvironmentNew();
	Environment ev;

	somPrintf("SOM_WarnLevel=%d\n",SOM_WarnLevel);
	somPrintf("SOM_TraceLevel=%d\n",SOM_TraceLevel);
	somPrintf("SOM_AssertLevel=%d\n",SOM_AssertLevel);
	somPrintf("SOM_MaxThreads=%d\n",SOM_MaxThreads);
	somPrintf("SOM_MajorVersion=%ld\n",SOM_MajorVersion);
	somPrintf("SOM_MinorVersion=%ld\n",SOM_MinorVersion);

	SOM_InitEnvironment(&ev);

	check_som();

	somPrintf("completed\n");

	somEnvironmentEnd();

	return 0;
}

static void dump_classTree(SOMClass SOMSTAR cls,int index,_IDL_SEQUENCE_SOMClass *seq)
{
	if (cls)
	{
		unsigned long i=seq->_length;
		_IDL_SEQUENCE_SOMClass s2={0,0,NULL};
		unsigned long totalSize=SOMClass_somGetInstanceSize(cls);
		unsigned long partSize=SOMClass_somGetInstancePartSize(cls);

		while (i--)
		{
			if (seq->_buffer[i]==cls) return;
		}
		somPrintf("[%d,%ld]=%s(%ld,%ld)\n",
				index,
				seq->_length,
				SOMClass_somGetName(cls),
				totalSize,
				partSize);
		if (seq->_length < seq->_maximum)
		{
			seq->_buffer[seq->_length++]=cls;
		}
		s2=SOMClass_somGetParents(cls);
		i=0;
		while (i < s2._length)
		{
			dump_classTree(s2._buffer[i],i+index,seq);

			i++;
		}
		if (s2._buffer) SOMFree(s2._buffer);
	}
}

static void confirm_class(struct class_data *cd,void *cds,SOMClass SOMSTAR cls,long major,long minor,char *name)
{
	somTD_SOMClass_somGetName somGetName=(somTD_SOMClass_somGetName)somResolveByName(cls,"somGetName");
	somTD_SOMClass_somGetVersionNumbers somGetVersionNumbers=(somTD_SOMClass_somGetVersionNumbers)somResolveByName(cls,"somGetVersionNumbers");
	somTD_SOMClass_somRenewNoInitNoZero somRenewNoInitNoZero=(somTD_SOMClass_somRenewNoInitNoZero)somResolveByName(cls,"somRenewNoInitNoZero");
	somTD_SOMClass_somGetClassData somGetClassData=(somTD_SOMClass_somGetClassData)somResolveByName(cls,"somGetClassData");
	long m1=0,m2=0;
	char *p=somGetName(cls);
	somClassDataStructure *cdsp=somGetClassData(cls);
	somTD_SOMClass_somGetClassMtab somGetClassMtab=(somTD_SOMClass_somGetClassMtab)somResolveByName(cls,"somGetClassMtab");
	somMethodTab *tab=somGetClassMtab(cls);

	cd->cls=cls;
	cd->major=major;
	cd->minor=minor;
	cd->methods=NULL;
	cd->name=name;

	{
		SOMClass SOMSTAR list[256];
		_IDL_SEQUENCE_SOMClass seq={sizeof(list)/sizeof(list[0]),0,list};
		dump_classTree(cls,0,&seq);
	}

	if (cds != cdsp)
	{
		somClassDataStructure *cdspp=cdsp;

		somPrintf("class data ptr mismatch,%p != %p\n",cds,cdsp);

		cdsp=cds;

		if (cdspp)
		{
			SOMClass SOMSTAR list[256];
			_IDL_SEQUENCE_SOMClass seq={sizeof(list)/sizeof(list[0]),0,list};

			dump_classTree(cdspp->classObject,0,&seq);
		}
	}


	cd->ph=cdsp->tokens;

	if (strcmp(p,name))
	{
		somTD_SOMObject_somDumpSelf pfn=(somTD_SOMObject_somDumpSelf)somResolveByName(cls,"somDumpSelf");
		somPrintf("wrong class name\n");
		pfn(cls,0);
		exit(1);
	}
	somGetVersionNumbers(cls,&m1,&m2);
	if ((m1!=major)||(m2!=minor))
	{
		somPrintf("actual %s(%ld,%ld) != expected (%ld,%ld)\n",
				name,
				m1,m2,
				major,minor);

		if ((major > m1)||((major==m1) && (minor> m2)))
		{
			exit(1);
		}
	}

	somRenewNoInitNoZero(cls,&cd->obj);

	if (cd->obj.obj.mtab!=tab)
	{
		/* ORB became SIProxyForORB,
			RegistryManager becamse SIProxyForRegistryManager
		*/
		somPrintf("mtab wrong? %p!=%p\n",cd->obj.obj.mtab,tab);
		somPrintf("mtab==%s\n",cd->obj.obj.mtab->className);

		if (cd->obj.obj.mtab)
		{
			SOMClass SOMSTAR list[256];
			_IDL_SEQUENCE_SOMClass seq={sizeof(list)/sizeof(list[0]),0,list};

			dump_classTree(cd->obj.obj.mtab->classObject,0,&seq);
		}
	}
}

static void confirm_mtoken(struct class_data *cd,SOMClass SOMSTAR cls,somMToken token,char *name,somMToken *cdp)
{
	somTD_SOMClass_somGetMethodData somGetMethodData=(somTD_SOMClass_somGetMethodData)somResolveByName(cls,"somGetMethodData");
	somMethodData data;
	somId id=somIdFromString(name);

	if (cdp != cd->ph) 
	{
		somPrintf("wrong order...\n");

		exit(1);
	}

	cd->ph++;

	if (!token)
	{
		somPrintf("is NULL\n");
		if (somGetMethodData(cls,id,&data))
		{
			somPrintf("found as %s\n",somStringFromId(data.descriptor));
		}
		exit(1);
	}
	else
	{
		somTD_SOMClass_somGetMethodToken somGetMethodToken=(somTD_SOMClass_somGetMethodToken)somResolveByName(cls,"somGetMethodToken");
		somMToken tok=somGetMethodToken(cls,id);
		somMethodPtr m1=NULL,m2=NULL;
		somTD_SOMClass_somGetNumMethods somGetNumMethods=(somTD_SOMClass_somGetNumMethods)somResolveByName(cls,"somGetNumMethods");
		somTD_SOMClass_somGetNthMethodData somGetNthMethodData=(somTD_SOMClass_somGetNthMethodData)somResolveByName(cls,"somGetNthMethodData");

	/*	somPrintf("doing the getmethoddata...\n");*/

		somGetMethodData(cls,id,&data);

	/*	somPrintf("doing the init...\n");*/

		if (token)
		{
			__try
			{
				m1=somResolve(&cd->obj.obj,token);
			}
			__except(1)
			{
				somPrintf("caught exception...\n");
			}
		}

		if ((!tok) || (!m1))
		{
			somPrintf("failed to get token %p, %x\n",token,token);

			if (m1) 
			{
				long i=somGetNumMethods(cls);
				while (i--)
				{
					if (somGetNthMethodData(cls,i,&data))
					{
						if (somResolve(&cd->obj.obj,data.mToken)==m1)
						{
							somPrintf("actually it matches %s\n",somStringFromId(data.descriptor));
						}
					}
				}
			}

			
			exit(1);
		}

	/*	somPrintf("doing the resolve...\n");*/

		__try
		{
			m2=somResolve(&cd->obj.obj,tok);
		}
		__except(1)
		{
			somPrintf("caught exception...\n");
		}

		if (m1 != m2)
		{
			somTD_SOMClass_somGetName pfn=(somTD_SOMClass_somGetName)somResolveByName(cls,"somGetName");
			char *c=pfn(cls);
			somPrintf("m1=%p,m2=%p\n",m1,m2);
			somPrintf("token=%p\n",token);
			somPrintf("tok=%p\n",tok);

			somPrintf("id=%s\n",somStringFromId(data.id));
			somPrintf("desc=%s\n",somStringFromId(data.descriptor));
			somPrintf("token=%p\n",data.mToken);
			somPrintf("mptr=%p\n",data.method);

			somPrintf("%s::%s\n",c,name);


			{
				long i=somGetNumMethods(cls);
				while (i--)
				{
					if (somGetNthMethodData(cls,i,&data))
					{
						if (somResolve(&cd->obj.obj,data.mToken)==m1)
						{
							somPrintf("actually it matches %s\n",somStringFromId(data.descriptor));
						}
					}
				}
			}

			exit(1);
		}
	}

	if (id)
	{
		struct methods *m=SOMMalloc(sizeof(*m));

		m->next=cd->methods;
		m->id=id;
		m->cls=cd;
		cd->methods=m;
	}
}

static void confirm_ignore(struct class_data *cd,SOMClass SOMSTAR cls,char *name,somMToken *cdp)
{
	somId id=somIdFromString(name);

	if (cdp != cd->ph) 
	{
		somPrintf("wrong order...\n");

		exit(1);
	}

	cd->ph++;
	if (id)
	{
		struct methods *m=SOMMalloc(sizeof(*m));

		m->next=cd->methods;
		m->id=id;
		m->cls=cd;
		cd->methods=m;
	}
}

static void confirm_cleanup(struct class_data *cd)
{
	long totalNum=SOMClass_somGetNumStaticMethods(cd->cls);
	long n=0,j=0;

	while (j < totalNum)
	{
		somMethodData data;
		int i=(int)strlen(cd->name);
		
		if (SOMClass_somGetNthMethodData(cd->cls,j,&data))
		{
			char *desc=somStringFromId(data.descriptor);

			if (!memcmp(desc,cd->name,i))
			{
				struct methods *m=cd->methods;

				while (m)
				{
					if (somCompareIds(m->id,data.id))
					{
						somMethodPtr p=NULL;

						if (SOMClass_somFindMethod(cd->cls,m->id,&p))
						{	
					/*	break;*/
						}

						if (p) break;
					}

					m=m->next;
				}

				if (!m)
				{
					somPrintf("\tCHECK_MTOKEN(%s)\n",desc);
					n++;
				}
			}
		}

		j++;
	}

	if (n)
	{
		exit(1);
	}
}

