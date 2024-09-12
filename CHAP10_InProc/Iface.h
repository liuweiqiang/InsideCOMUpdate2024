

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 22:14:07 2038
 */
/* Compiler settings for SERVER.IDL:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Iface_h__
#define __Iface_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IX_FWD_DEFINED__
#define __IX_FWD_DEFINED__
typedef interface IX IX;

#endif 	/* __IX_FWD_DEFINED__ */


#ifndef __IY_FWD_DEFINED__
#define __IY_FWD_DEFINED__
typedef interface IY IY;

#endif 	/* __IY_FWD_DEFINED__ */


#ifndef __IZ_FWD_DEFINED__
#define __IZ_FWD_DEFINED__
typedef interface IZ IZ;

#endif 	/* __IZ_FWD_DEFINED__ */


#ifndef __Component1_FWD_DEFINED__
#define __Component1_FWD_DEFINED__

#ifdef __cplusplus
typedef class Component1 Component1;
#else
typedef struct Component1 Component1;
#endif /* __cplusplus */

#endif 	/* __Component1_FWD_DEFINED__ */


#ifndef __Component2_FWD_DEFINED__
#define __Component2_FWD_DEFINED__

#ifdef __cplusplus
typedef class Component2 Component2;
#else
typedef struct Component2 Component2;
#endif /* __cplusplus */

#endif 	/* __Component2_FWD_DEFINED__ */


#ifndef __Component3_FWD_DEFINED__
#define __Component3_FWD_DEFINED__

#ifdef __cplusplus
typedef class Component3 Component3;
#else
typedef struct Component3 Component3;
#endif /* __cplusplus */

#endif 	/* __Component3_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IX_INTERFACE_DEFINED__
#define __IX_INTERFACE_DEFINED__

/* interface IX */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IX;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32bb8323-b41b-11cf-a6bb-0080c7b2d682")
    IX : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FxStringIn( 
            /* [string][in] */ wchar_t *szIn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FxStringOut( 
            /* [string][out] */ wchar_t **szOut) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IXVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IX * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IX * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IX * This);
        
        DECLSPEC_XFGVIRT(IX, FxStringIn)
        HRESULT ( STDMETHODCALLTYPE *FxStringIn )( 
            IX * This,
            /* [string][in] */ wchar_t *szIn);
        
        DECLSPEC_XFGVIRT(IX, FxStringOut)
        HRESULT ( STDMETHODCALLTYPE *FxStringOut )( 
            IX * This,
            /* [string][out] */ wchar_t **szOut);
        
        END_INTERFACE
    } IXVtbl;

    interface IX
    {
        CONST_VTBL struct IXVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IX_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IX_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IX_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IX_FxStringIn(This,szIn)	\
    ( (This)->lpVtbl -> FxStringIn(This,szIn) ) 

#define IX_FxStringOut(This,szOut)	\
    ( (This)->lpVtbl -> FxStringOut(This,szOut) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IX_INTERFACE_DEFINED__ */


#ifndef __IY_INTERFACE_DEFINED__
#define __IY_INTERFACE_DEFINED__

/* interface IY */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IY;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32bb8324-b41b-11cf-a6bb-0080c7b2d682")
    IY : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FyCount( 
            /* [out] */ long *sizeArray) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FyArrayIn( 
            /* [in] */ long sizeIn,
            /* [size_is][in] */ long arrayIn[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FyArrayOut( 
            /* [in][out] */ long *psizeInOut,
            /* [size_is][out] */ long arrayOut[  ]) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IYVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IY * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IY * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IY * This);
        
        DECLSPEC_XFGVIRT(IY, FyCount)
        HRESULT ( STDMETHODCALLTYPE *FyCount )( 
            IY * This,
            /* [out] */ long *sizeArray);
        
        DECLSPEC_XFGVIRT(IY, FyArrayIn)
        HRESULT ( STDMETHODCALLTYPE *FyArrayIn )( 
            IY * This,
            /* [in] */ long sizeIn,
            /* [size_is][in] */ long arrayIn[  ]);
        
        DECLSPEC_XFGVIRT(IY, FyArrayOut)
        HRESULT ( STDMETHODCALLTYPE *FyArrayOut )( 
            IY * This,
            /* [in][out] */ long *psizeInOut,
            /* [size_is][out] */ long arrayOut[  ]);
        
        END_INTERFACE
    } IYVtbl;

    interface IY
    {
        CONST_VTBL struct IYVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IY_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IY_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IY_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IY_FyCount(This,sizeArray)	\
    ( (This)->lpVtbl -> FyCount(This,sizeArray) ) 

#define IY_FyArrayIn(This,sizeIn,arrayIn)	\
    ( (This)->lpVtbl -> FyArrayIn(This,sizeIn,arrayIn) ) 

#define IY_FyArrayOut(This,psizeInOut,arrayOut)	\
    ( (This)->lpVtbl -> FyArrayOut(This,psizeInOut,arrayOut) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IY_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_SERVER_0000_0002 */
/* [local] */ 

typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_SERVER_0000_0002_0001
    {
    double x;
    double y;
    double z;
    } 	Point3d;



extern RPC_IF_HANDLE __MIDL_itf_SERVER_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SERVER_0000_0002_v0_0_s_ifspec;

#ifndef __IZ_INTERFACE_DEFINED__
#define __IZ_INTERFACE_DEFINED__

/* interface IZ */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IZ;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32bb8325-b41b-11cf-a6bb-0080c7b2d682")
    IZ : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FzStructIn( 
            /* [in] */ Point3d pt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FzStructOut( 
            /* [out] */ Point3d *pt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IZVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IZ * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IZ * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IZ * This);
        
        DECLSPEC_XFGVIRT(IZ, FzStructIn)
        HRESULT ( STDMETHODCALLTYPE *FzStructIn )( 
            IZ * This,
            /* [in] */ Point3d pt);
        
        DECLSPEC_XFGVIRT(IZ, FzStructOut)
        HRESULT ( STDMETHODCALLTYPE *FzStructOut )( 
            IZ * This,
            /* [out] */ Point3d *pt);
        
        END_INTERFACE
    } IZVtbl;

    interface IZ
    {
        CONST_VTBL struct IZVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IZ_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IZ_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IZ_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IZ_FzStructIn(This,pt)	\
    ( (This)->lpVtbl -> FzStructIn(This,pt) ) 

#define IZ_FzStructOut(This,pt)	\
    ( (This)->lpVtbl -> FzStructOut(This,pt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IZ_INTERFACE_DEFINED__ */



#ifndef __ServerLib_LIBRARY_DEFINED__
#define __ServerLib_LIBRARY_DEFINED__

/* library ServerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ServerLib;

EXTERN_C const CLSID CLSID_Component1;

#ifdef __cplusplus

class DECLSPEC_UUID("0c092c29-882c-11cf-a6bb-0080c7b2d682")
Component1;
#endif

EXTERN_C const CLSID CLSID_Component2;

#ifdef __cplusplus

class DECLSPEC_UUID("0c092c2a-882c-11cf-a6bb-0080c7b2d682")
Component2;
#endif

EXTERN_C const CLSID CLSID_Component3;

#ifdef __cplusplus

class DECLSPEC_UUID("0c092c2b-882c-11cf-a6bb-0080c7b2d682")
Component3;
#endif
#endif /* __ServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


