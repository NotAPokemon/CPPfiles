import json
from flask import Flask
from waitress import serve

lineforuseonlybyprintstatement = 0

with open("o.json","w") as f:
	x = {}
	json.dump(x,f)

def print(x):
	global lineforuseonlybyprintstatement
	lineforuseonlybyprintstatement+=1
	data = {str(lineforuseonlybyprintstatement):x}
	with open("o.json","r") as f:
		o = json.load(f)
		o.update(data)
		data = o
	with open("o.json","w") as f:
		json.dump(data,f,indent=4)

try:

	app = Flask(__name__)
	

	@app.route('/')
	def hello_world():
		return 'Hello, JJ!'
	

	if __name__ == '__main__':
	
		serve(app, host='0.0.0.0', port=5000)
	
except Exception as e:
	lineforuseonlybyprintstatement = 0
	print(e)
