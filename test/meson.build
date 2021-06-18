ut_dep = declare_dependency(
           include_directories: include_directories('lib/ut/include/'))

test_dep = [random_dep, ut_dep]

test('test_random_seed',
     executable('test_random_seed', 'src/random_seed.cpp',
                dependencies: test_dep))

test('test_mt19937',
     executable('test_mt19937', 'src/mt19937.cpp',
                dependencies: test_dep))

test('test_mt19937_64',
     executable('test_mt19937_64', 'src/mt19937_64.cpp',
                dependencies: test_dep))
