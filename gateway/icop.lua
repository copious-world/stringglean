-- FOR USE WITH GPP preprocessor
local _i_prs = ffi.new("int [?]", MAX_INT_PARMS)
local _f_prs = ffi.new("float [?]", MAX_FLOAT_PARMS)
-- -- -- -- -- -- -- --
-- -- -- -- -- -- -- --
-- -- -- -- -- -- -- --
-- -- -- -- -- -- -- --
--
--
--
--
--
local CopperClass = {}
--
-- should be called from the factory..
--
function CopperClass:new (o)
o = o or {}   -- create object if user does not provide one
self.uuid = 111
self.loggerId = g_mlcl.get_logger('CopperC')
--
return o
end
function CopperClass:run_task()
--
local shmlgr_i = self.loggerId -- use the macros to write  -- symbolic replacement -- number set later
_f_prs[1] = 3; _f_prs[2] = (-4); _f_prs[3] = 7; _f_prs[4] = (-4); _f_prs[5] = 8; _f_prs[6] = (-2); _f_prs[7] = 13; _f_prs[8] = (-5); _f_prs[9] = 5.4; _f_prs[10] = PI; _f_prs[11] = 10;  g_mlcl.f_critical(shmlgr_i,11,_f_prs)
_i_prs[1] = 4; _i_prs[2] = (-2); _i_prs[3] = (-5); _i_prs[4] = 2;  g_mlcl.i_error(shmlgr_i,4,_i_prs)
_i_prs[1] = 10; _i_prs[2] = (-5);  g_mlcl.i_log(shmlgr_i,2,_i_prs)
_i_prs[1] = 14; _i_prs[2] = (-5);  g_mlcl.i_info(shmlgr_i,2,_i_prs)
print("run_task")
--
end
return CopperClass

