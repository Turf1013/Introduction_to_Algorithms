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
	ref_attribs = [
		'Y',
	]
	COUNT = 200
	PACKET = 10

class CFA(constForAPI):

	@staticmethod
	def get_year(ent):
		ret = None
		if isinstance(ent, list):
			if ent:
				ret = ent[0].get('Y')
		elif isinstance(ent, dict):
			ret = ent.get('Y')
		return ret
		
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
		if isinstance(ent, list):
			ret = map(lambda d:d.get("Id"), ent)
			return filter(lambda x:x is not None, ret)
		elif isinstance(ent, dict):
			ret = ent.get("Id")
			if not ret:
				ret = []
			return ret
		else:
			return []
			
	@staticmethod
	def get_RId(ent):
		if isinstance(ent, list):
			ret = map(lambda d:d.get("RId"), ent)
			return reduce(lambda x,y:x+y, ret)
			
		elif isinstance(ent, dict):
			ret = ent.get("RId")
			if not ret:
				ret = []
			return ret
		else:
			return []
			
		
	@staticmethod
	def get_AuId(ent):
		if isinstance(ent, list):
			ret = map(lambda d:CFA.get_ids(d.get("AA"), "AuId"), ent)
			return reduce(lambda x,y:x+y, ret)
		elif isinstance(ent, dict):
			ret = CFA.get_ids(ent.get("AA"), "AuId")
			return ret
		else:
			return []
			
			
	@staticmethod
	def get_AfId(ent, auid=None):
		if auid:
			ret = []
			if isinstance(ent, list):
				for attrDict in ent:
					AA_List = attrDict.get("AA")
					if not AA_List:
						continue
					for d in AA_List:
						if d.get("AuId")==auid:
							tmp = d.get("AfId")
							if tmp:
								ret.append(tmp)
			elif isinstance(ent, dict):
				AA_List = attrDict.get("AA")
				if AA_List:
					for d in AA_List:
						if d.get("AuId")==auid:
							tmp = d.get("AfId")
							if tmp:
								ret.append(tmp)
			return ret
		else:
			if isinstance(ent, list):
				ret = map(lambda d:CFA.get_ids(d.get("AA"), "AfId"), ent)
				return reduce(lambda x,y:x+y, ret)
			elif isinstance(ent, dict):
				ret = CFA.get_ids(ent.get("AA"), "AfId")
				return ret
			else:
				return []
			
			
	@staticmethod
	def get_CId(ent):
		if isinstance(ent, list):
			ret = map(lambda d:CFA.get_ids(d.get("C"), "CId"), ent)
			return reduce(lambda x,y:x+y, ret)
		elif isinstance(ent, dict):
			ret = CFA.get_ids(ent.get("C"), "CId")
			return ret
		else:
			return []
			
			
	@staticmethod
	def get_JId(ent):
		if isinstance(ent, list):
			ret = map(lambda d:CFA.get_ids(d.get("J"), "JId"), ent)
			return reduce(lambda x,y:x+y, ret)
		elif isinstance(ent, dict):
			ret = CFA.get_ids(ent.get("J"), "JId")
			return ret
		else:
			return []
			
			
	@staticmethod
	def get_FId(ent):
		if isinstance(ent, list):
			ret = map(lambda d:CFA.get_ids(d.get("F"), "FId"), ent)
			return reduce(lambda x,y:x+y, ret)
		elif isinstance(ent, dict):
			ret = CFA.get_ids(ent.get("F"), "FId")
			return ret
		else:
			return []
			
			
	@staticmethod
	def	get_mainId_List(ent):
		ret = []
		ret += CFA.get_FId(ent)
		ret += CFA.get_CId(ent)
		ret += CFA.get_JId(ent)
		ret += CFA.get_AuId(ent)
		return ret
			
			
	@staticmethod
	def get_mainId_Set(ent):
		return set(CFA.get_mainId_List(ent))
		
		
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
	
	
	@staticmethod
	def get_AfId_Dict(ent):
		ret = defaultdict(list)
		if isinstance(ent, dict):
			ent = [ent]
		if isinstance(ent, list):
			for attrDict in ent:
				AA_List = attrDict.get("AA")
				if not AA_List:
					continue
				for d in AA_List:
					afid = d.get("AfId")
					auid = d.get("AuId")
					if afid and auid:
						ret[afid].append(auid)
		return ret	
		
		
	@staticmethod
	def get_AuId_Dict(ent):
		ret = defaultdict(set)
		if isinstance(ent, dict):
			ent = [ent]
		if isinstance(ent, list):
			for attrDict in ent:
				AA_List = attrDict.get("AA")
				if not AA_List:
					continue
				for d in AA_List:
					afid = d.get("AfId")
					auid = d.get("AuId")
					if afid and auid:
						ret[auid].add(afid)
		return ret	

	@staticmethod
	def get_RId_rDict(ent):
		ret = defaultdict(set)
		if isinstance(ent, dict):
			ent = [ent]
		if isinstance(ent, list):
			for attrDict in ent:
				id = attrDict.get("Id")
				if not id:
					continue
				rid_List = CFA.get_RId(attrDict)
				for rid in rid_List:
					ret[rid].add(id)
		return ret
		

class constForEvaluate:
	subKey = "f7cc29509a8443c5b3a5e56b0e38b5a6"
	order_RID = "RId:asc"
	order_ID = "Id:asc"
	
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
		id_exp = Util.expr_multi_or(ids, Util.expr_Id)
		return "And(%s,RId=%s)" % (id_exp, rid)
		
	@staticmethod
	def expr_ids_with_rids(ids, rids):
		if not ids or not rids:
			raise ValueError, "[expr_ids_with_rids] ids & rids must not null"
		id_exp = Util.expr_multi_or(ids, Util.expr_Id)
		rid_exp = Util.expr_multi_or(rids, Util.expr_RId)
		return "And(%s,%s)" % (id_exp, rid_exp)
			
	@staticmethod
	def expr_id_and_rid(id, rid):
		return "And(Id=%s,RId=%s)" % (id, rid)
		
	@staticmethod
	def expr_id_and_auid(id, auid):
		return "And(Id=%s,Composite(AA.AuId=%s))" % (id, auid)	
		
	@staticmethod
	def expr_fid_and_rid(fid, rid):
		return "And(RId=%s,Composite(F.FId=%s))" % (rid, fid)
		
		
	@staticmethod
	def expr_cid_and_rid(cid, rid):
		return "And(RId=%s,Composite(C.CId=%s))" % (rid, cid)
		
		
	@staticmethod
	def expr_jid_and_rid(jid, rid):
		return "And(RId=%s,Composite(J.JId=%s))" % (rid, jid)
		
		
	@staticmethod
	def expr_auid_and_rid(auid, rid):
		return "And(Composite(AA.AuId=%s),RId=%s)" % (auid, rid)
		
		
	@staticmethod	
	def	expr_composite(item):
		return "Composite(%s=%s)" % (item[0], item[1])
		
	@staticmethod
	def	expr_all_and_auid(items, auid):
		or_exp =  Util.expr_multi_or(items, Util.expr_composite)
		return "And(Composite(AA.AuId=%s),%s)" % (auid, or_exp)
		
	@staticmethod
	def expr_all_and_rid(items, rid):
		or_exp = Util.expr_multi_or(items, Util.expr_composite)
		return "And(RId=%s,%s)" % (rid, or_exp)
		
		
	@staticmethod
	def expr_ids(ids):
		if not ids:
			raise ValueError, "[expr_ids] ids must not null"
		return Util.expr_multi_or(ids, Util.expr_Id)
		
		
	@staticmethod
	def expr_all_and_ids(items, ids):
		if not ids:
			raise ValueError, "[expr_all_and_id] ids must not null"
		or_exp = Util.expr_multi_or(items, Util.expr_composite)
		id_exp = Util.expr_multi_or(ids, Util.expr_Id)
		return "And(%s,%s)" % (id_exp, or_exp)
			
			
	@staticmethod
	def expr_all_and_year(ids, year):
		id_exp = Util.expr_multi_or(ids, Util.expr_Id)
		if year:
			return "And(%s,Y<=%s)" % (id_exp, year)
		else:
			return id_exp
	
	@staticmethod
	def expr_auid_and_year(auid, year):
		return "And(Composite(AA.AuId=%s),Y<=%s)" % (auid, year)
	

	@staticmethod
	def expr_Id(id):
		return "Id=%s" % (id)
		
	@staticmethod
	def expr_RId(id):
		return "RId=%s" % (id)
		
	@staticmethod
	def expr_AuId(id):
		return "Composite(AA.AuId=%s)" % (id)
		
	@staticmethod
	def expr_AfId(id):
		return "Composite(AA.AfId=%s)" % (id)
		
	@staticmethod
	def expr_CId(id):
		return "Composite(C.CId=%s)" % (id)
		
	@staticmethod
	def expr_JId(id):
		return "Composite(J.JId=%s)" % (id)
		
	@staticmethod
	def expr_FId(id):
		return "Composite(F.FId=%s)" % (id)
		
	@staticmethod
	def expr_comp_AuId(id1, id2):
		return "And(Composite(AA.AuId=%s),Composite(AA.AuId=%s))" % (id1, id2)
		
		
	@staticmethod
	def expr_auIds_match_afIds(auIds, afIds):
		auid_exp = Util.expr_multi_or(auIds, Util.expr_AuId)
		afid_exp = Util.expr_multi_or(afIds, Util.expr_AfId)
		return "And(%s,%s)" % (auid_exp, afid_exp)
		
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
	def find_auIds_match_afIds(entList, auIds, afIds):
		ret = []
		d = CFA.get_AfId_Dict(entList)
		for afid in afIds:
			L = d.get(afid)
			if L:
				ret += map(lambda x:[x,afid], set(L))
		return ret
		
	@staticmethod
	def find_rid_match_rid(ent, rid_Set):
		ret = []
		if isinstance(ent, dict):
			ent = [ent]
		if isinstance(ent, list):
			for attrDict in ent:
				id = attrDict.get("Id")
				rids = attrDict.get("RId")
				if id and rids:
					tmpSet = rid_Set & set(rids)
					ret += map(lambda x:[id, x], tmpSet)
		return ret		
		
		
	@staticmethod
	def to_hop2(medium, st, ed):
		return map(lambda x:[st, long(x), ed], medium)
		
	@staticmethod
	def to_hop3(medium, st, ed):
		return map(lambda x:[st, long(x[0]), long(x[1]), ed], medium)
	
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
		Id -> Id -> Id	(hard)		(1)
		Id -> F.FId -> Id 			(2)
		Id -> C.CId -> Id 			(3)
		Id -> J.JId -> Id 			(4)
		Id -> AA.AuId -> Id 		(5)
		"""
		ret = []
		
		# Evaluate stId & edId
		attrib = CFA.attribs
		data = self.eva.getData(CFE.get_Id_params(edId, attrib))
		ed_entList = json.loads(data)["entities"]
		
		attrib += [CFA.RID]
		data = self.eva.getData(CFE.get_Id_params(stId, attrib))
		st_entList = json.loads(data)["entities"]
		
		print "ed =", ed_entList
		print "st =", st_entList
		
		# step1: handle 2-5
		st_mainId_Set = CFA.get_mainId_Set(st_entList)
		ed_mainId_Set = CFA.get_mainId_Set(ed_entList)
		tmpSet = st_mainId_Set & ed_mainId_Set
		tmpList = map(lambda x:long(x), tmpSet)
		ret += tmpList
		
		# step2: handle 1
		RIds = list(set(CFA.get_RId(st_entList)))
		print "RIds =", RIds
		tmpList = []
		RIds_length = len(RIds)
		attribs = [CFA.ID]
		for i in xrange(0, RIds_length, CFA.PACKET):
			ids = RIds[i:i+CFA.PACKET]
			count = len(ids)
			expr = Util.expr_ids_and_rid(ids, edId)
			print "expr =", expr
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			entList = json.loads(data)["entities"]
			print "entList =", entList
			tmpList += CFA.get_Id(entList)
		ret += tmpList
		
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
		attrib = CFA.attribs + ['Y']
		data = self.eva.getData(CFE.get_Id_params(edId, attrib))
		ed_entList = json.loads(data)["entities"]
		
		attrib += [CFA.RID]
		data = self.eva.getData(CFE.get_Id_params(stId, attrib))
		st_entList = json.loads(data)["entities"]
		
		print "ed =", ed_entList
		print "st =", st_entList
		
		# step1: handle 2-5
		st_FId_Set = set(CFA.get_FId(st_entList))
		st_CId_Set = set(CFA.get_CId(st_entList))
		st_JId_Set = set(CFA.get_JId(st_entList))
		st_AuId_Set = set(CFA.get_AuId(st_entList))
		print "st_FId_Set =", st_FId_Set
		print "st_CId_Set =", st_CId_Set
		print "st_JId_Set =", st_JId_Set
		print "st_AuId_Set =", st_AuId_Set
		attribs = [CFA.ID]
		L = []
		if len(st_FId_Set):
			attribs.append(CFA.FFID)
			L += map(lambda x:[CFA.FFID, x], st_FId_Set)
		if len(st_CId_Set):
			attribs.append(CFA.CCID)
			L += map(lambda x:[CFA.CCID, x], st_CId_Set)
		if len(st_JId_Set):
			attribs.append(CFA.JJID)
			L += map(lambda x:[CFA.JJID, x], st_JId_Set)
		if len(st_AuId_Set):
			attribs.append(CFA.AAAUID)
			L += map(lambda x:[CFA.AAAUID, x], st_AuId_Set)
		if L:
			expr = Util.expr_all_and_rid(L, edId)
			print "expr =", expr
			count = CFA.COUNT
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			entList = json.loads(data)["entities"]
			print "entList = ", entList
			allSet = st_FId_Set | st_CId_Set | st_JId_Set | st_AuId_Set
			tmpList = []
			for attrDict in entList:
				id = attrDict.get("Id")
				if not id:
					continue
				tmpSet = CFA.get_mainId_Set(attrDict)
				tmpSet &= allSet
				tmpList += map(lambda x:[x, id], tmpSet)
			ret += tmpList
			
		# step2: handle 6-9 
		ed_year = CFA.get_year(ed_entList)
		if not ed_year:
			ed_year = 2014
		print "ed_year = ", ed_year
		st_RId_Set = CFA.get_RId(st_entList)
		st_RId_List = list(st_RId_Set)
		ed_FId_Set = set(CFA.get_FId(ed_entList))
		ed_CId_Set = set(CFA.get_CId(ed_entList))
		ed_JId_Set = set(CFA.get_JId(ed_entList))
		ed_AuId_Set = set(CFA.get_AuId(ed_entList))
		print "st_RId_Set =", st_RId_Set
		print "ed_FId_Set =", ed_FId_Set
		print "ed_CId_Set =", ed_CId_Set
		print "ed_JId_Set =", ed_JId_Set
		print "st_AuId_Set =", st_AuId_Set
		attribs = [CFA.ID, CFA.RID, 'Y']
		allSet = set()
		if len(ed_FId_Set):
			attribs.append(CFA.FFID)
			allSet |= ed_FId_Set
		if len(ed_CId_Set):
			attribs.append(CFA.CCID)
			allSet |= ed_CId_Set
		if len(ed_JId_Set):
			attribs.append(CFA.JJID)
			allSet |= ed_JId_Set
		if len(ed_AuId_Set):
			attribs.append(CFA.AAAUID)
			allSet |= ed_AuId_Set
		st_RId_length = len(st_RId_List)
		Id3_rDict = defaultdict(set)
		for j in xrange(0, st_RId_length, CFA.PACKET):
			id2s = st_RId_List[j:j+CFA.PACKET]
			expr = Util.expr_ids(id2s)
			print "%d: expr = %s" % (j, expr)
			count = len(id2s)
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			print "data =", data
			entList = json.loads(data)["entities"]
			print "entList = ", entList
			tmpList = []
			for attrDict in entList:
				id2 = attrDict.get("Id")
				if not id2:
					continue
				# calculate (6)-(9)
				tmpSet = CFA.get_mainId_Set(attrDict)
				tmpSet &= allSet
				tmpList += map(lambda x:[id2, x], tmpSet)
				
				# `stId->Id2->Id3->edId` store valid rid
				year = attrDict.get('Y')
				if not year or year>=ed_year+2:
					rids_ = CFA.get_RId(attrDict)
					for rid in rids_:
						Id3_rDict[rid].add(id2)
			ret += tmpList
			
		# step3: handle 1
		Id3_List = Id3_rDict.keys()
		Id3_length = len(Id3_List)
		attribs = [CFA.ID]
		for i in xrange(0, Id3_length, CFA.PACKET):
			id3s = Id3_List[i:i+CFA.PACKET]
			count = len(id3s)
			expr = Util.expr_ids_and_rid(id3s, edId)
			print "%d: expr = %s" % (i, expr)
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			entList = json.loads(data)["entitites"]
			print "entList =", entList
			id3s_ = CFA.get_Id(entList)
			tmpList = []
			for id3 in id3s_:
				tmpList += map(lambda id2:[id2, id3], Id3_rDict[id3])
			ret += tmpList
			
		return Util.to_hop3(ret, stId, edId)
		
		
	def get_hop(self, stId, edId):
		print "From Id to Id"
		return self.get_1hop(stId, edId) + self.get_2hop(stId, edId) + self.get_3hop(stId, edId)	

		
		
class solution_Id_AuId:

	def __init__(self):
		self.eva = Evaluation()


	def get_1hop(self, stId, edId):
		"""
			Id -> AA.AuId
		"""
		data = self.eva.getData(CFE.get_Id_AuId_params(stId, edId))
		if json.loads(data)["entities"]:
			return [[stId, edId]]
		else:
			return []
		
		
	def get_2hop(self, stId, edId):
		"""
			Id -> Id -> AA.AuId
		"""
		expr = Util.expr_Id(stId)
		attrib = [CFA.ID, CFA.RID]
		data = self.eva.getData(CFE.get_params(expr, attrib))
		st_entList = json.loads(data)["entities"]
		
		expr = Util.expr_AuId(edId)
		order = CFE.order_ID
		attrib = [CFA.ID]
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attrib, count))
		ed_entList = json.loads(data)["entities"]
		
		print "stId =", stId
		print "edId =", edId
		print "st_entList =", st_entList
		print "ed_entList =", ed_entList
		
		# they should be sort already
		stRIds = CFA.get_RId(st_entList)
		edIds = CFA.get_Id(ed_entList)
		print "stRIds =", stRIds
		print "edIds =", edIds
		stRIds.sort()
		ret = Util.find_common(stRIds, edIds)
		
		return Util.to_hop2(ret, stId, edId)
		
		
	def get_3hop(self, stId, edId):
		"""
			Id -> Id -> Id -> AA.AuId				(1)
			Id -> F.FId -> Id -> AA.AuId			(2)
			Id -> C.CId -> Id -> AA.AuId			(3)
			Id -> J.JId -> Id -> AA.AuId			(4)
			Id -> AA.AuId -> Id -> AA.AuId			(5)
			Id -> AA.AuId -> AA.AfId -> AA.AuId		(6)
		"""
		ret = []
		
		attribs = CFA.attribs + [CFA.RID, CFA.AAAFID, CFA.AAAUID]
		data = self.eva.getData(CFE.get_Id_params(stId, attribs))
		st_entList = json.loads(data).get("entities")
		
		attribs = CFA.attribs + [CFA.ID, CFA.AAAFID, CFA.AAAUID]
		expr = Util.expr_AuId(edId)
		count = CFA.COUNT
		order = CFE.order_ID
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attribs, count))
		ed_entList = json.loads(data).get("entities")
		
		print "st_entList =", st_entList
		print "ed_entList =", ed_entList
		
		# step1: handle 2-5
		st_mainId_Set = CFA.get_mainId_Set(st_entList)
		print "st_mainId_Set =", st_mainId_Set
		tmpList = []
		for attrDict in ed_entList:
			id = attrDict.get("Id")
			if not id:
				continue
			ed_mainId_Set = CFA.get_mainId_Set(attrDict)
			print "ed: id = %s, mainIds = %s" % (id, ed_mainId_Set)
			tmpSet = st_mainId_Set & ed_mainId_Set
			tmpList += map(lambda x:[x, id], tmpSet)
		ret += tmpList	
		
		# step2: handle 6
		st_auId_Dict = CFA.get_AuId_Dict(st_entList)
		ed_afId_Set = set(CFA.get_AfId(ed_entList, edId))
		print "st_auId_Dict =", st_auId_Dict
		print "ed_afId_Set =", ed_afId_Set
		if ed_afId_Set and st_auId_Dict:
			tmpList = []
			for st_auId, st_afId_Set in st_auId_Dict.iteritems():
				print st_auId, st_afId_Set
				tmpSet = st_afId_Set & ed_afId_Set
				tmpList += map(lambda x:[st_auId, x], tmpSet)
			ret += tmpList
			
		# step3: handle 1
		Id3_List = CFA.get_Id(ed_entList)
		Id3_Set = set(Id3_List)
		Id2_List = CFA.get_RId(st_entList)
		print "Id3_List =", Id3_List
		print "Id2_List =", Id2_List
		if Id2_List and Id3_List:
			Id2_length = len(Id2_List)
			tmpList = []
			for i in xrange(0, Id2_length, CFA.PACKET):
				id2s = Id2_List[i:i+CFA.PACKET]
				expr = Util.expr_ids_with_rids(id2s, Id3_List)
				count = len(id2s)
				print "expr =", expr
				attribs = [CFA.ID, CFA.RID]
				data = self.eva.getData(CFE.get_params(expr, attribs, count))
				print "entData =", data
				entList = json.loads(data).get("entities")
				print "entList =", entList
				tmpList += Util.find_rid_match_rid(entList, Id3_Set)
			ret += tmpList
		
		return Util.to_hop3(ret, stId, edId)
	
			
	def get_hop(self, stId, edId):
		print "From Id to AuId"
		return self.get_1hop(stId, edId) + self.get_2hop(stId, edId) + self.get_3hop(stId, edId)	

	
class solution_AuId_Id:

	def __init__(self):
		self.eva = Evaluation()


	def get_1hop(self, stId, edId):
		"""
			AA.AuId -> Id
		"""
		data = self.eva.getData(CFE.get_Id_AuId_params(edId, stId))
		if json.loads(data)["entities"]:
			return [[stId, edId]]
		else:
			return []
		
		
	def get_2hop(self, stId, edId):
		"""
			AA.AuId -> Id -> Id
		"""
		expr = Util.expr_auid_and_rid(stId, edId)
		print "expr =", expr
		attrib = [CFA.ID]
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params(expr, attrib, count))
		entList = json.loads(data)["entities"]
		print "entList =", entList
		
		ret = CFA.get_Id(entList)
		
		return Util.to_hop2(ret, stId, edId)
		
		
	def get_3hop(self, stId, edId):
		"""
			AA.AuId -> Id -> Id -> Id				(1)
			AA.AuId -> Id -> F.FId -> Id			(2)
			AA.AuId -> Id -> C.CId -> Id			(3)
			AA.AuId -> Id -> J.JId -> Id			(4)
			AA.AuId -> Id -> AA.AuId -> Id			(5)
			AA.AuId -> AA.AfId -> AA.AuId -> Id		(6)
		"""
		ret = []
		
		attribs = CFA.attribs + [CFA.AAAFID]
		data = self.eva.getData(CFE.get_Id_params(edId, attribs))
		ed_entList = json.loads(data)["entities"]
		
		print "ed_entList =", ed_entList
		
		ed_FId_Set = set(CFA.get_FId(ed_entList))
		ed_CId_Set = set(CFA.get_CId(ed_entList))
		ed_JId_Set = set(CFA.get_JId(ed_entList))
		ed_AuId_Set = set(CFA.get_AuId(ed_entList))
		print "ed_FId_Set =", ed_FId_Set
		print "ed_CId_Set =", ed_CId_Set
		print "ed_JId_Set =", ed_JId_Set
		print "ed_AuId_Set =", ed_AuId_Set
		attribs = [CFA.ID, CFA.RID, 'Y']
		if ed_FId_Set:
			attribs.append(CFA.FFID)
		if ed_CId_Set:
			attribs.append(CFA.CCID)
		if ed_JId_Set:
			attribs.append(CFA.JJID)
		if ed_AuId_Set:
			attribs += [CFA.AAAUID, CFA.AAAFID]
		expr = Util.expr_AuId(stId)
		count = CFA.COUNT
		print "expr =", expr
		print "attribs =", attribs
		data = self.eva.getData(CFE.get_params(expr, attribs, count))
		st_entList = json.loads(data)["entities"]
		
		print "st_entList =", st_entList
		
		# step1: handle 2-5
		allSet = ed_FId_Set | ed_CId_Set | ed_JId_Set | ed_AuId_Set
		print "allSet =", allSet
		tmpList = []
		for attrDict in st_entList:
			id = attrDict.get("Id")
			if not id:
				continue
			tmpSet = CFA.get_mainId_Set(attrDict)
			tmpSet &= allSet
			tmpList += map(lambda x:[id, x], tmpSet)
		ret += tmpList
		
		# step2: handle 6
		st_AfId_Set = set(CFA.get_AfId(st_entList, stId))
		ed_AfId_Dict = CFA.get_AfId_Dict(ed_entList)
		print "st_AfId_Set =", st_AfId_Set
		print "ed_AfId_Dict =", ed_AfId_Dict
		tmpList = []
		for st_AfId in st_AfId_Set:
			ed_AuId_Set = ed_AfId_Dict[st_AfId]
			tmpList += map(lambda x:[st_AfId, x], ed_AuId_Set)
		ret += tmpList
		
		# step3: handle 1
		tmpList = []
		Id2_rDict = CFA.get_RId_rDict(st_entList)
		Id2_List = Id2_rDict.keys()
		Id2_length = len(Id2_List)
		attribs = [CFA.ID]
		for i in xrange(0, Id2_length, CFA.PACKET):
			id2s = Id2_List[i:i+CFA.PACKET]
			count = len(id2s)
			expr = Util.expr_ids_and_rid(id2s, edId)
			print "expr =", expr
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			entList = json.loads(data)["entities"]
			print "entList =", entList
			id2s_ = CFA.get_Id(entList)
			for id2 in id2s_:
				tmpList += map(lambda x:[x, id2], Id2_rDict[id2])
		ret += tmpList
		
		return Util.to_hop3(ret, stId, edId)
		
		
	def get_hop(self, stId, edId):
		print "From AuId to Id"
		return self.get_1hop(stId, edId) + self.get_2hop(stId, edId) + self.get_3hop(stId, edId)	
		
	
class solution_AuId_AuId:

	def __init__(self):
		self.eva = Evaluation()


	def get_1hop(self, stId, edId):
		return []
		
		
	def get_2hop(self, stId, edId):
		"""
			AA.AuId -> AA.AfId -> AA.AuId		(1)
			AA.AuId -> Id -> AA.AuId			(2)
		"""
		ret = []
		
		expr = Util.expr_AuId(stId)
		attrib = [CFA.ID, CFA.AAAUID, CFA.AAAFID]
		count = CFA.COUNT
		order = CFE.order_ID
		print "expr =", expr
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attrib, count))
		st_entList = json.loads(data)["entities"]
		print "st_entList =", st_entList
		
		expr = Util.expr_AuId(edId)
		attrib = [CFA.ID, CFA.AAAUID, CFA.AAAFID]
		count = CFA.COUNT
		order = CFE.order_ID
		print "expr =", expr
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attrib, count))
		ed_entList = json.loads(data)["entities"]
		print "ed_entList =", ed_entList
		
		# step1: handle 1
		st_AfId_Set = set(CFA.get_AfId(st_entList, stId))
		ed_AfId_Set = set(CFA.get_AfId(ed_entList, edId))
		print "st_AfId_Set =", st_AfId_Set
		print "ed_AfId_Set =", ed_AfId_Set
		tmpSet = st_AfId_Set & ed_AfId_Set
		ret += list(tmpSet)
		
		# step2: handle 2
		st_Id_List = CFA.get_Id(st_entList)
		ed_Id_List = CFA.get_Id(ed_entList)
		print "st_Id_List =", st_Id_List
		print "ed_Id_List =", ed_Id_List
		ret += Util.find_common(st_Id_List, ed_Id_List)
		
		return Util.to_hop2(ret, stId, edId)
	
	
	def get_3hop(self, stId, edId):
		"""
			AA.AuId -> Id -> Id -> AA.AuId		(1)
		"""
		ret = []
		
		attribs = [CFA.ID, CFA.RID]
		count = CFA.COUNT
		expr = Util.expr_AuId(stId)
		print "expr =", expr
		data = self.eva.getData(CFE.get_params(expr, attribs, count))
		st_entList = json.loads(data)["entities"]
		print "st_entList =", st_entList
		
		attribs = [CFA.ID]
		expr = Util.expr_AuId(edId)
		print "expr =", expr
		order = CFE.order_ID
		data = self.eva.getData(CFE.get_params_with_order(expr, order, attribs, count))
		ed_entList = json.loads(data)["entities"]
		print "ed_entList =", ed_entList
		
		# handle 1
		ed_Id_Set = set(CFA.get_Id(ed_entList))
		print "ed_Id_Set =", ed_Id_Set
		tmpList = []
		for attrDict in st_entList:
			st_Id = attrDict.get("Id")
			if not st_Id:
				continue
			st_RId_Set = set(CFA.get_RId(attrDict))
			print "st_Id = %s, st_RId_Set = %s" % (st_Id, st_RId_Set)
			tmpSet = st_RId_Set & ed_Id_Set
			tmpList += map(lambda x:[st_Id, x], tmpSet)
			
		ret += tmpList
		
		return Util.to_hop3(ret, stId, edId)
	
	
	def get_hop(self, stId, edId):
		print "From AuId to AuId"
		return self.get_1hop(stId, edId) + self.get_2hop(stId, edId) + self.get_3hop(stId, edId)
	
	
class solution:

	def __init__(self):
		self.eval = Evaluation()
		self.id2id = solution_Id_Id()
		self.id2auid = solution_Id_AuId()
		self.auid2id = solution_AuId_Id()
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
		if st_isId:
			if ed_isId:
				ret = self.id2id.get_hop(stId, edId)
			else:
				ret = self.id2auid.get_hop(stId, edId)
		else:
			if ed_isId:
				ret = self.auid2id.get_hop(stId, edId)
			else:
				ret = self.auid2auid.get_hop(stId, edId)
		return ret

		
	def solve(self, stId, edId):
		ret = self.get_hop(stId, edId)
		return json.dumps(ret)

global solver
solver = solution()

class hop:
	def GET(self, query):
		d = web.input()
		stId = long(d.id1)
		edId = long(d.id2)
		return solver.solve(stId, edId)
		

def localtest():
	urls = [
		# "http://localhost/?id2=2310280492&id1=2332023333",
		# "http://localhost/?id2=2180737804&id1=2251253715",
		"http://localhost/?id2=189831743&id1=2147152072",
		# "http://localhost/?id2=57898110&id1=2332023333",
		# "http://localhost/?id2=2014261844&id1=57898110",
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
		ans = solution().solve(stId, edId)
		print "ans =", ans
		

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
				stId = long(L[0].split('=')[-1])
				edId = long(L[1].split('=')[-1])
			else:
				edId = long(L[0].split('=')[-1])
				stId = long(L[1].split('=')[-1])
			
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
