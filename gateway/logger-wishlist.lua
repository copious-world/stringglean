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
local _i_prs = ffi.new("int [?]", MAX_INT_PARMS)
local _f_prs = ffi.new("float [?]", MAX_FLOAT_PARMS)
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
_f_prs[1] = 3; _f_prs[2] = (-4); _f_prs[3] = 7; _f_prs[4] = (-4); _f_prs[5] = 8; _f_prs[6] = (-2); _f_prs[7] = 13; _f_prs[8] = (-5); _f_prs[9] = 5.4; _f_prs[10] = PI; _f_prs[11] = 10;  g_mlcl.f_critical(shmlgr_i,11,_f_prs)
_i_prs[1] = 4; _i_prs[2] = (-2); _i_prs[3] = (-5); _i_prs[4] = 2;  g_mlcl.i_error(shmlgr_i,4,_i_prs)
_i_prs[1] = 10; _i_prs[2] = (-5);  g_mlcl.i_log(shmlgr_i,2,_i_prs)
_i_prs[1] = 14; _i_prs[2] = (-5);  g_mlcl.i_info(shmlgr_i,2,_i_prs)
--
-- top level main process exits
g_mlcl.release() -- stop using this for the entire application
--
print(string.format("elapsed time: %.2fn", os.clock() - start_time))
print(collectgarbage("count"))

