
function generate(templ, varlist)
	local r =string.gsub(templ, "%$(%w+)%$", varlist)
	return r
end

function generate_files(filename)
	local file = io.open(filename, "r")
	if not file then
		error("cannot open file " .. filename)
	end

	local lineno = 1

	for line in file:read("*l")
	end

end
