--[[
ffi interface to shared memory logging library. ...
--]]
local ffi = require("ffi")
ffi.cdef[[
//
void init(const char *app_tag,const unsigned char maxLoggers,const unsigned int perLoggerMsgCount,const unsigned char cpuCount,const unsigned int cpu_index,const unsigned int shmkey);
void release(void);
//
unsigned long int getTotalSize(void);
//
//	//
void i_log(const unsigned int logger, int count, const int *params);
void f_log(const unsigned int logger, int count, const float *params);
void i_warn(const unsigned int logger, int count, const int *params);
void f_warn(const unsigned int logger, int count, const float *params);
void i_error(const unsigned int logger, int count, const int *params);
void f_error(const unsigned int logger, int count, const float *params);
void i_critical(const unsigned int logger, int count, const int *params);
void f_critical(const unsigned int logger, int count, const float *params);
void i_info(const unsigned int logger, int count, const int *params);
void f_info(const unsigned int logger, int count, const float *params);
void i_debug(const unsigned int logger, int count, const int *params);
void f_debug(const unsigned int logger, int count, const float *params);
//
//
unsigned int get_logger(const char *tag);
void unget_logger(unsigned int logger_id);
//
]]
local lshm = ffi.load("lualogshm")
local MAX_INT_PARMS = 20
local MAX_FLOAT_PARMS = 10
local g_int_pars = ffi.new("int [?]", MAX_INT_PARMS);
local g_float_pars = ffi.new("float [?]", MAX_FLOAT_PARMS);
local LoggerClass = {}
function LoggerClass.i_log(logger_i,count,...) {
local parm={...}
for i=1,count do
g_int_pars[i] = parm[i]
end
lshm.i_log(logger_i,count,g_int_pars)
}
function LoggerClass.f_log(logger_i,count,...) {
local parm={...}
for i=1,count do
g_float_pars[i] = parm[i]
end
lshm.f_log(logger_i,count,g_float_pars)
}
--
function LoggerClass.i_warn(logger_i,count,...) {
local parm={...}
for i=1,count do
g_int_pars[i] = parm[i]
end
lshm.i_warn(logger_i,count,g_int_pars)
}
function LoggerClass.f_warn(logger_i,count,...) {
local parm={...}
for i=1,count do
g_float_pars[i] = parm[i]
end
lshm.f_warn(logger_i,count,g_float_pars)
}
--
--
function LoggerClass.i_error(logger_i,count,...) {
local parm={...}
for i=1,count do
g_int_pars[i] = parm[i]
end
lshm.i_error(logger_i,count,g_int_pars)
}
function LoggerClass.f_error(logger_i,count,...) {
local parm={...}
for i=1,count do
g_float_pars[i] = parm[i]
end
lshm.f_error(logger_i,count,g_float_pars)
}
--
--
function LoggerClass.i_critical(logger_i,count,...) {
local parm={...}
for i=1,count do
g_int_pars[i] = parm[i]
end
lshm.i_critical(logger_i,count,g_int_pars)
}
function LoggerClass.f_critical(logger_i,count,...) {
local parm={...}
for i=1,count do
g_float_pars[i] = parm[i]
end
lshm.f_critical(logger_i,count,g_float_pars)
}
--
--
function LoggerClass.i_info(logger_i,count,...) {
local parm={...}
for i=1,count do
g_int_pars[i] = parm[i]
end
lshm.i_info(logger_i,count,g_int_pars)
}
function LoggerClass.f_info(logger_i,count,...) {
local parm={...}
for i=1,count do
g_float_pars[i] = parm[i]
end
lshm.f_info(logger_i,count,g_float_pars)
}
--
--
function LoggerClass.i_debug(logger_i,count,...) {
local parm={...}
for i=1,count do
g_int_pars[i] = parm[i]
end
lshm.i_debug(logger_i,count,g_int_pars)
}
function LoggerClass.f_debug(logger_i,count,...) {
local parm={...}
for i=1,count do
g_float_pars[i] = parm[i]
end
lshm.f_debug(logger_i,count,g_int_pars)
}
--
return LoggerClass

