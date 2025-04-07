use arceos_posix_api::{self as api, ctypes::timeval};
use axerrno::LinuxResult;
use axhal::time::{NANOS_PER_SEC, monotonic_time_nanos, nanos_to_ticks};
use starry_core::{ctypes::SysInfo, ctypes::Tms, task::time_stat_output};

use crate::ptr::{PtrWrapper, UserPtr};

pub fn sys_clock_gettime(clock_id: i32, tp: UserPtr<api::ctypes::timespec>) -> LinuxResult<isize> {
    unsafe { Ok(api::sys_clock_gettime(clock_id, tp.get()?) as _) }
}

pub fn sys_get_time_of_day(ts: UserPtr<timeval>) -> LinuxResult<isize> {
    unsafe { Ok(api::sys_get_time_of_day(ts.get()?) as _) }
}

pub fn sys_times(tms: UserPtr<Tms>) -> LinuxResult<isize> {
    let (_, utime_us, _, stime_us) = time_stat_output();
    unsafe {
        *tms.get()? = Tms {
            tms_utime: utime_us,
            tms_stime: stime_us,
            tms_cutime: utime_us,
            tms_cstime: stime_us,
        }
    }
    Ok(nanos_to_ticks(monotonic_time_nanos()) as _)
}

/// get the system uptime and memory information.
/// # Arguments
/// * `info` - *mut SysInfo
pub fn sys_sysinfo(sysinfo: UserPtr<SysInfo>) -> LinuxResult<isize> {
    // let sysinfo = sysinfo.address().as_mut_ptr();
    // check if the pointer is valid
    // if sysinfo.is_null() {
    //     return Err(axerrno::LinuxError::EFAULT);
    // }
    // get the system uptime
    unsafe {
        *sysinfo.get()? = SysInfo {
            uptime: (monotonic_time_nanos() / NANOS_PER_SEC) as isize,
            loads: [0; 3],
            totalram: 0,
            freeram: 0,
            sharedram: 0,
            bufferram: 0,
            totalswap: 0,
            freeswap: 0,
            procs: 0,
            totalhigh: 0,
            freehigh: 0,
            mem_unit: 1,
        };
    }

    Ok(0)
}
