import math

class constForGenRoadNetwork():
	EARTH_RADIUS = 6378137
	
class CFGR(constForGenRoadNetwork):
	pass

def calcRad(d):
	return d * math.pi / 180.0

def calcEarthDist(lat1, lon1, lat2, lon2):
	radLat1 = calcRad(lat1)
	radLat2 = calcRad(lat2)
	radLon1 = calcRad(lon1)
	radLon2 = calcRad(lon2)
	if radLat1 < 0:	 
		radLat1 = math.pi / 2.0 + math.fabs(radLat1)
	if radLat1 > 0:	 
		radLat1 = math.pi / 2.0 - math.fabs(radLat1)
	if radLon1 < 0:	 
		radLon1 = math.pi * 2.0 - math.fabs(radLon1)
	if radLat2 < 0:	 
		radLat2 = math.pi / 2.0 + math.fabs(radLat2)
	if radLat2 > 0:	 
		radLat2 = math.pi / 2.0 - math.fabs(radLat2)
	if radLon2 < 0:	 
		radLon2 = math.pi * 2.0 - math.fabs(radLon2)
		
	x1 = CFGR.EARTH_RADIUS * math.cos(radLon1) * math.sin(radLat1)	
	y1 = CFGR.EARTH_RADIUS * math.sin(radLon1) * math.sin(radLat1)	
	z1 = CFGR.EARTH_RADIUS * math.cos(radLat1)	
	x2 = CFGR.EARTH_RADIUS * math.cos(radLon2) * math.sin(radLat2)	
	y2 = CFGR.EARTH_RADIUS * math.sin(radLon2) * math.sin(radLat2)	
	z2 = CFGR.EARTH_RADIUS * math.cos(radLat2)	
	d = ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)+ (z1 - z2) * (z1 - z2)) ** 0.5 
	theta = math.acos((CFGR.EARTH_RADIUS * CFGR.EARTH_RADIUS + CFGR.EARTH_RADIUS * CFGR.EARTH_RADIUS - d * d) / (2 * CFGR.EARTH_RADIUS * CFGR.EARTH_RADIUS))  
	dist = theta * CFGR.EARTH_RADIUS  
	return dist
	
if __name__ == "__main__":
	x1, y1 = 31.272052,121.621784
	x2, y2 = 31.269926,121.625961
	print calcEarthDist(x1, y1, x2, y2)
	