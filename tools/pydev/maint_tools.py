import os, re, requests, shutil, colorama, webbrowser
from lxml import html

colorama.init()
clearscr = lambda: os.system('cls')
clearscr()

def print_suite_head():
	clearscr()
	print "  ___       _                          _   "
	print " |_ _|_ __ | |_ ___ _ __ ___ ___ _ __ | |_ "
	print "  | || '_ \| __/ _ \ '__/ __/ _ \ '_ \| __|"
	print "  | || | | | ||  __/ | | (_|  __/ |_) | |_ "
	print " |___|_| |_|\__\___|_|  \___\___| .__/ \__|"
	print "                                |_|        "
	print ""
	print "     Intercept Python Development Tools    "
	print "     Available tools are: move, docify     "
	print "     Type exit to quit                     "
	print ""

def suite_menu():
	do_reinit = True
	while (True):
		if (do_reinit):
			print_suite_head()
			do_reinit = False
			
		str = raw_input(">>> ").strip()
		if str == "move":
			do_reinit = True
			moveifier_init()
		elif str == "docify":
			do_reinit = True
			docify()
		elif str == "exit":
			clearscr()
			break
		else:
			print "Couldn't find tool called " + str
			
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
	
# ******************************************************************************************************************
# ***************************************************** DOCIFY *****************************************************
# ******************************************************************************************************************
def docify():
	clist = docify_get_commandlist()
	docify_find_command(clist)
	return
	
def docify_get_commandlist():
	print "Getting documented command list..."
	page = requests.get('https://community.bistudio.com/wiki/Category:Scripting_Commands')
	tree = html.fromstring(page.content)
	commandsList = tree.xpath('//*[@id="mw-pages"]/div/table/tr/td[1]/ul/li/a/text()')
	commandsURLs = tree.xpath('//*[@id="mw-pages"]/div/table/tr/td[1]/ul/li/a//@href')
	
	if len(commandsList) != len(commandsURLs):
		print "An error occured retreiving the list of documented commands."
		print "List of commands and URLs mismatched."
	
	loopCount = 0
	wfk_arr = []
	while True:
		if loopCount == len(commandsList):
			break
		
		wk_url = "https://community.bistudio.com" + commandsURLs[loopCount]
		
		print "Command: " + " " + commandsList[loopCount] + " " +to_snake(commandsList[loopCount]) + " " + wk_url
		
		wfk_pair = [commandsList[loopCount], to_snake(commandsList[loopCount]), wk_url]
		wfk_arr.append(wfk_pair)
		loopCount += 1
		
	return wfk_arr
	
def docify_find_command(commands):
	print ""
	print ""
	print "     Found " + str(len(commands)) + " documented commands on the biki."
	print ""
	print ""
	folderloc = raw_input("Please input the path to the header file to document: ").strip()
	if not os.path.isfile(folderloc):
		print folderloc
		print "Path is invalid: file does not exist."
		return
	else:
		# Backup the original file here.
		if os.path.isfile(folderloc + ".backup_nodoc"):
			ow_confirm = raw_input("WARNING: Backup of this file already exists, press enter to overwrite or type 'cancel' to cancel. ").strip()
			
			#if ow_confirm == "":
			#	return
				
		shutil.copy(folderloc, folderloc + ".backup_nodoc")
		oloc = folderloc + ".backup_nodoc"
		
	funpat = re.compile('[\w_ \:\<\>]+\(.*\)\;')
	function_definitions = []
	
	implementationcounter = 0
	f_arr = []
	
	with open(folderloc, 'r') as f: contents = f.readlines()
	
	i = 0
	lastmatch = ""
	#print contents
	
	while True:
		if i >= len(contents):
			break
		line = contents[i]


		# Check if the line seems to be a function.
		if funpat.match(line.strip()):
			# Check if the last match is this match.
			if lastmatch == line:
				i += 1
				continue
			else:
				lastmatch = line
				
			# Is the line a comment?
			if (line.strip().startswith("\\") or line.strip().startswith("\*") or line.strip().startswith("*") or line.strip().startswith("\**")):
				continue		
				
			clearscr()
			print "Docmenting command: " + contents[i]
			print ""
			print "Available options: "
			print "          Press enter to continue"
			print "          Type 'exit' to quit and save"
			print "          Type 'cancel' to quit without saving,"
			print "          Type 'skip' to move on"
			found_rwi = raw_input("   >>> ").strip()
			if found_rwi == "exit":
				break
			elif found_rwi == "cancel":
				return
			elif found_rwi == "skip":
				i += 1
				continue
			else:
				print "Continuing... "
			doxycomment = do_docify(contents[i], commands)
			if len(doxycomment) > 5:
				contents.insert(i, doxycomment + "\n")
			#i += 1
				
		print str(i) + line
			

		
		i += 1
	
	print "Writing file..."
	with open(folderloc, 'w+') as f: f.writelines(contents)
	
	raw_input("PRESS ENTER TO CONTINUE")
	print "Function implemenations found: " + str(implementationcounter)
def do_docify(function, commands):
	leadingWhitespace = re.match(r"\s*", function).group()
	fparams = function.partition("(")
	funcsig = fparams[0].rsplit(' ', 1)
	funcsignature = funcsig[1] + fparams[1] + fparams[2]
	
	rematches = re.match("^\s*(\w+)\s*\((.*)\)", funcsignature).groups()
	
	f_url = ""
	for cmd in commands:
		if rematches[0] == cmd[1]:
			f_url = cmd[2]
	
	if f_url == "":
		print "WARNING: No documentation found for function " + rematches[0]
		if "_" not in rematches[0]:
			print "Are you sure this function is in snake case?"
		
		d = raw_input("Press enter to continue.")
		return ""
	description = docify_get_description(f_url, leadingWhitespace)

	doxycomment = 	"\n" + leadingWhitespace + "/*!\n"
	doxycomment +=	leadingWhitespace + "@brief " + description + "\n\n"


	function_identifier = rematches[0]
	if len(rematches[1]) is not 0:
		fnc_params = rematches[1].split(",")
	else:
		fnc_params = []

	docify_print_inprogress(doxycomment, function, leadingWhitespace)
	webbrowser.open(f_url)
	
	if len(fnc_params) is not 0:
		for param in fnc_params:
			param_identifer = param.rsplit(" ", 1)[-1].replace("&", "")
			prm = leadingWhitespace + "@param " + param_identifer + " "
			if "=" in param:
				prm += "[OPTIONAL]"

			docify_print_inprogress(doxycomment, function, leadingWhitespace)
			
			doxycomment +=	prm + raw_input(prm.replace(leadingWhitespace, "")) + "\n"
			
	if "void" not in funcsig[0]:
		docify_print_inprogress(doxycomment, function, leadingWhitespace)
		doxycomment += leadingWhitespace + "@return " + raw_input("@return ") + "\n"
		
	doxycomment +=  leadingWhitespace + "@sa " + f_url + "\n"
	doxycomment +=	leadingWhitespace + "*/"

	return doxycomment
	
def docify_print_inprogress(comment, signature, lwhitespace):
	clearscr()
	print ""
	print color.BOLD + signature.strip() + colorama.Style.RESET_ALL
	
	
	print comment.replace(lwhitespace, " ")
	return
	
def docify_get_description(url, lwhitespace):
	page = requests.get(url)
	tree = html.fromstring(page.content)
	descrArray = tree.xpath('//*[@id="mw-content-text"]/div[2]/dl[2]/dd//text()')
	descrJoined = ' '.join(descrArray)
	return descrJoined.replace("\n", "\n" + lwhitespace)
	

	
def peek_line(f):
    pos = f.tell()
    line = f.readline()
    f.seek(pos)
    return line
	
def to_snake(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()
	
class color:
   PURPLE = '\033[95m'
   CYAN = '\033[96m'
   DARKCYAN = '\033[36m'
   BLUE = '\033[94m'
   GREEN = '\033[92m'
   YELLOW = '\033[93m'
   RED = '\033[91m'
   BOLD = '\033[1m'
   UNDERLINE = '\033[4m'
   END = '\033[0m'
   
suite_menu()