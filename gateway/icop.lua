-- FOR USE WITH GPP preprocessor
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
g_mlcl.f_critical(shmlgr_i,12,[3,(-4),7,(-4),8,(-2),13,(-5),10,0xffffffff,5.4,PI])
g_mlcl.i_error(shmlgr_i,4,[4,(-2),(-5),2])
g_mlcl.i_log(shmlgr_i,2,[10,(-5)])
g_mlcl.i_info(shmlgr_i,2,[14,(-5)])
print("run_task")
--
end
return CopperClass

