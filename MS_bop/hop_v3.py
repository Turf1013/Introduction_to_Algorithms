#!/usr/bin/python
import BaseHTTPServer
import httplib, urllib, json
import urlparse
from collections import defaultdict
from time import clock

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
	vId_attribs = [
		RID,
		FFID,
		CCID,
		JJID,
		AAAUID,
	]
	vAuId_attribs = [
		ID,
		RID,
		FFID,
		CCID,
		JJID,
		AAAUID,
		AAAFID,
	]
	COUNT = 3000
	PACKET = 30

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
						ret[afid].add(auid)
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
	def expr_ids_and_rids(ids, rids):
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
	def expr_auids(auids):
		if not auids:
			raise ValueError, "[expr_auids] auids must not null"
		return Util.expr_multi_or(auids, Util.expr_AuId)
	
	
	@staticmethod
	def	expr_auids_and_afids(auids, afids):
		auids_exp = Util.expr_multi_or(auids, Util.expr_AuId)
		afids_exp = Util.expr_multi_or(afids, Util.expr_AfId)
		return "And(%s,%s)" % (auids_exp, afids_exp)
		
		
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
			st = d.get(afid)
			ret += map(lambda x:[x,afid], st)
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
		self.max_times = 10
		
		
	def getData(self, expr):
		for i in xrange(self.max_times):
			self.conn.request("GET", CFA.url+"evaluate?%s" % (expr))
			data = self.conn.getresponse().read()
			if data:
				return data
		return self.null_data
		
		
	def getEnt(self, expr):
		ret = []
		for i in xrange(self.max_times):
			self.conn.request("GET", CFA.url+"evaluate?%s" % (expr))
			data = self.conn.getresponse().read()
			#print "data =", data
			try:
				d = json.loads(data)
				ret = d.get("entities")
				if ret is not None:
					break
			except :
				pass
		return ret
		
		
class vId:

	def __init__(self, id, entList):
		self.Id = id
		self.mainSet = set()
		self.mainAttribs = []
		
		self.FIdSet = set(CFA.get_FId(entList))
		if self.FIdSet:
			self.mainSet |= self.FIdSet
			self.mainAttribs.append( CFA.FFID )
			
		self.CIdSet = set(CFA.get_CId(entList))
		if self.CIdSet:
			self.mainSet |= self.CIdSet
			self.mainAttribs.append( CFA.CCID )
			
		self.JIdSet = set(CFA.get_JId(entList))
		if self.JIdSet:
			self.mainSet |= self.JIdSet
			self.mainAttribs.append( CFA.JJID )
			
		self.AuIdSet = set(CFA.get_AuId(entList))
		if self.AuIdSet:
			self.mainSet |= self.AuIdSet
			self.mainAttribs.append( CFA.AAAUID )
			
		self.RIdSet = set(CFA.get_RId(entList))	
		
		
	def get_mainItems(self):
		ret = []
		ret += map(lambda val:[CFA.FFID, val], self.FIdSet)
		ret += map(lambda val:[CFA.CCID, val], self.CIdSet)
		ret += map(lambda val:[CFA.JJID, val], self.JIdSet)
		ret += map(lambda val:[CFA.AAAUID, val], self.AuIdSet)
		return ret
		
		
	def __str__(self):
		print "Id =", self.Id
		print "FIdSet =", self.FIdSet
		print "CIdSet =", self.CIdSet
		print "JIdSet =", self.JIdSet
		print "AuIdSet =", self.AuIdSet
		print "mainSet =", self.mainSet
		
		
	def __hash__(self):
		return hash(self.Id)
	
	
class vAuId:

	def __init__(self, auid, entList):
		self.AuId = auid
		self.mainSet = set()
		self.vId_Dict = dict()
		for attrDict in entList:
			id = attrDict.get("Id")
			if not id:
				continue
			self.vId_Dict[id] = vId(id, attrDict)
		self.IdSet = set(self.vId_Dict.keys())
		self.AfIdSet = set(CFA.get_AfId(entList, auid))
		
		
	def	get_RId_rDict(self):
		ret = defaultdict(set)
		for id,vnode in self.vId_Dict.iteritems():
			for rid in vnode.RIdSet:
				ret[rid].add(id)
		return ret
		
		
	def __str__(self):
		print "AuId =", self.AuId
		for id in self.vId_Dict:
			print self.vId_Dict[id]
			
		
	def __hash__(self):
		return hash(self.AuId)
		
		
		
global eva
eva = Evaluation()

global vId_Dict
vId_Dict = dict()
		
def get_vId(id):
	ret = vId_Dict.get(id)
	if not ret:
		expr = Util.expr_Id(id)
		#print "expr =", expr
		entList = eva.getEnt(CFE.get_params(expr, CFA.vId_attribs, count=1))
		ret = vId(id, entList)
		vId_Dict[id] =  ret
	return ret

	
	
global vAuId_Dict
vAuId_Dict = dict()	

def get_vAuId(id):
	ret = vAuId_Dict.get(id)
	if not ret:
		expr = Util.expr_AuId(id)
		count = CFA.COUNT * 3
		#print "expr =", expr
		entList = eva.getEnt(CFE.get_params(expr, CFA.vAuId_attribs, count))
		ret = vAuId(id, entList)
		vAuId_Dict[id] = ret
	return ret
	
		
class solution_Id_Id:
	
	def __init__(self):
		self.eva = Evaluation()
		
		
	def get_hop(self, stId, edId):
		print "From Id to Id"
		ret1, ret2, ret3 = [],[],[]
		
		# step1
		st_vId = get_vId(stId)
		ed_vId = get_vId(edId)
		
		if edId in st_vId.RIdSet:
			ret1 = [[stId, edId]]
			
		tmpSet = st_vId.mainSet & ed_vId.mainSet
		ret2 += list(tmpSet)
		
		if st_vId.mainSet:
			mainItems = st_vId.get_mainItems()
			expr = Util.expr_all_and_rid(mainItems, edId)
			#print "expr =", expr
			attribs = st_vId.mainAttribs + [CFA.ID]
			count = CFA.COUNT * 5
			entList = self.eva.getEnt(CFE.get_params(expr, attribs, count))
			for attrDict in entList:
				id = attrDict.get("Id")
				if not id:
					continue
				tmpSet = CFA.get_mainId_Set(attrDict)	
				tmpSet &= st_vId.mainSet
				ret3 += map(lambda x:[x, id], tmpSet)
				
		if st_vId.RIdSet:
			RRId_rDict = defaultdict(set)
			expr = Util.expr_ids(list(st_vId.RIdSet))
			#print "expr =", expr
			attribs = ed_vId.mainAttribs + [CFA.ID, CFA.RID]
			count = len(st_vId.RIdSet)
			entList = self.eva.getEnt(CFE.get_params(expr, attribs, count))
			for attrDict in entList:
				id = attrDict.get("Id")
				if not id:
					continue
				tmpSet = CFA.get_mainId_Set(attrDict)
				tmpSet &= ed_vId.mainSet
				ret3 += map(lambda x:[id, x], tmpSet)
				rids = CFA.get_RId(attrDict)
				for rid in rids:
					RRId_rDict[rid].add(id)
					
			ret2 += list(RRId_rDict[edId])
			
			RRId_List = RRId_rDict.keys()
			RRId_length = len(RRId_List)
			for i in xrange(0, RRId_length, CFA.PACKET):
				expr = Util.expr_ids_and_rid(RRId_List[i:i+CFA.PACKET], edId)
				#print "expr =", expr
				attribs = [CFA.ID]
				count = CFA.PACKET
				entList = self.eva.getEnt(CFE.get_params(expr, attribs, count))
				for attrDict in entList:
					id = attrDict.get("Id")
					if not id:
						continue
					ret3 += map(lambda x:[x, id], RRId_rDict[id])
					
				
		return ret1 + Util.to_hop2(ret2, stId, edId) + Util.to_hop3(ret3, stId, edId)

		
class solution_Id_AuId:

	def __init__(self):
		self.eva = Evaluation()
	
	
	def get_hop(self, stId, edId):
		print "From Id to AuId"
		ret1, ret2, ret3 = [],[],[]
		
		st_vId = get_vId(stId)
		ed_vAuId = get_vAuId(edId)
		
		if edId in st_vId.AuIdSet:
			ret1 = [[stId, edId]]
			
		tmpSet = st_vId.RIdSet & ed_vAuId.IdSet
		ret2 += list(tmpSet)
		
		
		for id, ed_vId in ed_vAuId.vId_Dict.iteritems():
			tmpSet = st_vId.mainSet & ed_vId.mainSet
			ret3 += map(lambda x:[x, id], tmpSet)
			
		if st_vId.AuIdSet and ed_vAuId.AfIdSet:
			'!!!!!! here may be wrong.'
			expr = Util.expr_auids_and_afids(list(st_vId.AuIdSet), list(ed_vAuId.AfIdSet))
			#print "expr =", expr
			count = CFA.COUNT * 6
			attribs = [CFA.AAAUID, CFA.AAAFID]
			entList = self.eva.getEnt(CFE.get_params(expr, attribs, count))
			AuId_Dict = CFA.get_AuId_Dict(entList)
			for auid in st_vId.AuIdSet:
				tmpSet = AuId_Dict[auid]
				tmpSet &= ed_vAuId.AfIdSet
				ret3 += map(lambda x:[auid, x], tmpSet)
			
		if st_vId.RIdSet and ed_vAuId.IdSet:
			st_RId_List = list(st_vId.RIdSet)
			ed_Id_List = list(ed_vAuId.IdSet)
			ed_Id_length = len(ed_Id_List)
			for i in xrange(0, ed_Id_length, CFA.PACKET):
				rids = ed_Id_List[i:i+CFA.PACKET]
				expr = Util.expr_ids_and_rids(st_RId_List, rids)
				#print "expr =", expr
				attribs = [CFA.ID, CFA.RID]
				count = CFA.COUNT * 5
				entList = self.eva.getEnt(CFE.get_params(expr, attribs, count))
				rids_Set = set(rids)
				for attrDict in entList:
					id = attrDict.get("Id")
					if not id:
						continue
					tmpSet = set(CFA.get_RId(attrDict))
					tmpSet &= rids_Set
					ret3 += map(lambda x:[id, x], tmpSet)
				
			
		return ret1 + Util.to_hop2(ret2, stId, edId) + Util.to_hop3(ret3, stId, edId)
	
	
class solution_AuId_Id:

	def __init__(self):
		self.eva = Evaluation()

	def get_hop(self, stId, edId):
		print "From AuId to Id"
		ret1, ret2, ret3 = [],[],[]
		
		st_vAuId = get_vAuId(stId)
		ed_vId = get_vId(edId)
		
		if edId in st_vAuId.IdSet:
			ret1 = [[stId, edId]]
			
		for st_id, st_vId in st_vAuId.vId_Dict.iteritems():
			if edId in st_vId.RIdSet:
				ret2.append(st_id)
				
			tmpSet = st_vId.mainSet & ed_vId.mainSet
			ret3 += map(lambda x:[st_id, x], tmpSet)
			
		if st_vAuId.AfIdSet and ed_vId.AuIdSet:
			'!!!!!! here may be wrong.'
			expr = Util.expr_auids_and_afids(list(ed_vId.AuIdSet), list(st_vAuId.AfIdSet))	
			#print "expr =", expr
			count = CFA.COUNT * 6
			attribs = [CFA.AAAUID, CFA.AAAFID]
			entList = self.eva.getEnt(CFE.get_params(expr, attribs, count))
			AuId_Dict = CFA.get_AuId_Dict(entList)
			for auid in ed_vId.AuIdSet:
				tmpSet = AuId_Dict[auid]
				tmpSet &= st_vAuId.AfIdSet
				ret3 += map(lambda x:[x, auid], tmpSet)
				
		st_RId_rDict = st_vAuId.get_RId_rDict()
		if st_RId_rDict:
			st_RId_List = st_RId_rDict.keys()
			st_RId_length = len(st_RId_List)
			for i in xrange(0, st_RId_length, CFA.PACKET):
				rids = st_RId_List[i:i+CFA.PACKET]
				expr = Util.expr_ids_and_rid(rids, edId)
				#print "expr =", expr
				count = CFA.COUNT * 6
				attribs = [CFA.ID]
				entList = self.eva.getEnt(CFE.get_params(expr, attribs, count))
				for attrDict in entList:
					id = attrDict.get("Id")
					if not id:
						continue
					ret3 += map(lambda x:[x, id], st_RId_rDict[id])
					
		
		return ret1 + Util.to_hop2(ret2, stId, edId) + Util.to_hop3(ret3, stId, edId)
		
	
class solution_AuId_AuId:

	def __init__(self):
		self.eva = Evaluation()

		
	def get_hop(self, stId, edId):
		print "From AuId to AuId"
		ret1, ret2, ret3 = [],[],[]
		
		st_vAuId = get_vAuId(stId)
		ed_vAuId = get_vAuId(edId)
		
		tmpSet = st_vAuId.AfIdSet & ed_vAuId.AfIdSet
		ret2 += list(tmpSet)
		
		tmpSet = st_vAuId.IdSet & ed_vAuId.IdSet
		ret2 += list(tmpSet)
		
		for st_id, st_vId in st_vAuId.vId_Dict.iteritems():
			tmpSet = st_vId.RIdSet & ed_vAuId.IdSet
			ret3 += map(lambda x:[st_id, x], tmpSet)
		
		return ret1 + Util.to_hop2(ret2, stId, edId) + Util.to_hop3(ret3, stId, edId)
	
	
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
		print "stId =", stId
		print "edId =", edId
		ret = self.get_hop(stId, edId)
		return json.dumps(ret)

		
global solver
solver = solution()
		

def localtest():
	urls = [
		# "http://localhost/?id2=2310280492&id1=2332023333",
		# "http://localhost/?id2=2180737804&id1=2251253715",
		# "http://localhost/?id2=189831743&id1=2147152072",
		# "http://localhost/?id2=57898110&id1=2332023333",
		# "http://localhost/?id2=2014261844&id1=57898110",
		
		# From Id to Id
		"http://localhost/?id1=2169574628&id2=2104095591",
		"http://localhost/?id1=2129963373&id2=2104095591",
		"http://localhost/?id1=1935460876&id2=2104095591",
		"http://localhost/?id1=2090373321&id2=2169551590",

		# From Id to AuId
		"http://localhost/?id1=2169574628&id2=2047672443",
		"http://localhost/?id1=2169574628&id2=1985324749",
		"http://localhost/?id1=2169574628&id2=2096139825",
		"http://localhost/?id1=2083117615&id2=2147380636",
		"http://localhost/?id1=2070068582&id2=2147380636",

		# From AuId to Id
		"http://localhost/?id1=2095616704&id2=2104095591",
		"http://localhost/?id1=2095616704&id2=2101309634",
		"http://localhost/?id1=2095616704&id2=2104095591",
		"http://localhost/?id1=2241113319&id2=2294662270",
		"http://localhost/?id2=2083117615&id1=2147380636",
		"http://localhost/?id2=2070068582&id1=2147380636",

		# From AuId to AuId
		"http://localhost/?id1=2095616704&id2=1985324749",
		"http://localhost/?id1=2145586907&id2=2141729011",
		"http://localhost/?id1=2145586907&id2=2141729011",
		"http://localhost/?id1=2103501775&id2=2121612746",
		"http://localhost/?id1=2096377446&id2=1804221844",
		"http://localhost/?id1=2103501775&id2=1804221844",
	]
	clock()
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
		print 
	print "time usage: %s" % (clock())


class RequestHandler(BaseHTTPServer.BaseHTTPRequestHandler):

	def do_GET(self):
		d = urlparse.urlparse(self.path)
		query = d.query
		try:
			L = query.split('&')
			if L[1].startswith('id2'):
				stId = long(L[0].split('=')[-1])
				edId = long(L[1].split('=')[-1])
			else:
				edId = long(L[0].split('=')[-1])
				stId = long(L[1].split('=')[-1])
				
			ans = solver.solve(stId, edId)
			self.send_response(200, 'OK')
			self.end_headers()
			self.wfile.write(ans)
			self.wfile.flush()
			
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
