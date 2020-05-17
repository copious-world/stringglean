

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

    g_mlcl.critical(shmlgr_i,"bad things going down" .. 5.4 .. "in situ:" .. PI .. "in vitro" .. 10 .. "times")
    g_mlcl.error(shmlgr_i,"bad things oopsin all around" .. 2)
    g_mlcl.log(shmlgr_i,"made it around to here")
    g_mlcl.info(shmlgr_i,"you should know")

    print("run_task")
    --
end


return CopperClass