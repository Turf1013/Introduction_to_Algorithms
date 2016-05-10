#!/usr/bin/python
import httplib, urllib, base64

class constForAPI:
	website = "oxfordhk.azure-api.net"
	url = "/academic/v1.0/"

class CFA(constForAPI):
	pass

class constForEvaluate:
	subKey = "f7cc29509a8443c5b3a5e56b0e38b5a6"

class CFE(constForEvaluate):
	pass

def dumpData(filename, data):
	if isinstance(data, str):
		with open(filename, "w") as fout:
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

if __name__ == "__main__":
	Evaluate.evaluate_ById(2157025439)
	# Evaluate.evaluate_ByAuId(2157025439)
	# Evaluate.evaluate_ByAfId(2157025439)