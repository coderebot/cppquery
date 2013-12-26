-- generate the template for function

function generate(templ, varlist)
	local r =string.gsub(templ, "%$(%w+)%$", varlist)
	return r
end

--- gen method ptr
method_ptr_templ=[[
template<class R, class X, $TempArgDef$> struct method_function$N$ {
	typedef R(X::*method)($ArgDef$);
	typedef R result_type;
	method method_;
	method_function$N$(method const& m) : method_(m) { }
	method_function$N$(method_function$N$ const& m): method_(m.method_) { }
	R operator()(X* x) const
	{ return (x->*method_)(); }
	R operator()(X& x) const
	{ return (x.*method_)(); }
};
template<class R, class X, $TempArgDef$> struct method_const_function$N$ {
	typedef R(X::*method)($ArgDef$) const;
	typedef R result_type;
	method method_;
	method_const_function$N$(method const& m) : method_(m) { }
	method_const_function$N$(method_const_function$N$ const& m): method_(m.method_) { }
	R operator()(X const* x) const
	{ return (x->*method_)(); }
	R operator()(X const& x) const
	{ return (x.*method_)(); }
};
template<class R, class X, $TempArgDef$> method_function$N$<R,X,$ArgDef$> method_ptr(R(X::*f)($ArgDef$))
{ return method_function$N$<R,X,$ArgDef$>(f); }
template<class R, class X, $TempArgDef$> method_const_function$N$<R,X,$ArgDef$> method_ptr(R(X::*f)($ArgDef$)const)
{ return method_const_function$N$<R,X,$ArgDef$>(f); }
]]

function gen_template_arg_list(base, n)
	local def_list=""
	local arg_list=""
	local arg_def_list=""
	local arg_def_const_list=""
	local call_list=""
	for i=1,n do
		def_list = def_list .. string.format("class %s%d, ", string.upper(base), i)
		arg_list = arg_list .. string.format("%s%d, ", string.upper(base), i)
		arg_def_list = arg_def_list .. string.format("%s%d %s%d, ", string.upper(base), i, string.lower(base), i)
		arg_def_const_list = arg_def_const_list .. string.format(", %s%d const& %s%d, ", string.upper(base), i, string.lower(base), i)
		call_list = call_list .. string.format("%s%d, ", string.lower(base), i)
	end
	return {
		N = n,
		TempArgDef = string.sub(def_list, 1, #def_list-2),
		ArgDef = string.sub(arg_list, 1, #arg_list-2),
		ArgDefName = string.sub(arg_def_list, 1, #arg_def_list-2),
		ArgConstDef = string.sub(arg_def_const_list, 1, #arg_def_const_list-2),
		CallDef = string.sub(call_list, 1, #call_list-2),
	}
end

function gen_all(templ, base, s, e)
	for i=s,e do
		print(generate(templ, gen_template_arg_list(base, i)))
		print("")
	end
end

--gen_all(method_ptr_templ, "T", 1, 9)

print("/////////////////////////////////////////////")
print[[

template<class F>
function_t<F, list0> make_function(F const &f){
	return function_t<F, list0>(f, list0());
}
]]

make_function_templ=[[
template<class F, $TempArgDef$>
function_t<F, list$N$<$ArgDef$> > make_function(F const& f, $ArgDefName$)
{ return function_t<F, list$N$<$ArgDef$> >(f, list$N$<$ArgDef$>($CallDef$)); }
]]
gen_all(make_function_templ, "A", 1, 9)
