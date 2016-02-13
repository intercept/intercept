import sys, os, re, requests, shutil, webbrowser, CppHeaderParser, json, cgi
from lxml import html

def to_snake(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()

scriptpath = os.path.realpath(__file__)
projectpath = os.path.join(os.path.dirname(os.path.dirname(scriptpath)), "src\\client\\headers\\client")
projectpath_sqf = os.path.join(projectpath, "sqf")

headers = [];

print "Getting documented command list from wiki..."
page = requests.get('https://community.bistudio.com/wiki/Category:Scripting_Commands')
tree = html.fromstring(page.content)
commandsList = tree.xpath('//*[@id="mw-pages"]/div/table/tr/td/ul/li/a/text()')
commandsURLs = tree.xpath('//*[@id="mw-pages"]/div/table/tr/td/ul/li/a//@href')

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
	
# Walk through our source files and figure out which ones are used in our code
for file in os.listdir(projectpath_sqf):
	if file.endswith(".hpp"):
	
		if file.startswith("common_helpers"):
			continue
			
		source_file = os.path.join(projectpath_sqf, file) # find our source file contents
		try:
			cppHeader = CppHeaderParser.CppHeader(source_file)
			print(len(cppHeader.functions))
			for item in cppHeader.functions:
			
				if (item["name"].startswith("_")):
					continue;
					
				sqfN = False
				sqfNoDoc = True
				for snake in wfk_arr:
					if item["name"] == snake[1]:
						sqfNoDoc = False
						sqfN = snake[0]
						break;
					
				parameters = []
				for pr in item["parameters"]:
					pr["raw_type"] = cgi.escape(pr["raw_type"])
					parameters.append({
						"const": True if (pr["constant"] == 1) else False,
						"type": (pr["raw_type"] + "&") if (pr["reference"] == 1) else pr["raw_type"],
						"label": cgi.escape(pr["name"]),
						"description": "No description provided."
					})
					
				hdr = {
					"sqf": sqfN if (sqfN != False) else item["name"].replace("_",""), 
					"namespace": cgi.escape(item['namespace']), 
					"description": "No description has been provided.", 
					"nodoc": sqfNoDoc,
					"include": cgi.escape(file), 
					"signature": {
						"return": {
							"type": cgi.escape(item["returns"]),
							"description": "No description provided."
						},
						"name": cgi.escape(item["name"]),
						"params": parameters
					}
				}
				headers.append(hdr);
		except CppHeaderParser.CppParseError as e:
			print(e)
			sys.exit(1)
		
# Sort our functions alphabetically		
headers_sorted = sorted(headers, key=lambda func: func["sqf"].lower())

with open("datax.json", "w") as text_file:
	json.dump(headers_sorted, text_file)