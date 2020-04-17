demo_1_exe = executable('demo_1_int_ll',
			'demo_1_int_ll.c',
			include_directories : inc,
			link_with : libltypes)

demo_2_exe = executable('demo_2_str_ll',
			'demo_2_str_ll.c',
			include_directories : inc,
			link_with : libltypes)

demo_3_exe = executable('demo_3_int_dll',
			'demo_3_int_dll.c',
			include_directories : inc,
			link_with : libltypes)

demo_4_exe = executable('demo_4_str_dll',
			'demo_4_str_dll.c',
			include_directories : inc,
			link_with : libltypes)
demo_5_exe = executable('demo_5_fibonacci_ll',
            'demo_5_fibonacci_ll.c',
            include_directories : inc,
            link_with : libltypes)

test('libltypes', demo_1_exe)
test('libltypes', demo_2_exe)
test('libltypes', demo_3_exe)
test('libltypes', demo_4_exe)
test('libltypes', demo_5_exe)
