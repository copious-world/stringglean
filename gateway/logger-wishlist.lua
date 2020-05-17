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
--   -- load library
g_mlcl = require("shm_logger") -- set it to be used by macros -- precompile
--
--
--
local app_tag = "TestAPP"
local shmkey = 3453
local maxLoggers = 512
local maxMessageSize = 250
local cpu_index = 1  -- -- set by command line args
local cpuCount = 4
-- -- CALL INIT ONCE PER APPLICATION PROCESS/THREAD
g_mlcl.init(app_tag,maxLoggers,maxMessageSize,cpuCount,cpu_index,shmkey)
-- -- CALL GET at least once -- call it per module or specific context (e.g. api lifecycle)
-- --              -- get_logger returns an index from C++ lib
local shmlgr_i = g_mlcl.get_logger('shm-1') -- use the macros to write  -- symbolic replacement -- number set later
--
--
local start_time = os.clock()
local instance_cop = require('icop')
instance_cop:run_task()
--
--
g_mlcl.f_critical(shmlgr_i,12,[3,(-4),7,(-4),8,(-2),13,(-5),10,0xffffffff,5.4,PI])
g_mlcl.i_error(shmlgr_i,4,[4,(-2),(-5),2])
g_mlcl.i_log(shmlgr_i,2,[10,(-5)])
g_mlcl.i_info(shmlgr_i,2,[14,(-5)])
--
-- top level main process exits
g_mlcl.release() -- stop using this for the entire application
--
print(string.format("elapsed time: %.2fn", os.clock() - start_time))
print(collectgarbage("count"))

