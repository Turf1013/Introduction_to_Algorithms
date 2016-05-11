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
			dumpData("Evaluate_Id.out", data)
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
		'attributes': 'Id,Ti,AA.AuId,F.FId,C.CId,J.JId',
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
	# Evaluate.evaluate_ByAuId(2157025439)
	# Evaluate.evaluate_ByAfId(2157025439)
	
	# test_multi_id(IdList)
	# for id in IdList:
		# test_isAuId(id)
	test_Both_Author(2048498903, 2223920688)