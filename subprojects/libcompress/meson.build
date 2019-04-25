project('libcompress', 'cpp',
  version : '0.1.0',
  license: 'MIT')

inc = include_directories('include')

subdir('include')
subdir('src')

libcompress_dep = declare_dependency(include_directories : inc,
  link_with : libcompress)
