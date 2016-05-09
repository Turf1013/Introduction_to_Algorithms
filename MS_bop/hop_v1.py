#!/usr/bin/python
import web
import httplib, urllib, base64, json

urls = (
	'/v1/(.*)', 'hop'
)

class constForAPI:
	website = "oxfordhk.azure-api.net"
	url = "/academic/v1.0/"

class CFA(constForAPI):
	pass

class constForEvaluate:
	subKey = "f7cc29509a8443c5b3a5e56b0e38b5a6"
	
	@staticmethod
	def get_Id_params(Id, attrib=['Id'], count=1):
		ret = urllib.urlencode({
			'expr': "Id=%s" % (Id),
			'count': count,
			'attributes': ','.join(attrib),
	    	'subscription-key': CFE.subKey,
		})
		return ret

	@staticmethod
	def get_AuId_params(AuId, attrib=['Id'], count=1):
		ret = urllib.urlencode({
			'expr': "Composite(AA.AuId=%s)" % (AuId),
			'count': count,
			'attributes': ','.join(attrib),
	    	'subscription-key': CFE.subKey,
		})
		return ret

	@staticmethod	
	def get_Id_RId_params(Id, RId, attrib=['Id'], count=1):
		ret = urllib.urlencode({
			'expr': "And(Id=%s, RId=%s)" % (Id, RId),
			'count': count,
			'attributes': ','.join(attrib),
	    	'subscription-key': CFE.subKey,
		})
		return ret

	@staticmethod
	def get_Id_AuId_params(Id, AuId, attrib=['Id'], count=1):
		ret = urllib.urlencode({
			'expr': "And(Id=%s,Composite(AA.AuId=%s))" % (Id, AuId),
			'count': count,
			'attributes': ','.join(attrib),
	    	'subscription-key': CFE.subKey,
		})
		return ret
	

class CFE(constForEvaluate):
	pass

class solution_Id_Id:

	def __init__(self):
		self.conn = httplib.HTTPSConnection(CFA.website)


	def get_1hop(self, stId, edId):
		self.conn.request("GET", CFA.url+"evaluate?%s" % (CFE.get_Id_RId_params(stId, edId)))
		data = self.conn.getresponse().read()
		if json.loads(data)["entities"]:
			return [stId, edId]
		else:
			return []

class solution_Id_AuId:

	def __init__(self):
		self.conn = httplib.HTTPSConnection(CFA.website)


	def get_1hop(self, stId, edId):
		self.conn = httplib.HTTPSConnection(CFA.website)
		self.conn.request("GET", CFA.url+"evaluate?%s" % (CFE.get_Id_AuId_params(stId, edId)))
		data = self.conn.getresponse().read()
		if json.loads(data)["entities"]:
			return [stId, edId]
		else:
			return []


class solution_AuId_Id:

	def __init__(self):
		self.conn = httplib.HTTPSConnection(CFA.website)


	def get_1hop(self, stId, edId):
		self.conn = httplib.HTTPSConnection(CFA.website)
		self.conn.request("GET", CFA.url+"evaluate?%s" % (CFE.get_Id_AuId_params(edId, AuId)))
		data = self.conn.getresponse().read()
		if json.loads(data)["entities"]:
			return [stId, edId]
		else:
			return []


class solution_AuId_AuId:

	def __init__(self):
		self.conn = httplib.HTTPSConnection(CFA.website)


	def get_1hop(self, stId, edId):
		return []


class solution:

	def __init__(self):
		self.conn = None

	def Init(self):
		self.conn = httplib.HTTPSConnection(CFA.website)

		
	def Clear(self):
		self.conn.close()


	def isId(self, id):
		self.conn.request("GET", CFA.url+"evaluate?%s" % (CFE.get_Id_params(id)))
		data = self.conn.getresponse().read()
		return len(json.loads(data)["entities"])>0


	def isAuId(self, id):
		self.conn.request("GET", CFA.url+"evaluate?%s" % (CFE.get_AuId_params(id)))
		data = self.conn.getresponse().read()
		return len(json.loads(data)["entities"])>0


	def get_1hop(self, stId, edId):
		st_isId = self.isId(stId)
		ed_isId = self.isId(edId)
		if st_isId:
			if ed_isId:
				ret = solution_Id_Id().get_1hop(stId, edId)
			else:
				ret = solution_Id_AuId().get_1hop(stId, edId)
		else:
			if ed_isId:
				ret = solution_AuId_Id().get_1hop(stId, edId)
			else:
				ret = solution_AuId_AuId().get_1hop(stId, edId)
		return ret


	def solve(self, qline):
		self.Init()
		L = qline.split('&')
		stId = int(L[0].split('=')[1])
		edId = int(L[1].split('=')[1])
		ret = []
		hop1 = self.get_1hop(stId, edId)
		ret.append(hop1)
		self.Clear()
		return json.dumps(ret)


class hop:
	def GET(self, query):
		return solution().solve(query)

def localtest():
	urls = [
		"http://localhost:8080/v1/id1=2157025439&id2=2134746982",
		"http://localhost:8080/v1/id1=2157025439&id2=1982462162",
		"http://localhost:8080/v1/id1=1982462162&id2=2157025439",
		"http://localhost:8080/v1/id1=1982462162&id2=2063838112",
	]
	for url in urls:
		query = url[url.rindex('/')+1:]
		print query
		print solution().solve(query)


if __name__ == "__main__":
	# localtest()
	app = web.application(urls, globals())
	app.run()
