

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 22:14:07 2038
 */
/* Compiler settings for ..\CHAP11\SERVER.IDL:
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


#ifndef __Component_FWD_DEFINED__
#define __Component_FWD_DEFINED__

#ifdef __cplusplus
typedef class Component Component;
#else
typedef struct Component Component;
#endif /* __cplusplus */

#endif 	/* __Component_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IX_INTERFACE_DEFINED__
#define __IX_INTERFACE_DEFINED__

/* interface IX */
/* [oleautomation][dual][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IX;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32BB8326-B41B-11CF-A6BB-0080C7B2D682")
    IX : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Fx( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FxStringIn( 
            /* [in] */ BSTR bstrIn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FxStringOut( 
            /* [retval][out] */ BSTR *pbstrOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FxFakeError( void) = 0;
        
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
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IX * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IX * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IX * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IX * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IX, Fx)
        HRESULT ( STDMETHODCALLTYPE *Fx )( 
            IX * This);
        
        DECLSPEC_XFGVIRT(IX, FxStringIn)
        HRESULT ( STDMETHODCALLTYPE *FxStringIn )( 
            IX * This,
            /* [in] */ BSTR bstrIn);
        
        DECLSPEC_XFGVIRT(IX, FxStringOut)
        HRESULT ( STDMETHODCALLTYPE *FxStringOut )( 
            IX * This,
            /* [retval][out] */ BSTR *pbstrOut);
        
        DECLSPEC_XFGVIRT(IX, FxFakeError)
        HRESULT ( STDMETHODCALLTYPE *FxFakeError )( 
            IX * This);
        
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


#define IX_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IX_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IX_Fx(This)	\
    ( (This)->lpVtbl -> Fx(This) ) 

#define IX_FxStringIn(This,bstrIn)	\
    ( (This)->lpVtbl -> FxStringIn(This,bstrIn) ) 

#define IX_FxStringOut(This,pbstrOut)	\
    ( (This)->lpVtbl -> FxStringOut(This,pbstrOut) ) 

#define IX_FxFakeError(This)	\
    ( (This)->lpVtbl -> FxFakeError(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IX_INTERFACE_DEFINED__ */



#ifndef __ServerLib_LIBRARY_DEFINED__
#define __ServerLib_LIBRARY_DEFINED__

/* library ServerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ServerLib;

EXTERN_C const CLSID CLSID_Component;

#ifdef __cplusplus

class DECLSPEC_UUID("0C092C2C-882C-11CF-A6BB-0080C7B2D682")
Component;
#endif
#endif /* __ServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


