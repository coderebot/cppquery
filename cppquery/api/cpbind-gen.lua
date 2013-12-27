-- generate cpbind.h

function generate(templ, varlist)
	local r =string.gsub(templ, "%$([%w_]+)%$", varlist)
	return r
end

print[[
#ifndef CP_BIND_H
#define CP_BIND_H

#include "cqfunction.h"

namespace cppquery {

]]


-- bind normal function
print[[
template<class R>
function_t<function_ptr0<R>, list0> bind(R (*f) (void) )
{ return function_t<function_ptr0<R>, list0>(function_ptr0<R>(f), list0()); }
]]

ClassTs="class T1"
ClassAs="class A1"
Ts="T1"
As="A1"
AConst_as="A1 a1"
as="a1"
for i = 1,9 do

print(generate([[

template<class R, $ClassTs$, $ClassAs$>
function_t<function_ptr$N$<R,$Ts$>, list$N$<$As$> > bind(R (*f)($Ts$), $AConst_as$)
{ return function_t<function_ptr$N$<R,$Ts$>, list$N$<$As$> >(function_ptr$N$<R,$Ts$>(f), list$N$<$As$>($as$)); }
]],
{
	N = i,
	ClassTs = ClassTs,
	ClassAs = ClassAs,
	Ts = Ts,
	As = As,
	AConst_as = AConst_as,
	as = as
}))
ClassTs = ClassTs .. ", class T" .. i + 1
ClassAs = ClassAs .. ", class A" .. i + 1
Ts = Ts .. ", T" .. i + 1
As = As .. ", A" .. i + 1
AConst_as = AConst_as .. ", " .. string.format("A%d a%d", i + 1, i + 1)
as = as .. ", a" .. i + 1
end

--- bind for __stdcall --
print[[
//wind3 bind
#ifdef WIN32
template<class R>
function_t<function_ptr_cbapi0<R>, list0> bind(R (CBAPI *f) (void) )
{ return function_t<function_ptr_cbapi0<R>, list0>(function_ptr_cbapi0<R>(f), list0()); }
]]

ClassTs="class T1"
ClassAs="class A1"
Ts="T1"
As="A1"
AConst_as="A1 a1"
as="a1"
for i = 1,9 do

print(generate([[

template<class R, $ClassTs$, $ClassAs$>
function_t<function_ptr_cbapi$N$<R,$Ts$>, list$N$<$As$> > bind(R (CBAPI *f)($Ts$), $AConst_as$)
{ return function_t<function_ptr_cbapi$N$<R,$Ts$>, list$N$<$As$> >(function_ptr_cbapi$N$<R,$Ts$>(f), list$N$<$As$>($as$)); }
]],
{
	N = i,
	ClassTs = ClassTs,
	ClassAs = ClassAs,
	Ts = Ts,
	As = As,
	AConst_as = AConst_as,
	as = as
}))
ClassTs = ClassTs .. ", class T" .. i + 1
ClassAs = ClassAs .. ", class A" .. i + 1
Ts = Ts .. ", T" .. i + 1
As = As .. ", A" .. i + 1
AConst_as = AConst_as .. ", " .. string.format("A%d a%d", i + 1, i + 1)
as = as .. ", a" .. i + 1
end
print[[
#endif //WIN32
]]

--- method bind
print[[

template<class R, class X, class XRef>
function_t<method_function0<R,X>, list1<XRef> > bind(R (X::*f)(), XRef self)
{ return function_t<method_function0<R, X>, list1<XRef> >(method_function0<R, X>(f), list1<XRef>(self)); }
template<class R, class X, class XRef>
function_t<method_const_function0<R,X>, list1<XRef> > bind(R (X::*f)() const, XRef self)
{ return function_t<method_const_function0<R, X>, list1<XRef> >(method_function0<R, X>(f), list1<XRef>(self)); }
]]


ClassTs="class T1"
ClassAs="class A1"
Ts="T1"
As="A1"
AConst_as="A1 a1"
as="a1"
for i = 2,9 do

print(generate([[

template<class R, class X, class XRef, $ClassTs$, $ClassAs$>
function_t<method_function$MN$<R, X, $Ts$>, list$N$<XRef, $As$> > bind(R (*f)($Ts$), XRef self, $AConst_as$)
{ return function_t<method_function$MN$<R,$Ts$>, list$N$<XRef, $As$> >(method_function$MN$<R, X, $Ts$>(f), list$N$<XRef, $As$>(self, $as$)); }
template<class R, class X, class XRef, $ClassTs$, $ClassAs$>
function_t<method_const_function$MN$<R, X, $Ts$>, list$N$<XRef, $As$> > bind(R (*f)($Ts$), XRef self, $AConst_as$)
{ return function_t<method_const_function$MN$<R,$Ts$>, list$MN$<XRef, $As$> >(method_const_function$MN$<R, X, $Ts$>(f), list$N$<XRef, $As$>(self, $as$)); }
]],
{
	MN = i-1,
	N = i,
	ClassTs = ClassTs,
	ClassAs = ClassAs,
	Ts = Ts,
	As = As,
	AConst_as = AConst_as,
	as = as
}))
ClassTs = ClassTs .. ", class T" .. i
ClassAs = ClassAs .. ", class A" .. i
Ts = Ts .. ", T" .. i
As = As .. ", A" .. i
AConst_as = AConst_as .. ", " .. string.format("A%d a%d", i, i)
as = as .. ", a" .. i
end


print[[
}

#endif
]]


