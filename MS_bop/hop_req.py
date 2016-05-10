#!/usr/bin/python
import httplib, urllib
import json

def query(website):
	conn = httplib.HTTPConnection(website, 80)
	params = urllib.urlencode({
		'id2': 189831743,
		'id1': 2147152072,
	})
	conn.request("GET", "/eval?%s" % (params))
	response = conn.getresponse()
	data = response.read()
	print data
	# print json.loads(data)
	conn.close()
	

if __name__ == "__main__":
	path = "172.16.3.2"
	query(path)