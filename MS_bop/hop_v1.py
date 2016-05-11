#!/usr/bin/python
import web
import BaseHTTPServer
import httplib, urllib, json
import urlparse
from collections import defaultdict

urls = (
	# '/v1(.*)', 'hop',
	'/v1/eval(.*)', 'hop',
)

class constForAPI:
	website = "oxfordhk.azure-api.net"
	url = "/academic/v1.0/"
	ID = 'ID'
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
	ref_attribs = [
		'Y',
	]
	order_RID = "RId:asc"
	order_ID = "Id:asc"
	COUNT = 200
	PACKET = 10

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
		
	@staticmethod
	def has_FId(d, val):
		vals = d.get("F")
		if not vals:
			return False
		if isinstance(vals, list):
			for vals_ in vals:
				if vals_.get("FId") == val:
					return True
		elif isinstance(vals, dict):
			if vals.get("FId") == val:
				return True
		else:
			return False
			
	@staticmethod
	def has_CId(d, val):
		vals = d.get("C")
		if not vals:
			return False
		if isinstance(vals, list):
			for vals_ in vals:
				if vals_.get("CId") == val:
					return True
		elif isinstance(vals, dict):
			if vals.get("CId") == val:
				return True
		else:
			return False
			
	@staticmethod
	def has_JId(d, val):
		vals = d.get("J")
		if not vals:
			return False
		if isinstance(vals, list):
			for vals_ in vals:
				if vals_.get("JId") == val:
					return True
		elif isinstance(vals, dict):
			if vals.get("JId") == val:
				return True
		else:
			return False
			
	@staticmethod
	def has_RId(d, val):
		vals = d.get("RId")
		if not vals:
			return False
		if isinstance(vals, list):
			return val in vals
		else:
			return False
	
	@staticmethod
	def has_AuId(d, val):
		vals = d.get("AA")
		if not vals:
			return False
		if isinstance(vals, list):
			for vals_ in vals:
				if vals_.get("AuId") == val:
					return True
		elif isinstance(vals, dict):
			if vals.get("AuId") == val:
				return True
		else:
			return False
			
	@staticmethod
	def has_AfId(d, val):
		vals = d.get("AA")
		if not vals:
			return False
		if isinstance(vals, list):
			for vals_ in vals:
				if vals_.get("AfId") == val:
					return True
		elif isinstance(vals, dict):
			if vals.get("AfId") == val:
				return True
		else:
			return False		
		
		
	@staticmethod
	def has_Id(d, name, val):
		if not isinstance(d, dict):
			raise TypeError, "[has_Id] first param need to be dict"
		if name[0] == 'F':
			return CFA.has_FId(d, val)
		elif name[0] == 'C':
			return CFA.has_CId(d, val)
		elif name[0] == 'J':
			return CFA.has_JId(d, val)
		elif name[0] == 'R':
			return CFA.has_RId(d, val)	
		elif name[0] == 'A':
			if name[1] == 'u':
				return CFA.has_AuId(d, val)
			elif name[1] == 'f':
				return CFA.has_AfId(d, val)
		raise ValueError, "[has_Id] undefined id name"
		

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
	def expr_multi_or(ids, expr_func):
		length = len(ids)
		if length==1:
			return expr_func(ids[0])
		half = length>>1
		lexp = Util.expr_multi_or(ids[:half], expr_func)
		rexp = Util.expr_multi_or(ids[half:], expr_func)
		return "Or(%s,%s)" % (lexp, rexp)
		
	@staticmethod	
	def expr_multi_and(ids, expr_func):
		length = len(ids)
		if length==1:
			return expr_func(ids[0])
		half = length>>1
		lexp = Util.expr_multi_and(ids[:half], expr_func)
		rexp = Util.expr_multi_and(ids[half:], expr_func)
		return "And(%s,%s)" % (lexp, rexp)

		
	@staticmethod
	def expr_ids_and_rid(ids, rid):
		if len(ids)==1:
			return "And(Id=%s, RId=%s)" % (ids[0], rid)
		else:
			id_exp = Util.expr_multi_or(ids, Util.expr_id)
			return "And(id_exp, RId=%s)" % (id_exp, rid)
			
			
	@staticmethod
	def expr_id_and_rid(id, rid):
		return "And(Id=%s, RId=%s)" % (id, rid)
		
		
	@staticmethod
	def expr_fid_and_rid(fid, rid):
		return "And(RId=%s, Composite(F.FId=%s))" % (rid, fid)
		
		
	@staticmethod
	def expr_cid_and_rid(cid, rid):
		return "And(RId=%s, Composite(C.CId=%s))" % (rid, cid)
		
		
	@staticmethod
	def expr_jid_and_rid(jid, rid):
		return "And(RId=%s, Composite(J.JId=%s))" % (rid, jid)
		
		
	@staticmethod
	def expr_auid_and_rid(auid, rid):
		return "And(Composite(AA.AuId=%s), RId=%s)" % (auid, rid)
		
		
	@staticmethod	
	def	expr_composite(item):
		return "Composite(%s=%s)" % (item[0], item[1])
		
		
	@staticmethod
	def expr_all_and_rid(items, rid):
		or_exp = Util.expr_mutli_or(items, Util.expr_composite)
		return "And(RId=%s, %s)" % (rid, or_exp)
		
		
	@staticmethod
	def expr_ids(ids):
		if not ids:
			raise ValueError, "[expr_all_and_id] ids must not null"
		return Util.expr_multi_or(ids, Util.expr_id)
		
	@staticmethod
	def expr_all_and_ids(items, ids):
		if not ids:
			raise ValueError, "[expr_all_and_id] ids must not null"
		or_exp = Util.expr_mutli_or(items, Util.expr_composite)
		id_exp = Util.expr_multi_or(ids, Util.expr_id)
		return "And(%s, %s)" % (id_exp, or_exp)
			
			
	@staticmethod
	def expr_ref_with_date(ids, refDict):
		year = refDict.get('Y')
		id_exp = Util.expr_multi_or(ids, Util.expr_id)
		if year:
			return "And(Id=%s, Y<%s)" % (id_exp, year)
		else:
			return id_exp
	

	@staticmethod
	def expr_Id(id):
		return CFA.ID + "=" + id
		
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
		ed_attrList = json.loads(data)["entities"]
		
		attrib += [CFA.RID]
		data = self.eva.getData(CFE.get_Id_params(stId, attrib))
		st_attrList = json.loads(data)["entities"]
		
		# print ed_attrList, st_attrList
		
		# step1: check F.FId
		stIds = CFA.get_FId(st_attrList)
		edIds = CFA.get_FId(ed_attrList)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step2: check J.JId
		stIds = CFA.get_JId(st_attrList)
		edIds = CFA.get_JId(ed_attrList)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step3: check C.CId
		stIds = CFA.get_CId(st_attrList)
		edIds = CFA.get_CId(ed_attrList)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step4: check AA.AuId
		stIds = CFA.get_AuId(st_attrList)
		edIds = CFA.get_AuId(ed_attrList)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step0: check Id's Rid's Rid
		RIds = CFA.get_RId(st_attrList)
		medium = []
		RIds_length = len(RIds)
		for i in xrange(0, RIds_length, CFA.PACKET):
			ids = RIds[i:i+CFA.PACKET]
			expr = Util.expr_ids_and_rid(ids, edId)
			count = len(ids)
			data = self.eva.getData(CFE.get_params(expr, attrib, count))
			resList = json.loads(data)["entities"]
			for resDict in resList:
				id = resDict.get("Id")
				if id:
					medium.append(id)
		ret += medium
		
		return Util.to_hop2(ret, stId, edId)
		
		
	def get_3hop(self, stId, edId):
		"""
			Id -> Id -> Id -> Id				(1)
			Id -> F.FId -> Id -> Id				(2)
			Id -> C.CId -> Id -> Id				(3)
			Id -> J.JId -> Id -> Id				(4)
			Id -> AA.AuId -> Id -> Id			(5)
			Id -> Id -> F.FId -> Id				(6)
			Id -> Id -> C.CId -> Id				(7)
			Id -> Id -> J.JId -> Id				(8)
			Id -> Id -> AA.AuId -> Id			(9)
		"""
		ret = []
		
		# Evaluate stId & edId
		attrib = CFA.attribs
		data = self.eva.getData(CFE.get_Id_params(edId, attrib))
		ed_attrList = json.loads(data)["entities"]
		
		attrib += [CFA.RID]
		data = self.eva.getData(CFE.get_Id_params(stId, attrib))
		st_attrList = json.loads(data)["entities"]
		
		# step1: handle 2-5
		FIds = CFA.get_FId(st_attrList)
		CIds = CFA.get_CId(st_attrList)
		JIds = CFA.get_JId(st_attrList)
		AuIds = CFA.get_AuId(st_attrList)
		n_fid,n_cid,n_jid,n_auid = len(FIds), len(CIds), len(JIds), len(AuIds)
		mx = max(n_fid,n_cid,n_jid,n_auid)
		for i in xrange(mx):
			L = []
			attribs = []
			if i<n_auid:
				L.append([CFA.AAAUID, AuIds[i]])
				attribs.append(CFA.AAAUID)
			if i<n_cid:
				L.append([CFA.CCID, CIds[i]])
				attribs.append(CFA.CCID)
			if i<n_jid:
				L.append([CFA.JJID, JIds[i]])
				attribs.append(CFA.JJID)
			if i<n_fid:
				L.append([CFA.FFID, FIds[i]])
				attribs.append(CFA.FFID)
			expr = Util.expr_all_and_rid(L, edId)
			count = CFA.COUNT
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			resList = json.loads(data)["entities"]
			tmpList = []
			for resDict in resList:
				id = resDict.get("Id")
				if not id:
					continue
				for idName, idVal in L:
					if CFA.has_Id(resDict, idName, idVal):
						tmpList.append([idVal, id])
			ret += tmpList
			
		# step2: handle 6-9 & 1
		data = self.eva.getData(CFE.get_Id_params(edId, ['Y']))
		ed_refDict = json.loads(data)["entities"][0]
		ed_year = ed_refDict.get("Y")
		if not ed_year:
			ed_year = 2020
		RIds = CFA.get_RId(st_attrList)
		FIds = CFA.get_FId(ed_attrList)
		CIds = CFA.get_CId(ed_attrList)
		JIds = CFA.get_JId(ed_attrList)
		AuIds = CFA.get_AuId(ed_attrList)
		attribs = [CFA.ID, 'Y'] + CFA.attrib
		Id2Id_List = []
		RIds_length = len(RIds)
		for j in xrange(0, RIds_length, CFA.PACKET):
			ids = RIds[j:j+CFA.PACKET]
			expr = Util.expr_ids(L, ids)
			count = CFA.PACKET
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			resList = json.loads(data)["entities"]
			tmpList = []
			for resDict in resList:
				id = resDict.get("Id")
				if not id:
					continue
					
				for fid in FIds:
					if CFA.has_FId(resDict, fid):
						tmpList.append([id, fid])
				for cid in CIds:
					if CFA.has_CId(resDict, cid):
						tmpList.append([id, cid])
				for jid in JIds:
					if CFA.has_JId(resDict, jid):
						tmpList.append([id, jid])
				for auid in AuIds:
					if CFA.has_AuId(resDict, auid):
						tmpList.append([id, auid])
				ret += tmpList
				
				# check currenct rid's year for next `Id->Id`
				year = resDict.get('Y')
				if year and year>=ed_year+2:
					Id2Id_List.append(id)
					
		# rrid_Set is two layer's reference			
		rref_Dict = defaultdict(list)
		rrid_Set = set()		
		Id2Id_length = len(Id2Id_List)
		for j in xrange(0, Id2Id_length, CFA.PACKET):
			ids = Id2Id_List[j:j+CFA.PACKET]
			expr = Util.expr_ids(ids)
			count = len(ids)
			attribs = [CFA.ID, CFA.RID, 'Y']
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			resList = json.loads(data)["entities"]
			tmpList = []
			for resDict in resList:
				id = resDict.get("Id")
				ridList = resDict.get("RId")
				if not ridList or not id:
					continue
				year = resDict.get('Y')
				if year and year>=ed_year+1:
					for rid in ridList:
						rref_Dict[rid].append(id)
					tmpList += ridList
			rrid_Set |= set(tmpList)
		
		rrid_List = list(rrid_Set)
		rrid_length = len(rrid_List)
		for j in xrange(0, rrid_length, CFA.PACKET):
			ids = rrid_List[j:j+CFA.PACKET]
			expr = Util.expr_ids_and_rid(ids, edId)
			count = len(ids)
			attribs = [CFA.ID]
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			resList = json.loads(data)["entities"]
			tmpList = []
			for resDict in resList:
				id = resDict.get("Id")
				if not id:
					continue
				tmpList += map(lambda x: [x, id], rref_Dict[id])
			ret += tmpList
			
		return Util.to_hop3(ret, stId, edId)
		
		
	def get_hop(self, stId, edId):
		print "From Id to Id"
		return self.get_1hop(stId, edId) + self.get_2hop(stId, edId) + self.get_3hop(stId, edId)	

		
		
class solution_Id_AuId:

	def __init__(self):
		self.eva = Evaluation()


	def get_1hop(self, stId, edId):
		data = self.eva.getData(CFE.get_Id_AuId_params(stId))
		if json.loads(data)["entities"]:
			return [[stId, edId]]
		else:
			return []
			
			
	def get_r1hop(self, stId, edId):
		data = self.eva.getData(CFE.get_Id_AuId_params(stId))
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
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attrib, count))
		st_attrList = json.loads(data)["entities"]
		
		expr = Util.expr_AuId(edId)
		order = CFA.order_ID
		attrib = [CFA.ID]
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attrib, count))
		ed_attrList = json.loads(data)["entities"]
		
		# they should be sort already
		stIds = CFA.get_RId(st_attrList)
		edIds = CFA.get_Id(ed_attrList)
		medium = Util.find_common(stIds, edIds)
		
		return Util.to_hop2(medium, stId, edId)
		
	def get_r2hop(self, stId, edId):
		"""
			Id -> Id -> AA.AuId
		"""
		expr = Util.expr_Id(stId)
		order = CFA.order_RID
		attrib = [CFA.RID]
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attrib, count))
		st_attrList = json.loads(data)["entities"]
		
		expr = Util.expr_AuId(edId)
		order = CFA.order_ID
		attrib = [CFA.ID]
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attrib, count))
		ed_attrList = json.loads(data)["entities"]
		
		# they should be sort already
		stIds = CFA.get_RId(st_attrList)
		edIds = CFA.get_Id(ed_attrList)
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
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params(expr, attrib, count))
		attrDict = json.loads(data)["entities"]
		ret += 	CFA.get_AfId(attrDict)
		
		attrib = [CFA.ID]
		count = CFA.COUNT
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
		ret = self.get_hop(stId, edId)
		return json.dumps(ret)

global solver
solver = solution()

class hop:
	def GET(self, query):
		d = web.input()
		stId = int(d.id1)
		edId = int(d.id2)
		return solver.solve(stId, edId)
		

def localtest():
	urls = [
		"http://localhost/?id2=2310280492&id1=2332023333",
		# "http://localhost/?id2=2180737804&id1=2251253715",
		"http://localhost/?id2=189831743&id1=2147152072",
	]
	for url in urls:
		query = url[url.rindex('/')+1:]
		L = query.split('&')
		if L[1].startswith('id2'):
			stId = int(L[0].split('=')[-1])
			edId = int(L[1].split('=')[-1])
		else:
			edId = int(L[0].split('=')[-1])
			stId = int(L[1].split('=')[-1])
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
			
			ans = solver.solve(stId, edId)
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
	# remoteTest()
	localtest()
	# app = web.application(urls, globals())
	# app.run()
