libcompress_proj = subproject('libcompress')
libcompress_dep = libcompress_proj.get_variable('libcompress_dep')
gtkmm_dep = dependency('gtkmm-3.0', version: '>= 3.18')

sources = ['main.cxx', 'window.cxx']
executable('libcompress-gui', sources,
  include_directories : inc,
  dependencies : [libcompress_dep, gtkmm_dep],
  install : true)

