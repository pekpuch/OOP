add_test( MyClassTest.test_sozd /mnt/c/Users/nikgl/OneDrive/Desktop/123/build/tests/hello_test2 [==[--gtest_filter=MyClassTest.test_sozd]==] --gtest_also_run_disabled_tests)
set_tests_properties( MyClassTest.test_sozd PROPERTIES WORKING_DIRECTORY /mnt/c/Users/nikgl/OneDrive/Desktop/123/build/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( hello_test2_TESTS MyClassTest.test_sozd)
