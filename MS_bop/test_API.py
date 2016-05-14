#!/usr/bin/python
import httplib, urllib, base64
from time import sleep

class constForAPI:
	website = "oxfordhk.azure-api.net"
	url = "/academic/v1.0/"

class CFA(constForAPI):
	pass

class constForEvaluate:
	subKey = "f7cc29509a8443c5b3a5e56b0e38b5a6"

class CFE(constForEvaluate):
	pass

def dumpData(filename, data, flag="w"):
	if isinstance(data, str):
		with open(filename, flag) as fout:
			fout.write(data)

class Evaluate(object):

	@staticmethod
	def evaluate_ById(Id):
		params = urllib.urlencode({
			'expr': "Id=%s" % (Id),
			'count': 2,
			'attributes': 'Id,Ti,AA.AuId,AA.AfId,RId,C.CId,J.JId,F.FId',
	    	'subscription-key': CFE.subKey,
		})
		try:
			conn = httplib.HTTPSConnection(CFA.website)
			conn.request("GET", CFA.url+"evaluate?%s" % (params))
			response = conn.getresponse()
			data = response.read()
			dumpData("Evaluate_Id.out", data, "a")
		except Exception as e:
			# print e
			print("[Errno {0}] {1}".format(e.errno, e.strerror))

	@staticmethod
	def evaluate_ByAuId(AuId):
		params = urllib.urlencode({
			'expr': "Composite(AA.AuId=%s)" % (AuId),
			'count': 2,
			'attributes': 'Id,Ti,AA.AuId,AA.AfId',
	    	'subscription-key': CFE.subKey,
		})
		try:
			conn = httplib.HTTPSConnection(CFA.website)
			conn.request("GET", CFA.url+"evaluate?%s" % (params))
			response = conn.getresponse()
			data = response.read()
			dumpData("Evaluate_AuId.out", data)
		except Exception as e:
			# print e
			print("[Errno {0}] {1}".format(e.errno, e.strerror))		 

	@staticmethod
	def evaluate_ByAfId(AfId):
		params = urllib.urlencode({
			'expr': "Composite(AA.AfId=%s)" % (AfId),
			'count': 2,
			'attributes': 'Id,Ti,AA.AuId,AA.AfId',
	    	'subscription-key': CFE.subKey,
		})
		try:
			conn = httplib.HTTPSConnection(CFA.website)
			conn.request("GET", CFA.url+"evaluate?%s" % (params))
			response = conn.getresponse()
			data = response.read()
			dumpData("Evaluate_AfId.out", data)
		except Exception as e:
			# print e
			print("[Errno {0}] {1}".format(e.errno, e.strerror))	


	def __str__(self):
		return "Evaluate API"

def test_interpret():
	pass

def test_repeated_id(id):
	pass
	
def dfs_or(ids):
	# print ids
	length = len(ids)
	if length==1:
		return "Id=%s" % (ids[0])
	half = length>>1
	lexp = dfs_or(ids[:half])
	rexp = dfs_or(ids[half:])
	return "Or(%s,%s)" % (lexp, rexp)
	
	
def test_multi_id(ids):
	if len(ids)==1:
		expr = "Id=%s" % (id_exp)
	else:
		expr = dfs_or(ids)
	print expr
	# return 
	count = len(ids)
	params = urllib.urlencode({
		'expr': expr,
		'count': count,
		'attributes': 'Id,Ti,AA.AuId,F.FId,C.CId,J.JId',
		'subscription-key': CFE.subKey,
	})
	
	for i in xrange(1):
		try:
			conn = httplib.HTTPSConnection(CFA.website)
			conn.request("GET", CFA.url+"evaluate?%s" % (params))
			response = conn.getresponse()
			data = response.read()
			dumpData("data_%s.out" % (i+1), data)
		except Exception as e:
			# print e
			print("[Errno {0}] {1}".format(e.errno, e.strerror))
			
def test_isAuId(id):
	count = 1
	params = urllib.urlencode({
		'expr': "Composite(AA.AuId=%s)" % (id),
		'attributes': 'Id,Ti,AA.AuId,F.FId,C.CId,J.JId',
		'subscription-key': CFE.subKey,
	})
	try:
		conn = httplib.HTTPSConnection(CFA.website)
		conn.request("GET", CFA.url+"evaluate?%s" % (params))
		response = conn.getresponse()
		data = response.read()
		dumpData("data_%s.out" % (id), data)
	except Exception as e:
		print e
		# print("[Errno {0}] {1}".format(e.errno, e.strerror))	
	connc.close()
	
		
def test_Both_Author(AuId1, AuId2):
	count = 5
	expr = "And(Composite(AA.AuId=%s),Composite(AA.AuId=%s))" % (AuId1, AuId2)
	params = urllib.urlencode({
		'expr': expr,
		'attributes': 'Id,Ti,AA.AuId,F.FId,C.CId,J.JId',
		'count': count,
		'subscription-key': CFE.subKey,
	})
	try:
		conn = httplib.HTTPSConnection(CFA.website)
		conn.request("GET", CFA.url+"evaluate?%s" % (params))
		response = conn.getresponse()
		data = response.read()
		dumpData("data_both_author_m1.out", data)
	except Exception as e:
		print e
	
	expr = 	"Composite(And(AA.AuId=%s,AA.AuId=%s))" % (AuId1, AuId2)
	params = urllib.urlencode({
		'expr': expr,
		'attributes': 'Id,Ti,AA.AuId,F.FId,C.CId,J.JId,R.RId',
		'count': count,
		'subscription-key': CFE.subKey,
	})
	try:
		conn.request("GET", CFA.url+"evaluate?%s" % (params))
		response = conn.getresponse()
		data = response.read()
		dumpData("data_both_author_m2.out", data)
	except Exception as e:
		print e
		
	conn.close()
	
	
def FetchAll_ByAuId(auId):
	count = 500
	params = urllib.urlencode({
		'expr': "Composite(AA.AuId=%s)" % (auId),
		'attributes': 'Id,AA.AuId,AA.AuN,AA.AfId,AA.AfN',
		'count': count,
		'subscription-key': CFE.subKey,
	})
	try:
		conn = httplib.HTTPSConnection(CFA.website)
		conn.request("GET", CFA.url+"evaluate?%s" % (params))
		response = conn.getresponse()
		data = response.read()
		dumpData("auId_%s.out" % (auId), data)
	except Exception as e:
		print e
		
def FetchAll_ByCId_RId(CId, RId):
	count = 500
	params = urllib.urlencode({
		'expr': "And(RId=%s,Composite(C.CId=%s))" % (RId, CId),
		'attributes': 'Id,RId,C.CId',
		'count': count,
		'subscription-key': CFE.subKey,
	})
	try:
		conn = httplib.HTTPSConnection(CFA.website)
		conn.request("GET", CFA.url+"evaluate?%s" % (params))
		response = conn.getresponse()
		data = response.read()
		dumpData("CId_%s_RId_%s.out" % (CId, RId), data)
	except Exception as e:
		print e
		
def FetchAll_ByCId(CId):
	count = 10000
	params = urllib.urlencode({
		'expr': "Composite(C.CId=%s)" % (CId),
		'attributes': 'Id,RId,C.CId',
		'count': count,
		'subscription-key': CFE.subKey,
	})
	try:
		conn = httplib.HTTPSConnection(CFA.website)
		conn.request("GET", CFA.url+"evaluate?%s" % (params))
		response = conn.getresponse()
		data = response.read()
		dumpData("CId_%s.out" % (CId), data)
	except Exception as e:
		print e
		
def test_Author_and_or(AuId1, AuId2):
	expr = 	"And(Composite(AA.AuId=%s),AA.AuId=%s))" % (AuId1, AuId2)
	params = urllib.urlencode({
		'expr': expr,
		'attributes': 'Id,Ti,AA.AuId,F.FId,C.CId,J.JId,R.RId',
		'count': count,
		'subscription-key': CFE.subKey,
	})
	try:
		conn = httplib.HTTPSConnection(CFA.website)
		conn.request("GET", CFA.url+"evaluate?%s" % (params))
		response = conn.getresponse()
		data = response.read()
		dumpData("data_both_author_m2.out", data)
		conn.close()
	except Exception as e:
		print e
		
	
def test_RId(rid):
	expr = "RId=%s" % (rid)
	count = 10000
	params = urllib.urlencode({
		'expr': expr,
		'attributes': 'Id,Ti,AA.AuId,AA.AuN,AA.AfId,AA.AfN,RId',
		'count': count,
		'subscription-key': CFE.subKey,
	})
	try:
		conn = httplib.HTTPSConnection(CFA.website)
		conn.request("GET", CFA.url+"evaluate?%s" % (params))
		response = conn.getresponse()
		data = response.read()
		dumpData("data_rid.out", data)
		conn.close()
	except Exception as e:
		print e
	
def expr_auids(auids):
	length = len(auids)
	if length==1:
		return "Composite(AA.AuId=%s)" % (auids[0])
	mid = length>>1
	lexpr = expr_auids(auids[:mid])
	rexpr = expr_auids(auids[mid:])
	return "Or(%s,%s)" % (lexpr, rexpr)
	
def expr_afids(afids):
	length = len(afids)
	if length==1:
		return "Composite(AA.AfId=%s)" % (afids[0])
	mid = length>>1
	lexpr = expr_afids(afids[:mid])
	rexpr = expr_afids(afids[mid:])
	return "Or(%s,%s)" % (lexpr, rexpr)
	
def expr_auids_and_afids(auids, afids):
	auids_expr = expr_auids(auids)
	afids_expr = expr_afids(afids)
	return "And(%s,%s)" % (auids_expr,afids_expr)
	
	
def test_AuId_and_AfId():
	auids = [
		2095616704,2241113319,2095616704
	]
	afids = [
		1290206253,125839683,98285908
	]
	expr = expr_auids_and_afids(auids, afids)
	count = 5000
	params = urllib.urlencode({
		'expr': expr,
		'attributes': 'Id,AA.AuId,AA.AfId',
		'count': count,
		'subscription-key': CFE.subKey,
	})
	try:
		conn = httplib.HTTPSConnection(CFA.website)
		conn.request("GET", CFA.url+"evaluate?%s" % (params))
		response = conn.getresponse()
		data = response.read()
		dumpData("data_auid_and_afid.out", data)
		conn.close()
	except Exception as e:
		print e
	
	
if __name__ == "__main__":
	IdList = [
		2180737804,
		2251253715,
		189831743,
		2147152072,
		2310280492,
		2332023333,
	]
	# for id in IdList:
		# Evaluate.evaluate_ById(id)
		# sleep(2)
	# Evaluate.evaluate_ById(2332023333)
	# Evaluate.evaluate_ByAfId(2157025439)
	
	# test_multi_id(IdList)
	# for id in IdList:
		# test_isAuId(id)
	# test_Both_Author(2048498903, 2223920688)
	# for auId in [2224185131L, 166801255, 2118962444, 2095616704, 2277027218L]:
		# FetchAll_ByAuId(auId)
		# sleep(1)
	# for CId, RId in [[1158167855, 2310280492]]:
		# FetchAll_ByCId_RId(CId, RId)
		# sleep(1)
	# FetchAll_ByCId(1158167855)
	
	# test_RId(1965061793)
	# FetchAll_ByAuId(2095616704)
	test_AuId_and_AfId()