set(CTEST_CUSTOM_COVERAGE_EXCLUDE
  ${CTEST_CUSTOM_COVERAGE_EXCLUDE}
  "build/vcpkg_installed/*"      # Ignore third-party dependencies installed by vcpkg
)