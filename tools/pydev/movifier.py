		
# ******************************************************************************************************************
# **************************************************** movefier ****************************************************
# ******************************************************************************************************************
			
def moveifier_init():
	print "This tool will move function definitions and the"
	print "corresponding implementation to another file."
	print ""
	folderloc = raw_input("Please input the folder containing the hpp and cpp files: ").strip()
	if not os.path.exists(folderloc):
		print folderloc
		print "Path is invalid: directory does not exist."
		return
		
	filenameer = raw_input("Please type the filename (excluding extension): ").strip()
	header_file = os.path.join(folderloc, filenameer + ".hpp")
	if not os.path.isfile(header_file):
		print header_file
		print "Header file is invalid: file not found."
		return
	else:
		print "Header: " + header_file + " OK!"
		
	implementation_file = os.path.join(folderloc, filenameer + ".cpp")
	if not os.path.isfile(implementation_file):
		print implementation_file
		print "Implementation file is invalid: file not found."
		return
	else: 
		print "Implementation: " + implementation_file + " OK!"
	print "OK! Header and implementation found."
	
	dest = raw_input("Please input the script output location: ").strip()
	if not os.path.exists(dest):
		print dest
		print "Script output folder is invalid: folder does not exist."
		return
	else: 
		print "Output: " + dest + " OK!"
	moveifier_scan_files(header_file, implementation_file, dest)
	
def moveifier_scan_files(headerf, implf, dest):
	funpat = re.compile('[\w_ \:]+\(.*\)\;')
	function_definitions = []
	flag_verbose = True
	# Find all function signatures.
	with open(headerf) as f:
		for line in f:
			cleanline = line.strip()
			if funpat.match(cleanline):
				if (cleanline.startswith("\\") or cleanline.startswith("\*") or cleanline.startswith("*") or cleanline.startswith("\**")):
					moveifier_print_to_unsorted(cleanline, os.path.join(dest, "_unsorted.hpp"))
					continue
				function_definitions.append(cleanline)
				if flag_verbose:
					print "Found definition: " + cleanline
			else:
				moveifier_print_to_unsorted(cleanline, os.path.join(dest, "_unsorted.hpp"))
		print "Function definitions found: " + str(len(function_definitions))
		
	# Find the function implementation
	implementationcounter = 0
	f_arr = []
	with open(implf) as f:
		fcache = f.readlines()
		f.seek(0)
		clineno = 0
		for definit in function_definitions:
			while True:
				line = f.readline()
				clineno = clineno + 1
				if not line: break
				if definit.strip(';') in line.strip():
					open_braces = line.strip().count("{")
					
					if open_braces < 1:
						print "NO open braces on line" + line
						if (peek_line(f).strip().count("{") < 1):
							print "NO open braces on peeked line."
							continue
					
					open_braces = open_braces - line.strip().count("}")
					
					function_imp = line;
					fcache[clineno] = ""
					while (open_braces > 0):
						thisline = f.readline()
						fcache[clineno] = ""
						clineno = clineno + 1
						function_imp = function_imp + "\n"  + thisline
						open_braces = open_braces + thisline.strip().count("{")
						open_braces = open_braces - thisline.strip().count("}")

					
					print "Found implementation for " + definit.strip(';')
					f_pair = [definit, function_imp]
					f_arr.append(f_pair)
					implementationcounter = implementationcounter + 1
					continue;
			clineno = 0
			f.seek(0)
		print "Function implemenations found: " + str(implementationcounter)
		print "Writing unsorted backup... please wait." 
		for line in fcache:
			moveifier_print_to_unsorted(line, os.path.join(dest, "_unsorted.cpp"))
		
	print ""
	print ""
	print "     Source file parsing completed successfully. "
	print ""
	print "     Header: " + headerf
	print "     Implementation: " + headerf
	print "     Outputting to: "
	print ""
	print "        Function definitions found: " + str(len(function_definitions))
	print "        Function implemenations found: " + str(implementationcounter)
	print ""
	print "        Functions to be moveed: " + str(len(f_arr))
	print ""
	print ""
	print ""
	print "     The next stage will move the detected functions into files."
	print "     To view the manual before moving, type 'man', otherwise type 'yes' to continue or 'no' to cancel."
	print ""
	while (True):
		ask_result = raw_input("     Do you wish to begin moving the functions? [yes/no/man]: ").strip()
		if ask_result == "yes":
			moveifier_do_move(f_arr, dest)
			clearscr()
			print ""
			print "     moving finished!"
			print ""
			print "     Summary: "
			print "     Functions moveed: "
			print "     Functions skipped: "
			print ""
			raw_input("Press enter to return to the main menu.")
			return
		elif ask_result == "no":
			return
		elif ask_result == "man":
			moveifier_show_manual(f_arr, dest)
			break
			
def moveifier_show_manual(f_arr, dest):
	print ""
	print "==========================================================================="
	print ""
	print "     Intercept pydev Move tool manual "
	print ""
	print "     This tool is designed to assist in the fast movement of functions and their"
	print "     implementation between files. The tool discovers defined functions and"
	print "     attempts to match these definitions to implementations. Once this has been"
	print "     done the user will then be presented with the series of functions which"
	print "     were discovered and asked to provide a filename to move these functions to."
	print "     "
	print "     To move a function simply type the name (with no ext.) of the file you wish to move it into."
	print "     "
	print "     To skip a function just press enter with no filename entered. This will move the"
	print "     function into a file named _skipped.xpp"
	print "     "
	print "     To stop moving functions press ctrl+c or close the command prompt."
	print "     "
	print "     "
	print "     Note: Functions are moved immediatley, with no undo function, however, the original"
	print "     source file from which functions come from are not modified in any way."
	print "     "
	print "     The next stage will move the detected functions into files."
	print "     Type 'yes' to start moving functions or 'no' to cancel."
	print ""
	ask_result = raw_input("     Do you wish to begin moving the functions? [yes/no]: ").strip()
	if ask_result == "yes":
		moveifier_do_move(f_arr, dest)
		clearscr()
		print ""
		print "     moving finished!"
		print ""
		print "     Summary: "
		print "     Functions moveed: "
		print "     Functions skipped: "
		print ""
		raw_input("Press enter to return to the main menu.")
		return
	elif ask_result == "no":
		return
def moveifier_print_to_unsorted(line, dest):
		with open(dest,'a') as f: f.write(line + "\n")
			
def moveifier_do_move(f_arr, dest):
	i = 0
	for func in f_arr:
		i = i + 1
		clearscr()
		print ""
		print ""
		print "     --== moving Function #" + str(i) + "/" + str(len(f_arr)) + " ==--"
		print ""
		moveifier_print_func_info(func, False)
		dest_loc = raw_input("     Destination [blank to skip]: ").strip()
		if dest_loc == "":
			dest_loc = "_unsorted"
		header_op_to = os.path.join(dest, dest_loc + ".hpp")
		implementation_op_to = os.path.join(dest, dest_loc + ".cpp")
		with open(header_op_to,'a') as f: f.write(func[0] + "\n")
		with open(implementation_op_to,'a') as f: f.write(func[1] + "\n")
		
def moveifier_print_func_info(func, expand_impl):
	print ""
	print ""
	print "    Function Signature: " + func[0]
	print ""
	print "    Function Implementation:\n" + func[1]
	print ""
	print ""