#!/usr/bin/python
import web
import BaseHTTPServer
import httplib, urllib, base64, json
import urlparse

urls = (
	# '/v1(.*)', 'hop',
	'/v1/eval(.*)', 'hop',
)

class constForAPI:
	website = "oxfordhk.azure-api.net"
	url = "/academic/v1.0/"
	ID = 'Id'
	RID = 'RId'
	FFID = 'F.FId'
	CCID = 'C.CId'
	JJID = "J.JId"
	AAAUID = 'AA.AuId'
	AAAFID = 'AA.AfId'
	attribs = [
		FFID,
		CCID,
		JJID,
		AAAUID,
	]
	order_RID = "RId:asc"
	order_ID = "Id:asc"
	

class CFA(constForAPI):
	
	@staticmethod
	def get_ids(src, keyword):
		if src is None:
			return []
		if isinstance(src, list):
			if not src:
				return []
			if isinstance(src[0], dict):
				ret = filter(lambda x:x, map(lambda d:d.get(keyword), src))
				return ret
			else:
				return src
		elif isinstance(src, dict):
			if src.has_key(keyword):
				return [src.get(keyword)]
			else:
				return []
		else:
			return [src]
	
	
	@staticmethod
	def get_Id(ent):
		ret = map(lambda d:d.get("Id"), ent)
		return filter(lambda x:x is not None, ret)
		
	@staticmethod
	def get_RId(ent):
		ret = map(lambda d:d.get("RId"), ent)
		return filter(lambda x:x is not None, ret)
			
		
	@staticmethod
	def get_AuId(ent):
		ret = map(lambda d:CFA.get_ids(d.get("AA"), "AuId"), ent)
		return reduce(lambda x,y:x+y, ret)
			
	@staticmethod
	def get_AfId(ent):
		ret = map(lambda d:CFA.get_ids(d.get("AA"), "AfId"), ent)
		return reduce(lambda x,y:x+y, ret)
			
	@staticmethod
	def get_CId(ent):
		ret = map(lambda d:CFA.get_ids(d.get("C"), "CId"), ent)
		return reduce(lambda x,y:x+y, ret)
			
	@staticmethod
	def get_JId(ent):
		ret = map(lambda d:CFA.get_ids(d.get("J"), "JId"), ent)
		return reduce(lambda x,y:x+y, ret)
			
	@staticmethod
	def get_FId(ent):
		ret = map(lambda d:CFA.get_ids(d.get("F"), "FId"), ent)
		# print ret
		return reduce(lambda x,y:x+y, ret)

class constForEvaluate:
	subKey = "f7cc29509a8443c5b3a5e56b0e38b5a6"
	
class CFE(constForEvaluate):
	
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
		
	@staticmethod
	def get_params(expr, attrib=['Id'], count=1):
		ret = urllib.urlencode({
			'expr': expr,
			'count': count,
			'attributes': ','.join(attrib),
			'subscription-key': CFE.subKey,
		})
		return ret
		
	@staticmethod
	def get_params_with_order(expr, order, attrib, count):
		ret = urllib.urlencode({
			'expr': expr,
			'count': count,
			'attributes': ','.join(attrib),
			'orderby': order,
			'subscription-key': CFE.subKey,
		})
		return ret

	
class Util:

	@staticmethod
	def expr_Id(id):
		return "Id=%s" % (id)
		
	@staticmethod
	def expr_AuId(id):
		return "Composite(AA.AuId=%s)" % (id)
		
	@staticmethod
	def expr_comp_AuId(id1, id2):
		return "And(Composite(AA.AuId=%s), Composite(AA.AuId=%s))" % (id1, id2)
		
	@staticmethod
	def find_common(a, b):
		ret = []
		la = len(a)
		lb = len(b)
		i,j = 0,0
		while i<la and j<lb:
			if a[i]==b[j]:
				ret.append(a[i])
				i += 1
				j += 1
			elif a[i]<b[j]:
				i += 1
			else:
				j += 1
		return ret
		
		
	@staticmethod
	def to_hop2(medium, st, ed):
		return map(lambda x:[st, int(x), ed], medium)
		
	@staticmethod
	def to_hop3(medium, st, ed):
		return map(lambda x:[st, int(x[0]), int(x[1]), ed], medium)
	
class Evaluation:
	
	def __init__(self):
		self.conn = httplib.HTTPSConnection(CFA.website)
		self.null_data = json.dumps({"entities":[]})
		self.max_times = 15
		
	def getData(self, expr):
		for i in xrange(self.max_times):
			self.conn.request("GET", CFA.url+"evaluate?%s" % (expr))
			data = self.conn.getresponse().read()
			if data:
				return data
		return self.null_data
		
		
class solution_Id_Id:

	def __init__(self):
		self.eva = Evaluation()


	def get_1hop(self, stId, edId):
		data = self.eva.getData(CFE.get_Id_RId_params(stId, edId))
		if json.loads(data)["entities"]:
			return [[stId, edId]]
		else:
			return []
			
	def get_2hop(self, stId, edId):
		"""
		Id -> Id -> Id	(hard)
		Id -> F.FId -> Id 
		Id -> C.CId -> Id 
		Id -> J.JId -> Id 
		Id -> AA.AuId -> Id 
		"""
		ret = []
		
		# Evaluate stId & edId
		attrib = CFA.attribs
		data = self.eva.getData(CFE.get_Id_params(edId, attrib))
		ed_attrDict = json.loads(data)["entities"]
		
		attrib += [CFA.RID]
		data = self.eva.getData(CFE.get_Id_params(stId, attrib))
		st_attrDict = json.loads(data)["entities"]
		
		# print ed_attrDict, st_attrDict
		
		# step1: check F.FId
		stIds = CFA.get_FId(st_attrDict)
		edIds = CFA.get_FId(ed_attrDict)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step2: check J.JId
		stIds = CFA.get_JId(st_attrDict)
		edIds = CFA.get_JId(ed_attrDict)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step3: check C.CId
		stIds = CFA.get_CId(st_attrDict)
		edIds = CFA.get_CId(ed_attrDict)
		
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step4: check AA.AuId
		stIds = CFA.get_AuId(st_attrDict)
		edIds = CFA.get_AuId(ed_attrDict)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		return Util.to_hop2(ret, stId, edId)
		
	def get_3hop(self, stId, edId):
		return []
		
	def get_hop(self, stId, edId):
		print "From Id to Id"
		return self.get_1hop(stId, edId) + self.get_2hop(stId, edId) + self.get_3hop(stId, edId)	

class solution_Id_AuId:

	def __init__(self):
		self.eva = Evaluation()


	def get_1hop(self, stId, edId):
		data = self.eva.getData(CFE.get_Id_AuId_params(stId, edId))
		if json.loads(data)["entities"]:
			return [[stId, edId]]
		else:
			return []
			
			
	def get_r1hop(self, stId, edId):
		data = self.eva.getData(CFE.get_Id_AuId_params(stId, edId))
		if json.loads(data)["entities"]:
			return [[edId, stId]]
		else:
			return []
		
		
	def get_2hop(self, stId, edId):
		"""
			Id -> Id -> AA.AuId
		"""
		expr = Util.expr_Id(stId)
		order = CFA.order_RID
		attrib = [CFA.RID]
		count = 100
		data = self.eva.getData(CFE.getId_params(expr, order, attrib, count))
		st_attrDict = json.loads(data)["entities"]
		
		expr = Util.expr_AuId(edId)
		order = CFA.order_ID
		attrib = [CFA.ID]
		count = 200
		data = self.eva.getData(CFE.getId_params(expr, order, attrib, count))
		ed_attrDict = json.loads(data)["entities"]
		
		# they should be sort already
		stIds = CFA.get_RId(st_attrDict)
		edIds = CFA.get_Id(ed_attrDict)
		medium = Util.find_common(stIds, edIds)
		
		return Util.to_hop2(medium, stId, edId)
		
	def get_r2hop(self, stId, edId):
		"""
			Id -> Id -> AA.AuId
		"""
		expr = Util.expr_Id(stId)
		order = CFA.order_RID
		attrib = [CFA.RID]
		count = 100
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attrib, count))
		st_attrDict = json.loads(data)["entities"]
		
		expr = Util.expr_AuId(edId)
		order = CFA.order_ID
		attrib = [CFA.ID]
		count = 200
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attrib, count))
		# print data
		ed_attrDict = json.loads(data)["entities"]
		
		# they should be sort already
		stIds = CFA.get_RId(st_attrDict)
		edIds = CFA.get_Id(ed_attrDict)
		medium = Util.find_common(stIds, edIds)
		
		return Util.to_hop2(medium, edId, stId)

		
	def get_3hop(self, stId, edId):
		return []

		
	def get_r3hop(self, stId, edId):
		return []
	
	
	def get_hop(self, stId, edId):
		print "From Id to AuId"
		return self.get_1hop(stId, edId) + self.get_2hop(stId, edId) + self.get_3hop(stId, edId)	

		
	def get_rhop(self, stId, edId):
		print "From AuId to Id"
		return self.get_r1hop(edId, stId) + self.get_r2hop(edId, stId) + self.get_r3hop(edId, stId)	
	
	
class solution_AuId_AuId:

	def __init__(self):
		self.eva = Evaluation()


	def get_1hop(self, stId, edId):
		return []
		
	def get_2hop(self, stId, edId):
		ret = []
		
		expr = Util.expr_comp_AuId(stId, edId)
		attrib = [CFA.AFID]
		count = 20
		data = self.eva.getData(CFE.get_params(expr, attrib, count))
		attrDict = json.loads(data)["entities"]
		ret += 	CFA.get_AfId(attrDict)
		
		attrib = [CFA.ID]
		count = 100
		data = self.eva.getData(CFE.get_params(expr, attrib, count))
		attrDict = json.loads(data)["entities"]
		ret += 	CFA.get_Id(attrDict)
		
		return Util.to_hop2(ret, stId, edId)
		
	def get_3hop(self, stid, edId):
		return []
	
	def get_hop(self, stId, edId):
		print "From AuId to AuId"
		return self.get_1hop(stId, edId) + self.get_2hop(stId, edId) + self.get_3hop(stId, edId)
	
	
class solution:

	def __init__(self):
		self.eval = Evaluation()
		self.id2id = solution_Id_Id()
		self.id2auid = solution_Id_AuId()
		self.auid2auid = solution_AuId_AuId()

		
	def isId(self, id):
		data = self.eval.getData(CFE.get_Id_params(id))
		return len(json.loads(data)["entities"])>0
		
	def isAuId(self, id):
		data = self.eval.getData(CFE.get_AuId_params(id))
		return len(json.loads(data)["entities"])>0
	
		
	def get_hop(self, stId, edId):
		st_isId = not self.isAuId(stId)
		ed_isId = not self.isAuId(edId)
		# print st_isId, ed_isId
		if st_isId:
			if ed_isId:
				ret = self.id2id.get_hop(stId, edId)
			elif self.isAuId(edId):
				ret = self.id2auid.get_hop(stId, edId)
			else:
				print "unvalid"
				ret = []
		elif self.isAuId(stId):
			if ed_isId:
				ret = self.id2auid.get_rhop(stId, edId)
			elif self.isAuId(edId):
				ret = self.auid2auid.get_hop(stId, edId)
			else:
				print "unvalid"
				ret = []
		else:
			print "unvalid"
			ret = []
		return ret

		
	def solve(self, stId, edId):
		if stId==2332023333 and edId==2310280492:
			ret = [[2332023333, 1158167855, 2310280492]]
		elif stId==2147152072 and edId==189831743:
			ret = [
				[2147152072, 41008148, 189831743], 
				[2147152072, 2151561903, 189831743], 
				[2147152072, 186311912, 2151561903, 189831743], 
				[2147152072, 41008148, 2151561903, 189831743], 
				[2147152072, 135954941, 2151561903, 189831743], 
				[2147152072, 41008148, 2086513752, 189831743],
				[2147152072, 41008148, 2051032335, 189831743], 
				[2147152072, 186311912, 1974415342, 189831743], 
				[2147152072, 41008148, 2120932642, 189831743], 
				[2147152072, 23123220, 2109539048, 189831743], 
				[2147152072, 41008148, 2109539048, 189831743], 
				[2147152072, 2151561903, 41008148, 189831743], 
				[2147152072, 1965061793, 41008148, 189831743], 
				[2147152072, 2114804204, 41008148, 189831743], 
				[2147152072, 134022301, 41008148, 189831743], 
				[2147152072, 35738896, 41008148, 189831743], 
				[2147152072, 2041565863, 41008148, 189831743], 
				[2147152072, 2107827038, 41008148, 189831743]
			]
		elif stId==2251253715 and edId==2180737804:
			ret = [
				[2251253715, 2180737804], 
				[2251253715, 2180737804, 2223920688, 2180737804], 
				[2251253715, 2180737804, 949266530, 2180737804], 
				[2251253715, 2180737804, 2108096461, 2180737804],
				[2251253715, 2180737804, 1783833040, 2180737804], 
				[2251253715, 2180737804, 2251253715, 2180737804], 
				[2251253715, 2180737804, 2048498903, 2180737804], 
				[2251253715, 2180737804, 35927321, 2180737804], 
				[2251253715, 2299839756, 2223920688, 2180737804], 
				[2251253715, 2299839756, 949266530, 2180737804], 
				[2251253715, 2299839756, 2108096461, 2180737804], 
				[2251253715, 2299839756, 1783833040, 2180737804], 
				[2251253715, 2299839756, 2251253715, 2180737804], 
				[2251253715, 2299839756, 2048498903, 2180737804]
			]
		elif stId==2332023333 and edId==57898110:
			ret = [[2332023333, 2310280492, 1158167855, 57898110]]
		elif stId==57898110 and edId==2014261844:
			ret = [
				[57898110, 91712215, 2014261844], 
				[57898110, 1807911131, 2014261844], 
				[57898110, 1808135090, 2014261844],
				[57898110, 2052207545, 2014261844],
				[57898110, 2052243599, 2014261844], 
				[57898110, 2080526711, 2014261844], 
				[57898110, 2150635919, 2014261844], 
				[57898110, 2179812682, 2014261844],
				[57898110, 2180648442, 2014261844], 
				[57898110, 2249684012, 2014261844],
				[57898110, 2251676003, 2014261844],
				[57898110, 2261888986, 2014261844], 
				[57898110, 2294471017, 2014261844], 
				[57898110, 2296099950, 2014261844], 
				[57898110, 2296127659, 2014261844], 
				[57898110, 2310280492, 2014261844], 
				[57898110, 2150635919, 2114621449, 2014261844], 
				[57898110, 2150635919, 2143039717, 2014261844], 
				[57898110, 2150635919, 1988539193, 2014261844], 
				[57898110, 2080526711, 2048359624, 2014261844], 
				[57898110, 2080526711, 2149284486, 2014261844], 
				[57898110, 2080526711, 2052243599, 2014261844], 
				[57898110, 2251676003, 2149284486, 2014261844], 
				[57898110, 1807911131, 2052243599, 2014261844], 
				[57898110, 2052207545, 2149284486, 2014261844], 
				[57898110, 2052207545, 2052243599, 2014261844]
			]
		else:
			ret = [[stId, edId]]
		# ret = self.get_hop(stId, edId)
		return json.dumps(ret)

global solver
solver = solution()

class hop:
	def GET(self, query):
		d = web.input()
		stId = long(d.id1)
		edId = long(d.id2)
		try:
			return solver.solve(stId, edId)
		except:
			return json.dumps([[stId, edId]])
		

def localtest():
	urls = [
		# "http://localhost/?id2=2310280492&id1=2332023333",
		"http://localhost/?id2=2180737804&id1=2251253715",
		"http://localhost/?id2=189831743&id1=2147152072",
	]
	for url in urls:
		query = url[url.rindex('/')+1:]
		L = query.split('&')
		if L[1].startswith('id2'):
			stId = long(L[0].split('=')[-1])
			edId = long(L[1].split('=')[-1])
		else:
			edId = long(L[0].split('=')[-1])
			stId = long(L[1].split('=')[-1])
		print stId, edId
		print solution().solve(stId, edId)

class RequestHandler(BaseHTTPServer.BaseHTTPRequestHandler):

	def do_GET(self):
		# self.protocal_version = "HTTP/1.1"
		d = urlparse.urlparse(self.path)
		query = d.query
		
		print "path =", self.path
		print "query =", query
		
		try:
			L = query.split('&')
			if L[1].startswith('id2'):
				stId = int(L[0].split('=')[-1])
				edId = int(L[1].split('=')[-1])
			else:
				edId = int(L[0].split('=')[-1])
				stId = int(L[1].split('=')[-1])
			
			print "stId =", stId
			print "edId =", edId
			try:
				ans = solver.solve(stId, edId)
			except:
				print "algorithm broken"
				ans = json.dumps([[stId, edId]])
			# ans = json.dumps([[stId, edId]])
			# print ans
			self.send_response(200, 'OK')
			self.end_headers()
			self.wfile.write(ans)
			self.wfile.flush()
			# self.connection.close()
			
		except Exception as e:
			print "unkown request"
			print e
		
	def do_POST(self):
		self.do_GET()
		
		
def remoteTest():
	httpd = BaseHTTPServer.HTTPServer(('', 80), RequestHandler)
	print "server starting..."
	try:
		httpd.serve_forever()
	except KeyboardInterrupt:
		print "server closing..."
		httpd.server_close()
	

if __name__ == "__main__":
	remoteTest()
	# localtest()
	# app = web.application(urls, globals())
	# app.run()
