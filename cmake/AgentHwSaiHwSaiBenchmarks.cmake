# CMake to build libraries and binaries in fboss/agent/hw/sai/hw_test

# In general, libraries and binaries in fboss/foo/bar are built by
# cmake/FooBar.cmake

function(BUILD_SAI_BENCHMARKS SAI_IMPL_NAME SAI_IMPL_ARG)

  message(STATUS "Building SAI_IMPL_NAME: ${SAI_IMPL_NAME} SAI_IMPL_ARG: ${SAI_IMPL_ARG}")

  add_executable(sai_fsw_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_fsw_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    -Wl,--whole-archive
    hw_fsw_scale_route_add_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    route_scale_gen
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_fsw_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_fsw_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_fsw_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    -Wl,--whole-archive
    hw_fsw_scale_route_del_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    route_scale_gen
    ${SAI_IMPL_ARG}
    sai_switch_ensemble
  )

  set_target_properties(sai_fsw_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_th_alpm_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_th_alpm_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    -Wl,--whole-archive
    hw_th_alpm_scale_route_add_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    route_scale_gen
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_th_alpm_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_th_alpm_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_th_alpm_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    -Wl,--whole-archive
    hw_th_alpm_scale_route_del_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    route_scale_gen
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_th_alpm_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_hgrid_du_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_hgrid_du_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    -Wl,--whole-archive
    hw_hgrid_du_scale_route_add_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    route_scale_gen
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_hgrid_du_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_hgrid_du_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_hgrid_du_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    -Wl,--whole-archive
    hw_hgrid_du_scale_route_del_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    route_scale_gen
    ${SAI_IMPL_ARG}

  )

  set_target_properties(sai_hgrid_du_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_hgrid_uu_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_hgrid_uu_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    -Wl,--whole-archive
    hw_hgrid_uu_scale_route_add_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    route_scale_gen
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_hgrid_uu_scale_route_add_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_hgrid_uu_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_hgrid_uu_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    -Wl,--whole-archive
    hw_hgrid_uu_scale_route_del_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    route_scale_gen
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_hgrid_uu_scale_route_del_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_stats_collection_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_stats_collection_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    -Wl,--whole-archive
    hw_stats_collection_speed
    -Wl,--no-whole-archive
    sai_switch_ensemble
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_stats_collection_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_tx_slow_path_rate-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_tx_slow_path_rate-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    hw_tx_slow_path_rate
    sai_switch_ensemble
    -Wl,--no-whole-archive
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_tx_slow_path_rate-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_warm_boot_exit_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_warm_boot_exit_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    hw_warm_boot_exit_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_warm_boot_exit_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_ecmp_shrink_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_ecmp_shrink_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    hw_ecmp_shrink_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    sai_ecmp_utils
    sai_port_utils
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_ecmp_shrink_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )

  add_executable(sai_ecmp_shrink_with_competing_route_updates_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX} /dev/null)

  target_link_libraries(sai_ecmp_shrink_with_competing_route_updates_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    -Wl,--whole-archive
    hw_ecmp_shrink_with_competing_route_updates_speed
    sai_switch_ensemble
    -Wl,--no-whole-archive
    sai_ecmp_utils
    sai_port_utils
    ${SAI_IMPL_ARG}
  )

  set_target_properties(sai_ecmp_shrink_with_competing_route_updates_speed-${SAI_IMPL_NAME}-${SAI_VER_SUFFIX}
    PROPERTIES COMPILE_FLAGS
    "-DSAI_VER_MAJOR=${SAI_VER_MAJOR} \
    -DSAI_VER_MINOR=${SAI_VER_MINOR}  \
    -DSAI_VER_RELEASE=${SAI_VER_RELEASE}"
  )


endfunction()

BUILD_SAI_BENCHMARKS("fake" fake_sai)

# If libsai_impl is provided, build sai tests linking with it
find_library(SAI_IMPL sai_impl)
message(STATUS "SAI_IMPL: ${SAI_IMPL}")

if(SAI_IMPL)
  BUILD_SAI_BENCHMARKS("sai_impl" ${SAI_IMPL})

  install(
    TARGETS
    sai_fsw_scale_route_add_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_hgrid_du_scale_route_add_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_hgrid_uu_scale_route_del_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_th_alpm_scale_route_add_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_fsw_scale_route_del_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_ecmp_shrink_with_competing_route_updates_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_th_alpm_scale_route_del_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_ecmp_shrink_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_hgrid_uu_scale_route_add_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_hgrid_du_scale_route_del_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_stats_collection_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_warm_boot_exit_speed-sai_impl-${SAI_VER_SUFFIX})
  install(
    TARGETS
    sai_tx_slow_path_rate-sai_impl-${SAI_VER_SUFFIX})
endif()