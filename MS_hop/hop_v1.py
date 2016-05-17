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
		ed_entList = json.loads(data)["entities"]
		
		attrib += [CFA.RID]
		data = self.eva.getData(CFE.get_Id_params(stId, attrib))
		st_entList = json.loads(data)["entities"]
		
		print "ed =", ed_entList
		print "st =", st_entList
		
		# step1: check F.FId
		stIds = CFA.get_FId(st_entList)
		edIds = CFA.get_FId(ed_entList)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step2: check J.JId
		stIds = CFA.get_JId(st_entList)
		edIds = CFA.get_JId(ed_entList)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step3: check C.CId
		stIds = CFA.get_CId(st_entList)
		edIds = CFA.get_CId(ed_entList)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step4: check AA.AuId
		stIds = CFA.get_AuId(st_entList)
		edIds = CFA.get_AuId(ed_entList)
		stIds.sort()
		edIds.sort()
		medium = Util.find_common(stIds, edIds)
		ret += medium
		
		# step0: check Id's Rid's Rid
		RIds = CFA.get_RId(st_entList)
		# print RIds
		medium = []
		RIds_length = len(RIds)
		for i in xrange(0, RIds_length, CFA.PACKET):
			ids = RIds[i:i+CFA.PACKET]
			expr = Util.expr_ids_and_rid(ids, edId)
			# print expr
			count = len(ids)
			data = self.eva.getData(CFE.get_params(expr, attrib, count))
			# print data
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
		ed_entList = json.loads(data)["entities"]
		
		attrib += [CFA.RID]
		data = self.eva.getData(CFE.get_Id_params(stId, attrib))
		st_entList = json.loads(data)["entities"]
		
		print "ed =", ed_entList
		print "st =", st_entList
		
		# step1: handle 2-5
		FIds = CFA.get_FId(st_entList)
		CIds = CFA.get_CId(st_entList)
		JIds = CFA.get_JId(st_entList)
		AuIds = CFA.get_AuId(st_entList)
		print "FIds =", FIds
		print "CIds =", CIds
		print "JIds =", JIds
		print "AuIds =", AuIds
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
			print "%d: expr = %s" % (i+1, expr)
			count = CFA.COUNT
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			resList = json.loads(data)["entities"]
			print "resList = ", resList
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
		RIds = CFA.get_RId(st_entList)
		FIds = CFA.get_FId(ed_entList)
		CIds = CFA.get_CId(ed_entList)
		JIds = CFA.get_JId(ed_entList)
		AuIds = CFA.get_AuId(ed_entList)
		attribs = [CFA.ID, 'Y'] + CFA.attribs
		Id2Id_List = []
		RIds_length = len(RIds)
		for j in xrange(0, RIds_length, CFA.PACKET):
			ids = RIds[j:j+CFA.PACKET]
			expr = Util.expr_ids(ids)
			print "%d: expr = %s" % (j, expr)
			count = len(ids)
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			print "data =", data
			entList = json.loads(data)["entities"]
			print "entList = ", entList
			tmpList = []
			for attrDict in entList:
				id = attrDict.get("Id")
				if not id:
					continue
					
				for fid in FIds:
					if CFA.has_FId(attrDict, fid):
						tmpList.append([id, fid])
				for cid in CIds:
					if CFA.has_CId(attrDict, cid):
						tmpList.append([id, cid])
				for jid in JIds:
					if CFA.has_JId(attrDict, jid):
						tmpList.append([id, jid])
				for auid in AuIds:
					if CFA.has_AuId(attrDict, auid):
						tmpList.append([id, auid])
				ret += tmpList
				
				# check currenct rid's year for next `Id->Id`
				year = attrDict.get('Y')
				if year and year>=ed_year+2:
					Id2Id_List.append(id)
					
		# rrid_Set is two layer's reference			
		rref_Dict = defaultdict(list)
		rrid_Set = set()		
		Id2Id_length = len(Id2Id_List)
		for j in xrange(0, Id2Id_length, CFA.PACKET):
			ids = Id2Id_List[j:j+CFA.PACKET]
			expr = Util.expr_ids(ids)
			print "%d: expr = %s" % (j, expr)
			count = len(ids)
			attribs = [CFA.ID, CFA.RID, 'Y']
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			entList = json.loads(data)["entities"]
			print "entList =", entList
			tmpList = []
			for attrDict in entList:
				id = attrDict.get("Id")
				ridList = attrDict.get("RId")
				if not ridList or not id:
					continue
				year = attrDict.get('Y')
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
			print "%d: expr = %s" % (j, expr)
			count = len(ids)
			attribs = [CFA.ID]
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			entList = json.loads(data)["entities"]
			print "entList =", entList
			tmpList = []
			for attrDict in entList:
				id = attrDict.get("Id")
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
		attrib = [CFA.RID]
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params(expr, attrib, count))
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
		medium = Util.find_common(stRIds, edIds)
		
		
		return Util.to_hop2(medium, stId, edId)
		
		
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
		
		# step1 handle 2-5
		attribs = CFA.attribs + [CFA.RID, CFA.AAAFID]
		data = self.eva.getData(CFE.get_Id_params(stId, attribs))
		st_entList = json.loads(data).get("entities")
		
		# this could be error just because entry may fit the expression but query-data may not
		attribs = [CFA.ID, CFA.AAAFID, CFA.AAAUID]
		expr = Util.expr_AuId(edId)
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params(expr, attribs, count))
		ed_entList = json.loads(data).get("entities")
		
		print "st_entList =", st_entList
		print "ed_entList =", ed_entList
		
		ids = CFA.get_Id(ed_entList)
		ids_length = len(ids)
		attribs = CFA.attribs + [CFA.ID]
		attrIds_Set = CFA.get_mainId_Set(st_entList)
		print "ed_ids =", ids
		print "st_attrIds =", attrIds_Set
		for i in xrange(0, ids_length, CFA.PACKET):
			ids_ = ids[i:i+CFA.PACKET]
			count = len(ids_)
			expr = Util.expr_ids(ids_)
			print "%d: %s" % (i, expr)
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			entList = json.loads(data).get("entities")
			print "entList = ", entList
			tmpList = []
			for attrDict in entList:
				id = attrDict.get("Id")
				if not id:
					continue
				idSet = CFA.get_mainId_Set(attrDict)
				print "id = %s, idSet = %s" % (id, idSet)
				tmpSet = attrIds_Set & idSet
				tmpList += map(lambda x:[id, x], tmpSet)
			ret += tmpList	
		
		# step2: handle 6
		ed_afId_Set = set(CFA.get_AfId(ed_entList, edId))
		st_auId_Dict = CFA.get_AuId_Dict(st_entList)
		print "ed_afId_Set =", ed_afId_Set
		print "st_auId_Dict =", st_auId_Dict
		if ed_afId_Set and st_auId_Dict:
			tmpList = []
			for st_auId, st_afId_Set in st_auId_Dict.iteritems():
				print st_auId, st_afId_Set
				tmpSet = st_afId_Set & ed_afId_Set
				tmpList += map(lambda x:[st_auId, x], tmpSet)
			ret += tmpList
			
		# step3: handle 1
		rid_Set = set(CFA.get_Id(ed_entList))
		rid_List = list(rid_Set)
		id_List = CFA.get_RId(st_entList)
		id_length = len(id_List)
		if rid_List:
			for i in xrange(0, id_length, CFA.PACKET):
				ids = id_List[i:i+CFA.PACKET]
				count = len(ids)
				expr = Util.expr_ids_with_rids(ids, rid_List)
				print "expr =", expr
				attribs = [CFA.ID, CFA.RID]
				data = self.eva.getData(CFE.get_params(expr, attribs, count))
				print "entData =", data
				entList = json.loads(data).get("entities")
				print "entList =", entList
				tmpList = Util.find_rid_match_rid(entList, rid_Set)
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
		
		
	def get_2hop(self, stId, edId, rev=False):
		"""
			AA.AuId -> Id -> Id
		"""
		expr = Util.expr_auid_and_rid(stId, edId)
		print "expr =", expr
		attrib = [CFA.ID]
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params(expr, attrib, count))
		entList = json.loads(data)["entities"]
		ids = CFA.get_Id(entList)
		
		print "entList =", entList
		print "ids =", ids
		
		return Util.to_hop2(ids, stId, edId)
		
		
	def get_3hop(self, stId, edId):
		"""
			AA.AuId -> AA.AfId -> AA.AuId -> Id		(1)
			AA.AuId -> Id -> Id -> Id				(2)
			AA.AuId -> Id -> F.FId -> Id			(3)
			AA.AuId -> Id -> C.CId -> Id			(4)
			AA.AuId -> Id -> J.JId -> Id			(5)
			AA.AuId -> Id -> AA.AuId -> Id			(6)
		"""
		ret = []
		
		# step1: handle (3)-(6)
		attribs = CFA.attribs + ['Y']
		data = self.eva.getData(CFE.get_Id_params(edId, attribs))
		ed_entList = json.loads(data)["entities"]
		
		print "ed_entList =", ed_entList
		
		FIds = CFA.get_FId(ed_entList)
		CIds = CFA.get_CId(ed_entList)
		JIds = CFA.get_JId(ed_entList)
		AuIds = CFA.get_AuId(ed_entList)
		LL = map(lambda x:["AA.AuId", x], AuIds)
		L = map(lambda x:["F.FId", x], FIds)+\
			map(lambda x:["C.CId", x], CIds)+\
			map(lambda x:["J.JId", x], JIds)+\
			LL
		count = CFA.COUNT
		expr = Util.expr_all_and_auid(L, stId)
		print "expr =", expr
		attribs = CFA.attribs + [CFA.ID]
		data = self.eva.getData(CFE.get_params(expr, attribs, count))
		entList = json.loads(data)["entities"]
		
		print "entList =", entList
		id_Set = set(FIds + CIds + JIds + AuIds)
		for attrDict in entList:
			id = attrDict.get("Id")
			if not id:
				continue
			ids_List = CFA.get_mainId_List(attrDict)
			ids_List = filter(lambda id:id in id_Set, ids_List)
			tmpList = map(lambda x:[id, x], ids_List)
			ret += tmpList
		
		# step2: handle 1
		count = CFA.COUNT
		expr = Util.expr_all_and_auid(LL, stId)
		print "expr =", expr
		attribs = [CFA.AAAFID, CFA.AAAUID]
		data = self.eva.getData(CFE.get_params(expr, attribs, count))
		entList = json.loads(data)["entities"]
		print "entList =", entList
		afId_Dict = CFA.get_AfId_Dict(entList)
		for afId, auIds in afId_Dict.iteritems():
			try:
				auIds.remove(stId)
			except:
				print "may invalid in AuId to Id 3-hop (1)"
			tmpList = map(lambda x:[afId, x], auIds)
			ret += tmpList
			
		# step3: handle 2
		if ed_entList:
			ed_attrDict = ed_entList[0]
			year = ed_attrDict.get('Y')
			if not year:
				year = 2014
			attribs = [CFA.ID, CFA.RID]
			count = CFA.COUNT
			expr = Util.expr_auid_and_year(stId, year+2)
			print "expr =", expr
			data = self.eva.getData(CFE.get_params(expr, attribs, count))
			entList = json.loads(data)["entities"]
			print "entList =", entList
			
			ids = CFA.get_RId(entList)
			ids_length = len(ids)
			attribs = [CFA.ID, CFA.RID]
			for i in xrange(0, ids_length, CFA.PACKET):
				ids_ = ids[i:i+CFA.PACKET]
				count = len(ids_)
				expr = Util.expr_ids_and_rid(ids_, edId)
				print "expr =", expr
				data = self.eva.getData(CFE.get_params(expr, attribs, count))
				entList = json.loads(data)["entities"]
				print "entList =", entList
				tmpList = []
				for attrDict in entList:
					id = attrDict.get("Id")
					if not id:
						continue
					rids = CFA.get_RId(attrDict)
					tmpList += map(lambda x:[id, x], rids)
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
		
		# step1: handle 1
		expr = Util.expr_comp_AuId(stId, edId)
		attrib = [CFA.AAAFID, CFA.AAAUID]
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params(expr, attrib, count))
		entList = json.loads(data)["entities"]
		print "expr =", expr
		print "entList =", entList
		ret += 	CFA.get_AfId(entList, edId)
		
		# step2: handle 2
		attrib = [CFA.ID]
		count = CFA.COUNT
		data = self.eva.getData(CFE.get_params(expr, attrib, count))
		entList = json.loads(data)["entities"]
		print "expr =", expr
		print "entList =", entList
		ret += 	CFA.get_Id(entList)
		
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
		ed_idsList = CFA.get_Id(ed_entList)
		print "ed_idsList =", ed_idsList
		
		for attrDict in st_entList:
			id = attrDict.get("Id")
			if not id:
				continue
			rids = CFA.get_RId(attrDict)
			print "rids =", rids
			rids.sort()
			medium = Util.find_common(rids, ed_idsList)
			tmpList = map(lambda x:[id, x], medium)
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
		"http://localhost/?id2=2310280492&id1=2332023333",
		# "http://localhost/?id2=2180737804&id1=2251253715",
		# "http://localhost/?id2=189831743&id1=2147152072",
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
