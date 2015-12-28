
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